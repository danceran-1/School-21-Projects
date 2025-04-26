SELECT DISTINCT p.name FROM person p

JOIN person_order po ON po.person_id = p.id 
JOIN menu m ON po.menu_id = m.id AND (m.pizza_name = 'pepperoni pizza' OR m.pizza_name = 'mushroom pizza')

WHERE (p.address = 'Moscow' or p.address = 'Samara' ) AND (p.gender = 'male')

ORDER BY p.name DESC