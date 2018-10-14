SELECT * FROM people;
SELECT people.name FROM people, customer
	WHERE people.account_number=customer.people_account_number;


SET @customer1 = (SELECT people.name FROM people, customer
	WHERE people.account_number = customer.people_account_number
    ORDER BY people.age DESC limit 1);
SET @customer2 = (SELECT people.name FROM people, customer
	WHERE people.account_number = customer.people_account_number
    ORDER BY people.age ASC limit 1);

set @cloth1 = (SELECT name FROM product
	WHERE type='clothing'
    ORDER BY unit_price * discount DESC limit 1);
SELECT @cloth1;
set @food1 = (SELECT name FROM product
	WHERE type='food'
    ORDER BY unit_price * discount DESC limit 1);
SELECT @food1;
set @fun1 = (SELECT name FROM product
	WHERE type='fun'
    ORDER BY unit_price * discount DESC limit 1);
SELECT @fun1;

set @cloth2 = (SELECT name FROM product
	WHERE type='clothing'
    ORDER BY stock_quantity DESC limit 1);
SELECT @cloth2;
set @food2 = (SELECT name FROM product
	WHERE type='food'
    ORDER BY stock_quantity DESC limit 1);
SELECT @food2;
set @fun2 = (SELECT name FROM product
	WHERE type='fun'
    ORDER BY stock_quantity DESC limit 1);
SELECT @fun2;
