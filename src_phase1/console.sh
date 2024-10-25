#!/bin/bash

MODE=$1

# Check if the argument is "time" or "valgrind"
if [ "$MODE" == "time" ] || [ "$MODE" == "valgrind" ]; then
    echo "\n"
else
    echo "Invalid argument. Please use 'time' or 'valgrind'."
    exit 1
fi

rm $MODE.txt
make clean;
make DEBUG=!

for file in Professor/*.1maps; do
    echo -e "\n\n\n$file" | tee -a $MODE.txt

    if [ "$MODE" == "time" ]; then
        { time ./navigate "$file"; } 2>&1 | tee -a $MODE.txt
    elif [ "$MODE" == "valgrind" ]; then
        valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./navigate "$file" 2>&1 | tee -a $MODE.txt
    fi

    # Check if both files exist before comparing
    diff "$output_file" "$expected_file" > /dev/null
    if [ $? -eq 0 ]; then
        echo "You did it: $output_file matches $expected_file" | tee -a $MODE.txt
    else
        echo "You're dumb brother: $output_file differs from $expected_file" | tee -a $MODE.txt
    fi
    "$file" 2>&1 | tee -a $MODE.txt
done;
