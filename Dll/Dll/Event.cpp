#include "Event.h"

set<Event> Event::events;

Event::Event(const string& n, const Sport* sp, bool is_team)
{
    name = n;
    sport = sp;
    this->is_team = is_team;
}

const Event* Event::insert(const string& s_name, const string& e_name, bool is_team)
{
    const Sport* s = Sport::insert(s_name);
    events.insert(Event(e_name, s, is_team));
    const Event* e = &(*events.find(Event(e_name, nullptr, false)));
    s->push_event(e);
    return e;
}

bool Event::operator<(const Event& e) const
{
    return name < e.name;
}
