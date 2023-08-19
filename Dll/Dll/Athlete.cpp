#include "Athlete.h"
#include "AthletesInfo.h"

set <Athlete> Athlete::athletes;

Athlete::Athlete(int i)
{
    id = i;
    AthletesInfo::add_to_read(id);
}

const Athlete* Athlete::insert(const string& a)
{
    Athlete at(atoi(a.c_str()));
    athletes.insert(at);
    return &(*athletes.find(at));
}

bool Athlete::operator<(const Athlete& a) const
{
    return id < a.id;
}

std::set<Athlete>::iterator Athlete::sbegin()
{
    return athletes.begin();
}

std::set<Athlete>::iterator Athlete::send()
{
    return athletes.end();
}
