#pragma once
#include <iostream>
#include <fstream>
#include <regex>
#include <ctime>
#include "Competitor.h"
#include "AthletesInfo.h"
#include "Team.h"
#include "Athlete.h"
#include "Event.h"
using namespace std;

extern Competitor::Medal last_medal;
extern bool was_medal;

extern map <const Games*, set <pair<const Competitor*, pair <const Event*, string>>>> mapGamesCompetitorsAndEventsAndMedal;
extern map <const Games*, set <const Event*>> mapGamesEvents;

set <const Competitor*> handle_filter(string& sport, string& country, string& medal, int& year, char& type);

void read();