#include "oi_PieChart.h"
#include <iostream>
#include <string>
#include "main.h"
#include "java_cpp.h"

using namespace std;

JNIEXPORT void JNICALL Java_oi_PieChart_getData
(JNIEnv* env, jobject pieChart)
{
	//std::cout << "Hello from C++" << std::endl;
	jclass PieChart = env->GetObjectClass(pieChart);
	jmethodID add = env->GetMethodID(PieChart, "add", "(Ljava/lang/String;I)V");

	set <const Competitor*> competitors;
	string metrics;
	competitors = filter(env, pieChart, metrics);

	map <const Country*, set <const Competitor*>> m;

	//cout << competitors.size() << endl;
	for (auto& i : competitors)
		m[i->get_country()].insert(i);

	for (auto& i : m)
	{
		//cout << i.first->get_name() << " " << i.second.size() << endl;
		env->CallVoidMethod(pieChart, add, env->NewStringUTF(i.first->get_name().c_str()), jint(i.second.size()));
	}
	//cout << "Kraj" << endl;
}