# AP1-ex4
Advanced Programming 1, Computer Science Major at Bar-Ilan University

Link to project's github repository

This project provides a structure for solving problems and managing their solutions with a LRU cache manager. Particularly, the following problem sovlers were implemented:

 1) StringReverser - Reverse any string
 2)   Searcher - graph searching algorithms (Best First Search, A*, BFS, DFS)
 
# Key Features
Server-client connection and parallel handling
Multi-Threading
Usage of C++ STL, I/O
Usage of OOP Design Patterns: Bridge, Object Adapter...

# Running the tests
 Finding a path in KxN Graphs:
 
  ```//This is a 3x4 graph
   1,6,2,3
   7,-1,1,6
   3,7,8,1
   2,6,7,5
   0,0
   3,3
   end
   ```
   
this means the program will find a path from (0,0) to (3,3) vertices in this spesific graph. -1 means that this vertix isn't connected to any other vertix.

The default searching algorithm (and our favorite) is Best First Search which returns the shortest path between two vertices. That said, switching to another searching algorithm can be easily changed
# Authors
Idan bazel

Gal rouash
