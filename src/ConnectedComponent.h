/*
*
* ConnectedComponent.h
* Author: FU CHIN SENG
* Date of creation: 4/12/2013
* Declare the function of connected component.
*
*/

#ifndef CONNECTEDCOMPONENT_H
#define CONNECTEDCOMPONENT_H

#include "Graph.h"

// Parameters:
//	G: the graph which is about to operate.
//	connected: the array of the connected part. Data presents the i-th connected part.
//	t: the value of the valve.
//	mode: the mode of t1, t2.
//	startIndex: the startIndex of every connected part.
void ConnectedComponent(Graph &G, int connected[], double t, int mode, int startIndex, Graph &Result);

#endif
