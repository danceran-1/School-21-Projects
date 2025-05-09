CREATE MATERIALIZED VIEW mv_dmitriy_visits_and_eats AS
SELECT pz.name AS pizzeria_name
FROM person_visits pv
JOIN person p ON pv.person_id = p.id
JOIN menu m ON pv.pizzeria_id = m.pizzeria_id
JOIN pizzeria pz ON pz.id = pv.pizzeria_id
WHERE p.name = 'Dmitriy'
  AND pv.visit_date = DATE '2022-01-08'
  AND m.price < 800;
