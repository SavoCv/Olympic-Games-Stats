#ifndef  EVENT_INCLUDED
#define EVENT_INCLUDED

#include <vector>
#include <utility>
#include <set>
#include <map>
#include <regex>
#include <string>
#include "Information.h"
#include "Sport.h"

using namespace std;

class Event : public Information
{
	const Sport* sport;
	string name;
	static set <Event> events;
	Event(const string& n, const Sport*);
public:
	static const Event* insert(const string& s_name, const string& e_name, bool is_team);
	bool operator<(const Event&) const;
	const Sport* get_sport() const { return sport; }
	string get_name() const { return name; }
};

#endif
