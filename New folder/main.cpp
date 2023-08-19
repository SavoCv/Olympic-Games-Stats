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

#define endl "\n"

const bool DEBUG = true;

void add(const smatch& sm, bool is_team = false)
{
	const Games* g = Games::insert(sm[1], sm[2]);
	const Event* e = Event::insert(sm[3], sm[4], is_team);
	const Country* c = Country::insert(sm[5]);
	const Competitor* co;
	if (is_team)
		co = Team::insert(sm[6]);
	else
		co = Athlete::insert(sm[6]);
	co->set(g, e, sm[7], c);
}

void read()
{
	ifstream in_c, in_e;
	string file_name_c = "athletes.txt", file_name_e = "events.txt";
	char c = 's';
	if (!DEBUG) {
		cout << "Unesite ime fajla u kome se nalaze podaci o takmicarima: ";
		cin >> file_name_c;
	}
	in_c.open(file_name_c);
	if (!DEBUG) {
		cout << "Unesite ime fajla u kome se nalaze podaci o dogadjajima: ";
		cin >> file_name_e;
	}
	in_e.open(file_name_e);
	if (!in_c.is_open() || !in_e.is_open())
		throw exception("Fajlovi ne mogu da se otvore");
	if(!DEBUG){
		cout << "Da li se unosi svi podaci (s) ili samo o odredjenoj godini(o)? ";
		cin >> c;
	}
	int poc_time = time(0);
	bool svi = false;
	int godina = 0;
	switch (c)
	{
	case 's': case 'S': svi = true; break;
	case 'o': case 'O':
		cout << "Unesite godinu: ";
		cin >> godina;
		break;
	default:
		throw exception("Nije unesena ispravna opcija.");
	}

	string tmp;
	string pattern_i = "([^!]*)!([^!]*)!([^!]*)!([^!]*)!Individual!([^!]*)!([^!]*)!([^!]*)";
	regex r_i(pattern_i);
	smatch sm;
	string pattern_t = "([^!]*)!([^!]*)!([^!]*)!([^!]*)!Team!([^!]*)!\\[([^!]*)\\]!([^!]*)";
	regex r_t(pattern_t);
	int g;
	while(getline(in_e, tmp))
	{
		if (regex_match(tmp, sm, r_i))
		{
			sscanf_s(string(sm[0]).c_str(), "%d", &g);
			if (svi || g == godina)
				add(sm);
		}
		else if (regex_match(tmp, sm, r_t))
		{
			sscanf_s(string(sm[0]).c_str(), "%d", &g);
			if (svi || g == godina)
				add(sm, true);
		}
		else
			throw exception("Podaci nisu u dobrom formatu.");
	}

	int second_time = time(0);
	cout << "Citanje podataka o dogadjajima gotovo " << second_time - poc_time << "s" << endl;

	AthletesInfo::read(in_c);
	int t_time = time(0);
	cout << "Citanje podataka o sportistima gotovo " << t_time - second_time << "s (ukupno " << t_time - poc_time << "s)" << endl;

	in_c.close();
	in_e.close();
}

int menu()
{
	cout << endl;
	cout << "1. Broj ucesnika na svim dogadjajima na Olimpijskim igrama" << endl;
	cout << "2. Broj disciplina na OI" << endl;
	cout << "3. Prosecna visina" << endl;
	cout << "4. Prosecna tezina" << endl;
	cout << "5. Broj razlicitih sportova u kojima je zadata drzava osvojila barem jednu medalju" << endl;
	cout << "6. Tri najbolje drzave na zadatim OI" << endl;
	cout << "7. Drzave koje su na barem jednim OI ostvarile najbolji uspeh" << endl;
	cout << "8. Deset najmladjih ucesnika OI koji su osvojili medalju na svom prvom ucescu" << endl;
	cout << "9. Svi parovi drzava - sportista, za sve sportiste koji su osvojili barem jednu medaljuu pojedinacnoj i barem jednu medalju u grupnoj konkurenciji(ne nuzno iste godine)" << endl;
	cout << "10. Odredjivanje svih sportista koji su ucestvovali na zadatom paru Olimpijskih igara" << endl;
	cout << "11. Svi timovi drzave" << endl;
	cout << "12. Svi gradovi gde su odrzane" << endl;
	cout << endl;
	cout << "0. Kraj rada" << endl;
	cout << endl;
	cout << "Molimo izaberite opciju: ";
	int i;
	cin >> i;
	return i;
}

void print_filters(string& sport, string& country, string& medal, int& year, char& type)
{
	sport = country = medal = "";
	year = type = 0;
	while (true)
	{
		cout << "Filter" << endl;
		cout << "0. zavrsi filtriranje" << endl;
		cout << "1. po sportu" << endl;
		cout << "2. po drzavi" << endl;
		cout << "3. po godini" << endl;
		cout << "4. na osnovu tipa dogadjaja" << endl;
		cout << "5. na osnovu medalje" << endl;
		cout << "Molimo izaberite opciju po kojoj zelite da se filtrira: ";
		int o;
		cin >> o;
		if (!o)
			break;
		switch (o)
		{
		case 1:
			if (sport != "")
				cout << "Sport je vec definisan: " << sport << endl;
			else
			{
				cout << "Unesite sport: ";
				cin.ignore();
				getline(cin, sport);
			}
			break;
		case 2:
			if (country != "")
				cout << "Drzava je vec definisana: " << country << endl;
			else
			{
				cout << "Unesite drzavu: ";
				cin.ignore();
				getline(cin, country);
			}
			break;
		case 3:
			if (year)
				cout << "Godina je vec definisana: " << year << endl;
			else
			{
				cout << "Unesite godinu: ";
				cin >> year;
			}
			break;
		case 4:
			if (type)
				cout << "Tip je vec definisan: " << type << endl;
			else
			{
				cout << "Unesite tip (I/T): ";
				cin >> type;
			}
			break;
		case 5:
			if (medal != "")
				cout << "Medalja je vec definisana: " << medal << endl;
			else
			{
				cout << "Unesite medalju (Gold/Silver/Bronze/No): ";
				cin >> medal;
			}
			break;
		default:
			cout << "Pogresna opcija." << endl;
			break;
		}
		cout << endl;
	}
}

Competitor::Medal last_medal;
bool was_medal;

set <const Competitor*> filter()
{
	string sport, country, medal;
	int year = 0;
	char type = 0;
	was_medal = false;

	print_filters(sport, country, medal, year, type);

	set <const Competitor*> competitors;

	//Type processing
	if (type == 'T' || type == 0)
		for (set<Team>::iterator i = Team::sbegin(); i != Team::send(); ++i)
			competitors.insert(&*i);
	if (type == 'I' || type == 0)
		for (auto i = Athlete::sbegin(); i != Athlete::send(); ++i)
			competitors.insert(&*i);

	//Processing sport
	if (sport != "")
	{
		const Sport* s = Sport::find(sport);
		set <const Competitor*> sp;
		if (s != nullptr) {
			for (auto b = s->begin(); b != s->end(); ++b)
				(*b)->insert_all(sp);
			vector <const Competitor*> v(sp.size());
			auto end = set_intersection(competitors.begin(), competitors.end(), sp.begin(), sp.end(), v.begin());
			competitors.clear();
			competitors.insert(v.begin(), end);
		}
		else {
			cout << "Ne postoji sport" << endl;
			return set<const Competitor*>();
		}
	}

	//Processing country
	if (country != "")
	{
		const Country* c = Country::find(country);
		if (c != nullptr) {
			set <const Competitor*> sp;
			c->insert_all(sp);
			vector <const Competitor*> v(sp.size());
			auto end = set_intersection(competitors.begin(), competitors.end(), sp.begin(), sp.end(), v.begin());
			competitors.clear();
			competitors.insert(v.begin(), end);
		}
		else
		{
			cout << "Ne postoji drzava" << endl;
			return set<const Competitor*>();
		}
	}

	//Processing year
	if (year != 0)
	{
		set <const Competitor*> sp;
		const Games* g = Games::find(year, Games::SUMMER);
		int ch = 0;
		if(g != nullptr)
			g->insert_all(sp);
		g = Games::find(year, Games::WINTER);
		if (g != nullptr)
			g->insert_all(sp);
		if (sp.empty())
		{
			cout << "Nema podataka za trazenu godinu" << endl;
			return set<const Competitor*>();
		}
		vector <const Competitor*> v(sp.size());
		auto end = set_intersection(competitors.begin(), competitors.end(), sp.begin(), sp.end(), v.begin());
		competitors.clear();
		competitors.insert(v.begin(), end);
	}

	//Proccessing medal
	if (medal != "")
	{
		Competitor::Medal m = Competitor::stom(medal);
		last_medal = m;
		was_medal = true;
		set <const Competitor*> sp(Competitor::nbsg_begin(m), Competitor::nbsg_end(m));
		vector <const Competitor*> v(sp.size());
		auto end = set_intersection(competitors.begin(), competitors.end(), sp.begin(), sp.end(), v.begin());
		competitors.clear();
		competitors.insert(v.begin(), end);
	}
	
	return competitors;
}

set <int> filter_athletes()
{
	set <const Competitor*> s = filter();
	set <int> ids;
	for (auto& i : s)
		i->insert_all(ids);
	return ids;
}

void num_of_competitors()
{
	set <int> s = filter_athletes();
	cout << "Broj takmicara je: " << s.size() << endl;
}

void num_of_events()
{
	set <const Competitor*> s = filter();
	set <const Event*> r;
	for (auto& i : s)
	{
		if (was_medal)
			i->insert_events_with_medal(last_medal, r);
		else
			i->insert_all_events(r);
	}
	cout << "Broj disciplina je: " << r.size() << endl;
}

void avg_height()
{
	set <int> s = filter_athletes();
	double sum = 0;
	int count = 0;
	for (auto& i : s) {
		AthletesInfo* ai = AthletesInfo::from_id(i);
		if (ai == nullptr)
			throw exception("Greska AthletesInfo");
		if (ai->get_height() != INT_MAX)
			sum += ai->get_height(), ++count;
	}
	if (count == 0)
		cout << "Filtrirani su svi, ostao je prazan skup" << endl;
	else
		cout << "Prosecna visina je: " << sum / count << endl;
}

void avg_weight()
{
	set <int> s = filter_athletes();
	double sum = 0;
	int count = 0;
	for (auto& i : s) {
		AthletesInfo* ai = AthletesInfo::from_id(i);
		if (ai == nullptr)
			throw exception("Greska AthletesInfo");
		if (ai->get_weight() != INT_MAX)
			sum += ai->get_weight(), ++count;
	}
	if (count == 0)
		cout << "Filtrirani su svi, ostao je prazan skup" << endl;
	else
		cout << "Prosecna tezina je: " << sum / count << endl;
}

void num_of_sports()
{
	string country;
	cout << "Unesite drzavu: ";
	cin.ignore();
	getline(cin, country);
	const Country* c = Country::find(country);
	if (c != nullptr) {
		set <const Competitor*> sp;
		c->insert_all(sp);
		set <const Event*> se;
		set <const Sport*> ss;
		for (auto& i : sp)
			i->insert_events_with_any_medal(se);
		for (auto& i : se)
			ss.insert(i->get_sport());
		cout << "Broj sportova je: " << ss.size() << endl;
	}
	else
	{
		cout << "Ne postoji drzava" << endl;
	}
}

map <pair<int, pair<int, int> >, const Country*> map_medals_countries(const Games* g)
{
	map <const Country*, pair<int, pair<int, int> > > m;
	for (auto& i : *g)
	{
		set <const Event*> se;
		i->insert_events_with_medal(Competitor::GOLD, se);
		m[i->get_country()].first += se.size();
		i->insert_events_with_medal(Competitor::SILVER, se);
		m[i->get_country()].second.first += se.size();
		i->insert_events_with_medal(Competitor::BRONZE, se);
		m[i->get_country()].second.second += se.size();
	}
	map <pair<int, pair<int, int> >, const Country*> m2;
	for (auto& i : m)
		m2[i.second] = i.first;
	return m2;
}

const Games* input_games()
{
	int year;
	cout << "Unesite godinu: ";
	cin >> year;
	string t;
	cout << "Unesite godisnje doba (Summer, Winter): ";
	cin >> t;
	Games::Type type;
	if (t == "Summer")
		type = Games::SUMMER;
	else
		if (t == "Winter")
			type = Games::WINTER;
		else
		{
			cout << "Los izbor" << endl;
			return nullptr;
		}
	const Games* g = Games::find(year, type);
	if (g == nullptr)
	{
		cout << "Te godine nisu odrzane OI" << endl;
		return nullptr;
	}
	return g;
}

void best_3()
{
	const Games* g = input_games();
	if (g == nullptr)
		return;
	map <pair<int, pair<int, int> >, const Country*> m2 = map_medals_countries(g);
	auto it = m2.rbegin();
	for (int i = 1; i <= 3; ++i) {
		cout << i << ". mesto: ";
		cout << (*it).second->get_name() << " " << (*it).first.first << " " << (*it).first.second.first << " " << (*it).first.second.first << endl;
		++it;
	}
}

void the_best_anytime()
{
	set <const Country*> c;
	for (auto it = Games::sbegin(); it != Games::send(); ++it)
	{
		map <pair<int, pair<int, int> >, const Country*> m2 = map_medals_countries(&*it);
		c.insert(m2.rbegin()->second);
	}
	for (auto& i : c)
		cout << i->get_name() << endl;
}

void yongest_with_medal()
{
	set <int> played, first_play_medalist, playing, medalist;
	for (auto it = Games::sbegin(); it != Games::send(); ++it)
	{
		for (auto& i : *it) {
			i->insert_all(playing);
			if (i->win_medal(&*it))
				i->insert_all(medalist);
		}
		vector <int> v;
		vector <int>::iterator iter;
		v.resize(medalist.size());
		iter = set_difference(medalist.begin(), medalist.end(), played.begin(), played.end(), v.begin());
		first_play_medalist.insert(v.begin(), iter);
		
		played.insert(playing.begin(), playing.end());

		medalist.clear();
		playing.clear();
	}
	auto cmp = [](int a, int b) {
		AthletesInfo* ai = AthletesInfo::from_id(a), * bi = AthletesInfo::from_id(b);
		return ai->get_years() < bi->get_years() || (ai->get_years() == bi->get_years() && ai->get_id() < bi->get_id());
	};
	set <int, decltype(cmp) > res(cmp);
	res.insert(first_play_medalist.begin(), first_play_medalist.end());
	int i = 0;
	int last_years = 0;
	for (auto& k : res)
	{
		++i;
		AthletesInfo* ai = AthletesInfo::from_id(k);
		if (i < 11 || ai->get_years() == last_years)
		{
			cout << i <<  ". " << ai->get_name() << " " << ai->get_years() << endl;
			last_years = ai->get_years();
		}
		else
			break;
	}
}

void individual_and_team_medalist()
{
	set <int> individual, team;
	for (auto it = Country::sbegin(); it != Country::send(); ++it)
	{
		for (auto& i : *it)
		{
			if (i->win_medal(nullptr))
				if (typeid(*i) == typeid(Athlete))
					i->insert_all(individual);
				else
					i->insert_all(team);
		}
		vector <int> v(individual.size());
		vector <int>::iterator iter, q;
		iter = set_intersection(individual.begin(), individual.end(), team.begin(), team.end(), v.begin());
		for (q = v.begin(); q != iter; ++q)
		{
			cout << it->get_name() << " - " << AthletesInfo::from_id(*q)->get_name() << endl;
		}
		individual.clear();
		team.clear();
	}
}

void compete_in_pair_OI()
{
	const Games* g1 = input_games();
	if (g1 == nullptr)
		return;
	const Games* g2 = input_games();
	if (g2 == nullptr)
		return;
	set <int> s1, s2;
	g1->insert_all(s1);
	g2->insert_all(s2);
	vector <int> v(s1.size());
	vector <int>::iterator iter, it;
	iter = set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(), v.begin());
	for (it = v.begin(); it != iter; ++it)
		cout << AthletesInfo::from_id(*it)->get_name() << endl;
}

void all_teams()
{
	set <const Team*> s;
	string country;
	cout << "Unesite drzavu: ";
	cin.ignore();
	getline(cin, country);
	const Country* c = Country::find(country);
	if (c != nullptr) {
		for (auto& i : *c)
			if (dynamic_cast<const Team*>(i) != nullptr)
				s.insert(dynamic_cast<const Team*>(i));
		vector <const Team*> v(s.begin(), s.end());
		sort(v.begin(), v.end(), [](const Team* a, const Team* b) {
			return a->lower(b);
		});
		for (auto& i : v)
		{
			cout << *i << endl;
		}
	}
	else
	{
		cout << "Ne postoji drzava" << endl;
	}
}

void all_towns()
{
	set <string> s;
	for (auto it = Games::sbegin(); it != Games::send(); ++it)
		s.insert(it->get_city());
	for (auto& i : s)
		cout << i << endl;
}

void solve()
{
	int ind = true;
	char c;
	while (ind) {
		switch (menu())
		{
		case 0: cout << "Stvarno zelite da izadjete (y, n)?" << endl;
			cin >> c;
			if (c == 'y')
				ind = false;
			break;
		case 1: num_of_competitors(); break;
		case 2: num_of_events(); break;
		case 3: avg_height(); break;
		case 4: avg_weight(); break;
		case 5: num_of_sports(); break;
		case 6: best_3(); break;
		case 7: the_best_anytime(); break;
		case 8: yongest_with_medal(); break;
		case 9: individual_and_team_medalist(); break;
		case 10: compete_in_pair_OI(); break;
		case 11: all_teams(); break;
		case 12: all_towns(); break;
		default: cout << "Ne postojeca opcija"; break;
		}
	}
}

/*int main()
{
	//ios_base::sync_with_stdio(false);
	//cin.tie(0);
	//cout.tie(0);
	try {
		read();
		solve();
	}
	catch (exception e)
	{
		cout << e.what() << endl;
	}

	return 0;
}*/