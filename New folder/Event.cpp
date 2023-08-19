#include "Event.h"

set<Event> Event::events;

Event::Event(const string& n, const Sport* sp)
{
    name = n;
    sport = sp;
}

const Event* Event::insert(const string& s_name, const string& e_name, bool is_team)
{
    const Sport* s = Sport::insert(s_name);
    events.insert(Event(e_name, s));
    const Event* e = &(*events.find(Event(e_name, nullptr)));
    s->push_event(e);
    return e;
}

bool Event::operator<(const Event& e) const
{
    return name < e.name;
}
