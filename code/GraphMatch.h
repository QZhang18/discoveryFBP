#pragma once


#ifndef GRAPHMATCH_H
#define	GRAPHMATCH_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "Edge.h"

/**
* Stores a list of edges and nodes in the original graph that matched a query graph.
*/
class GraphMatch
{
public:
	
	void addEdge(const Edge &gEdge, const Edge &hEdge);
	
	const std::vector<int> &edges() const { return _edges; }
	
	const std::vector<int> &nodes() const { return _nodes; }
	
	bool hasNode(int u) const;
	
	int getQueryEdge(int gEdge) const { return _gEdge2hEdgeMap.find(gEdge)->second; }
	
	int getQueryNode(int gNode) const { return _gNode2hNodeMap.find(gNode)->second; }
	
	void disp() const;
private:
	std::vector<int> _edges, _nodes;
	std::unordered_set<int> _nodeSet;
	std::unordered_map<int, int> _gEdge2hEdgeMap;
	std::unordered_map<int, int> _gNode2hNodeMap;
};

#endif	/* GRAPHMATCH_H */

