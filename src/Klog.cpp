#include <iostream>
#include <fstream>
#include<string>
#include<stdlib.h>
#include<time.h>

using namespace std;



class Klog {
	const string logPath = "res/data/logs.txt";
	string timeString;
	fstream logFile;
	time_t currTime;
	//public methods
	public:
	Klog(){
		//open log file
		try{
			logFile.open(logPath,ios::app);
			currTime = time(NULL);
			timeString = ctime(&currTime);
			logFile<<"\n\n\n-------------------------------------------------------------------\n";
			logFile<<"New Session:\n";
			logFile<<timeString<<endl;
		}catch(exception e){
			cout<<"Error writing logs\n";
		}
	}
	void log(string data){
		//write to file
		try{			
			logFile<<data<<endl;
		}catch(exception e){
			cout<<"Error writing logs\n";
		}
	}

	void clear(){
		try{			
			logFile.close();
			logFile.open(logPath,ios::out);
		}catch(exception e){
			cout<<"Error clearing logs\n";
		}
	}

	~Klog(){
		logFile.close();
	}
};