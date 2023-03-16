# Shortest Path Algorithms
Research work on faster shortest path algorithms done as a research assistant. Problem statement - `Can we do better than Dijkstra's?`. Contains implementations of binary heap, binomial heap, dijkstra's algorithm.

## Solution proposed
Compute a `nxn` reachability matrix as a preprocessing step, in order to prune nodes which are not accessible. Reduces the number of nodes inserted in the priority queue. Useful for `disconnected graphs`.
