using namespace std;
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <queue>
#include <random>
#include <stdint.h>
#include <stack>
#include "DataGraph.h"
#include "GraphSearch.h"
#include "GraphFilter.h"
#include "GraphExtension.h"
#include "FileIO.h"
#include "Children.h"
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <chrono>
#include <cfloat>
#include <sstream>
#include<functional>
#include<map>  
#include<time.h>
#include "FBP.h"







inline void constructDeTemoralGraph(string datagraphFile) {
	nodes.resize(cnt_node);
	node_label.resize(cnt_node);
	for (int i = 0; i < cnt_node; i++)
	{
		index[node_id[i]].push_back(i);
	}
	ifstream fin(datagraphFile);
	string line;
	string str1, str2, str3;
	string str4, str5;
	while (getline(fin, line)) {
		istringstream is(line);
		is >> str1 >> str2 >> str3 >> str4 >> str5;
		int count = 0;
		for (int i = 0; i < nodes[index[str2][0]].size(); i++)
		{
			if (index[str3][0] == nodes[index[str2][0]][i])
			{
				count++; break;
			}
		}
		if (count > 0) continue;
		nodes[index[str2][0]].push_back(index[str3][0]);
		nodes[index[str3][0]].push_back(index[str2][0]);
		if (node_label[index[str2][0]].size() == 0)
		{
			node_label[index[str2][0]].push_back(str4);
		}
		if (node_label[index[str3][0]].size() == 0)
		{
			node_label[index[str3][0]].push_back(str5);
		}
	}
	fin.close();
	/************************计算节点度的最大值***********************************************/
	degree_data = new int[cnt_node];
	int sum_degree = 0;
	MAX_DEGREE = 0;
	for (int i = 0; i < cnt_node; i++) {
		int degree = nodes[i].size();
		degree_data[i] = degree;
		sum_degree += degree;
		if (degree > MAX_DEGREE)
			MAX_DEGREE = degree;
	}
}



// Constructor with given graph database and minsup
//Runner::Runner(vector<Graph*>& db, int ms) {
//	graph_db = db;
//	graph_count = db.size();
//	minsup = ms;
//}
//
//vector<AdjMatrix> generateFrequentNodes() {
//	unordered_map<string, AdjMatrix> string_adj_matrix_map;
//		int graph_size =cnt_node;
//		for (int j = 0; j < graph_size; j++) {
//			string label = node_label[j][0];
//			AdjMatrix new_adj_matrix(1, 1);
//			new_adj_matrix.setElement(0, 0, label);
//			Embedding new_emb;
//			new_emb.setData({ j });
//
//			string matrix_code = new_adj_matrix.genCode();
//			// If same AdjMatrix is not in string_adj_matrix_map, add the new_adj_matrix to it
//			// If already in exists, insert the new embedding to existing AdjMatrix
//			if (string_adj_matrix_map.find(matrix_code) == string_adj_matrix_map.end()) {
//				string_adj_matrix_map[matrix_code] = new_adj_matrix;
//			}
//			string_adj_matrix_map[matrix_code].insertEmb(0, new_emb);
//		}
//	for (auto it = string_adj_matrix_map.begin(); it != string_adj_matrix_map.end(); it++) {
//		pair<string, AdjMatrix> item = *it;
//		if (item.second.getFrequency() >= burstiness*time_segment) {
//			freq_node_list.push_back(item.second);
//		}
//	}
//}
//
//
//
//vector<AdjMatrix> generateFrequentEdges() {
//	unordered_map<string, AdjMatrix> string_adj_matrix_map;
//		int graph_size = cnt_node;
//		for (int j = 0; j < graph_size; j++) {
//			GraphNode node_j;
//			for (auto it = node_j.adj_list.begin(); it != node_j.adj_list.end(); it++) {
//				pair<int, int> edge = *it;
//				int k = edge.first;
//				string node1_label = graph_db[0]->getNodeLabel(j);
//				string node2_label = graph_db->getNodeLabel(k);
//				string edge_label = intToStr(edge.second);
//				assert(edge_label != "0");
//				if (node1_label < node2_label) {
//					continue;
//				}
//				string code = node1_label + edge_label + node2_label;
//				Embedding new_emb;
//				new_emb.setData({ j, k });
//
//				if (string_adj_matrix_map.find(code) == string_adj_matrix_map.end()) {
//					AdjMatrix new_adj_matrix(2, graph_count);
//					new_adj_matrix.setElement(0, 0, node1_label);
//					new_adj_matrix.setElement(1, 1, node2_label);
//					new_adj_matrix.setElement(0, 1, edge_label);
//					string_adj_matrix_map[code] = new_adj_matrix;
//				}
//				string_adj_matrix_map[code].insertEmb(i, new_emb);
//			}
//		}
//	
//	vector<AdjMatrix> freq_edge_list;
//	for (auto it = string_adj_matrix_map.begin(); it != string_adj_matrix_map.end(); it++) {
//		pair<string, AdjMatrix> item = *it;
//		if (item.second.getFrequency() >= minsup) {
//			freq_edge_list.push_back(item.second);
//		}
//	}
//	freq_edges = freq_edge_list;
//	return freq_edge_list;
//}


inline void Result_List(string label1, string label2) {
	GraphSearch search1;
	result_list = new int[time2.size()];
	memset(result_list, 0, sizeof(int) * (time2.size()));
	set<int>::iterator it;
	int num = 0;
	for (it = time2.begin(); it != time2.end(); it++)
	{
		timestamp.push_back(*it);
		GraphFilter::filter(g, *it, *it, g2);//求当前时刻的快照
		vector<GraphMatch> results = search1.findOrderedSubgraphs(g2, p, criteria, limit, delta);
		result_list[num] = results.size();
		num++;
	}
}





inline void initializeTimeSegment(string label1, string label2) {
	CSC = new int[time2.size() + 1];
	vector<vector<float> > MTS;
	//CSC = (int *)malloc((fre_counts.size()+1) * sizeof(int));
	MTS.resize(time2.size());
	CSC[0] = 0;
	int sum = 0;
	int count = 0;
	for (int i = 0; i < time2.size(); i++)
	{
		sum += result_list[i];//计算每一时刻的累加匹配数目
		CSC[++count] = sum;
	}
	int L = time_segment;
	//int L1 = 0;

	if (time2.size() >L)
	{
		/*for (int i = 0; i < fre_counts.size(); i++)
		{
		if (time_edge1[i] - time_edge1[0] >= time_interval)
		{
		L1 = i; break;
		}
		}
		for (int i = 0; i < fre_counts.size(); i++)
		{
		if (time_edge1[fre_counts.size() - 1] - time_edge1[i]+1 >= time_interval&&time_edge1[fre_counts.size() - 1] - time_edge1[i + 1]+1<time_interval)
		{
		L = i; break;
		}
		}*/
		int is = 0, ie = -1;
		int *CH = new int[time2.size() - L + 1];

		for (int t = L; t <time2.size(); t++)
		{
			if (ie >= 0 && CH[ie - 1] >= 0)
			{
				int slope1 = (CSC[t - L] - CSC[CH[ie]]) / (t - L - CH[ie]);
				int slope2 = (CSC[CH[ie]] - CSC[CH[ie - 1]]) / (CH[ie] - CH[ie - 1]);
				while (is<ie &&slope1 <= slope2)
				{
					ie = ie - 1;
				}

			}
			CH[++ie] = t - L;
			if (CH[is + 1] >= 0) {
				int slope3 = (CSC[t] - CSC[CH[is]]) / (t - CH[is]);
				int slope4 = (CSC[CH[is + 1]] - CSC[CH[is]]) / (CH[is + 1] - CH[is]);
				while (is<ie&&slope3 >= slope4)
				{
					is = is + 1;
				}
			}
			MTS[t].push_back(CH[is]);//开始时间
			MTS[t].push_back(t - 1);//结束时间
			MTS[t].push_back((CSC[t] - CSC[CH[is]]) / (t - CH[is]));//当前的最大值
		}
		/*****计算最大的平均匹配数目********/
		MTS_count.clear();
		for (int i = 0; i < L; i++)
		{
			MTS_count.push_back(0);
		}
		for (int i = L; i < time2.size(); i++)
		{
			MTS_count.push_back(MTS[i][2]);
		}

		//vector<int>::iterator biggest = max_element(MTS_count.begin(), MTS_count.end());
		////stringstream ss1,ss2;
		////ss1 << label1;
		////ss2 << label2;
		//string code = label1 + "+" + label2;

		//freq_edges1.push_back(code);
		//int p = distance(MTS_count.begin(), biggest);
		//cout << "edge: " << code << " start time: " << MTS[p][0] << " end time: " << MTS[p][1] << " max value: " << MTS[p][2] << endl;
		//freq_edges[code].push_back(label1);
		//freq_edges[code].push_back(label2);
		//MTS_count.clear();
		//findBurstPattern(label1, label2, MTS[p][0], MTS[p][1]);//对于每一个的初始化（t_s,T）求优化的pattern graph
	}
}

void subGraphMining(FSGraph &subGraph,int t1,int t2) {
	//cout<<gc[0].fromLabel<<" "<<gc[0].eLabel<<" "<<gc[0].toLabel<<" "<<gc.supporter.size()<<endl;
	//return;
	subGraph.g = subGraph.gc.toGraph(subGraph.g);
	if (!subGraph.gc.isMin(subGraph.g))
		return;

	if (resultSet.size() > 0) {
		if (subGraph.gc.size() > resultSet.back().gc.size())
			resultSet.back().isMaximal = false;
		else
			resultSet.back().isMaximal = true;
	}
	//加入结果集
	resultSet.push_back(subGraph);
	//subGraph = resultSet.back();
	map<Edge5, vector<int>> summary;

	//挖掘子代
	for (int i = 0; i < subGraph.supporter.size(); i++) {
		//获得一个支持者
		GraphFilter::filter(g, timestamp[t1], timestamp[t2], g2);

		Children c(g2, subGraph.gc, ef);
		c.getChildren();
		//获得一个子代
		set<Edge5>::iterator itr;
		for (itr = c.begin(); itr != c.end(); itr++) {
			const Edge5 &child = *itr;
			
			summary[child].push_back(subGraph.supporter[i]);
		}

	}
	map<Edge5, vector<int>>::iterator itr;

	for (itr = summary.begin(); itr != summary.end(); itr++) {

		if (itr->second.size() / (t2 - t1) < burstiness);
			continue;
		FSGraph childGraph;
		childGraph.gc = subGraph.gc;
		childGraph.gc.push_back(itr->first);//添加增长的边
											//childGraph.gc = child_gc;
		childGraph.supporter = (itr->second);//添加支持者
		subGraphMining(childGraph,t1,t2);//子代挖掘
	}
	//if(pre_size == resultSet.size())//没有子代增长，所以是极大的！
	//	subGraph.isMaximal = false;
}


inline void smoothLocal(vector<int>l, vector<int>u, int h, int t, bool maxima) {
	l[h] = t;
	double epn = maxima ? MS[l[h]] : -MS[l[h]];
	double xi = exp(epn) * localAvgChange[l[h]];
	if (xi >= 3 * avgChange) xi = 3 * avgChange;
	while (l[h] > 0 &&abs(MS[l[h] - 1] - MS[l[h]]) < xi) {
		l[h]--;
		//epn = maxima ? Math.max(cden[l[h]], 0) : Math.max(-cden[l[h]], 0);
		epn = maxima ? MS[l[h]] : -MS[l[h]];
		xi = exp(epn) * localAvgChange[l[h]];
		if (xi >= 3 * avgChange) xi = 3 * avgChange;
		if (h > 0 && l[h] == u[h - 1]) break;
	}
	u[h] = t;
	//epn = maxima ? Math.max(cden[u[h]], 0) : Math.max(-cden[u[h]], 0);
	epn = maxima ? MS[u[h]] : -MS[u[h]];
	xi = exp(epn) * localAvgChange[u[h]];
	if (xi >= 3 * avgChange) xi = 3 * avgChange;
	while (u[h] < time2.size() - 1 && abs(MS[u[h] + 1] - MS[u[h]]) < xi) {
		u[h]++;
		//epn = maxima ? Math.max(cden[u[h]], 0) : Math.max(-cden[u[h]], 0);
		epn = maxima ? MS[u[h]] : -MS[u[h]];
		xi = exp(epn) * localAvgChange[u[h]];
		if (xi >= 3 * avgChange) xi = 3 * avgChange;
	}
}



inline void doIntervalSelect(DataGraph p, int t1, int t2) {
	
	int T = time2.size();
	GraphSearch search3;
	for (int i = 0; i < time2.size(); i++)
	{
		if (t1- delta<0)
		{
			GraphFilter::filter(g, timestamp[0], timestamp[i+ delta], g2);
		}
		else
		{
			GraphFilter::filter(g, timestamp[i - delta], timestamp[i + delta], g2);
		}


		//====================================================sampling====================================================
		//
		int seeds[10] = { 5,10,15,20,25,30,35,40,45,50 };
		for (int jj = 0; jj < 10; jj++)
		{
			int seed_p = seeds[jj];
			double rn;
			vector<long> ids;
			default_random_engine e(seed_p);
			uniform_real_distribution<double> u(0.0, 1.0);
			for (long i = 0; i < g2.dispEdge; i++)
			{
				rn = u(e);
				//cout<<rn<<endl;
				if (rn <= pp) {
					/*if(G.edges_[i].tim==1197014240)
					{*/
					//cout<<i<<" ";
					ids.push_back(i);
				}
			}
			cout << "number of sampling:" << ids.size() << endl;
		    vector<GraphMatch> results = search3.findOrderedSubgraphs(g2, p, criteria, limit, delta);
			MS.push_back(results.size());
		}
	}
	double xi = 1.0;
	avgChange = 0;
	for (int i = 0; i < time2.size()-1; i++)
	{
		avgChange += abs(MS[i + 1] - MS[i]);
	}
	if (time2.size()>1)
	{
		avgChange /= (time2.size() - 1);
	}
	xiSmooth = avgChange * xi;
	if (time2.size()>5)
	{
		localAvgChange[1] = localAvgChange[0]
			= (abs(MS[1] - MS[0])
				+ abs(MS[2] - MS[1])
				+ abs(MS[3] - MS[2])
				+ abs(MS[4] - MS[3])) / 4;
		for (int i = 2; i < time2.size()-2; i++)
		{
			localAvgChange[i] = (abs(MS[i] - MS[i - 1])
				+ abs(MS[i - 1] - MS[i - 2])
				+ abs(MS[i] - MS[i + 1])
				+ abs(MS[i + 1] - MS[i + 2])) / 4;
		}
		localAvgChange[T - 2] = localAvgChange[T - 1]
			= (abs(MS[T - 1] - MS[T - 2])
				+ abs(MS[T - 2] - MS[T - 3])
				+ abs(MS[T - 3] - MS[T - 4])
				+ abs(MS[T - 4] - MS[T - 5])) / 4;
		for (int i = 0; i < T; i++) {
			if (localAvgChange[i] > avgChange)
				localAvgChange[i] = avgChange;
		}
	}
	//计算local maximal 在近似的支持度曲线上
	for (int i = 0; i < MS.size(); i++)
	{
		int num = 0;
		for (int j = 1; j <=r; j++)
		{
			if (i-j<0)
			{
				if (MS[i+r]<MS[i])
				{
					num++;
				}
			}
			else
			{
				if (MS[i - r]<MS[i]&&MS[i + r]<MS[i])
				{
					num++;
				}
			}
		}
		if (num==r)
		{
			localmaxima.push_back(i);
		}
	}
	// 根据local maxima 来选择时间间隔候选集
	vector<int>l;	// lower sides of maximums
	vector<int>u;	// upper sides of maximums
	int h = 0;
	for (int i = 0; i < T; i++) {
		if ((i - 4 < 0 || MS[i] > MS[i - 4])
			&& (i - 3 < 0 || MS[i] > MS[i - 3])
			&& (i - 2 < 0 || MS[i] > MS[i - 2])
			&& (i - 1 < 0 || MS[i] > MS[i - 1])
			&& (i + 1 >= T || MS[i] > MS[i + 1])
			&& (i + 2 >= T || MS[i] > MS[i + 2])
			&& (i + 3 >= T || MS[i] > MS[i + 3])
			&& (i + 4 >= T || MS[i] > MS[i + 4])) {
			smoothLocal(l, u, h, i, true);
			h++;
		}
	}
	for (int i = 0; i < h; i++)
	{
		for (int j = i+1; j < h; j++)
		{
			if (u[i] <= l[j]) {
				for (int step = 1; step < h; step++)
				{
					for (int start = 0; start < h-step; start++)
					{
						int left = u[start], right = l[start + step];
						if (left > right) continue;
						GraphFilter::filter(g,left, right, g2);
						vector<GraphMatch> results = search3.findOrderedSubgraphs(g2, p, criteria, limit, delta);
						double pcd = results.size() / (right - left);
						optimal_timeinterval.push_back(pcd);
					}
				}
			}
		}
	}
}






inline void miningFBP(string label1, string label2) {
	
	for (int i = time_segment; i < time2.size(); i++)
	{
		if (MTS_count[i]>= burstiness)
		{
			for (int j = 0; j < i- time_segment; j++)
			{
				Edge5 e(0, 1, label1, 0,label2);
				DFScode gc;
				FSGraph subGraph;
				subGraph.gc = gc;
				int temp = resultSet.size();
				subGraphMining(subGraph,j,i);//仅仅在当前快照内由一条边频繁增长图挖掘
				doIntervalSelect(p, j, i);//用来选择optimal time interval 
				for (int i = 0; i < optimal_timeinterval.size(); i++)
				{
					MAXinterval.insert(optimal_timeinterval[i]);
				}
				if (*MAXinterval.rbegin()>=max_pattern_value)
				{
					break;
				}
				else
				{
					cout << "Find an FBP:" << p.dispEdge << endl;
				}
			}
		}
	}

}





inline void initializePattern() {
	GraphSearch search;
	

	for (int i = 0; i < cnt_node; i++)
	{
		for (int j = 0; j < nodes[i].size; j++)
		{
			string label1 = node_label[i][0];
			string label2 = node_label[nodes[i][j]][0];
			/*Graph1 p(2);
			p.labels.push_back(label1);
			p.labels.push_back(label2);
			universal_labels = p.labels;
			Edge1 e(i, nodes[i][j], "0");
			p.edges.push_back(e);
			universal_edges = p.edges;*/
			Attributes a;
			a.addStringValue("0");
			p.addEdge(node_label[i][0], node_label[i][0],0,a);
			vector<GraphMatch> results = search.findOrderedSubgraphs(g, p, criteria, limit, delta);
			if (results.size()>= burstiness*time_segment)
			{
				Result_List(label1, label2);
				initializeTimeSegment(label1, label2);
				miningFBP(label1, label2);
			}
		}
		
	}
}







int main(int argc, char *argv[]) {
	datagraphFile = argv[1]; 
	string option = argv[2];
	bool output = false;

	if (option == "-f")
		output = false;
	else if (option == "-fo")
		output = true;
	else {
		cerr << "Please enter the correct parameter!" << endl;
		return 0;
	}
	burstiness = stoi(argv[3]);  //paramater burstiness threshold 
	pattern_size= stoi(argv[4]);
	time_segment = stoi(argv[5]);
	k= stoi(argv[6]);
	cout << "Loading data graph from " << datagraphFile<< endl;
	 g = FileIO::loadGenericGDF(datagraphFile);
	cout << g.nodes().size() << " nodes, " << g.edges().size() << " edges" << endl;
	cnt_node = g.nodes().size();
	constructDeTemoralGraph(datagraphFile);
	g2.setNodeAttributesDef(g.nodeAttributesDef());
	g2.setEdgeAttributesDef(g.edgeAttributesDef());//用来计算每一时刻的图快照和范围查询
	initializePattern();//计算种子边并进行子图扩展
}