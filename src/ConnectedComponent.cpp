/*
*
* ConnectedCompoent.cpp
* Author: FU CHIN SENG
* Date of creation: 4/12/2013
* Calculate connected component.
*
*/

#include "ConnectedComponent.h"
#include <stdlib.h>
#include <math.h>

void ConnectedComponent(Graph &G, int connected[], double t, int mode, int startIndex, Graph &Result)
{
	struct LNode
	{
		int pos;
		struct LNode * next;
	}*head, *tmp, *tail;
	struct List * current, * tmpList;

	head = new struct LNode;
	head->pos = startIndex;
	head->next = NULL;
	tail = head;

	while (head)
	{
		current = G.head[head->pos].next;
		while (current)
		{
			if (mode == 0)
			{
				if (connected[current->des] < 0 && (int) t < floor(current->dis))
				{
					tmp = new struct LNode;
					tmp->next = NULL;
					tmp->pos = current->des;
					tail->next = tmp;
					tail = tmp;
					connected[current->des] = connected[startIndex];
					tmpList = new struct List;
					tmpList->des = current->des;
					tmpList->dis = current->dis;
					tmpList->next = Result.head[head->pos].next;
					Result.head[head->pos].next = tmpList;
					Result.m++;
				}
			}
			else if (mode == 1)
			{
				if (connected[current->des] < 0 && t < current->dis - (double)floor(current->dis))
				{
					tmp = new struct LNode;
					tmp->next = NULL;
					tmp->pos = current->des;
					tail->next = tmp;
					tail = tmp;
					connected[current->des] = connected[startIndex];
					tmpList = new struct List;
					tmpList->des = current->des;
					tmpList->dis = current->dis;
					tmpList->next = Result.head[head->pos].next;
					Result.head[head->pos].next = tmpList;
					Result.m++;
				}
			}
			else
			{
				if (connected[current->des] < 0 && t < current->dis)
				{
					tmp = new struct LNode;
					tmp->next = NULL;
					tmp->pos = current->des;
					tail->next = tmp;
					tail = tmp;
					connected[current->des] = connected[startIndex];
					tmpList = new struct List;
					tmpList->des = current->des;
					tmpList->dis = current->dis;
					tmpList->next = Result.head[head->pos].next;
					Result.head[head->pos].next = tmpList;
					Result.m++;
				}
			}
			current = current->next;
		}
		head = head->next;
	}
}
