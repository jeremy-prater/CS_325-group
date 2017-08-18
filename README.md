# CS 325 Group 10 TSP Project

# Parallel Genetic TSP Solver

Once you download the zip, or clone the repo, enter the following commands to build the application.

````
mkdir build
cd build
cmake ..
make
cd ..
````

Program usage

````
> ./build/cs325-group
Incorrect number of arguments!

Usage : cs325-group <input file> -t <180>           -- Run for 180 seconds
Usage : cs325-group <input file> -m <mindistance>   -- Run until (min distance * 1.25) is found
````

Now the executable is created. To run tests, the TSP Example files and TSP Competition files are located in sub-folders

````
> ./build/cs325-group ./TSP_Files/tsp_example_1.txt -t 180
Reading file [./TSP_Files/tsp_example_1.txt]
Read Complete! [76] Cities. Beginning TSP.
Using 24 threads.
Running for 180 seconds...
Using Population Count 1263
Using Elite Count 631
Using Tournament Count 631
Initial distance: 445625
Average loop execution time 251ms.
1 seconds execution...  Min path [416607]
2 seconds execution...  Min path [390871]
3 seconds execution...  Min path [356797]
4 seconds execution...  Min path [337336]
5 seconds execution...  Min path [313322]
6 seconds execution...  Min path [302500]
7 seconds execution...  Min path [286361]
````

The output file name is the same as the input file name with ".tour" appended to the end

Once an exit condition is reached, either time, or minimum path found, the program will write the data to the file and terminate

````
Finished in 1905 ms.
Final distance: 377400
Solution:
Writing to file [./TSP_Files/tsp_example_1.txt.tour]
````
