#include "Games.h"
#include <regex>

set <Games> Games::games;

Games::Games(const string& name, const string& city)
{
	this->city = city;
	regex rs("([0-9]+) Summer");
	regex rw("([0-9]+) Winter");
	smatch sm;
	if (regex_match(name, sm, rs))
	{
		year = atoi(string(sm[1]).c_str());
		type = SUMMER;
	}
	else
		if (regex_match(name, sm, rw))
		{
			year = atoi(string(sm[1]).c_str());
			type = WINTER;
		}
		else
			throw exception("Podaci o igrama nisu dobri");
}

const Games* Games::insert(const string& name, const string& city)
{
	games.insert(Games(name, city));
	return  &(*games.find(Games(name, city)));
}

const Games* Games::find(int y, Type t)
{
	auto g = games.find(Games(y, t));
	if (g == games.end())
		return nullptr;
	return &(*g);
}

bool Games::operator<(const Games& g) const 
{
	return year < g.year || (year == g.year && type < g.type);
}