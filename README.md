# cs470-sliding-puzzle

![alt tag](https://raw.githubusercontent.com/dustin-fox/cs470-sliding-puzzle/master/documentation/readme_screenshots/Sliding8Puzzle.PNG)

This project is meant to help me explore different search techniques used in artificial intelligence to solve a sliding 8 puzzle.
The Sliding 8 puzzle is fully playable and it also incorporates the following 5 algorithms to automatically solve the puzzle:

1. Breadth First Search (no closed list)
2. Breadth First Search (with a closed list)
3. Depth First Search
4. A\* Search (using Manhattan Distance heuristic)
5. A\* Search (using Straight Line Distance heuristic)

The puzzle starts out fully solved then the user may either manually enter moves to randomize the board or they can hit (1) and apply 100 random moves to the board. Once the board is fully randomized the user has a choice between the 5 individual algorithms listed above with the commands (5,6,7,8,9) or they can hit (0) to solve the board with each algorithm individually and report the results for comparison.

![alt tag](https://raw.githubusercontent.com/dustin-fox/cs470-sliding-puzzle/master/documentation/readme_screenshots/AlgorithmStats.PNG)

*Note: I limited the search to 3,000,000 nodes so that I would not run out of memory. This can easily be changed, if needed, by changing the value in the Solve() method of Solver.cpp.

## Developer Info ##
This project is built using c++11

## How To Compile and Run

To compile just open bash in a linux terminal that has g++ installed,
navagate to the folder that you cloned the project in and type the command:

`make`

Then to run the program type:

`bin/runner`

## Contributing

1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request :D

## Licence 
Apache 2.0
