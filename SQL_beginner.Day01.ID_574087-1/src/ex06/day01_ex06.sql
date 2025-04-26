SELECT action_date,person.name AS person_name 
FROM(
    SELECT order_date AS action_date , person_id
    FROM person_order
    
    INTERSECT

    SELECT visit_date AS action_date, person_id
    FROM person_visits

) AS actions
JOIN person ON actions.person_id = person.id

ORDER BY action_date ASC , person_name DESC