WITH generate_ser AS 
    (SELECT 
        pz.name AS pizzeria_name
    FROM menu m
    JOIN pizzeria pz ON pz.id = m.pizzeria_id
    JOIN person_order po ON po.menu_id = m.id
    JOIN person p ON p.id = po.person_id AND p.name = 'Andrey'),

generate_ser1 AS 
    (SELECT 
        pz.name AS pizzeria_name FROM person_visits pv

    JOIN pizzeria pz ON pz.id = pv.pizzeria_id
    JOIN person p ON p.id = pv.person_id AND p.name = 'Andrey')

SELECT pizzeria_name 
FROM generate_ser1
EXCEPT
SELECT pizzeria_name 
FROM generate_ser
ORDER BY pizzeria_name;