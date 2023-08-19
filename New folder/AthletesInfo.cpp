#include "AthletesInfo.h"
#include <iostream>

map<int, AthletesInfo> AthletesInfo::m;
set<int> AthletesInfo::to_read;

void AthletesInfo::read(istream& is)
{
	string tmp;
	regex r("([0-9]*)!([^!]*)!(M|F)!([0-9]*|NA)!([0-9.]*|NA)!([0-9.]*|NA)");
	smatch sm;
	while (getline(is, tmp))
	{
		if (regex_match(tmp, sm, r))
		{
			AthletesInfo af;
			af.id = atoi(string(sm[1]).c_str());
			if (to_read.find(af.id) == to_read.end())
				continue;
			af.name = sm[2];
			af.gender = string(sm[3])[0];
			if (sm[4] == "NA")
				af.years = INT_MAX;
			else
				af.years = atoi(string(sm[4]).c_str());
			if (sm[5] == "NA")
				af.height = INT_MAX;
			else
				af.height = atof(string(sm[5]).c_str());
			if (sm[6] == "NA")
				af.weight = INT_MAX;
			else
				af.weight = atof(string(sm[6]).c_str());
			m[af.id] = af;
		}
		else
			throw exception(string("Podaci nisu u dobrom formatu: " + tmp).c_str());
	}
}

void AthletesInfo::add_to_read(int i)
{
	to_read.insert(i);
}

AthletesInfo* AthletesInfo::from_id(int id)
{
	if (m.find(id) == m.end())
		return nullptr;
	return &m[id];
}
