SELECT m.pizza_name , m.price ,piz.name AS pizzeria_name , pv.visit_date
FROM person p 

JOIN person_visits pv ON pv.person_id = p.id 
JOIN pizzeria piz ON pv.pizzeria_id = piz.id 
JOIN menu m ON m.pizzeria_id = piz.id

WHERE p.name = 'Kate' AND m.price BETWEEN 800 AND 1000

ORDER BY m.pizza_name , m.price, piz.name