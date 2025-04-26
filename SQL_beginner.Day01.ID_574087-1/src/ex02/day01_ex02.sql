
SELECT pizza_name
FROM(
    SELECT pizza_name ,ROW_NUMBER() OVER (PARTITION BY pizza_name) AS num
    FROM menu)
WHERE num = 1
ORDER BY pizza_name DESC;