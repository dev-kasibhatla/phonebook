#include <iostream>
#include <fstream>
#include<string>
#include<sstream>
#include<vector>
#include<istream>
#include<stdlib.h>


using namespace std;

class DataProvider	{
	protected:
	string dataPath =  "res/data/dataset.csv";// objectPath = "res/data/.objects/dataprovider.txt";
	fstream csvData;//objectFile;

	void clearVectors(){
		firstName.clear();
		lastName.clear();
		phone.clear();
		email.clear();
		address.clear();
		city.clear();
		state.clear();
	}

	public:

	vector<string> firstName, lastName, phone, email, address, city, state;
	//public methods
	DataProvider(){
		csvData.open(dataPath,ios::in);
	}

	void loadFromFile(){
		clearVectors();
		string line, temp="";
		int currWord=0;
		while(getline(csvData,line)){
			cout<<line[line.length()-1];
			for(int i=0;i<line.length();i++){
				if(line[i] == ','){
					switch (currWord){
						case 0:
							firstName.push_back(temp);
							break;
						case 1:
							lastName.push_back(temp);
							break;
						case 2:
							phone.push_back(temp);
							break;
						case 3:
							email.push_back(temp);
							break;
						case 4:
							address.push_back(temp);
							break;
						case 5:
							city.push_back(temp);
							break;
						default:
							cout<<"\nError adding elements to vectors\n";
							exit(0);
					}
					temp = "";
					currWord++;
				}else if(line[i] == '\n' || line[i]=='\r'){
					state.push_back(temp);
					temp="";
					currWord=0;
				}else{
					//cout<<line[i];
					temp.push_back(line[i]);
				}
			}
		}
		//all data added to memory
		//cout<<firstName.size() - 1<<" contacts loaded to memory\n";
	}

	void saveToFile(){
		//reopen file as out
		
		try{
			csvData.close();
			csvData.open(dataPath,ios::out);
			for (int i=0;i<firstName.size();i++){
				csvData<<firstName.at(i)<<","<<lastName.at(i)<<","<<phone.at(i)<<
				","<<email.at(i)<<","<<address.at(i)<<","<<city.at(i)<<","<<state.at(i)<<'\r';
			}
			//cout<<"Contacts saved to file\n";
		}catch(exception e){
			cout<<"Error saving to file "<<e.what();
		}
		//reopen as in
		csvData.close();
		csvData.open(dataPath,ios::in);
	}
	/*
	void load(){
		try{
			objectFile.open(objectPath,ios::in);
			objectFile.read((char*)this,sizeof(*this));
			objectFile.close();
			if(firstName.size()<2){
				loadFromFile();
				save();
			}
		}catch(exception e){
			cout<<"error reading object\n";
			loadFromFile();
		}
	}
	*/
	/**
	 * Save instance to memory
	 * */
	/*
	void save (){
		objectFile.open(objectPath,ios::out);
		objectFile.write((char*)this,sizeof(*this));
		objectFile.close();
		cout<<"Successfully saved object\n";
	}
	*/
	/**
	 * To check if all vectors are of the same size
	 * */


	void add(){
		string temp1,temp2;
		cout<<"Creating a new contact. Please enter required details:\n";
		cout<<"First and last name: ";
		cin>>temp1>>temp2;
		firstName.push_back(temp1);
		lastName.push_back(temp2);
		cout<<"Phone: ";
		cin>>temp1;
		cout<<"email: ";
		cin>>temp2;
		phone.push_back(temp1);
		email.push_back(temp2);
		cout<<"Address: ";
		cin.ignore();
		getline(cin,temp1);
		cout<<"City: ";
		cin>>temp2;
		address.push_back(temp1);
		city.push_back(temp2);
		cout<<"State: ";
		cin>>temp1;
		state.push_back(temp1);

		cout<<"Data has been collected. Save?[y/n]:  ";
		char choice;
		cin>>choice;
		if(choice=='y' || choice == 'Y'){
			saveToFile();
			cout<<firstName.back()<<" was saved.\n";
		}else{
			cout<<"Contact was discarded.\n";
		}
	}

	bool del(int index){
		string ftemp = getName(index);
		firstName.erase(firstName.begin()+index);
		lastName.erase(lastName.begin()+index);
		phone.erase(phone.begin()+index);
		email.erase(email.begin()+index);
		address.erase(address.begin()+index);
		city.erase(city.begin()+index);
		state.erase(state.begin()+index);
		saveToFile();
		system("clear");
		cout<<endl<<ftemp<<" was deleted\n";
	}

	int size(){
		//returns number of contacts
		return firstName.size() - 1;
	}

	string getName(int index){
		string name="";
		name += firstName.at(index);
		name += " ";
		name += lastName.at(index);
		return name;
	}

	~DataProvider(){
		try{
			csvData.close();
		}catch(exception e){
			cout<<"Dataset already closed\n";
		}
	}
};

class Editor :public DataProvider {
	string * explode(string s){
		string *n = new string[2];
		string temp1, temp2;
		bool flag = false;
		for(int i=0;i<s.length();i++){
			if(!flag){
				if(s[i] == ' '){
					n[0] = temp1;
					flag=true;
				}else{
					temp1 += s[i];
				}
			}else{
				temp2 += s[i];
			}
		}
		n[1] = temp2;
		return n;
	}

public:

	void edit(int index){
		string temp1;
		cout<<"[Type to change. Press enter to keep the same\n";
		cout<<"Name: ";
		cin.ignore();
		getline(cin,temp1);
		if(temp1 != ""){
			string *n = explode(temp1);
			firstName.at(index) = n[0];
			lastName.at(index) = n[1];
		}else{
			//move a line up
			system("printf \"\033[1A\"");
			cout<<"Name: "<<getName(index)<<endl;
		}
		//cin.ignore();
		cout<<"Phone: ";
		getline(cin,temp1);
		if(temp1 !=""){
			phone.at(index) = temp1;
		}else{
			//move a line up
			system("printf \"\033[1A\"");
			cout<<"Phone: "<<phone.at(index)<<endl;
		}
		//cin.ignore();
		cout<<"Email: ";
		getline(cin,temp1);
		if(temp1 !=""){
			email.at(index) = temp1;
		}else{
			//move a line up
			system("printf \"\033[1A\"");
			cout<<"Email: "<<email.at(index)<<endl;
		}
		//cin.ignore();
		cout<<"Address: ";
		getline(cin,temp1);
		if(temp1 !=""){
			address.at(index) = temp1;
		}else{
			//move a line up
			system("printf \"\033[1A\"");
			cout<<"Address: "<<address.at(index)<<endl;
		}
		//cin.ignore();
		cout<<"City: ";
		getline(cin,temp1);
		if(temp1 !=""){
			city.at(index) = temp1;
		}else{
			//move a line up
			system("printf \"\033[1A\"");
			cout<<"City: "<<city.at(index)<<endl;
		}
		//cin.ignore();
		cout<<"State: ";
		getline(cin,temp1);
		if(temp1 !=""){
			state.at(index) = temp1;
		}else{
			//move a line up
			system("printf \"\033[1A\"");
			cout<<"State: "<<state.at(index)<<endl;
		}
		cout<<"Save these changes? [y/n]: ";
		char c;
		cin>>c;
		if(c == 'y' || c=='Y'){
			saveToFile();
			system("clear");
			cout<<"\nChanges to "<<getName(index)<<" were saved\n";
		}else{
			system("clear");
			cout<<"\nChanges to "<<getName(index)<<" were NOT saved\n";
		}
		
	}

};
