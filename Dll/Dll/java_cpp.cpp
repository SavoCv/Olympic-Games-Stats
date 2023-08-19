#include "java_cpp.h"
#include <iostream>
#include "Competitor.h"
#include <set>
#include "main.h"

string jstring2string(JNIEnv* env, jstring jStr) {
	//cout << "<js2s" << endl;
	if (!jStr) {
		//cout << "js2s>" << endl;
		return "";
	}
	jboolean isCopy;
	const char* cstr = (env)->GetStringUTFChars(jStr, &isCopy);
	string tmp = string(cstr);
	//cout << "js2s>" << endl;
	return tmp;
}

void input_filter(JNIEnv* env, jobject chart, string &metrics, string &sport, string &medal, int &year, bool &ind, bool &team)
{
	jclass Chart = env->GetObjectClass(chart);
	jfieldID filterID = env->GetFieldID(Chart, "filter", "Loi/Graph$Filter;");
	//jclass Filter = env->FindClass("oi/Graph$Filter");
	jobject filter = env->GetObjectField(chart, filterID);
	jclass Filter = env->GetObjectClass(filter);

	//cout << "2DBG" << endl;

	jfieldID metricsID, sportID, medalID, yearID, indID, teamID;

	metricsID = env->GetFieldID(Filter, "metrics", "Ljava/lang/String;");
	sportID = env->GetFieldID(Filter, "sport", "Ljava/lang/String;");
	medalID = env->GetFieldID(Filter, "medal", "Ljava/lang/String;");
	yearID = env->GetFieldID(Filter, "year", "I");
	indID = env->GetFieldID(Filter, "ind", "Z");
	teamID = env->GetFieldID(Filter, "team", "Z");//*/

	//cout << "3DBG" << endl;
	metrics = jstring2string(env, (jstring)env->GetObjectField(filter, metricsID));
	//cout << "4DBG" << endl;
	sport = jstring2string(env, (jstring)env->GetObjectField(filter, sportID));
	medal = jstring2string(env, (jstring)env->GetObjectField(filter, medalID));
	year = (int)env->GetIntField(filter, yearID);
	ind = (bool)env->GetBooleanField(filter, indID);
	team = (bool)env->GetBooleanField(filter, teamID);
}

set <const Competitor*> filter(JNIEnv* env, jobject chart, string& metrics)
{
	string sport, medal;
	int year;
	bool ind, team;
	input_filter(env, chart, metrics, sport, medal, year, ind, team);
	//cout << metrics << " " << sport << " " << medal << " " << year << " " << ind << " " << team << endl;
	
	char type;
	if (!ind && !team)
		return set <const Competitor*>();
	else
		if (!ind)
			type = 'T';
		else
			if (!team)
				type = 'I';
			else
				type = 0;

	string s("");
	//cout << "FILTER: " << sport << ", " << medal << ", " << year << ", " << type << endl;


	read();

	return handle_filter(sport, s, medal, year, type);
}

set <const Competitor*> filter(JNIEnv* env, jobject chart, string& metrics, string& sport, string& medal, int& year, char& type)
{
	bool ind, team;
	//cout << "FILDBG" << endl;
	input_filter(env, chart, metrics, sport, medal, year, ind, team);
	//cout << metrics << " " << sport << " " << medal << " " << year << " " << ind << " " << team << endl;

	if (!ind && !team)
		return set <const Competitor*>();
	else
		if (!ind)
			type = 'T';
		else
			if (!team)
				type = 'I';
			else
				type = 0;

	string s("");

	read();

	return handle_filter(sport, s, medal, year, type);
}