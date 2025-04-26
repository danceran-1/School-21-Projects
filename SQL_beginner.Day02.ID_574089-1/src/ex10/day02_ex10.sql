SELECT p1.name , p2.name, p1.address
FROM person p1

JOIN person p2 on p1.address = p2.address AND p1.name < p2.name

ORDER BY p1.name , p2.name DESC, p1.address

