#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
COUNTER=0
DIFF_RES=""

echo " " >> log.txt
echo " " >> log.txt
date -u  >> log.txt
echo " " >> log.txt

for var in -v -c -l -n -h
do
  for var2 in -v -c -l -n -h
  do
      for var3 in -v -c -l -n -h
      do
        if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
        then
          TEST1="for s21_grep.c s21_grep.h Makefile $var $var2 $var3"
          ./s21_grep $TEST1 > s21_grep.txt
          grep $TEST1 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          (( COUNTER++ ))
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              echo "✅SUCCESS : $TEST1" >> log.txt
              (( COUNTER_SUCCESS++ ))
            else
              echo "❌FAIL    : $TEST1" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_grep.txt grep.txt

          TEST2="for s21_grep.c $var $var2 $var3"
          ./s21_grep $TEST2 > s21_grep.txt
          grep $TEST2 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          (( COUNTER++ ))
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              echo "✅SUCCESS : $TEST2" >> log.txt
              (( COUNTER_SUCCESS++ ))
            else
              echo "❌FAIL    : $TEST2" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_grep.txt grep.txt

          TEST3="-e for -e ^int s21_grep.c s21_grep.h Makefile $var $var2 $var3"
          ./s21_grep $TEST3 > s21_grep.txt
          grep $TEST3 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          (( COUNTER++ ))
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              echo "✅SUCCESS : $TEST3" >> log.txt
              (( COUNTER_SUCCESS++ ))
            else
              echo "❌FAIL    : $TEST3" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_grep.txt grep.txt

          TEST4="-e for -e ^int s21_grep.c $var $var2 $var3"
          ./s21_grep $TEST4 > s21_grep.txt
          grep $TEST4 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          (( COUNTER++ ))
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              echo "✅SUCCESS : $TEST4" >> log.txt
              (( COUNTER_SUCCESS++ ))
            else
              echo "❌FAIL    : $TEST4" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_grep.txt grep.txt

          TEST5="-e regex -e ^print s21_grep.c $var $var2 $var3 -f pattern.txt"
          ./s21_grep $TEST5 > s21_grep.txt
          grep $TEST5 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          (( COUNTER++ ))
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              echo "✅SUCCESS : $TEST5" >> log.txt
              (( COUNTER_SUCCESS++ ))
            else
              echo "❌FAIL    : $TEST5" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_grep.txt grep.txt

          TEST6="-e while -e void s21_grep.c Makefile $var $var2 $var3 -f pattern.txt"
          ./s21_grep $TEST6 > s21_grep.txt
          grep $TEST6 > grep.txt
          DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
          (( COUNTER++ ))
          if [ "$DIFF_RES" == "Files s21_grep.txt and grep.txt are identical" ]
            then
              echo "✅SUCCESS : $TEST6" >> log.txt
              (( COUNTER_SUCCESS++ ))
            else
              echo "❌FAIL    : $TEST6" >> log.txt
              (( COUNTER_FAIL++ ))
          fi
          rm s21_grep.txt grep.txt

        fi
      done
  done
done

echo -e "✅  \033[32mSUCCESS: $COUNTER_SUCCESS\033[0m"
echo -e "❌  \033[31mFAIL: $COUNTER_FAIL\033[0m"
echo -e "📄 ALL: $COUNTER"