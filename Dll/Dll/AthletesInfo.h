#ifndef ATHLETES_INFO_INCLUDED
#define ATHLETES_INFO_INCLUDED

#include <vector>
#include <utility>
#include <set>
#include <map>
#include <regex>
#include <string>
using namespace std;

class AthletesInfo
{
	int id;
	string name;
	char gender;
	int years;
	double height;
	double weight;
	static map<int, AthletesInfo> m;
	static set<int> to_read;
public:
	static void read(istream& is);
	static void add_to_read(int i);
	static AthletesInfo* from_id(int id);
	int get_id() const { return id; }
	int get_years() const { return years; }
	int get_height() const { return height; }
	int get_weight() const { return weight; }
	string get_name() const { return name; }
	char get_gender() const { return gender; }
};

#endif