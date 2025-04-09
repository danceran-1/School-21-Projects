#!/bin/sh
OUTPUT_FILE="result.csv"

INPUT_FILE="../ex03/hh_positions.csv"
HEADER=$(head -n 1 "$INPUT_FILE")

FILES=$(ls *.csv 2>/dev/null)

echo "$HEADER" > "$OUTPUT_FILE"

for FILE in $FILES; do
    tail -n +2 "$FILE" >> "$OUTPUT_FILE"
done
