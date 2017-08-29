# Dijkstras-Algorithm
Implementation of Dijkstra's algorithm using min heaps and adjacency matrix

Dijkstra Algorithm is a popular algorithm for finding the shortest path in graphs.
It takes a node (s) as starting node in the graph, and computes the shortest
paths to ALL the other nodes in the graph. The shortest path to (s) is assumed
to be 0(zero).

The algorithm works on both directed and undirected graphs, but assumes that all
the weights in the graph are non-negative.

It is not necessary that all the nodes may be reachable from (s). For
unreachable nodes, this program returns -1.

There are two separate files, one for directed graphs and another one for
undirected graphs. However, the change is a trivial one.

The algorithm is implemented using min-heaps, as suggested in the book.
Also, to represent the graph, adjacency matrix has been used and not adjacency
list.

Complete code is implemented using the pseudo-code provided in the book.

There are some issues with the pseudo-code, which I have fixed during the
implementation. For example:

The extract-min in the pseudo code, page 658 expects the node in the graph to be returned.
However, heap-extract-max (similar to heap-extract-min) pseudo code on page 163
returns the max(or min in this case) value, and NOT the node of the graph.

I hope the code helps the student community in learning both the heap sort
algorithm, heaps, and dijkstra's algorithm by looking at this code.

If there are any issues in the code, feel free to raise them.

PS: If you re-use this code in your application, please don't forget to provide
the reference to this project.

# References:
1. Introduction to Algorithms, Third Edition, Cormen, Leiserson, Rivest and
Stein
2. https://www.hackerrank.com/challenges/dijkstrashortreach
