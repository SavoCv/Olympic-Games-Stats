#include "oi_XYGraph.h"
#include <iostream>
#include <string>
#include "main.h"
#include "java_cpp.h"

using namespace std;

JNIEXPORT void JNICALL Java_oi_XYGraph_getData
(JNIEnv* env, jobject xyGraph)
{
	jclass XYGraph = env->GetObjectClass(xyGraph);
	jmethodID add = env->GetMethodID(XYGraph, "add", "(DD)V");

	set <const Competitor*> competitors;
	string metrics, sport, medal, country;
	int year;
	char type;
	//cout << "1DBG" << endl;
	competitors = filter(env, xyGraph, metrics, sport, medal, year, type);

	//cout << metrics << endl;
	
	if (metrics == "Num of events")
	{
		for (auto& i : mapGamesEvents)
		{
			int j = i.first->get_year();
			if (year != 0 && j != year)
				continue;
			if (i.first->get_type() == Games::Type::WINTER)
				j = -j;
			int cnt = 0;
			for (auto& k : i.second) {
				if (sport == "" || k->get_sport()->get_name() == sport)
					if (type == 0 || (type == 'T' && k->get_is_team()) || (type == 'I' && !k->get_is_team()))
						++cnt;
			}
			env->CallVoidMethod(xyGraph, add, (jdouble)j, (jdouble)cnt);
		}
	}
	else if (metrics == "Avg height") {

		for (auto& i : mapGamesCompetitorsAndEventsAndMedal)
		{
			int j = i.first->get_year();
			if (year != 0 && j != year)
				continue;
			if (i.first->get_type() == Games::Type::WINTER)
				j = -j;
			int cnt = 0;
			double sum = 0;
			set <int> ath;
			for (auto& k : i.second)
			{
				if (type == 0 || (type == 'T' && k.second.first->get_is_team()) || (type == 'I' && !k.second.first->get_is_team()))
					if (sport == "" || k.second.first->get_sport()->get_name() == sport)
						if (medal == "" || k.second.second == medal || (medal == "None" && k.second.second == ""))
							k.first->insert_all(ath);
			}
			for (auto& k : ath)
			{
				AthletesInfo* ai = AthletesInfo::from_id(k);
				if (ai->get_height() != INT_MAX) {
					cnt++;
					sum += ai->get_height();
				}
			}
			if (cnt != 0)
				env->CallVoidMethod(xyGraph, add, (jdouble)j, (jdouble)(sum / cnt));
		}

	}
	else // avg weight
	{
		for (auto& i : mapGamesCompetitorsAndEventsAndMedal)
		{
			int j = i.first->get_year();
			if (year != 0 && j != year)
				continue;
			if (i.first->get_type() == Games::Type::WINTER)
				j = -j;
			int cnt = 0;
			double sum = 0;
			set <int> ath;
			for (auto& k : i.second)
			{
				if (type == 0 || (type == 'T' && k.second.first->get_is_team()) || (type == 'I' && !k.second.first->get_is_team()))
					if (sport == "" || k.second.first->get_sport()->get_name() == sport)
						if (medal == "" || k.second.second == medal || (medal == "None" && k.second.second == ""))
							k.first->insert_all(ath);
			}
			for (auto& k : ath)
			{
				AthletesInfo* ai = AthletesInfo::from_id(k);
				if (ai->get_weight() != INT_MAX) {
					cnt++;
					sum += ai->get_weight();
				}
			}
			if (cnt != 0)
				env->CallVoidMethod(xyGraph, add, (jdouble)j, (jdouble)(sum / cnt));
		}
	}
}