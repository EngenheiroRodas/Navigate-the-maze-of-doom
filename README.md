# AED Project

AED Project 24/25: IST-NAVIGATE

## Preface
In this project, we aim to develop a program capable of navigating through static rectangular maps where only horizontal and vertical movements are allowed. Each cell in these maps has an attribute representing energy, which can be negative, zero, or positive. The goal is for a student (from LEEC, of course) placed in one of the cells to navigate the map, gaining and losing energy upon entering cells, with the objective of maximizing their energy if possible.

### Restrictions:
1. The student cannot use any cell more than once, including the starting cell.
2. The path taken must have exactly k steps, no more, no less.
3. The student cannot continue if their energy drops to zero or below at any point.

### Objectives:
1. Reach or exceed a specific energy value with exactly k steps.
2. Achieve the highest possible energy after k steps.

## Objectives and Tasks
### Part 1 - 3 Tasks:
1. Identify the highest positive energy value within k steps from the starting position.
2. Sum all positive energy values of cells within k steps from the starting position.
3. Produce a path from (l1, c1) to (l2, c2), moving vertically first, then horizontally.

### Part 2 - 2 Tasks:
1. Reach or exceed a given energy value with exactly k steps.
2. Achieve the maximum possible energy with exactly k steps.

## Usage
The program has an executable named `navigate` and requires a single argument: the name of a file with the extension `.1maps` for the intermediate phase and `.maps` for the final phase. The file may contain one or more problems, separated by at least one blank line.

For example, for the final phase, the program `navigate` should be invoked from the command line as follows:
```sh
./navigate <filename>.maps
```


Input Format

The input file has an extension .1maps and may contain multiple problems, each with different dimensions. The first line of each problem (header) consists of:

    Map dimensions, L (rows) and C (columns).
    Coordinates of a starting point, l and c, identifying a cell on the map.
    Number of steps k (with k < 0 for task #1, k > 0 for task #2, or k = 0 for task #3).
    If k = 0, two additional integers, l2 and c2, are included.

Following the header are L x C integers representing the energy associated with each cell.
Output Format

For the intermediate phase, the output file has the same name as the input file but with the extension .sol1maps, and includes the results for all problems in the input file.

For the final phase, the output file has the same name as the input file but with the extension .solmaps, and includes the final energy or indicates that the problem has no solution.
