COUNTER_SUCCESS=0
COUNTER_FAIL=0
COUNTER=0
DIFF_RES=""
TEST_FILE="test1.txt"

echo " " >> log.txt
echo " " >> log.txt
date -u  >> log.txt
echo " " >> log.txt

# 1 flags
for var in -b -e -n -s -t
do
    TEST="$var $TEST_FILE"
    ./s21_cat $TEST > s21_cat.txt
    cat $TEST > cat.txt
    DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
    (( COUNTER++ ))
    if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
    then
        echo "✅SUCCESS : $TEST" >> log.txt
        (( COUNTER_SUCCESS++ ))
    else
        echo "❌FAIL    : $TEST" >> log.txt
        (( COUNTER_FAIL++ ))
    fi
    rm s21_cat.txt cat.txt
done

# 2 flags
for var in -b -e -n -s -t
do
    for var2 in -b -e -n -s -t -v
    do
        if [ $var != $var2 ]
        then
            TEST="$var $var2 $TEST_FILE"
            ./s21_cat $TEST > s21_cat.txt
            cat $TEST > cat.txt
            DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
            (( COUNTER++ ))
            if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
                echo "✅SUCCESS : $TEST" >> log.txt
                (( COUNTER_SUCCESS++ ))
            else
                echo "❌FAIL    : $TEST" >> log.txt
                (( COUNTER_FAIL++ ))
            fi
            rm s21_cat.txt cat.txt
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
                ./s21_cat $TEST > s21_cat.txt
                cat $TEST > cat.txt
                DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
                (( COUNTER++ ))
                if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
                then
                    echo "✅SUCCESS : $TEST" >> log.txt
                    (( COUNTER_SUCCESS++ ))
                else
                    echo "❌FAIL    : $TEST" >> log.txt
                    (( COUNTER_FAIL++ ))
                fi
                rm s21_cat.txt cat.txt
            fi
        done
    done
done

echo -e "✅  \033[32mSUCCESS: $COUNTER_SUCCESS\033[0m"
echo -e "❌  \033[31mFAIL: $COUNTER_FAIL\033[0m"
echo -e "📄 ALL: $COUNTER"


