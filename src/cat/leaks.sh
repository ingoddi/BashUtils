COUNTER_SUCCESS=0
COUNTER_FAIL=0
COUNTER=0
TEST_FILE="test1.txt"

echo " " >> log.txt
echo " " >> log.txt
date -u  >> log.txt
echo " " >> log.txt

# 1 flag
for var in -b -e -n -s -t
do
    TEST="$var $TEST_FILE"
    leaks -quiet -atExit -- ./s21_cat $TEST > test_s21_cat.log
    leak=$(grep -A100000 leaks test_s21_cat.log)
    (( COUNTER++ ))
    if [[ $leak == *"0 leaks for 0 total leaked bytes"* ]]
      then
        (( COUNTER_SUCCESS++ ))
        echo -e"\033[31m$COUNTER_FAIL\033[0m/\033[32m$COUNTER_SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m cat $TEST"
      else
        (( COUNTER_FAIL++ ))
        echo -e "\033[31m$COUNTER_FAIL\033[0m/\033[32m$COUNTER_SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m cat $TEST"
    fi
    rm test_s21_cat.log
done

# 2 flags
for var1 in -b -e -n -s -t
do
    for var2 in -b -e -n -s -t -v
    do
        if [ $var1 != $var2 ]
        then
            TEST="$var1 $var2 $TEST_FILE"
            leaks -quiet -atExit -- ./s21_cat $TEST > test_s21_cat.log
            leak=$(grep -A100000 leaks test_s21_cat.log)
            (( COUNTER++ ))
            if [[ $leak == *"0 leaks for 0 total leaked bytes"* ]]
              then
                (( COUNTER_SUCCESS++ ))
                echo -e "\033[31m$COUNTER_FAIL\033[0m/\033[32m$COUNTER_SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m cat $TEST"
              else
                (( COUNTER_FAIL++ ))
                echo -e "\033[31m$COUNTER_FAIL\033[0m/\033[32m$COUNTER_SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m cat $TEST"
            fi
            rm test_s21_cat.log
        fi
    done
done

# 3 flags
for var1 in -b -e -n -s -t
do
    for var2 in -b -e -n -s -t -v
    do
      for var3 in -b -e -n -s -t -v
      do
        if [ $var1 != $var2 ] && [ $var2 != $var3 ] && [ $var1 != $var3 ]
        then
            TEST="$var1 $var2 $var3 $TEST_FILE"
            leaks -quiet -atExit -- ./s21_cat $TEST > test_s21_cat.log
            leak=$(grep -A100000 leaks test_s21_cat.log)
            (( COUNTER++ ))
            if [[ $leak == *"0 leaks for 0 total leaked bytes"* ]]
              then
                (( COUNTER_SUCCESS++ ))
                echo -e "\033[31m$COUNTER_FAIL\033[0m/\033[32m$COUNTER_SUCCESS\033[0m/$COUNTER \033[32msuccess\033[0m cat $TEST"
              else
                (( COUNTER_FAIL++ ))
                echo -e "\033[31m$COUNTER_FAIL\033[0m/\033[32m$COUNTER_SUCCESS\033[0m/$COUNTER \033[31mfail\033[0m cat $TEST"
            fi
            rm test_s21_cat.log
        fi
      done
    done
done

echo -e "✅  \033[32mSUCCESS: $COUNTER_SUCCESS\033[0m"
echo -e "❌  \033[31mFAIL: $COUNTER_FAIL\033[0m"
echo -e "📄 ALL: $COUNTER"