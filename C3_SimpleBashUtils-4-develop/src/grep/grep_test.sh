#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_DIR="test_files"
TEST_PATTERNS=("-e Len" "-e ')$'" "-f patterns.txt" "char" "-e '*'")
TEST_FLAGS=( "-i" "-v" "-s" "-h" "-o" "-n" "-l" "-c" )
echo "" > log.txt

# Находим все файлы с расширением .txt в директории test_files
TEST_FILES=($(find $TEST_DIR -type f -name "*.txt"))

for pattern in "${TEST_PATTERNS[@]}"; do
    for test_file in "${TEST_FILES[@]}"; do
        for var in "${TEST_FLAGS[@]}"; do
            TEST1="$var $pattern $test_file"
            echo "$TEST1"
            ./s21_grep $TEST1 > s21_grep.txt
            grep $TEST1 > grep.txt
            DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
            if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]; then
                (( COUNTER_SUCCESS++ ))
            else
                echo "$TEST1" >> log.txt
                (( COUNTER_FAIL++ ))
            fi
            rm s21_grep.txt grep.txt
        done
    done
done

TEST1="-o -e '123' -e '33' $TEST_DIR/test_grep_file2.txt $TEST_DIR/test_grep_file.txt"
echo "$TEST1"
./s21_grep $TEST1 > s21_grep.txt
grep $TEST1 > grep.txt
DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]; then
    (( COUNTER_SUCCESS++ ))
else
    echo "$TEST1" >> log.txt
    (( COUNTER_FAIL++ ))
fi
rm s21_grep.txt grep.txt

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"
