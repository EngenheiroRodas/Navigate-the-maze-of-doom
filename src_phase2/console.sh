#!/bin/bash

rm output.txt

make clean;
make DEBUG=!

for dir1 in $(ls testers); do
    for dir2 in $(ls testers/$dir1); do
        for file in testers/$dir1/$dir2/*.maps; do
            echo -e "\n\n\n$file" | tee -a output.txt; 
            { valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./navigate $file; } 2>&1 | tee -a output.txt;
            ./navigateChecker $file 2>&1 | tee -a output.txt;
            echo " NavigateChecker: $?" 2>&1 | tee -a output.txt;
        done
    done
done;

# time command
# time ./navigate

# valgrind command
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./navigate
