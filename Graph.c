#include "Graph.h"

Graph init_graph(size_t n_node) {
    Graph g;
    // Store nodes number
    g.n_node = n_node;
    // Set up array of linked list of edges
    g.graph = malloc(n_node*sizeof(Edge*));
    for (size_t i=0; i<n_node; ++i) {
        g.graph[i]=NULL;
    }

    return g;
}

void free_graph(Graph g) {
    // Free linked lists
    for (size_t i=0; i<g.n_node; ++i) {
        Edge* edges = get_edges(g,i);
        while (edges!=NULL) {
            Edge* oldEdge = edges;
            edges = get_next(edges);
            free(oldEdge);
        }
    }
    // Free array stores linked list
    free(g.graph);
}

Edge* get_edges(Graph g, int n) {
    if (n>=g.n_node)
        return NULL;
    return g.graph[n];
}

void insert_edge(Graph* g, size_t from, size_t to, int weight) {
    // cosntruct new edge to linked list at space [from]
    if (from>=g->n_node || to>=g->n_node)
        return;
    Edge* newEdge = malloc(sizeof(Edge));
    newEdge->to = to;
    newEdge->next = g->graph[from];
    newEdge->weight = weight;
    g->graph[from]=newEdge;
}


Edge* get_next(Edge* edges) {
    if (edges==NULL)
        return edges;
    return edges->next;
}