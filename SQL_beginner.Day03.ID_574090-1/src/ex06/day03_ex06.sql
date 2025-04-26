SELECT 
    m.pizza_name, pz.name AS pizzeria_name1, pz.name AS pizzeria_name2 ,m.price

FROM pizzeria pz

JOIN menu m ON m.pizzeria_id = pz.id
WHERE (m.pizza_name ,m.price) IN (
    SELECT pizza_name, price
    FROM menu
    GROUP BY pizza_name,price
    HAVING COUNT(DISTINCT pizzeria_id)>1
)

ORDER BY m.pizza_name
