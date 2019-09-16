#include <iostream>
#include<string>
#include "Klog.cpp"
#include "DataProvider.cpp"
#include "UI.cpp"
using namespace std;

int main(){
	Klog logger;
	logger.clear();
	//DataProvider dp;
	//dp.loadFromFile();

	UI ui;
	ui.showOptions(ui.MAIN_SCREEN);



	/*cout<<"How many do you want me to display?  ";
	int max;
	cin>>max;
	char t = '\t';
	cout<<"SR. First Name\tLast Name\tPhone\t\tEmail\n";
	for(int i=1;i<=max;i++){
		cout<<i<<t<<dp.firstName.at(i)<<t<<dp.lastName.at(i)<<t<<dp.phone.at(i)<<t<<dp.email.at(i)<<endl;
	}*/
	return 0;
}
