#pragma once

#ifndef DEGRESTRICTION_H
#define	DEGRESTRICTION_H

#include <string>


class DegRestriction
{
public:
	DegRestriction(const std::string &edgeType, bool isOutDeg, bool isLessThan, int value);
	const std::string &edgeType() const { return _edgeType; }
	bool isOutDeg() const { return _isOutDeg; }
	bool isLessThan() const { return _isLessThan; }
	int value() const { return _value; }
private:
	std::string _edgeType;
	int _value;
	bool _isOutDeg, _isLessThan;
};

#endif	/* DEGRESTRICTION_H */

