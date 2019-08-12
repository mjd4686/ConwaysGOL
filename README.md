# SDL2 implementation of Conway's Game of Life 

Conways Game of Life is a cellular automaton that has alive and dead 'cells' represented with being colored on the grid.

It follows the simple rules:

1.  Any live cell with fewer than two live neighbours dies, as if by underpopulation.
2.  Any live cell with two or three live neighbours lives on to the next generation.
3.  Any live cell with more than three live neighbours dies, as if by overpopulation.
4.  Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

More can be read about the game here: https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life

## Playing

To play you start the program and left click the cells that you want to start as alive. You can drag the grid with right click and zoom with the mouse wheel. Then hit space to begin the simulation.


## Building

This project uses CMAKE for building, so you will need a g++ compiler. Simple Directmedia Layer 2 is used for graphics. These dependencies can be installed on ubuntu with:
```
sudo apt install libsdl2-dev cmake g++
```
Once you have the dependencies building is standard. From inside the cloned directory:
```
mkdir build
cd build
cmake ..
make -j8
```
Once building is complete the simulation is run by 
```
./ConwayGOL
```
