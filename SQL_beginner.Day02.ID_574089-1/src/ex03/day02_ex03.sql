WITH generate_ser AS (
    SELECT generate_series(
        DATE '2022-01-01',
        DATE '2022-01-10',
        INTERVAL '1 day'
    )::DATE AS day)

SELECT g.day AS missing_date
FROM generate_ser g

LEFT JOIN person_visits d ON  g.day = d.visit_date AND (d.person_id = 1 OR d.person_id = 2)
WHERE d.visit_date IS NULL;



