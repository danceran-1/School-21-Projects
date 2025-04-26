SELECT m.id AS menu_id
FROM menu m
WHERE m.id NOT IN (SELECT menu_id FROM person_order)
ORDER BY m.id;
