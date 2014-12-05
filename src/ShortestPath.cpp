/*
*
* ShortestPath.cpp
* Author: FU CHIN SENG
* Date of creation: 29/11/2013
* Calculate the shortest path 
*
*/


#include "ShortestPath.h"
#include "Graph.h"
#include <stdlib.h>

void ShortestPath(int startIndex, int path[], Graph &G)
{
	struct LNode
	{
		int pos;
		struct LNode * next;
	}*head, *tmp, *tail;
	struct List * current;

	head = new struct LNode;
	head->next = NULL;
	head->pos = startIndex;
	tail = head;

	while (head)
	{
		current = G.head[head->pos].next;
		while (current)
		{
			if (current->des != startIndex && path[current->des] == -1)
			{
				path[current->des] = head->pos;
				tmp = new struct LNode;
				tmp->next = NULL;
				tmp->pos = current->des;
				tail->next = tmp;
				tail = tmp;
			}
			current = current->next;
		}
		head = head->next;
	}
}
