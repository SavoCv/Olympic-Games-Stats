#include "Sport.h"
#include <iostream>

set <Sport> Sport::sports;

bool Sport::operator<(const Sport& s) const
{
    return name < s.name;
}

Sport::Sport(const string& n)
{
    name = n;
}

const Sport* Sport::insert(const string& n)
{
    sports.insert(Sport(n));
    return  &(*sports.find(Sport(n)));
}

void Sport::push_event(const Event* e) const
{
    events.push_back(e);
}

const Sport* Sport::find(const string& n)
{
    return  &(*sports.find(Sport(n)));
}