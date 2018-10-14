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

string rand_date() {
	return "DATE_ADD(now(), INTERVAL FLOOR(1+RAND() * 86400) SECOND)";
}

void product() {
	write("");
	write("# products");
	write("INSERT INTO mydb.product VALUES");
	right();
	char unit_price[10], discount[10], stock_quantity[10];
	string name = "a";

	for (int i = 1; i <= 10; ++i) {
		string type = "clothing";
		for (int j = 1; j <= 4; ++j) {
			name[0] = 'a' + i - 1;
			sprintf(unit_price, "%d", rand() % 100);
			sprintf(discount, "%f", (rand() % 100) * 1.0 / 100.0);
			write("(\'" + name + type + char('0'+j) + "\',\'" + people_id[i] + "\'," +
				rand_date() + "," + rand_date() + "," + unit_price + "," + discount + "," +
				stock_quantity + "," + type + "),");
		}
		type = "food";
		for (int j = 1; j <= 4; ++j) {
			name[0] = 'a' + i - 1;
			sprintf(unit_price, "%d", rand() % 100);
			sprintf(discount, "%f", (rand() % 100) * 1.0 / 100.0);
			write("(\'" + name + type + char('0'+j) + "\',\'" + people_id[i] + "\'," +
				rand_date() + "," + rand_date() + "," + unit_price + "," + discount + "," +
				stock_quantity + "," + type + "),");
		}
		type = "fun";
		for (int j = 1; j <= 4; ++j) {
			name[0] = 'a' + i - 1;
			sprintf(unit_price, "%d", rand() % 100);
			sprintf(discount, "%f", (rand() % 100) * 1.0 / 100.0);
			write("(\'" + name + type + char('0'+j) + "\',\'" + people_id[i] + "\'," +
				rand_date() + "," + rand_date() + "," + unit_price + "," + discount + "," +
				stock_quantity + "," + type + "),");
		}
	}
	left();
}

int main() 
{
	ios::sync_with_stdio(false);
	freopen("data.sql","w",stdout);
	indent = "";
	supplier();
	customer();
	product();
	for (auto iter = lst.begin(); iter != lst.end(); ++iter)
		cout << *iter;
	return 0;
}
