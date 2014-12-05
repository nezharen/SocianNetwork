/*
*
* Graph.h
* Author: FU CHIN SENG
* Date of creation: 29/11/2013
* Declare the structure of Graph
*
*/


#ifndef GRAPH_H
#define GRAPH_H

#define MAX_N 2000
#define INFINITY_LEN 20.0
 
struct List
{
	int des;
	double dis;
	struct List * next;
};

struct ListHead
{
	int num;
	struct List * next;
};

typedef struct
{
	int n, m;
	struct ListHead head[MAX_N];
}Graph;

#endif
