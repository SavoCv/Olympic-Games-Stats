#ifndef TEAM_INCLUDED
#define TEAM_INCLUDED

#include <vector>
#include <utility>
#include <set>
#include <map>
#include <regex>
#include <string>
#include "Competitor.h"
#include "AthletesInfo.h"
using namespace std;

class Team : public Competitor
{
	vector <int> ids;
	static std::set <Team> teams;
	Team(const string& t);
public:
	static const Team* insert(const string& t);
	bool operator<(const Team&) const;
	static std::set <Team>::iterator sbegin();
	static std::set <Team>::iterator send();
	vector <int>::const_iterator begin() const { return ids.begin(); }
	vector <int>::const_iterator end() const { return ids.end(); }
	virtual void insert_all(std::set <int>& s) const { s.insert(ids.begin(), ids.end()); }
	bool lower(const Team* t) const;
	friend ostream& operator<<(ostream& os, const Team& t);
};

#endif
