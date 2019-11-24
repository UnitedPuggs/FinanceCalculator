#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include "Header.h"
using namespace std;
/*
	Author : Eddie Poulson
	Vers : 0.11.0 (Full, fix, binary[small fix])
	Date : 11/21/19
	Desc : The finance calculator really only serves the purpose of holding the saving and spending
	percents you want and your yearly paychecks.
	What's new : Replaced shitty big old array for a linked list :)
*/
inputList* head = NULL;
inputList* ptr = new inputList;
int inputNum = 0; //This is probably going to be the index
int main() {
	cout << fixed << setprecision(2);
	vector<double> paychecks; //This will actually hold the paycheck values
	string input; //Just used for start menu input
	int numPut; //Used for number input, obviously
	bool running = false; 
	char key = ' '; 
	//The in versions are what are ripped from the input file
	double filePay = 0, inPay, fileSpend, inSpend, fileSave, inSave;
	ifstream inFile, paycheckFile;
	inFile.open("money.txt");
	paycheckFile.open("paychecks.txt");
	inFile >> inPay; //First, it loads the pay
	inFile >> inSpend; //Second, it loads the spending
	inFile >> inSave; //Third, it loads the saving
	//no shit, retard
	do {
		cout << "**************" << endl;
		cout << "* START MENU *" << endl;
		cout << "* -  Start - *" << endl;
		cout << "* -  Quit  - *" << endl;
		cout << "**************" << endl;
		key = ' ';
		cin >> input; //basic do-while input confirmation loop
		if (toupperStr(input) != "START" && toupperStr(input) != "QUIT") {
			cout << "Please enter a valid input! Press any key to continue. . ." << endl;
			key = _getch();
			system("CLS");
		}
	} while (toupperStr(input) != "START" && toupperStr(input) != "QUIT");
	if (toupperStr(input) == "START") {
		running = true;
	}
	else if (toupperStr(input) == "QUIT") {
		cout << "Shutting down. . ." << endl;
	}
	while (running) {
		cout << "Press any key to continue. . ." << endl;
		key = ' ';
		key = _getch();
		system("CLS");
		do {
			cout << "*********************" << endl;
			cout << "*     APP   MENU     *" << endl;
			cout << "*1- View Finances  -1*" << endl;
			cout << "*2-  Add Paycheck  -2*" << endl;
			cout << "*3- Adjust Amounts -3*" << endl;
			cout << "*0-      Quit      -0*" << endl;
			cout << "**********************" << endl;
			key = ' ';
			cin >> numPut;
			if (numPut != EXIT && numPut != VIEW && numPut != ADD && numPut != ADJUST) {
				cout << "Please enter a valid input! Press any key to continue. . ." << endl;
				key = _getch();
				system("CLS");
			}
		} while (numPut != EXIT && numPut != VIEW && numPut != ADD && numPut != ADJUST);
		if (numPut == EXIT) {
			running = false;
		}
		if (numPut == VIEW) {
			int viewnum;
			do {
				cout << "*********************" << endl;
				cout << "*     VIEW MENU     *" << endl;
				cout << "*4-   View Basic   -4*" << endl;
				cout << "*5- View Paychecks -5*" << endl;
				cout << "**********************" << endl;
				key = ' ';
				cin >> viewnum;
				if (viewnum != VIEWALL && viewnum != VIEWPAY) {
					cout << "Please enter a valid input! Press any key to continue. . ." << endl;
					key = _getch();
					system("CLS");
				}
			} while (viewnum != VIEWALL && viewnum != VIEWPAY);
			if (viewnum == VIEWALL) {
				inFile >> inPay;
				inFile >> inSpend;
				inFile >> inSave;
				cout << "Last Paycheck: $" << inPay << endl;
				cout << "Spending: $" << inSpend << endl;
				cout << "Saving: $" << inSave << endl;
			}
			else if (viewnum == VIEWPAY) {
				for (unsigned int i = 0; i < paychecks.size(); i++) {
					paycheckFile >> paychecks[i];
					cout << "Week: " << i + 1 << " " << paychecks[i] << endl;
				}
			}
		}
		if (numPut == ADD) {
			int addnum;
			do {
				cout << "*************************" << endl;
				cout << "*        ADD MENU       *" << endl;
				cout << "*6- Current Paycheck  -6*" << endl;
				cout << "*7- Existing Paycheck -7*" << endl;
				cout << "*************************" << endl;
				key = ' ';
				cin >> addnum;
				if (addnum != ADDCURRENT && addnum != ADDEXISTING) {
					cout << "Please enter a valid input! Press any key to continue. . ." << endl;
					key = _getch();
					system("CLS");
				}
			} while (addnum != ADDCURRENT && addnum != ADDEXISTING);
			ptr->inp = addnum;
			ptr->next = head;
			head = ptr;
			ptr = new inputList;
			if (addnum == ADDCURRENT) {
				cout << "~* Enter your paycheck: ";
				cin >> addnum;
				fileSpend = spendPercent(filePay, 70);
				fileSave = savePercent(filePay, 30);
			}
			else if (addnum == ADDEXISTING) {
				int existnum;
				do {
					cout << "********************" << endl;
					cout << "*    ADD SubMENU    *" << endl;
					cout << "*8- Add  Paycheck -8*" << endl;
					cout << "*9- Add  Spending -9*" << endl;
					cout << "*10- Add Saving - 10*" << endl;
					cout << "*********************" << endl;
					key = ' ';
					cin >> existnum;
					if (existnum != ADDPAY && existnum != ADDSPEND && existnum != ADDSAVE) {
						cout << "Please enter a valid input! Press any key to continue. . ." << endl;
						key = _getch();
						system("CLS");
					}
				} while (existnum != ADDPAY && existnum != ADDSPEND && existnum != ADDSAVE);
				ptr->inp = existnum;
				ptr->next = head;
				head = ptr;
				ptr = new inputList;
			}
		}
		if (numPut == ADJUST) {

		}
	} //end of running while loop
	printList(head);
	inFile >> inPay;
	inFile >> inSpend;
	inFile >> inSave;

	inFile.close();
	paycheckFile.close();

	ofstream paycheckOut("paychecks.txt", ios_base::out);
	ofstream outFile("money.txt", ios_base::out);
	//if()
	return 0;
}

double savePercent(double amt, double pct) {
	double total = amt * (pct / 100);
	return total;
}

double spendPercent(double amt, double pct) {
	double total = amt * (pct / 100);
	return total;
}

string toupperStr(string str) {
	for (int i = 0; i < str.length(); i++) {
		str[i] = toupper(str[i]);
	}
	return str;
}

void addToVec(vector<double>& vec, double paycheck) {
	vec.push_back(paycheck);
}
void printList(inputList* head) {
	while (head != NULL) {
		cout << head->inp << " ";
		head = head->next;
	}
}
