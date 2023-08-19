#pragma once
#include <vector>
#include <set>
using namespace std;

class Competitor;

class Information
{
	mutable vector <const Competitor*> competitors;
public:
	virtual ~Information() = 0;
	void push_competitor(const Competitor* c) const;
	vector <const Competitor*>::iterator begin() const { return competitors.begin(); }
	vector <const Competitor*>::iterator end() const { return competitors.end(); }
	void insert_all(set <int>& a) const;
	void insert_all(set <const Competitor*>& s) const;
};

