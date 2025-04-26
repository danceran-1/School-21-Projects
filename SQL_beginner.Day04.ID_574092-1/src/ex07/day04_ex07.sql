BEGIN;

INSERT INTO person_visits (id, person_id, pizzeria_id, visit_date)
VALUES (
    (SELECT MAX(id)+1 FROM person_visits),
    (SELECT id FROM person WHERE name = 'Dmitriy'),
    (
        SELECT pizzeria_id 
        FROM menu 
        WHERE price < 800 
          AND pizzeria_id NOT IN (
              SELECT DISTINCT pz.id
              FROM menu m
              JOIN pizzeria pz ON pz.id = m.pizzeria_id
              WHERE pz.name IN (SELECT pizzeria_name FROM mv_dmitriy_visits_and_eats)
          )
        LIMIT 1
    ),
    DATE '2022-01-08'
);

REFRESH MATERIALIZED VIEW mv_dmitriy_visits_and_eats;

COMMIT;
