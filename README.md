# Solver for the game 7^3

Jan Pokorný

## Overview
This is my effort to prove that in the Hypercube Tic-Tac-Toe of side lenght 7 and dimension 3 second player can force a draw.
To achieve this about 80 milion boards are checked for pairing strategy.

In this repository you can find program that tries to find pairing strategy for needed positions and some tools to verify the solution.

The main idea of this approax is that for any given play of the first player there exists a sequence of moves by the second player leading to draw. If only 4 (or 3 in some cases) moves of both players are made, then pairing strategy may exist. 

## Thing you need to run it yourself
 - c++17
 - OpenMP 
 - sqlite3 is used to store all the neccessary positions.
 - python3 for the naive checker 'src/checker.py'
 - 120 GB for the database of all neccessary positions

Everything can be compiled with `Makefile`, just run `make` and the executables will appear in folder `./exe/`. The only exception is `src/checker.py`, which is python program and thus no compilation is needed.


## How to run the solver.
To run the solver execute `./exe/main X`, where `X` is number of threads you want to give it. 

This may take quite a while, it took me more than half a day with 4 CPU cores.

The program will firstly create new database in `positions/DB`, if one already exists it will be replaced with the new one. Then representation of all neccessary position is generated. This should take a few seconds. After that the work is divided evenly between the threads and the most intensive part begins.

While the solver is running it will be writting `Transaction finished successfully!` which means that a lots of new solutions were found and has been written to the database.

If any error occurs during finding the pairing strategy it is written into an error file for the thread that runned into the problem. These error files are listed in folder `./error_out/` and are named as `eID` where `ID` is the ID of the thread.

There is one error message that means that given representation of placed stones is not valid.
For example `Invalid sequence [000, 030, 000]`, where the problem is that the first player is picking position 000 twice.
This error message can be ignored. Other error messages should be taken seriously.

After the computation is completed all the pairings will be in the database. To create index for faster access to the database run `./exe/create_index`.

## How to verify the solution
If you already have the database (it is in `positions/DB`) you have two options, use few of mine programs or ask the database by yourself.

### Prepared tools for verification
I tried to do the programs for verification as simple as possible to be able easy to understand. And hence together they are not very fast if you want to process all the pairing strategies.

For you to be able to run some of the following programs you have to run `make` and then run `exe/program`, where program is the name of the program without the `.cpp` suffix.

- `determine_board.cpp`
 - Interactive command line program that for the first player moves responds with second player moves and after enough moves are playd it will tell you the name of a starting position for which you can find the pairing strategy in the database.
- `determine_board_pc.cpp`
 - Same as `determine_board.cpp`, but it is not interactive. All the moves of first player are put as arguments of the program and then the program just answers the name or that the position is invalid.
- `position_selector.cpp`
 - With the name of the starting position it will find the pairing strategy in the database and print it.
- `calculate_strategy.cpp`
  - For only 3 or 4 moves (see Which positions have to be verified) of the first player it will calculate the pairing strategy and print it. Similar as if used `determine_board.cpp` and then the ouputed gived to `position_selector.cpp`.
- `verifier.cpp` 
 - For given pairing strategy (7x7x7 grid of numbers on input) it will check whether it is valid pairing strategy.
- `checker.py`
  - Script that verifies all needed positions are correct by calling previous programs. Depending on the argument (`DB` or `calc`) it will retrive solutionfrom database or calculate it. Then it verifies it with `verifier.cpp`. 
  - This script is made in python so it does not compile anything. You simply run it by `python3 ./src/checker.py` (*Note: you have to be in the root of this repository to be able for this to works properly). 


### I will do it on my own
 - The database has just 1 table `POSITIONS` which has three 3 columns.
   - ID - an id assigned by the database
   - START_POSITION - name of the starting positions made by the alternating moves of first and second players, separated by `_`.  
   - PAIRING - Grid of 7x7x7 numbers, where each number is either first player stone(-1), second player stone(-2), empty cell(0) or is assigned a ID of a pair in the pairing strategy.
 - Coordinate system for naming cells of the game board is made up of three numbers from 0 to 6, which are concatenated to give unique id for each cell in the board.

- The moves of the second player can be get from the program `determine_board.cpp` explained in previous section.

### Which positions have to be verified
- The moves of the second player are calculated based on first player moves (see `determine_board.cpp`).
- If the first player plays to the center of the board - cell 333, then 4 moves are needed to play for the pairing strategy to exist. But one move of the first player is already determined. This gives us about 1*343^3 positions to check.
- Else the the second player can take the cell 333 and only 3 moves are needed. So also about 1*343^3 positions to check.
- Some of the positions will be invalid in a way that the first player playd to an occupied cell, so they have to be excluded. But for all other positions the paring strategy has to be found.