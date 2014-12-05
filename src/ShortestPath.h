/*
*
* ShortestPath.h
* Author: FU CHIN SENG
* Date of creation: 29/11/2013
* Declare the function of shortest path
*
*/


#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include "Graph.h"

// Parameters:
//	startIndex: the startIndex of the node.
//	path: the «eÅX the every node.
//	d: the shortest distance of the startNode to every node.
//	G: the graph to opearate.
void ShortestPath(int startIndex, int path[], Graph &G);

#endif
