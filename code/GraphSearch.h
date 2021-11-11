#pragma once
#ifndef GRAPHSEARCH_H
#define	GRAPHSEARCH_H

#include "temporal.h"
#include "FBP.h"
#include <limits.h>
#include <vector>
#include <stack>
#include <unordered_set>
#include "GraphMatch.h"

/**
* Main class for performing subgraph searches.
*/
class GraphSearch
{
public:

	std::vector<GraphMatch> findOrderedSubgraphs(const Graph &g, const Graph &h, int limit = INT_MAX, int delta = INT_MAX);


	std::vector<GraphMatch> findOrderedSubgraphs(const Graph &g, const Graph &h, const MatchCriteria &criteria, int limit = INT_MAX, int delta = INT_MAX);

	
	std::vector<GraphMatch> findAllSubgraphs(const Graph &g, const Graph &h, int limit = INT_MAX);


	std::vector<GraphMatch> findAllSubgraphs(const Graph &g, const Graph &h, const MatchCriteria &criteria, int limit = INT_MAX);

private:

	/** Creates map of which nodes in G can map to the nodes we are searching for from H */
	std::vector<std::unordered_set<int>> mapPossibleNodes();

	/** Performs recursive unordered graph search, stopping at first matching subgraph */
	bool search(int &numAssigned, std::vector<std::unordered_set<int>> &h2gPossible);

	/** Performs recursive unordered graph search, storing each matching subgraph in results */
	bool search(int &numAssigned, std::vector<std::unordered_set<int>> &h2gPossible, std::vector<GraphMatch> &results);

	/** Returns true if the number assigned all match up with the appropriate edges */
	bool matchesSoFar(int numAssigned);


	int findNextMatch(int h_i, int startIndex);


	int findNextMatch(int h_i, const std::vector<int> &edgesToSearch, int startIndex);

	
	int findStart(int g_i, const std::vector<int> &edgeIndexes);

	/** Converts the given stack into a vector, without modifying it */
	std::vector<int> convert(std::stack<int> s);

	/** Converts the given stack and final edge to a GraphMatch object,
	without modifying the stack. */
	GraphMatch convert(const std::stack<int> &s, int g_lastEdge);

	// Private data members
	const Graph *_g, *_h;
	const MatchCriteria *_criteria;
	int _delta;
	time_t _firstEdgeTime;
	std::vector<int> _h2gNodes, _g2hNodes;
	std::vector<int> _numSearchEdgesForNode;
	std::stack<int> _sg_edgeStack; //, _h_edgeStack;
	std::vector<int> _allEdges;
};

#endif	/* GRAPHSEARCH_H */