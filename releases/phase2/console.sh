#!/bin/bash

rm -f "time.txt"

for file in testers/*.maps; do
    echo -e "\n\n\n$file" | tee -a time.txt

    { time ./navigate_p2 "$file"; } 2>&1 | tee -a time.txt
        
    ./navigateChecker "$file" 2>&1 | tee -a time.txt
    echo " NavigateChecker: $?" 2>&1 | tee -a time.txt
done

