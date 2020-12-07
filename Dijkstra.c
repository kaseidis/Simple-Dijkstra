#include "Dijkstra.h"
#include "PriorityQueue.h"
#include <limits.h>

Dijkstra *dijkstra_search(Graph g, size_t start, size_t n_edge)
{
    // Init priority queue
    Dijkstra *map = malloc(sizeof(Dijkstra) * g.n_node);
    char *processed = malloc(sizeof(char) * g.n_node);
    for (size_t i = 0; i < g.n_node; ++i)
    {
        processed[i] = 0;
        map[i].dist = -1;
        map[i].parent = 0;
    }
    PriorityQueue q = init_queue(n_edge);

    Node n;
    size_t v;

    // Start search, push start node to priority queue
    map[start].dist = 0;
    map[start].parent = start;
    n.node = start;
    n.dist = 0;
    push_element(&q, n);

    // Main search loop
    while (!is_empty(q))
    {
        // Check if curent pop element processed
        n = pop_element(&q);
        while (!is_empty(q) && processed[n.node])
            n = pop_element(&q);
        v = n.node;
        if (processed[v])
            break;

        // Set current node as processed node
        processed[v] = 1;

        // Search all edges from the node
        Edge *e = get_edges(g, v);
        while (e != NULL)
        {
            // Construct node
            n.node = e->to;
            n.dist = map[v].dist + (e->weight);

            if (map[n.node].dist > n.dist || map[n.node].dist == -1)
            {
                map[n.node].dist = n.dist;
                map[n.node].parent = v;
                if (!processed[n.node])
                    push_element(&q, n);
            }
            if (!processed[n.node])
                push_element(&q, n);
            // Get next edge
            e = get_next(e);
        }
    }

    // Free all located space except distance (which should be returned)
    free(processed);
    free_queue(q);

    // Return distance
    return map;
}