SELECT order_date , 
        CONCAT(name, ' (age:', age, ')') AS info
FROM
    (SELECT id, age, name FROM person)
NATURAL JOIN
    (SELECT person_id AS id, order_date FROM person_order)

ORDER BY order_date ASC , name ASC , age DESC