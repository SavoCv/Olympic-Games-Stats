#ifndef ATHLETE_INCLUDED
#define ATHLETE_INCLUDED

#include <vector>
#include <utility>
#include <set>
#include <map>
#include <regex>
#include <string>
#include "Competitor.h"
#include "AthletesInfo.h"
using namespace std;

class Athlete : public Competitor
{
	int id;
	static std::set <Athlete> athletes;
	Athlete(int i);
public:
	static const Athlete* insert(const string& a);
	bool operator<(const Athlete&) const;
	static std::set <Athlete>::iterator sbegin();
	static std::set <Athlete>::iterator send();
	int getId() const { return id; }
	virtual void insert_all(std::set <int>& s) const { s.insert(id); }
};

#endif