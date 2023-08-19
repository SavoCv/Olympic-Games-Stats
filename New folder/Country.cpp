#include "Country.h"

set <Country> Country::countries;

const Country* Country::insert(const string& n)
{
    countries.insert(Country(n));
    return  &(*countries.find(Country(n)));
}

bool Country::operator<(const Country& c) const
{
    return name < c.name;
}

Country::Country(const string& n)
{
    name = n;
}

const Country* Country::find(const string& n)
{
    auto i = countries.find(Country(n));
    if (i == countries.end())
        return nullptr;
    return  &(*i);
}