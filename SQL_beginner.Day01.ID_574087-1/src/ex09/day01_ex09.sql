
SELECT name 
FROM pizzeria
WHERE id NOT IN(SELECT pizzeria_id FROM person_visits)
ORDER BY name;

SELECT name
FROM pizzeria p
WHERE NOT EXISTS(
    SELECT 1 
    FROM person_visits v 
    WHERE p.id = v.pizzeria_id
)