CREATE VIEW v_price_with_discount AS
WITH disc AS(
    SELECT id, price * 0.9 AS discount_price FROM menu
  
)
SELECT p.name , m.pizza_name , m.price , CAST(d.discount_price AS INT)
FROM person p 
JOIN person_order po ON po.person_id = p.id 
JOIN menu m ON m.id = po.menu_id
JOIN disc d ON d.id = m.id

ORDER BY p.name , m.pizza_name
