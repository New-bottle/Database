delimiter //
CREATE TRIGGER check_stock BEFORE INSERT
	ON mydb.order FOR EACH ROW 
    BEGIN
		SELECT @num:= stock_quantity FROM mydb.product WHERE name=new.product_name;
        IF @num < new.amount THEN
			SIGNAL SQLSTATE 'HY000' SET mysql_errno=22, MESSAGE_TEXT = 'stock is not enough!'; 
		END IF;
    END
//

delimiter //
CREATE TRIGGER decrease_stock AFTER INSERT
	on mydb.order FOR EACH ROW
    BEGIN
		SELECT @id = supplier_people_account_number FROM mydb.order_form WHERE order_id = new.order_form_order_id;
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
		UPDATE mydb.product
			SET stock_quantity = stock_quantity + new.amount
			WHERE name = new.product_name AND
				supplier_people_account_number = new.supplier_people_account_number;
	END
//

delimiter //
CREATE TRIGGER increase_points AFTER INSERT 
	on mydb.comment FOR EACH ROW
    BEGIN
		SELECT @c_name = customer_people_account_number from order_form
			WHERE order_id = new.order_form_order_id;
		UPDATE mydb.customer
			SET vip_points = vip_points + 2
            WHERE @c_name = people_account_number;
    END
//
