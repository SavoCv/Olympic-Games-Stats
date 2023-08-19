#include "Information.h"
#include "Competitor.h"


Information::~Information() {}

void Information::push_competitor(const Competitor* c) const
{
	competitors.push_back(c);
}

void Information::insert_all(set<int>& a) const
{
	for(auto &i : competitors)
		i->insert_all(a);
}

void Information::insert_all(set<const Competitor*>& s) const
{
	s.insert(competitors.begin(), competitors.end());
}
