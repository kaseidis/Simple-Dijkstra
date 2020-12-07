# Homework 6

## Author Name
Shenghua Chen

## Comments
### Infomation
All source shortest path problem by applying Dijkstra. Return 10 longest path.

### Performance Test Results
Time Complexity: O(|V|*(|E|+|V|log|V|))

- On graph 1
  -``Running Time: 0.113696``
- On graph 2
  -``Running Time: 351.158186``


### File List
Here is file list:
- ``main.c`` main function
- ``Dijkstra.c`` Dijkstra algorithm implementation
- ``Dijkstra.h`` Dijkstra algorithm interface
- ``PriorityQueue.c`` Priority queue implementation based on min heap
- ``PriorityQueue.h`` Priority queue interface
- ``Node.h`` Data structure for node in the priority queue.
- ``Graph.h`` Data structure for directed graph.
- ``Graph.c`` Implementation for acesss function for graph.
- ``timer.c`` provided file from class
- ``timer.h`` provided file from class
- ``Requirement.md`` Homework requirements.

## Instruction for compile
``make main`` will generate a executable file.

The excecutable can accept follwing argument:
```
main <Input File Path> <Output File Path> <Thread Count>
```
- `Input File Path` The input file of vertices data
- `Output File Path` The output file of longest 10 path
- `Thread Count` The thread count of the code.
- Example:
  - ``main graph1.txt result.out 12``

Running the program will display running time on screen at the end of execution.

## Reference
- University of Chicago, 2020 Autumn MPCS 51100 Advanced Programming class note.