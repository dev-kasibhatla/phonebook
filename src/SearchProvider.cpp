#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>
#include<set>
//#include "DataProvider.cpp"
using namespace std;


class SearchProvider{
	string query;
	//vector<string> results;
	set<int> results;
	Klog logger;
	Editor editor;


	bool isSubString(string s1, string s2){
		if(s1.length() < s2.length()){
			return false;
		}else if(s1 == s2){
			return true;
		}
		string *kernels = getKernels(s2.length(),s1);
		int size = s1.length() - s2.length()+1;
		for(int i=0;i<size;i++){
			if(kernels[i] == s2){
				logger.log(s2 + " exists in "+s1);
				return true;
			}
		}
		return false;
	}

	string * getKernels(int kSize, string s1){
		string *kernels = new string[s1.length() - kSize+1];
		string temp="";
		for(int i=0;i<(s1.length() - kSize+1);i++){
			for(int j=i;j<i+kSize;j++){
				temp += s1[j];
			}
			kernels[i] = temp;
			temp="";
		}
		return kernels;
	}


	public:
	SearchProvider(){
		editor.loadFromFile();
	}

	set<int> searchEverything(string q){
		results.clear();
		searchNames(q);
		searchRest(q);
		return results;
	}

	void searchNames(string q){
		logger.log("Query: "+q);
		int size = editor.firstName.size();
		for(int i=1;i<size;i++){
			if(isSubString(editor.getName(i), q)){
				results.insert(i);
			}
		}
		//done searching names
	}

	void searchRest(string q){
		int size = editor.firstName.size();
		for(int i=1;i<size;i++){
			if(isSubString(editor.phone.at(i), q)){
				results.insert(i);
				continue;
			}
			if(isSubString(editor.email.at(i), q)){
				results.insert(i);
				continue;
			}
			if(isSubString(editor.address.at(i), q)){
				results.insert(i);
				continue;
			}
			if(isSubString(editor.city.at(i), q)){
				results.insert(i);
				continue;
			}
			if(isSubString(editor.state.at(i), q)){
				results.insert(i);
				continue;
			}
		}
	}
};