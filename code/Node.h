#pragma once
#ifndef NODE_H
#define	NODE_H

#include <vector>

class Node
{
public:
	/** All edges from or to this node, in chronological order */
	std::vector<int> &edges() { return _edges; }
	/** Outgoing edges, in chronological order */
	std::vector<int> &outEdges() { return _outEdges; }
	/** Ingoing edges, in chronological order */
	std::vector<int> &inEdges() { return _inEdges; }
	/** All edges from or to this node, in chronological order */
	const std::vector<int> &edges() const { return _edges; }
	/** Outgoing edges, in chronological order */
	const std::vector<int> &outEdges() const { return _outEdges; }
	/** Ingoing edges, in chronological order */
	const std::vector<int> &inEdges() const { return _inEdges; }
private:
	std::vector<int> _edges, _outEdges, _inEdges;
};

#endif	/* NODE_H */