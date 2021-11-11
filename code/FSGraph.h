#pragma once
#ifndef FSGRAPH_H
#define FSGRAPH_H
#include "Graph.h"
#include "DFScode.h"
#include <vector>
using namespace std;

class FSGraph {
public:
	Graph5 g;
	DFScode gc;
	vector<int> supporter;
	bool isMaximal;
	void show();
	void saveToFile() {

	}
	FSGraph() {
		isMaximal = true;
	}
};

#endif
