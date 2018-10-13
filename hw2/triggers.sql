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
	UPDATE mydb.product 
		SET stock_quantity = stock_quantity - new.amount
        WHERE name=new.product_name;
//

delimiter //
CREATE TRIGGER increase_stock AFTER UPDATE
	on mydb.order_form FOR EACH ROW
    UPDATE mydb.product
		SET stock_quantity = stock_quantity + new.amount
        WHERE name = new.product_name;
//
        