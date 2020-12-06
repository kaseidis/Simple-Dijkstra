#ifndef GRAPH_H
#define GRAPH_H

#include "stdlib.h"

/**
 * Data structure for edge (as linked list)
 */ 
typedef struct _edge
{
    size_t to;
    int weight;
    struct _edge* next;
} Edge;

/**
 * Data structure for graph
 */ 
typedef struct 
{
    Edge** graph;
    size_t n_node;
} Graph;

/**
 * Generate graph
 * @param nOfNode   Number of nodes.
 */ 
Graph init_graph(size_t nOfNode);

/**
 * Free all space used in graph
 */ 
void free_graph(Graph g);

/**
 * Get edges for node n in graph g
 * @param g     Graph
 * @param n     Index of node
 */ 
Edge* get_edges(Graph g, int n);

/**
 * Insert edge into graph
 * @param g         Graph
 * @param from      Index of node that the edge from
 * @param to        Index of node that the edge to
 * @param weight    Weight of the edge
 */ 
void insert_edge(Graph* g, size_t from, size_t to, int weight);

/**
 * Get edges for graph
 */ 
Edge* get_next(Edge* edges);

#endif