WITH generate_ser AS (
    SELECT 
        pz.name AS pizzeria_name,
        COUNT(*) FILTER (WHERE p.gender = 'female') AS female_count,
        COUNT(*) FILTER (WHERE p.gender = 'male') AS male_count
    FROM menu m 
    JOIN pizzeria pz ON m.pizzeria_id = pz.id
    JOIN person_order po ON po.menu_id = m.id
    JOIN person p ON po.person_id = p.id
    GROUP BY pz.name
)
SELECT pizzeria_name
FROM generate_ser
WHERE female_count < male_count OR male_count < female_count
ORDER BY pizzeria_name ASC ;
