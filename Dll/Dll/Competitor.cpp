#include "Competitor.h"
#include <iostream>

std::set <const Competitor*> Competitor::nbsg[4];

Competitor::~Competitor() {}

void Competitor::set(const Games* g, const Event* e, const string& medal, const Country* c) const
{
	Medal m = stom(medal);
	nbsg[m].insert(this);
	events[make_pair(e, g)] = m;
	country = c;
	c->push_competitor(this);
	e->push_competitor(this);
	g->push_competitor(this);
}

Competitor::Medal Competitor::stom(const string& medal)
{
	Medal m;
	if (medal == "Gold")
		m = GOLD;
	else
		if (medal == "Silver")
			m = SILVER;
		else
			if (medal == "Bronze")
				m = BRONZE;
			else
				if (medal == "" || medal == "No" || medal == "None")
					m = NO_MEDAL;
				else
					throw exception("Podaci nisu u dobrom formatu");
	return m;
}

void Competitor::insert_events_with_medal(Medal m, std::set<const Event*>& e) const
{
	for (auto& i : events)
	{
		if (i.second == m)
			e.insert(i.first.first);
	}
}

void Competitor::insert_all_events(std::set<const Event*>& e) const
{
	for (auto& i : events)
		e.insert(i.first.first);
}

void Competitor::insert_events_with_any_medal(std::set<const Event*>& e) const
{
	for (auto& i : events)
		if (i.second != NO_MEDAL) {
			e.insert(i.first.first);
		}
}

bool Competitor::win_medal(const Games* g) const
{
	for (auto& i : events)
		if (i.second != NO_MEDAL && (g == nullptr || i.first.second == g))
			return true;
	return false;
}
