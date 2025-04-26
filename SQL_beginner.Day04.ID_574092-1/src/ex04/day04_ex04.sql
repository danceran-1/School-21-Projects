CREATE VIEW v_symmetric_union AS
WITH R_table AS (
    SELECT person_id
    FROM person_visits
    WHERE visit_date = '2022-01-02'
),

S_table AS (
    SELECT person_id
    FROM person_visits
    WHERE visit_date = '2022-01-06'
)

SELECT rt.person_id FROM R_table rt EXCEPT SELECT st.person_id FROM S_table st 
UNION
SELECT st.person_id FROM S_table st EXCEPT SELECT rt.person_id FROM R_table rt