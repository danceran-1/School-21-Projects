SELECT pizza_name, pn.name AS pizzeria_name
FROM person p

JOIN person_order po ON po.person_id = p.id
JOIN menu m ON m.id = po.menu_id
JOIN pizzeria pn ON m.pizzeria_id = pn.id
WHERE p.name = 'Denis' OR p.name = 'Anna'

ORDER BY pizza_name, pn.name 