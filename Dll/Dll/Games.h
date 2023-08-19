#ifndef GAMES_INCLUDED
#define GAMES_INCLUDED

#include <vector>
#include <utility>
#include <set>
#include <map>
#include <regex>
#include <string>
#include "Information.h"
using namespace std;

class Games : public Information
{
public:
	enum Type { WINTER, SUMMER };
	static const Games* insert(const string& name, const string& city);
	static const Games* find(int y, Type t);
	static set<Games>::iterator sbegin() { return games.begin(); }
	static set<Games>::iterator send() { return games.end(); }
	bool operator<(const Games&) const;
	string get_city() const { return city; }
	Type get_type() const { return type; }
	int get_year() const { return year; }
private:
	Type type;
	string city;
	int year;
	static set <Games> games;
	Games(const string& name, const string& city);
	Games(int y, Type t) : year(y), type(t) {}
};

#endif