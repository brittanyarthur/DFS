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

There is an example of the input file and resulting output file in this repository, titled Example Input & Output
