SELECT pizza_name ,p.name ,price
FROM menu m

JOIN pizzeria p ON p.id = m.pizzeria_id AND (m.pizza_name = 'pepperoni pizza'  OR m.pizza_name = 'mushroom pizza')
ORDER BY m.pizza_name , p.name