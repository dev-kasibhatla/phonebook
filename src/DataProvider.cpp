#include <iostream>
#include <fstream>
#include<string>
#include<sstream>
#include<vector>
#include<istream>


using namespace std;

class DataProvider	{
	string dataPath =  "res/data/dataset.csv", objectPath = "res/data/.objects/dataprovider.txt";
	fstream csvData,objectFile;
	
	public:

	vector<string> firstName, lastName, phone, email, address, city, state; 
	//public methods
	DataProvider(){
		csvData.open(dataPath,ios::in);
	}

	void loadFromFile(){
		string line, temp="";
		int currWord=0;
		while(getline(csvData,line)){
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
							break;
					}					
					temp = "";
					currWord++;
				}else if(line[i] == '\n' || line[i]=='\r'){
					state.push_back(temp);
					temp="";
					currWord=0;
				}else{
					temp.push_back(line[i]);
				}
			}
		}	
		//all data added to memory
		cout<<firstName.size()<<" contacts loaded to memory\n";	
	}

	void saveToFile(){
		//reopen file as out
		csvData.close();
		csvData.open(dataPath,ios::out);
		for (int i=0;i<firstName.size();i++){
			csvData<<firstName.at(i)<<","<<lastName.at(i)<<","<<phone.at(i)<<
			","<<email.at(i)<<","<<address.at(i)<<","<<city.at(i)<<","<<state.at(i)<<endl;
		}
		cout<<"Contacts saved to file\n";	
		//reopen as in
		csvData.close();
		csvData.open(dataPath,ios::in);
	}

	void load(){
		try{
			objectFile.open(objectPath,ios::binary);
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

	/**
	 * Save instance to memory
	 * */
	void save (){
		objectFile.open(objectPath,ios::binary);
		objectFile.write((char*)this,sizeof(*this));
		objectFile.close();
		cout<<"Successfully saved object\n";
	}

	/**
	 * To check if all vectors are of the same size
	 * */
	void printSizesOfAll(){
		cout<<"sizes:\n";
		cout<<firstName.size()<<"\t"<<lastName.size()<<"\t"<<phone.size()<<"\t"<<email.size()<<"\t"<<address.size()
		<<city.size()<<"\t"<<state.size()<<"\n";
	}

	~DataProvider(){
		try{
			csvData.close();
		}catch(exception e){
			cout<<"Dataset already closed\n";
		}
	}

};
