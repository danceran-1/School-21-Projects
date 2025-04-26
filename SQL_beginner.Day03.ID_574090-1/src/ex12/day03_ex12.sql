INSERT INTO person_order (id, person_id, menu_id, order_date)
SELECT 
    (SELECT MAX(id) FROM person_order) + RANK() OVER (ORDER BY p.id, m.id),
    p.id, 
    m.id, 
    '2022-02-25'
FROM person p
JOIN menu m ON m.pizza_name = 'greek pizza';