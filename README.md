# AED Project

AED Project 24/25: IST-NAVIGATE

## About the project
In this project, we aim to develop a program capable of navigating through static rectangular maps where only horizontal and vertical movements are allowed. Each cell in these maps has an attribute representing energy, which can be negative, zero, or positive. The goal is for a student (from ECE, of course) placed in one of the cells to navigate the map, gaining and losing energy upon entering cells, with the objective of maximizing their energy if possible.

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


### Input Format for Intermediate Phase
The input file has an extension `.1maps` and may contain multiple problems, each with different dimensions. The first line of each problem (header) consists of:
1. Map dimensions, L (rows) and C (columns), where L is the number of rows and C is the number of columns.
2. Coordinates of a starting point, l and c, identifying a cell on the map (1 ≤ l ≤ L and 1 ≤ c ≤ C).
3. Number of steps, k, which can be k < 0 (task #1), k > 0 (task #2), or k = 0 (task #3). For task #1, the number of steps to use will be |k| (absolute value).
4. If k = 0, the line includes two additional integers, l2 and c2.

Following the header are L x C integers representing the energy associated with each cell. The polarity of k identifies the task, and its absolute value indicates the number of steps.

### Input Format for Final Phase
The input file has an extension `.maps` and may contain one or more maps to be solved. The header of each problem (first line) always consists of 7 integers:
1. Map dimensions: L (rows) and C (columns), where L > 0 and C > 0.
2. Task/energy: a positive integer for the minimum energy to reach (task #1) or -2 for task #2. Any other value is not admissible and indicates no solution.
3. Coordinates of the starting position: the coordinates can be inside or outside the matrix (if outside, the problem has no solution).
4. Number of steps, k: an integer such that k ∈ N and 0 ≤ k < L x C, for the problem to have a solution.
5. Initial energy: must be positive for the problem to have a solution.

Following the header are L x C integers representing the energy in each cell of the map. The program does not need to validate the values in the file but must ensure the correct file extension and existence. It should respond appropriately to both well-defined and ill-defined problems.

### Output Format for Intermediate Phase
The output file has the same name as the input file but with the extension `.sol1maps`, and includes the results for all problems in the input file. There are two possibilities:

1. Task #1 and Task #2: The output file should contain only one line per problem. It should repeat the five integers from the problem header in the same order, followed by the result. The sixth integer specifies the response, which will always be a non-negative number for well-defined problems (when the starting coordinates are within the map). If there are no positive energy cells within the search radius k, the response value should be zero. For ill-defined problems, the response value is absent.

2. Task #3: The output file should also start by repeating the first line of the problem. After this line, the path should be presented with one step per line, showing the coordinates of the destination of that step and the energy received. For ill-defined problems (starting and/or ending coordinates outside the map dimensions), no coordinates should be printed, only the first line of the problem with all seven integers.

If the input file contains more than one problem, the output file will concatenate the solutions for all problems, including a blank line as a separator between different solutions. It is mandatory that there is only one blank space between each integer.

### Output Format for Final Phase
The output file has the same name as the input file but with the extension `.solmaps`.

For any problem, the first line of the solution should always repeat the first line of the problem as presented in the input file, followed by an additional integer. This eighth integer should indicate the final energy for problems that have a solution, or -1 if the problem has no solution. If the eighth integer is positive, the following lines should contain the solution to the problem. There should be k lines of three integers each: the coordinates of the position to move to and the energy, ei, with i = 1, ..., k, for that position. If the eighth integer is -1, only the first line constitutes the appropriate response for the problem.
