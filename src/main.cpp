#include <iostream>
#include "Klog.cpp"
#include "DataProvider.cpp"
using namespace std;

int main(){
	Klog logger;
	logger.clear();
	DataProvider dataProvider;
	dataProvider.load();	
	return 0;
}