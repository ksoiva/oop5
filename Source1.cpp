//13. Створити базовий клас СПОРТИВНА УНІВЕРСІАДА(задаються назва і дата проведення).
//  Створити похідні класи ЗМАГАННЯ МІЖ 2 КОМАНДАМИ(задаються дані про двох суперників, кількість очок(голів),
//	набраних кожним з них проти іншого) та ЗМАГАННЯ «ЧИМ МЕНШЕ, ТИМ КРАЩЕ», наприклад, біг, плавання
//	(задаються дані про учасника, його результат, дані про лідера змагань та його результат).
//	Для введених даних про різні змагання визначити загальну кількість перемог учасників від кожного університету
//	і відсортувати університети за зростанням цієї кількості.Для перевірки використати масив вказівників на об’єкти базового класу,
//	яким присвоїти адреси об’єктів похідних класів.

#include <iostream>
#include <string>
#define N 20
using namespace std;

struct Team {
	string uni;
	int wins = 0;
}*teams;

class Universiada {
protected:
	string name;
	string date;
public:
	Universiada() {
		name = {};
		date = {};
	}
	
	virtual string WhoWins() {
		return "There is no competitions";
	}

	void InputInfo(string vname, string vdata) {
		name = vname;
		date = vdata;
	}
};

class Competition : public Universiada {
private:
	Team* team1;
	Team* team2;
	int score1;
	int score2;
public:

	Competition(): Universiada() {
		team1 = NULL;
		team2 = NULL;
		score1 = 0;
		score2 = 0;
	}

	Competition(Team* t1, Team* t2): Universiada(){
		team1 = t1;
		team2 = t2;
		cout << "Score of " << team1->uni << ":  ";
		cin >> score1;
		cout << "Score of " << team2->uni << ":  ";
		cin >> score2;
	}

	int Compare() {
		if (score1 > score2) {
			return 1;
		}
		if (score2 > score1) {
			return 2;
		}
		if (score1 = score2) {
			return 0;
		}
	}

	string WhoWins() {
		int result = Compare();
		if (result == 1) {
			team1->wins++;
			return (team1->uni + " won");
		}
		if (result == 2) {
			team2->wins++;
			return team2->uni + " won";
		}
		if (result == 0) {
			team1->wins++;
			team2->wins++;
			return "Draw";
		}
	}
};

class LessBetter : public Universiada {
private:
	Team* participant;
	double sc_part;
	Team* leader;
	double sc_lead;
public:
	LessBetter() : Universiada() {
		participant = NULL;
		sc_part = 0;
		leader = NULL;
		sc_lead = 0;
	}
	LessBetter(int num) {
		for (int i = 0; i < num; i++) {
			participant = &teams[i];
			cout << "Time(sec) of " << participant->uni << ":  ";
			cin >> sc_part;
			if (leader == NULL) {
				leader = participant;
				sc_lead = sc_part;
				continue;
			}
			if (sc_lead > sc_part) {
				leader = participant;
				sc_lead = sc_part;
			}
		}
	}
	string WhoWins() {
		leader->wins++;
		return leader->uni + " won";
	}

};

void InputTeams(int size) {
	for (int i = 0; i < size; i++) {
		cout << "Team " << i + 1 << ":  ";
		cin >> teams[i].uni;
	}
}

void OutputRes(int size) {
	cout << "\n\t\t  Team\t\tScore" << endl << endl;
	for (int i = 0; i < size; i++) {
		cout << "\t\t  " << teams[i].uni << "\t\t  " << teams[i].wins << endl;
	}
}

void Sort(int size) {
	Team temp;
	int i, j;
	for (i = 0; i < size - 1; i++) {
		for (j = i + 1; j < size; j++) {
			if (teams[i].wins > teams[j].wins) {
				temp = teams[j];
				teams[j] = teams[i];
				teams[i] = temp;
			}
		}
	}
}

int NumComps(int size) {
	int num = 0;
	size--;
	while (size != 0) {
		num += size;
		size--;
	}
	return num;
}

int main() {
	string name, date;
	cout << "Input name of universiade:  ";
	getline(cin, name);
	cout << "Input date of the event:  ";
	cin >> date;
	
	int numof;
	cout << "Number of teams:  ";
	cin >> numof;
	teams = new Team[numof];
	InputTeams(numof);
	
	int compsize = NumComps(numof);
	int size = compsize + 3;
	Universiada** comp = new Universiada*[size];
	int k;
	int j = 0;
	
	for (int i = 0; i < numof - 1; i++) {
		for (k = i + 1; k < numof && j < compsize; k++, j++) {
			Team* team1 = &teams[i], *team2 = &teams[k];
			cout << "\nCompetition between " << team1->uni << " and " << team2->uni << endl;
			comp[j] = new Competition(team1, team2);
			comp[j]->InputInfo(name, date);
			cout << comp[j]->WhoWins() << endl;
		}
	}
	
	cout << "\nCompetitions \"less better\" of run";
	k = 1;
	for (int i = compsize; i < size; i++, k++) {
		cout << endl << " Round " << k << endl;
		comp[i] = new LessBetter(numof);
		comp[i]->InputInfo(name, date);
		cout << comp[i]->WhoWins() << endl;
	}
	
	for (int i = 0; i < size; i++) {
		if(comp[i] != NULL)
			delete comp[i];
	}
	delete[] comp;
	Sort(numof);
	OutputRes(numof);
	delete[] teams;
	return 0;
}