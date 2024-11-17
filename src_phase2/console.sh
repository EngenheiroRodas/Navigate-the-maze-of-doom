#!/bin/bash

MODE=$1

# Check if the argument is "time" or "valgrind"
if [ "$MODE" == "time" ] || [ "$MODE" == "valgrind" ]; then
    echo "\n"
else
    echo "Invalid argument. Please use 'time' or 'valgrind'."
    exit 1
fi

# Remove previous log file if it exists
rm -f "$MODE.txt"

cd build
if [ "$MODE" == "time" ]; then
    make release
elif [ "$MODE" == "valgrind" ]; then
    make debug
fi
cd ..

for dir1 in $(ls testers); do
    for file in testers/$dir1/*.maps; do
        echo -e "\n\n\n$file" | tee -a $MODE.txt

        if [ "$MODE" == "time" ]; then
                { time ./build/navigate "$file"; } 2>&1 | tee -a $MODE.txt
        elif [ "$MODE" == "valgrind" ]; then
            valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./build/navigate "$file" 2>&1 | tee -a $MODE.txt
        fi

        ./navigateChecker "$file" 2>&1 | tee -a $MODE.txt
        echo " NavigateChecker: $?" 2>&1 | tee -a $MODE.txt
    done
done
