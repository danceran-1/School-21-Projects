#!/bin/sh
echo '"name","count"' > hh_uniq_positions.csv
echo "\"Junior\", $(grep -c -i "junior" ../ex03/hh_positions.csv)" >> hh_uniq_positions.csv
echo "\"Middle\", $(grep -c -i "middle" ../ex03/hh_positions.csv)" >> hh_uniq_positions.csv
echo "\"Senior\", $(grep -c -i "senior" ../ex03/hh_positions.csv)" >> hh_uniq_positions.csv