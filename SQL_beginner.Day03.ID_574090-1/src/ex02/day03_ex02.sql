WITH generate_ser AS (
    
    SELECT generate_series(1, 18, 1) AS day)

SELECT m.pizza_name ,m.price, pz.name 
FROM generate_ser g
JOIN menu m ON g.day = m.id
JOIN pizzeria pz ON m.pizzeria_id = pz.id
WHERE g.day NOT IN(SELECT menu_id FROM person_order po)


ORDER BY m.pizza_name , m.price