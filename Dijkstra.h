
#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Graph.h"

typedef struct _dijkstra
{
    int dist;
    size_t parent;
} Dijkstra;


/**
 * Generate all point shortest map for start point
 * @param g         Graph
 * @param start     Start node
 * @param n_edge    Number of edges (assume as max path space)
 */ 
Dijkstra* dijkstra_search(Graph g, size_t start, size_t n_edge);

#endif