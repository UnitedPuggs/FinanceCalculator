#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct inputList {
	int inp;
	inputList* next;
};
enum MENU {
	EXIT,
	VIEW,
	ADD,
	ADJUST,
	VIEWALL,
	VIEWPAY,
	ADDCURRENT,
	ADDEXISTING,
	ADDPAY,
	ADDSPEND,
	ADDSAVE
};
double savePercent(double amt, double pct);
double spendPercent(double amt, double pct);
string toupperStr(string str);
void addToVec(vector<double> &vec, double paycheck);
void printList(inputList* head);
