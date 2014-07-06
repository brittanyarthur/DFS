DFS
===

Using Depth First Search to find the strongly connected components in a digraph

Included:

Makefile, List.c, List.h, Graph.h, Graph.c, GraphTest.c, FindComponents.c

The main program FindComponents will do the following:
 Read the input file.
 Assemble a graph object G using newGraph() and addArc().
 Print the adjacency list representation of G to the output file.
 Run DFS on G and GT , processing the vertices in the second call by decreasing finish times from
the first call.
 Determine the strong components of G.
 Print the strong components of G to the output file in topologically sorted order.

FindComponents takes 2 command line arguments: an input file and an output file.

Here is an example of the input and output:
Input:
8
1 2
2 3
2 5
2 6
3 4
3 7
4 3
4 8
5 1
5 6
6 7
7 6
7 8
8 8
0 0

Output:
Adjacency list representation of G:
1: 2
2: 3 5 6
3: 4 7
4: 3 8
5: 1 6
6: 7
7: 6 8
8: 8

G contains 4 strongly connected components:
Component 1: 1 5 2
Component 2: 3 4
Component 3: 7 6
Component 4: 8
