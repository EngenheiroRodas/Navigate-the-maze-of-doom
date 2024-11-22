# DSA Project

DSA Final Project 24/25: IST-NAVIGATE

## About the project
In this project, we aim to develop a program capable of navigating through static rectangular maps where only horizontal and vertical movements are allowed. Each cell in these maps has an attribute representing energy, which can be negative, zero, or positive. The goal is for a student (from ECE, of course) placed in one of the cells to navigate the map, gaining and losing energy upon entering cells, with the objective of maximizing their energy if possible. 
There is also a program included that represents the cells within range for second phase.

### Restrictions:
1. The student cannot use any cell more than once, including the starting cell.
2. The student cannot continue if their energy drops to zero or below at any point.

## Objectives and Tasks
### Intermediate phase
#### 3 Tasks:
1. Identify the highest positive energy value within k steps from the starting position.
2. Sum all positive energy values of cells within k steps from the starting position.
3. Produce a path from (l1, c1) to (l2, c2), moving vertically first, then horizontally.

#### Input Format
The input file has an extension `.1maps` and may contain multiple problems, each with different dimensions. The first line of each problem (**header**) consists of:
1. Map dimensions, L (rows) and C (columns), where L is the number of rows and C is the number of columns.
2. Coordinates of a starting point, l and c, identifying a cell on the map (1 ≤ l ≤ L and 1 ≤ c ≤ C).
3. Number of steps, k, which can be:
--- k < 0 (task #1) (efective step value to use is |k|)
--- k > 0 (task #2)
--- k = 0 (task #3). 

4. If k = 0, the line includes two additional integers, l2 and c2.

Following the header are L x C integers representing the energy associated with each cell.

#### Output Format
The output file has the same name as the input file but with the extension `.sol1maps`, and includes the results for all problems in the input file. There are two possibilities:

1. Task #1 #2: The output file should contain only one line per problem. It should repeat the header, followed by the result. The sixth integer specifies the response, which will always be a non-negative number for well-defined problems (when all header parameters meet the requirements). 
If there are no positive energy cells within the search radius k, the response value should be zero. 
For ill-defined problems, the response value is absent.

2. Task #3: The output file starts by repeating the header. After this line, the path should be presented with one step per line, showing the coordinates of the destination of that step and the energy received. 
For ill-defined problems (when header parameters are not within requirements, for example starting and/or ending coordinates outside the map dimensions), no coordinates should be printed, only the first line of the problem with all seven integers.

If the input file contains more than one problem, the output file will concatenate the solutions for all problems, including a blank line as a separator between different solutions. It is mandatory that there is only one blank space between each integer.


### Final phase
#### 2 Tasks:
1. Reach or exceed a given energy value with exactly k steps.
2. Achieve the maximum possible energy with exactly k steps.

#### Input Format for Final Phase
The input file has an extension `.maps` and may contain one or more maps to be solved. The header of each problem (first line) always consists of 7 integers:
1. Map dimensions: L (rows) and C (columns), where L > 0 and C > 0.
2. An energy value, which represents the task:
--- a positive integer for the minimum energy to reach (task #1)
--- -2 for task #2. 

Any other value is not admissible and indicates no solution.

3. Coordinates of the starting position: the coordinates can be inside or outside the matrix (if outside, the problem has no solution).
4. Number of steps, k: an integer such that k ∈ N and 0 ≤ k < L x C, for the problem to have a solution.
5. Initial energy: must be positive for the problem to have a solution.

Following the header are L x C integers representing the energy in each cell of the map.

#### Output Format for Final Phase
The output file has the same name as the input file but with the extension `.solmaps`.

For any problem, the first line of the solution should always repeat the header, followed by an additional integer. This eighth integer should indicate the final energy for problems that have a solution, or -1 if the problem has no solution (path not found). 
If a path is found, the following lines should contain the solution to the problem. There should be k lines of three integers each: the coordinates of the position to move to and the energy of that cell. 
If a path is not found, only the first line constitutes the appropriate response for the problem.

### Visualization 
Bla bla bla bla visualizar celulas within rangecjsbchkskjbsvkbsjnhjbbsvjhks jv
gshvjvhbjv
chjsvcjkbs


## Usage
### Single use method
The program has an executable named `navigate` and requires a single argument: the name of a file with the extension `.1maps` for the first phase and `.maps` for the second phase. The file may contain one or more problems, separated by at least one blank line.

For example, for the final phase, the program `navigate` should be invoked from the command line as follows:

    ./navigate <filename>.maps

### Easy run (with script)
For simplicity, the executables are included in the releases folder along with a script that runs the program and checks if the output produced is correct. 

For visualizing the cells within range, there is no script included, since this program does not produce any solutions that need to be compared.