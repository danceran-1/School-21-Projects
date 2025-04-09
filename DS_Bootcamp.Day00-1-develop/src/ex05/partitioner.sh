#!/bin/bash
INPUT_FILE="../ex03/hh_positions.csv"

HEADER=$(head -n 1 "$INPUT_FILE")

tail -n +2 "$INPUT_FILE" |
awk -F ',' -v header="$HEADER" '{
    split($2, datetime, "T");
    date = datetime[1];
    file = "hh_" date ".csv";
    if (!(file in files)) {
        print header > file;
        files[file] = 1;
        }
        print $0 >> file;
    
}'