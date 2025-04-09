#!/bin/sh
head -n 1 ../ex02/hh_sorted.csv > hh_positions.csv
awk -F',' '{
    if (tolower($3) ~ /junior/) $3="\"Junior\""
    else if (tolower($3) ~ /senior/) $3="\"Senior\""
    else if (tolower($3) ~ /middle/) $3="\"Middle\""
    else if (tolower($3)~ /name/) next
    else $3 = "\"-\""
    print $0
}' OFS=',' ../ex02/hh_sorted.csv >> hh_positions.csv
