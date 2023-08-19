#include "Team.h"
#include "AthletesInfo.h"
#include "Event.h"
#include <iostream>

set<Team> Team::teams;

Team::Team(const string& t)
{
    const sregex_iterator end;
    regex re("'([0-9]+)'");
    for (sregex_iterator i(t.cbegin(), t.cend(), re); i != end; ++i)
        ids.push_back(atoi( string((*i)[1]).c_str() ));
    sort(ids.begin(), ids.end());
    for (auto& id : ids)
        AthletesInfo::add_to_read(id);
}

const Team* Team::insert(const string& t)
{
    Team te(t);
    teams.insert(te);
    return &(*teams.find(te));
}

bool Team::operator<(const Team& t) const
{
    for (int i = 0; i < ids.size() && i < t.ids.size(); ++i)
        if (ids[i] < t.ids[i])
            return true;
        else
            if (ids[i] > t.ids[i])
                return false;
    return ids.size() < t.ids.size();
}

std::set<Team>::iterator Team::sbegin()
{
    return teams.begin();
}

std::set<Team>::iterator Team::send()
{
    return teams.end();
}

bool Team::lower(const Team* t) const
{
    if (ids.size() == t->ids.size())
        return events.begin()->first.first < t->events.begin()->first.first;
    return ids.size() > t->ids.size();
}

ostream& operator<<(ostream& os, const Team& t)
{
    os << t.events.begin()->first.first->get_name() << " : ";
    for (int i = 0; i < t.ids.size(); ++i)
    {
        if (i != 0)
            os << ", ";
        os << AthletesInfo::from_id(t.ids[i])->get_name();
    }
    return os;
}

