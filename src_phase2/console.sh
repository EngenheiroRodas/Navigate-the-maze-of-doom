#!/bin/bash

MODE=$1

# Check if the argument is "time" or "valgrind"
if [ "$MODE" == "time" ] || [ "$MODE" == "valgrind" ]; then
    echo "\n"
else
    echo "Invalid argument. Please use 'time' or 'valgrind'."
    exit 1
fi

rm *.txt
make clean;
make DEBUG=!

for dir1 in $(ls testers); do
    for dir2 in $(ls testers/$dir1); do
        for file in testers/$dir1/$dir2/*.maps; do
            echo -e "\n\n\n$file" | tee -a $MODE.txt

            if [ "$MODE" == "time" ]; then
                { time ./navigate "$file"; } 2>&1 | tee -a $MODE.txt
            elif [ "$MODE" == "valgrind" ]; then
                valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./navigate "$file" 2>&1 | tee -a $MODE.txt
            fi

            ./navigateChecker "$file" 2>&1 | tee -a $MODE.txt
            echo " NavigateChecker: $?" 2>&1 | tee -a $MODE.txt
        done
    done
done
