#ifndef COMPETITOR_INCLUDED
#define COMPETITOR_INCLUDED

#include <vector>
#include <utility>
#include <set>
#include <map>
#include <regex>
#include <string>
#include "Event.h"
#include "Country.h"
#include "Games.h"
using namespace std;

class Event;

class Competitor
{
public:
	enum Medal { NO_MEDAL, BRONZE, SILVER, GOLD };
	virtual ~Competitor() = 0;
	void set(const Games* g, const Event* e, const string& medal, const Country* c) const;
	static Medal stom(const string& str);
	virtual void insert_all(std::set <int>& s) const = 0;
	static const auto nbsg_begin(Medal m) { return nbsg[m].begin(); }
	static const auto nbsg_end(Medal m) { return nbsg[m].end(); }
	void insert_events_with_medal(Medal m, std::set <const Event*>& e) const;
	void insert_all_events(std::set <const Event*>& e) const;
	void insert_events_with_any_medal(std::set <const Event*>& e) const;
	const Country* get_country() const { return country; }
	bool win_medal(const Games* g) const;
protected:
	mutable map < pair < const Event*, const Games* >, Medal > events;
private:
	mutable const Country* country;
	static std::set <const Competitor*> nbsg[4];
};

#endif

