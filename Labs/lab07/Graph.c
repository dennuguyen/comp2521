// Graph.c ... implementation of Graph ADT
// Written by John Shepherd, May 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Graph.h"
#include "Queue.h"

// graph representation (adjacency matrix)
typedef struct GraphRep
{
    int nV;      // #vertices
    int nE;      // #edges
    int **edges; // matrix of weights (0 == no edge)
} GraphRep;

// check validity of Vertex
int validV(Graph g, Vertex v)
{
    return (g != NULL && v >= 0 && v < g->nV);
}

// make an edge
static Edge mkEdge(Graph g, Vertex v, Vertex w)
{
    assert(g != NULL && validV(g, v) && validV(g, w));
    Edge new = {v, w}; // struct assignment
    return new;
}

// insert an Edge
// - sets (v,w) and (w,v)
void insertEdge(Graph g, Vertex v, Vertex w, int wt)
{
    assert(g != NULL && validV(g, v) && validV(g, w));

    if (g->edges[v][w] != 0 && g->edges[w][v] != 0)
        // an edge already exists; do nothing.
        return;

    g->edges[v][w] = wt;
    g->edges[w][v] = wt;
    g->nE++;
}

// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge(Graph g, Vertex v, Vertex w)
{
    assert(g != NULL && validV(g, v) && validV(g, w));
    if (g->edges[v][w] == 0 && g->edges[w][v] == 0)
        // an edge doesn't exist; do nothing.
        return;

    g->edges[v][w] = 0;
    g->edges[w][v] = 0;
    g->nE--;
}

// create an empty graph
Graph newGraph(int nV)
{
    assert(nV > 0);

    GraphRep *new = malloc(sizeof *new);
    assert(new != NULL);
    *new = (GraphRep){.nV = nV, .nE = 0};

    new->edges = calloc((size_t)nV, sizeof(int *));
    assert(new->edges != NULL);
    for (int v = 0; v < nV; v++)
    {
        new->edges[v] = calloc((size_t)nV, sizeof(int));
        assert(new->edges[v] != 0);
    }

    return new;
}

// free memory associated with graph
void dropGraph(Graph g)
{
    assert(g != NULL);
    for (int v = 0; v < g->nV; v++)
        free(g->edges[v]);
    free(g->edges);
    free(g);
}

// display graph, using names for vertices
void showGraph(Graph g, char **names)
{
    assert(g != NULL);
    printf("#vertices=%d, #edges=%d\n\n", g->nV, g->nE);
    int v, w;
    for (v = 0; v < g->nV; v++)
    {
        printf("%d %s\n", v, names[v]);
        for (w = 0; w < g->nV; w++)
        {
            if (g->edges[v][w])
            {
                printf("\t%s (%d)\n", names[w], g->edges[v][w]);
            }
        }
        printf("\n");
    }
}

// find a path between two vertices using breadth-first traversal
// only allow edges whose weight is less than "max"
int findPath(Graph g, Vertex src, Vertex dest, int max, int *path)
{
    assert(g != NULL);

    // cities are visited only once therefore leaving only one predecessor
    int *breadcrumbs = malloc(g->nV * sizeof(int));
    for (int i = 0; i < g->nV; i++)
        path[i] = breadcrumbs[i] = -1;

    Queue pq = newQueue(); // previous city queue
    Queue nq = newQueue(); // next city queue
    Queue wq = newQueue(); // weighting queue for number of trips
    QueueJoin(pq, src);
    QueueJoin(nq, src);
    QueueJoin(wq, 1);

    while (!QueueIsEmpty(nq))
    {
        Item p_city = QueueLeave(pq);
        Item n_city = QueueLeave(nq);
        Item n_trip = QueueLeave(wq);

        // if city is not in breadcrumb trail
        if (breadcrumbs[n_city] == -1)
        {
            breadcrumbs[n_city] = p_city;

            // arrived at destination
            if (n_city == dest)
            {
                // follow breadcrumbs back to src
                path[n_trip - 1] = dest;
                for (int i = n_trip - 2, b = dest; i >= 0; i--)
                    path[i] = b = breadcrumbs[b];
                dropQueue(pq);
                dropQueue(nq);
                dropQueue(wq);
                free(breadcrumbs);
                return n_trip; // return number of trips
            }

            // enqueue children cities from parent city if distance < max
            for (int i = 0; i < g->nV; i++)
                if (g->edges[n_city][i] < max)
                {
                    QueueJoin(pq, n_city);
                    QueueJoin(nq, i);
                    QueueJoin(wq, n_trip + 1);
                }
        }
    }

    dropQueue(pq);
    dropQueue(nq);
    dropQueue(wq);
    free(breadcrumbs);
    return 0; // could not find route
}
