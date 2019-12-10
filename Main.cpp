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
	Vers : 0.50.0 (Full, fix, binary[small fix])
	Date : 12/9/19
	Desc : The finance calculator really only serves the purpose of holding the saving and spending
	percents you want and your yearly paychecks.
	What's new : All menu options implemented!
	TODO : UI and Android App Port
*/
inputList* head = NULL;
inputList* ptr = new inputList;
int inputNum = 0; //This is probably going to be the index
int main() {
	int i = 0;
	cout << fixed << setprecision(2);
	vector<double> paychecks; //This will actually hold the paycheck values
	string input, throwaway; //Just used for start menu input and throwaway is to eat the strings when taking input
	int numPut; //Used for number input, obviously
	bool running = false; 
	char key = ' '; 
	//The in versions are what are ripped from the input file
	double filePay = 0, inPay, fileSpend = 0, inSpend, fileSave = 0, inSave, fileSpendPercent = 0, inSpendPercent, fileSavePercent = 0,
		inSavePercent, filePaychecks;
	ifstream inFile, paycheckFile;

	inFile.open("money.txt");
	paycheckFile.open("paychecks.txt");
	inFile >> throwaway >> inPay; //First, it loads the pay

	inFile >> throwaway >> inSpend; //Second, it loads the spending

	inFile >> throwaway >> inSave; //Third, it loads the saving

	inFile >> inSpendPercent;

	inFile  >> inSavePercent;

	while (paycheckFile >> filePaychecks) {
		paychecks.push_back(filePaychecks); //Finally, you load all the paychecks
	}
	//no shit
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
			cout << "***************************" << endl;
			cout << "*        APP  MENU        *" << endl;
			cout << "*1-    View Finances    -1*" << endl;
			cout << "*2-     Add Paycheck    -2*" << endl;
			cout << "*3-    Adjust Amounts   -3*" << endl;
			cout << "*0-         Quit        -0*" << endl;
			cout << "*Enter 44 to return to main*" << endl;
			cout << "****************************" << endl;
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
				if (viewnum != VIEWALL && viewnum != VIEWPAY && viewnum != 44) {
					cout << "Please enter a valid input! Press any key to continue. . ." << endl;
					key = _getch();
					system("CLS");
				}
			} while (viewnum != VIEWALL && viewnum != VIEWPAY && viewnum != 44);
			if (viewnum == VIEWALL) {
				cout << "Last Paycheck: $" << inPay << endl;
				cout << "Spending: $" << inSpend + fileSpend << endl;
				cout << "Saving: $" << inSave + fileSave << endl;
			}
			else if (viewnum == VIEWPAY) {
				for (unsigned int i = 0; i < paychecks.size(); i++) {
					paycheckFile >> paychecks[i];
					cout << "Week " << i + 1 << ": " << paychecks[i] << endl;
				}
			}
			else if (viewnum == 44) {
				continue;
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
				if (addnum != ADDCURRENT && addnum != ADDEXISTING && addnum != 44) {
					cout << "Please enter a valid input! Press any key to continue. . ." << endl;
					key = _getch();
					system("CLS");
				}
			} while (addnum != ADDCURRENT && addnum != ADDEXISTING && addnum != 44);

			ptr->inp = addnum;
			ptr->next = head;
			head = ptr;
			ptr = new inputList;

			if (addnum == ADDCURRENT) {
				cout << "~* Enter your paycheck: ";
				cin >> filePay;
				fileSpend = spendPercent(filePay, inSpendPercent);
				fileSave = savePercent(filePay, inSavePercent);
			}

			else if (addnum == ADDEXISTING) {
				//This is for stuff you already have recorded
				int existnum;

				do {
					cout << "********************" << endl;
					cout << "*    ADD SubMENU    *" << endl;
					cout << "*8- Add  Paycheck -8*" << endl;
					cout << "*9- Add  Spending -9*" << endl;
					cout << "*10- Add  Saving -10*" << endl;
					cout << "*********************" << endl;
					key = ' ';
					cin >> existnum;
					if (existnum != ADDPAY && existnum != ADDSPEND && existnum != ADDSAVE && existnum != 44) {
						cout << "Please enter a valid input! Press any key to continue. . ." << endl;
						key = _getch();
						system("CLS");
					}
				} while (existnum != ADDPAY && existnum != ADDSPEND && existnum != ADDSAVE && existnum != 44);

				ptr->inp = existnum;
				ptr->next = head;
				head = ptr;
				ptr = new inputList;

				if (existnum == ADDPAY) {
					int paycheckAmt;
					double loopPaycheck;
					cout << "How many paychecks would you like to add? ";
					cin >> paycheckAmt;
					for (int i = 0; i < paycheckAmt; i++) {
						cout << "~* Enter your paycheck: ";
						cin >> loopPaycheck;
						addToVec(paychecks, loopPaycheck);
					}
				}

				if (existnum == ADDSPEND) {
					double tempspendnum;
					cout << "~* Enter your spending: ";
					cin >> tempspendnum;
					fileSpend += tempspendnum;
				}

				if (existnum == ADDSAVE) {
					double tempsavenum;
					cout << "~* Enter your saving: ";
					cin >> tempsavenum;
					fileSave += tempsavenum;
				}

				if (existnum == 44) {
					continue;
				}
			}
			else if (addnum == 44) {
				continue;
			}
		}
		if (numPut == ADJUST) {
			/*
			* - Adjust Percentages
			* - Adjust Spendings
			* - Adjust Savings
			*/
			int adjustnum;
			do {
				cout << "**************************" << endl;
				cout << "*11-  Adjust Percents -11*" << endl;
				cout << "*12-  Adjust Spending -12*" << endl;
				cout << "*13-  Adjust Saving   -13*" << endl;
				cout << "**************************" << endl;
				key = ' ';
				cin >> adjustnum;
				if (adjustnum != ADJUSTPERCENT && adjustnum != ADJUSTSPENDING && adjustnum != ADJUSTSAVING&& adjustnum != 44) {
					cout << "Please enter a valid input! Press any key to continue. . ." << endl;
					key = _getch();
					system("CLS");
				}
			} while (adjustnum != ADJUSTPERCENT && adjustnum != ADJUSTSPENDING && adjustnum != ADJUSTSAVING && adjustnum != 44);
			if (adjustnum == ADJUSTPERCENT) {
				cout << "Current Spending Percent: " << inSpendPercent << endl;
				cout << "Current Saving Percent: " << inSavePercent << endl;
				do {
					cout << "~* Enter your spending percent: ";
					cin >> inSpendPercent;
					if (inSpendPercent > 100) {
						cout << "Please enter a number between 0-100!" << endl;
					}
				} while (inSpendPercent > 100);
				inSavePercent = 100 - inSpendPercent;
				cout << "Your save percent is now " << inSavePercent << endl;
			}
			else if (adjustnum == ADJUSTSPENDING) {
				cout << "~* Enter your new spending amount: ";
				cin >> inSpend;
				inSpend -= fileSpend;
			}
			else if (adjustnum == ADJUSTSAVING) {
				cout << "~* Enter your new saving amount: ";
				cin >> inSave;
				inSave -= fileSave;
			}
			else if (adjustnum == 44) {
				continue;
			}
		}
	} //end of running while loop

	inFile.close();
	paycheckFile.close();

	ofstream paycheckOut("paychecks.txt", ios_base::out);
	ofstream outFile("money.txt", ios_base::out);
	/*
	6 - Add a current Paycheck - Implemented!
	8 - Add an existing Paycheck - Implemented!
	9 - Add spending cash money - Implemented!
	10 - Add saving cash money - Implemented!
	*/
	while (head != NULL) {
		if (head->inp == 6) {
			inPay += filePay;
			inSpend += fileSpend;
			inSave += fileSave;
		}
		if (head->inp == 9) {
			inSpend += fileSpend;
		}
		if (head->inp == 10) {
			inSave += fileSave;
		}
		if (head->inp == 12) {
			inPay;
		}
		if (head->inp == 13) {
			inSave;
		}
		head = head->next;
	}
	delete ptr, head;
	outFile << fixed << setprecision(2) << "Paycheck(s): " << inPay << endl;
	outFile << fixed << setprecision(2) << "Spending: " << inSpend << endl;
	outFile << fixed << setprecision(2) << "Saving: " << inSave << endl; 
	outFile << fixed << setprecision(2) << inSpendPercent << endl;
	outFile << fixed << setprecision(2) << inSavePercent << endl;
	for (int i = 0; i < paychecks.size(); i++) {
		paycheckOut << paychecks[i] << endl;
	}
	outFile.close();
	paycheckOut.close();
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
