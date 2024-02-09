#!/bin/bash

COUNTER_SUCCESS=0
COUNTER_FAIL=0
COUNTER=0

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
          leaks -quiet -atExit -- ./s21_grep $TEST1 > test_s21_grep.log
          leak=$(grep -A100000 leaks test_s21_grep.log)
          (( COUNTER++ ))
          if [[ $leak == *"0 leaks for 0 total leaked bytes"* ]]
            then
              (( COUNTER_SUCCESS++ ))
              echo -e"\033[31m$COUNTER_FAIL\033[0m/\033[32m$COUNTER_SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m cat $TEST1"
            else
              (( COUNTER_FAIL++ ))
              echo -e "\033[31m$COUNTER_FAIL\033[0m/\033[32m$COUNTER_SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m cat $TEST1"
          fi
          rm test_s21_grep.log

          TEST2="for s21_grep.c $var $var2 $var3"
          leaks -quiet -atExit -- ./s21_grep $TEST2 > test_s21_grep.log
          leak=$(grep -A100000 leaks test_s21_grep.log)
          (( COUNTER++ ))
          if [[ $leak == *"0 leaks for 0 total leaked bytes"* ]]
            then
              (( COUNTER_SUCCESS++ ))
              echo -e"\033[31m$COUNTER_FAIL\033[0m/\033[32m$COUNTER_SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m cat $TEST2"
            else
              (( COUNTER_FAIL++ ))
              echo -e "\033[31m$COUNTER_FAIL\033[0m/\033[32m$COUNTER_SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m cat $TEST2"
          fi
          rm test_s21_grep.log

          TEST3="-e for -e ^int s21_grep.c s21_grep.h Makefile $var $var2 $var3"
          leaks -quiet -atExit -- ./s21_grep $TEST3 > test_s21_grep.log
          leak=$(grep -A100000 leaks test_s21_grep.log)
          (( COUNTER++ ))
          if [[ $leak == *"0 leaks for 0 total leaked bytes"* ]]
            then
              (( COUNTER_SUCCESS++ ))
              echo -e"\033[31m$COUNTER_FAIL\033[0m/\033[32m$COUNTER_SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m cat $TEST3"
            else
              (( COUNTER_FAIL++ ))
              echo -e "\033[31m$COUNTER_FAIL\033[0m/\033[32m$COUNTER_SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m cat $TEST3"
          fi
          rm test_s21_grep.log

          TEST4="-e for -e ^int s21_grep.c $var $var2 $var3"
          leaks -quiet -atExit -- ./s21_grep $TEST4 > test_s21_grep.log
          leak=$(grep -A100000 leaks test_s21_grep.log)
          (( COUNTER++ ))
          if [[ $leak == *"0 leaks for 0 total leaked bytes"* ]]
            then
              (( COUNTER_SUCCESS++ ))
              echo -e"\033[31m$COUNTER_FAIL\033[0m/\033[32m$COUNTER_SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m cat $TEST4"
            else
              (( COUNTER_FAIL++ ))
              echo -e "\033[31m$COUNTER_FAIL\033[0m/\033[32m$COUNTER_SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m cat $TEST4"
          fi
          rm test_s21_grep.log

          TEST5="-e regex -e ^print s21_grep.c $var $var2 $var3 -f pattern.txt"
          leaks -quiet -atExit -- ./s21_grep $TEST5 > test_s21_grep.log
          leak=$(grep -A100000 leaks test_s21_grep.log)
          (( COUNTER++ ))
          if [[ $leak == *"0 leaks for 0 total leaked bytes"* ]]
            then
              (( COUNTER_SUCCESS++ ))
              echo -e"\033[31m$COUNTER_FAIL\033[0m/\033[32m$COUNTER_SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m cat $TEST5"
            else
              (( COUNTER_FAIL++ ))
              echo -e "\033[31m$COUNTER_FAIL\033[0m/\033[32m$COUNTER_SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m cat $TEST5"
          fi
          rm test_s21_grep.log

          TEST6="-e while -e void s21_grep.c Makefile $var $var2 $var3 -f pattern.txt"
          leaks -quiet -atExit -- ./s21_grep $TEST6 > test_s21_grep.log
          leak=$(grep -A100000 leaks test_s21_grep.log)
          (( COUNTER++ ))
          if [[ $leak == *"0 leaks for 0 total leaked bytes"* ]]
            then
              (( COUNTER_SUCCESS++ ))
              echo -e"\033[31m$COUNTER_FAIL\033[0m/\033[32m$COUNTER_SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m cat $TEST6"
            else
              (( COUNTER_FAIL++ ))
              echo -e "\033[31m$COUNTER_FAIL\033[0m/\033[32m$COUNTER_SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m cat $TEST6"
          fi
          rm test_s21_grep.log
        fi
      done
  done
done

echo -e "✅  \033[32mSUCCESS: $COUNTER_SUCCESS\033[0m"
echo -e "❌  \033[31mFAIL: $COUNTER_FAIL\033[0m"
echo -e "📄 ALL: $COUNTER"