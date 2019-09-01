// ConsoleApplication3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//============================================================================
// Name        : phonebook.cpp
// Author      : pruthav
// Version     :
// Copyright   : Your copyright notice
// Description : attempt for phonebook database
//============================================================================

#include <iostream>
#include <fstream>
#include<string>
#include<sstream>

#include<vector>
#include<istream>

using namespace std;

int main() {
	int lines = 0;
	char c = 0;
	string temp;
	ifstream input("dataset.csv", ios::binary);
	vector <string> first_name;
	vector <string> last_name;
	vector <string> phone;
	vector <string> address;
	vector <string> city;
	vector <string> state;
	vector <string> email;



	string str;
	int count = 0;
	while (getline(input, str))
	{
		lines++;
		//cout << str << endl;
		stringstream s(str);

		while (getline(s, temp, ',')) {

			// add all the column data 
			// of a row to a vector 
			switch (count)
			{
			case 0:
			{
				first_name.push_back(temp);
				count++;
				break;
			}
			case 1:
			{
				last_name.push_back(temp);
				count++;
				break;
			}
			case 2:
			{
				phone.push_back(temp);
				count++;
				break;
			}
			case 3:
			{
				email.push_back(temp);
				count++;
				break;
			}
			case 4:
			{
				address.push_back(temp);
				count++;
				break;
			}
			case 5:
			{
				city.push_back(temp);
				count++;
				break;
			}
			case 6:
			{
				state.push_back(temp);
				count = 0;
				break;
			}
			default:
				break;
			}



		}

	}


	char option;
	cout << "do u want to save a contact? (y/n): ";
	cin >> option;
	switch (option)
	{
	case 'y':
	{
		cout << "enter details of ur contact : " << endl;
		cout << "first name ---> ";
		cin >> temp;
		first_name.push_back(temp);
		cout << endl;


		cout << "last name ---> ";
		cin >> temp;
		last_name.push_back(temp);
		cout << endl;


		cout << "addr ---> ";
		cin >> temp;
		address.push_back(temp);
		cout << endl;


		cout << "phone ---> ";
		cin >> temp;
		phone.push_back(temp);
		cout << endl;


		cout << "email ---> ";
		cin >> temp;
		email.push_back(temp);
		cout << endl;


		cout << "state ---> ";
		cin >> temp;
		state.push_back(temp);
		cout << endl;


		cout << "city ---> ";
		cin >> temp;
		city.push_back(temp);
		cout << endl;
		lines++;
		break;
	}
	case 'n':
	{
		break;
	}


	}

	cout << "List of first names " << endl << endl << endl << endl;
	for (int i = 0; i < lines; i++) {
		cout << first_name[i] << endl;
	}
	cout << "List of phones " << endl << endl << endl << endl;
	for (int i = 0; i < lines; i++) {
		cout << phone[i] << endl;
	}
	cout << "List of  last names " << endl << endl << endl << endl;
	for (int i = 0; i < lines; i++) {
		cout << last_name[i] << endl;
	}
	cout << "List of email" << endl << endl << endl << endl;
	for (int i = 0; i < lines; i++) {
		cout << email[i] << endl;
	}
	cout << "List of address " << endl << endl << endl << endl;
	for (int i = 0; i < lines; i++) {
		cout << address[i] << endl;
	}
	cout << "List of states " << endl << endl << endl << endl;
	for (int i = 0; i < lines; i++) {
		cout << state[i] << endl;
	}
	cout << "List of cities " << endl;
	for (int i = 0; i < lines; i++) {
		cout << city[i] << endl;
	}

	return 0;
}


/*
#include <iostream>


int main()
{
	std::cout << "Hello World!\n";
}
*/
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
