WITH visits_by_persons AS (
    SELECT visit_date
    FROM person_visits
    WHERE person_id = 1 OR person_id = 2
   
) 

SELECT DISTINCT d.visit_date AS missing_date
FROM person_visits d

LEFT JOIN visits_by_persons v ON  v.visit_date = d.visit_date 
WHERE v.visit_date IS NULL
ORDER BY d.visit_date;
