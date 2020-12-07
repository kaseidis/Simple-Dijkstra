#include <stdio.h>
#include "Dijkstra.h"
#include "Graph.h"
#include "timer.h"

//start vertex 1, end vertex 1, distance 1
typedef struct _result
{
    int start, end;
    int dist;
} Result;

// Comparer for results.
int results_compar(const void *a, const void *b)
{
    Result *ra, *rb;
    ra = (Result *)a;
    rb = (Result *)b;
    if (ra->dist == rb->dist)
    {
        if (ra->start == rb->start)
            return ra->end - rb->end;
        return ra->start - rb->start;
    }
    return ra->dist - rb->dist;
}

// Code for reduction
typedef struct _results
{
    Result results[10];
} Results;

Results resultsMax(Results a, Results b)
{
    Results newR;
    int ia = 9;
    int ib = 9;
    for (int i = 9; i >= 0; --i)
    {
        if (ia >= 0 && results_compar(&(a.results[ia]), &(b.results[ib])) > 0)
        {
            newR.results[i] = a.results[ia];
            --ia;
        }
        else if (ib >= 0)
        {
            newR.results[i] = b.results[ib];
            --ib;
        }
    }
    return newR;
}

int main(int argc, char **argv)
{
    /* Read Argument Open File */
    FILE *file;
    int thread;
    if (argc > 3)
    {
        file = fopen(argv[1], "r");
        if (file == NULL)
        {
            printf("Error Opening File\n");
            return -2;
        }
        sscanf(argv[3], "%d", &thread);
    }
    else
    {
        printf("Wrong numger of arguments\n");
        printf("\tUsage: %s <Input File Path> <Output File Path> <num_threads>\n", argv[0]);
        return -1;
    }

    /* Read Graph */
    int nodes, edges;
    while (!feof(file))
    {
        char line[100];
        fgets(line, 100, file);
        if (line[0] == '#')
            continue;
        sscanf(line, "%d %d", &nodes, &edges);
        break;
    }

    Graph g = init_graph(nodes);
    for (int i = 0; i < edges; ++i)
    {
        int from, to, weight;
        fscanf(file, "%d %d %d", &from, &to, &weight);
        insert_edge(&g, from, to, weight);
    }
    fclose(file);

    /* Max 10 Results */
    Results rs;
    for (int i = 0; i < 10; ++i)
    {
        rs.results[i].start = 0;
        rs.results[i].end = 0;
        rs.results[i].dist = 0;
    }

#pragma omp declare reduction(myMax:Results   \
                             : omp_out= \
                             resultsMax(omp_out, omp_in))
    StartTimer();

    /* Search */
#pragma omp parallel for schedule(dynamic) num_threads(thread) \
                        reduction(myMax: rs)
    for (int i = 0; i < nodes; ++i)
    {
        Dijkstra *map = dijkstra_search(g, i, edges);
        Result r;
        r.start = i;
        for (r.end = 0; r.end < nodes; ++(r.end))
        {
            if (map[r.end].dist > rs.results[0].dist)
            {
                r.dist = map[r.end].dist;
                rs.results[0] = r;
                qsort(rs.results, 10, sizeof(Result), &results_compar);
            }
        }
        // Since is dynamic scheduling, the i could be a estimate
        if (i % 1000 == 0)
            printf("%d/%d\n", i, nodes);
        free(map);
    }
    printf("%d/%d\n", nodes, nodes);
    double time = GetTimer() / 1000.0;

    /* Print Results */
    FILE *output = fopen(argv[2], "w");
    for (int i = 0; i < 10; ++i)
    {
        if (rs.results[i].start != rs.results[i].end)
        {
            fprintf(output, "start vertex %d, end vertex %d, distance %d\n",
                    rs.results[i].start,
                    rs.results[i].end,
                    rs.results[i].dist);
        }
    }

    fclose(output);

#define START rs.results[9].start
#define END rs.results[9].end

    // #define START 644
    // #define END 6172

    /* Print longest path */
    Dijkstra *map = dijkstra_search(g, START, edges);
    printf("Longest Path (from %d to %d): \n", START, END);
    size_t v = END;
    while (v != START)
    {
        size_t lastV = v;
        v = map[v].parent;
        int distDiff = map[lastV].dist - map[v].dist;
        printf("\t%d==%d==>%d\n", (int)v, distDiff, (int)lastV);
    }
    printf("Running Time: %f\n", time);

    /* Free Mem */
    free(map);
    free_graph(g);
}