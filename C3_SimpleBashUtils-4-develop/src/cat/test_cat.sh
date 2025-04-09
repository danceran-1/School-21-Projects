#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
DIFF_RES=""
TEST_FILE="test_files/*"
echo "" > log.txt

# Проверка одиночных флагов
for var in -b -e -n -s -t -v -E -T --number-nonblank --number --squeeze-blank
do
    TEST1="$var $TEST_FILE"
    echo "$TEST1"
    ./s21_cat $TEST1 > s21_cat.txt
    cat $TEST1 > cat.txt
    DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
    if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
    then
        (( COUNTER_SUCCESS++ ))
    else
        echo "$TEST1" >> log.txt
        (( COUNTER_FAIL++ ))
    fi
    rm s21_cat.txt cat.txt
done

# Проверка комбинаций флагов с одиночным флагом
for var in -b -e -n -s -t -v -E -T --number-nonblank --number --squeeze-blank
do
    for var2 in -b -e -n -s -t -v -E -T --number-nonblank --number --squeeze-blank
    do
        if [ "$var" != "$var2" ]
        then
            TEST1="$var $var2 $TEST_FILE"
            echo "$TEST1"
            ./s21_cat $TEST1 > s21_cat.txt
            cat $TEST1 > cat.txt
            DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
            if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
                (( COUNTER_SUCCESS++ ))
            else
                echo "$TEST1" >> log.txt
                (( COUNTER_FAIL++ ))
            fi
            rm s21_cat.txt cat.txt
        fi
    done
done

echo "SUCCESS: $COUNTER_SUCCESS"
echo "FAIL: $COUNTER_FAIL"
