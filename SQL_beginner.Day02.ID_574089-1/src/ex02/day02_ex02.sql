\pset null 'null'

SELECT 
    COALESCE(p.name, '-') AS person_name, 
    pv.visit_date AS visit_date,
    COALESCE(piz.name, '-') AS pizzeria_name  
   
FROM person p
LEFT  JOIN person_visits pv 
    ON p.id = pv.person_id AND pv.visit_date BETWEEN '2022-01-01' AND '2022-01-03'

FULL  JOIN pizzeria piz
    ON piz.id = pv.pizzeria_id


ORDER BY p.name IS NOT NULL, p.name, pv.visit_date ,piz.name;

