#include <cstdio>
#include <iostream>
#include <list>
#include <cstdlib>
#include <string>
using namespace std;

string indent = "";
list<string> lst;
char people_id[210][20];
char password[20] = "0000000000000000"; // 16 * '0'
int people_tot = 0;

void right() {
	indent += '\t';
}

void left() {
	indent.pop_back();
}

void write(const string& str) {
	lst.push_back(indent + str + '\n');
//	puts(indent + str);
}

void supplier() {
	write("# suppliers");
	write("INSERT INTO mydb.people VALUES");
	right();
	char phone[10], sex[10], age[10], name[20];
	for (int i = 0; i < 10; ++i) {
		++people_tot;
		sprintf(people_id[people_tot], "%016d", people_tot);
		sprintf(name, "%s", people_id[people_tot]);
		sprintf(age, "%d", rand() % 80 + 1);
		sprintf(sex, "%s", (rand() & 1) ? "male" : "female");
		sprintf(phone, "%08d", rand() % 10000000 + (rand() % 9 + 1) * 10000000);
		write("(\'" + (string)people_id[people_tot] + "\',\'" + password + "\',\'" +
			  name + "\',\'" + sex + "\',\'" + age + "\',\'" + phone + "\')" + 
			  (i == 9 ? ";" : ","));
	}
	left();

	write("INSERT INTO mydb.product VALUES");
	right();
	for (int i = 1; i <= 10; ++i) {
		write("(\'" + people_id[people_tot] + "\',\'" + people_id[people_tot] + "\',\'" +
			// rand date time
			 );
	}
	left();
}

void customer() {
	write("# customers");
	write("INSERT INTO mydb.people VALUES");
	right();
	char phone[10], sex[10], age[10], name[20];
	for (int i = 0; i < 100; ++i) {
		++people_tot;
		sprintf(people_id[people_tot], "%016d", people_tot);
		sprintf(name, "%s", people_id[people_tot]);
		sprintf(age, "%d", rand() % 80 + 1);
		sprintf(sex, "%s", (rand() & 1) ? "male" : "female");
		sprintf(phone, "%08d", rand() % 10000000 + (rand() % 9 + 1) * 10000000);
		write("(\'" + (string)people_id[people_tot] + "\',\'" + password + "\',\'" +
			  name + "\',\'" + sex + "\',\'" + age + "\',\'" + phone + "\')" + 
			  (i == 99 ? ";" : ","));
	}
	left();
}

int main() 
{
	ios::sync_with_stdio(false);
	freopen("data.sql","w",stdout);
	indent = "";
//	puts("INSERT INTO");
	supplier();
	customer();
	for (auto iter = lst.begin(); iter != lst.end(); ++iter)
		cout << *iter;
	return 0;
}
