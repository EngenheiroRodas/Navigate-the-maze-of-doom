#!/bin/bash

MODE=$1

# Check if the argument is "time" or "valgrind"
if [ "$MODE" == "time" ] || [ "$MODE" == "valgrind" ]; then
    echo "Mode set to: $MODE"
else
    echo "Invalid argument. Please use 'time' or 'valgrind'."
    exit 1
fi

# Remove previous log file if it exists
rm -f "$MODE.txt"
make clean
make DEBUG=!

for file in Professor/*.1maps; do
    echo -e "\n\n\nProcessing $file" | tee -a "$MODE.txt"

    # Run navigate with either time or valgrind based on MODE
    if [ "$MODE" == "time" ]; then
        { time ./navigate "$file"; } 2>&1 | tee -a "$MODE.txt"
    elif [ "$MODE" == "valgrind" ]; then
        valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./navigate "$file" 2>&1 | tee -a "$MODE.txt"
    fi

    # Define expected and output file names
    output_file="${file%.1maps}.sol1maps"
    expected_file="${file%.1maps}.QUERY"

    # Check if .sol1maps was generated by navigate
    if [ ! -f "$output_file" ]; then
        echo "Error: $output_file was not generated by navigate." | tee -a "$MODE.txt"
        continue
    fi

    # Compare .sol1maps with .query
    if [ -f "$expected_file" ]; then
        diff "$output_file" "$expected_file" > /dev/null
        if [ $? -eq 0 ]; then
            echo "You did it, the files match!" | tee -a "$MODE.txt"
        else
            echo "You're close, but there's a difference in the files." | tee -a "$MODE.txt"
        fi
    else
        echo "Warning: Expected file $expected_file not found." | tee -a "$MODE.txt"
    fi
done
