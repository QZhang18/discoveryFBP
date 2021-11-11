#pragma once


#ifndef EDGE_H
#define	EDGE_H

#include <time.h>


class Edge
{
public:

	Edge(int index, int source, int dest, time_t dateTime) { _index = index; _source = source; _dest = dest; _time = dateTime; }
	int index() const { return _index; }
	int source() const { return _source; }
	int dest() const { return _dest; }
	time_t time() const { return _time; }
private:
	int _index, _source, _dest;
	time_t _time;
};

#endif	/* EDGE_H */