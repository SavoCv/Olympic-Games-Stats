#pragma once
#include <string>
#include <jni.h>
#include <set>
#include "Competitor.h"
using namespace std;

string jstring2string(JNIEnv* env, jstring jStr);

void input_filter(JNIEnv* env, jobject chart, string& metrics, string& sport, string& medal, int& year, bool& ind, bool& team);

set <const Competitor*> filter(JNIEnv* env, jobject chart, string& metrics);

set <const Competitor*> filter(JNIEnv* env, jobject chart, string& metrics, string& sport, string& medal, int& year, char& type);