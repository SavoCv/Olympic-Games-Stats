#ifndef COUNTRY_INCLUDED
#define COUNTRY_INCLUDED

#include <vector>
#include <utility>
#include <set>
#include <map>
#include <regex>
#include <string>
#include "Information.h"
using namespace std;

class Country : public Information
{
	string name;
	static set<Country> countries;
	Country(const string& n);
public:
	static const Country* insert(const string& n);
	static const Country* find(const string& n);
	static auto sbegin() { return countries.begin(); }
	static auto send() { return countries.end(); }
	bool operator<(const Country&) const;
	string get_name() const { return name; }
};

#endif