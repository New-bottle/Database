delimiter //
CREATE TRIGGER check_stock BEFORE INSERT
	ON mydb.order FOR EACH ROW 
    BEGIN
		declare num int;
		set num = (SELECT stock_quantity FROM mydb.product WHERE name=new.product_name);
        IF num < new.amount THEN
			SIGNAL SQLSTATE 'HY000' SET mysql_errno=22, MESSAGE_TEXT = 'stock is not enough!'; 
		END IF;
    END
//

DROP TRIGGER IF EXISTS decrease_stock;
//

delimiter //
CREATE TRIGGER decrease_stock AFTER INSERT
	on mydb.order FOR EACH ROW
    BEGIN
		declare id VARCHAR(16);
		set id = (SELECT supplier_people_account_number FROM mydb.order_form WHERE order_id = new.order_form_order_id);
		UPDATE mydb.product 
			SET stock_quantity = stock_quantity - new.amount
			WHERE name=new.product_name AND
				supplier_people_account_number = id;
	END
//


delimiter //
CREATE TRIGGER increase_stock AFTER UPDATE
	on mydb.order_form FOR EACH ROW
    BEGIN
		declare id INT;
		IF old.status='solved' AND new.status='returned' THEN
			UPDATE mydb.product, mydb.order
				SET product.stock_quantity = product.stock_quantity + order.amount
                WHERE product.name = order.product_name AND
					  order.order_form_order_id = new.order_id AND
                      product.supplier_people_account_number = new.supplier_people_account_number;					
        END IF;
		
	END
//

delimiter //
CREATE TRIGGER increase_points AFTER INSERT 
	on mydb.comment FOR EACH ROW
    BEGIN
		declare c_name VARCHAR(16);
		set c_name = (SELECT customer_people_account_number from order_form
			WHERE order_id = new.order_form_order_id);
		UPDATE mydb.customer
			SET vip_points = vip_points + 2
            WHERE c_name = people_account_number;
    END
//
