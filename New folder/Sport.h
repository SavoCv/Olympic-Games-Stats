#ifndef SPORT_INCLUDED
#define SPORT_INCLUDED

#include <vector>
#include <utility>
#include <set>
#include <map>
#include <regex>
#include <string>
using namespace std;

class Event;

class Sport
{
public:
	static const Sport* insert(const string& n);
	static const Sport* find(const string& n);
	bool operator<(const Sport&) const;
	void push_event(const Event* e) const;
	vector <const Event*>::iterator begin() const { return events.begin(); }
	vector <const Event*>::iterator end() const { return events.end(); }
private:
	string name;
	mutable vector <const Event*> events;
	static set <Sport> sports;
	Sport(const string& n);
};

#endif