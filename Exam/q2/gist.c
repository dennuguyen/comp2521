// COMP2521 20T2 Final Exam Q2
// Check graph property

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Constants

#define MAXVERTICES 20
#define MAXLINE 100

// Directed graph as adjacency matrix
// The matrix is *not* symmetric
typedef struct _graph_rep
{
	int   nV;
	bool  edge[MAXVERTICES][MAXVERTICES];
} DiGraph;

// Helper functions
void readGraph(FILE *, DiGraph *);
bool graphIsBinTree(DiGraph);
void showGraph(FILE *, DiGraph);
void showGraphMatrix(FILE *out, DiGraph g);

int main(int argc, char **argv)
{
	DiGraph g;  // graph struct
	FILE *in;   // input file handle

	// handle command-line arguments
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s GraphFile\n", argv[0]);
		exit(1);
	}
	if ((in = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "Can't read %s\n", argv[1]);
		exit(1);
	}

	// main program
	readGraph(in, &g);
	// showGraphMatrix(stdout, g);
	showGraph(stdout, g);
	printf("\nGraph is ");
	if (!graphIsBinTree(g)) printf("not ");
	printf("a tree\n");

	// clean up
	return 0;
}

// graph is binary tree if incoming edges = 1, outgoing edges <= 2, has 1
// source node with no incoming edges, is spanning and every node is not
// visited twice.
//
// Test whether a graph is a binary tree
// It must satisfy the following conditions
// - only one node has no incoming edges
// - all other nodes have exactly one incoming edge
// - nodes may have 0, 1 or 2 outgoing edges
bool graphIsBinTree(DiGraph g)
{
	if (g.nV <= 0 || g.edge == NULL) // consider empty and invalid graph
		return false;

	if (g.nV == 1) // consider graph with single node
		return true;

	// initialise incoming array
	int incoming[g.nV];
	for (int i = 0; i < g.nV; i++)
		incoming[i] = 0;

	// count outgoing edges
	for (int i = 0; i < g.nV; i++)
		for (int j = 0, outgoing = 0; j < g.nV; j++)
		{
			if (g.edge[i][j] == true) // found an edge
			{
				outgoing++; // increment number of outgoing edges
				incoming[j]++; // increment node's number of incoming edges
			}
			if (outgoing > 2) // nodes cannot have more than 2 outgoing edges
				return false;
		}

	// count incoming edges
	int src = -1, n_src = 0;
	for (int i = 0; i < g.nV; i++)
	{
		if (incoming[i] > 1) // nodes cannot have more than 1 incoming edge
			return false;
		if (incoming[i] == 0) // found a src node
		{
			src = i; // update src node
			n_src++; // increment number of src nodes found
		}
	}
	if (n_src != 1) // binary trees can only have 1 src node
		return false;

	// By this point in the program, we know that we have 1 source node,
	// every other node has 1 incoming edge, and every node has <= 2 outgoing
	// edges. It can be extended that every node has been visited once and the
	// graph is spanning. But we did not consider disconnected cyclical cases.

	// initialise visited matrix and stack
	int top = 0;
	int stack[g.nV];
	bool visited[g.nV];
	for (int i = 0; i < g.nV; i++)
	{
		stack[i] = -1;
		visited[i] = false;
	}

	// visit src node
	stack[top++] = src;
	visited[src] = true;

	// traverse adjacency matrix from src
	while (top > 0) // while stack is not empty
	{
		int node = stack[--top]; // pop from stack
		for (int j = 0; j < g.nV; j++) // push child nodes onto stack
			if (g.edge[node][j] == true)
			{
				stack[top++] = j;
				visited[j] = true;
			}
	}

	// check for unvisited nodes
	for (int i = 0; i < g.nV; i++)
		if (visited[i] == false)
			return false;

	return true;
}

// Read Graph from "in" file
// Read into DiGraph struct referenced by "g"
void readGraph(FILE *in, DiGraph *g)
{
	char *c, line[MAXLINE];
	int  n, v, nV;
	bool first;

	for (int v = 0; v < MAXVERTICES; v++)
	{
		for (int w = 0; w < MAXVERTICES; w++)
			g->edge[v][w] = false;
	}
	nV = 0;
	while (fgets(line, MAXLINE, in) != NULL)
	{
		c = line; first = true;
		while (*c != '\0')
		{
			// find next number in line
			while (*c != '\0' && !isdigit(*c)) c++;
			if (*c == '\0') break;
			sscanf(c, "%d", &n);
			if (first)
			{
				v = n; first = false;
			}
			else
				g->edge[v][n] = true;
			// skip number we just scan'd
			while (*c != '\0' && isdigit(*c)) c++;
		}
		nV++;
	}
	g->nV = nV;
}

// Print graph info on output file "out"
void showGraph(FILE *out, DiGraph g)
{
	printf("V    Connected to\n");
	printf("--   ------------\n");
	int v, w;
	for (v = 0; v < g.nV; v++)
	{
		int nout = 0;
		printf("%-3d ", v);
		for (w = 0; w < g.nV; w++)
		{
			if (g.edge[v][w])
			{
				printf(" %d", w);
				nout++;
			}
		}
		if (nout == 0) printf(" -");
		printf("\n");
	}
}

void showGraphMatrix(FILE *out, DiGraph g)
{
	printf("\n");
	for (int i = 0; i < g.nV; i++)
	{
		for (int j = 0; j < g.nV; j++)
			printf("%d ", g.edge[i][j]);
		printf("\n");
	}
	printf("\n");
}
