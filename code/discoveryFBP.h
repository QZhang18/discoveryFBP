#pragma once
#include "DFScode.h"
#include "Edge5.h"
#include "Graph.h"
#include "FrequentSubGraphSet.h"
#include "FSGraph.h"
#include <set>
string datagraphFile;
DataGraph g;
DataGraph g2;
DataGraph p;
MatchCriteria_DataGraph criteria;
set<int>time2;
set<double>MAXinterval;
int cnt_node;
int max_pattern_value;
int *result_list;
vector<vector<int>>nodes;
vector<vector<string> > node_label;//节点的标签
map<string, vector<int> > index;
vector<string >node_id;
vector<int>timestamp;
vector<int>localmaxima;
vector<int>MS;
int * degree_data;
int *CSC = NULL;
int MAX_DEGREE;
int limit = INT_MAX; // No limit
vector<int >MTS_count;
string intToStr(int num);
EdgeFrequency ef;
double avgChange, xiSmooth;
vector<double> localAvgChange;
vector<double> optimal_timeinterval;
/***********************实验中用到的参数*******************************************/
int burstiness;
int  delta=2;
int time_segment;
int pattern_size;
int pp = 0.1;
int h = 4;
int r = 3;
int k
/**********************************************************************/





class EdgeFrequency {
public:
	int *dynamicArray;
	int x, y, z;
	int min_sup;
public:
	void init(int node_label_size, int edge_label_size, int _min_sup);
	int& operator()(int fromLabel, int eLabel, int toLabel);

	~EdgeFrequency() {
		delete[] dynamicArray;
	}

};


int &EdgeFrequency::operator()(int fromLabel, int eLabel, int toLabel) {
	return dynamicArray[fromLabel*y*z + eLabel*z + toLabel];
}
void EdgeFrequency::init(int node_label_size, int edge_label_size, int _min_sup) {
	min_sup = _min_sup;
	x = node_label_size;
	y = edge_label_size;
	z = node_label_size;
	dynamicArray = new int[x*y*z];
}










class GraphData {

public:
	vector<int> newId;//为reLabel后的节点赋予新的id
	vector<int> vertexLabel;//节点标签
	vector<bool> vertexMask;//节点掩码
	vector<int> from;//边的from顶点
	vector<int> to;//边的to顶点
	vector<int> edgeLabel;//边标签
	vector<bool> edgeMask;//边掩码

	Graph5& buildGraph(Graph5 &g);
};

Graph5 &GraphData::buildGraph(Graph5 &g) {
	for (size_t i = 0; i < vertexLabel.size(); i++) {
		if (vertexMask[i] == true) {
			g.addVertex(vertexLabel[i]);
		}
	}
	for (size_t j = 0; j < edgeLabel.size(); j++) {
		if (edgeMask[j] == true) {
			g.addEdge(from[j], to[j], edgeLabel[j]);
		}
	}
	return g;
}



class GraphDataSet :public vector<GraphData> {
public:

	int vertex_label_size;
	int edge_label_size;
	vector<int> nodeLabelRecover;
	vector<int> edgeLabelRecover;

	//从文件读取数据
	void readFromFile(ifstream &in);
	void reLabel(double min_sup_rate);


private:
	//用于统计频率
	int min_sup;
	vector<int>eLabels;
	vector<int>vLabels;

};

class LabelInfo {
public:
	int label;
	int frequency;
	int order;
	bool mask;

	LabelInfo(int l, int f, int o);
	bool operator<(LabelInfo &b);
	static bool compareByLabel(const LabelInfo &a, const LabelInfo &b);
};

class LabelInfoSet :public vector<LabelInfo> {
public:
	LabelInfoSet(vector<int> &labels);
	int setOrder();

	void filter(int min_sup);

};



FrequentSubGraphSet resultSet;//频繁子图结果集



class MatchCriteria
{
public:
	
	virtual bool isEdgeMatch(const Graph &g, int gEdgeIndex, const Graph &h, int hEdgeIndex) const;


	virtual bool isNodeMatch(const Graph &g, int gNodeIndex, const Graph &h, int hNodeIndex) const;
};

class MatchCriteria_DataGraph : public MatchCriteria
{
public:
	
	virtual bool isEdgeMatch(const Graph &g, int gEdgeIndex, const Graph &h, int hEdgeIndex) const override;

	
	virtual bool isNodeMatch(const Graph &g, int gNodeIndex, const Graph &h, int hNodeIndex) const override;

	/**
	* Returns true if the attributes match.
	*/
	virtual bool doAttributesMatch(const Attributes &a1, const Attributes &a2) const;
};

