#pragma once
#ifndef CHILDREN_H
#define CHILDREN_H

#include <set>
#include <vector>
#include <assert.h>
#include "Edge5.h"
#include "Graph.h"
#include "DFScode.h"
#include "FBP.h"

using namespace std;

class Children :public set<Edge5> {
public:
	DataGraph &g;
	DFScode &gc;

	Children(DataGraph &_g, DFScode &_gc, EdgeFrequency &_ef) :g(_g), gc(_gc), ef(_ef) {

	}

	void getChildren();

	void DFS(int current);

private:
	vector<int> graph2code;
	vector<int> code2graph;
	vector<vector<bool>> edgeVisited;
	vector<int> rmPath;
	EdgeFrequency &ef;

};

#endif
