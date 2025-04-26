SELECT object_name

FROM(
SELECT name AS object_name, 1 AS source
FROM person
UNION ALL
SELECT pizza_name AS object_name , 2 AS source
FROM menu)

ORDER BY source , object_name