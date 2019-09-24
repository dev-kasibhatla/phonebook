#include <iostream>
#include <string>
#include<map>
#include<iterator>
#include<iomanip>
#include<stdlib.h>
#include "SearchProvider.cpp"
#include<set>

/**
 * UI has two sections:
 * 1. Options
 * 2. Data
 *
 * Options will always occupy top end of the screen and will be indexed by small letters
 * Data will always appear below options and will be indexed by numbers
 */

using namespace std;

int i_edit_num;  //global variable used for edit Contact functionality now can be used for all places where array index is required
 class UI{

    //private members
    //create a map for all options
    map<char,string> optionMap;
    //DataProvider dp;
    Editor editor;
    SearchProvider sp;
    string currentQuery;
    void setOptions(){
        optionMap.insert(pair<char,string>('a',"List Contacts"));
        optionMap.insert(pair<char,string>('b',"Search"));
        optionMap.insert(pair<char,string>('c',"Create a contact"));
        optionMap.insert(pair<char,string>('e',"Edit this contact"));
        optionMap.insert(pair<char,string>('d',"Delete this contact"));
        optionMap.insert(pair<char,string>('h',"Home"));


        optionMap.insert(pair<char,string>('x',"Exit"));
    }

    void printOptions(string op){
        int width = 120;
        int len = 7;
        for(int i=0;i<width;i++){
            cout<<"-";
        }
        cout<<"\n";
        cout<<setw((width/2)+len/2)<<right<<"//OPTIONS//"<<endl;

        cout<<endl;
        string opConstructor="";
        for(int i=0;i<op.length();i++){
            //cout<<op[i]<<". "<<optionMap.at(op[i])<<"\t";
            opConstructor += op[i];
            opConstructor += ". ";
            opConstructor+= optionMap.at(op[i])+ "\t";
        }
        cout<<setw((width/2)+opConstructor.length()/2 - 7)<<right<<opConstructor<<endl;
        for(int i=0;i<width;i++){
            cout<<"-";
        }
        cout<<"\n\n\n";
    }

    void startSwitch(int context){
        CURRENT_CONTEXT = context;
        //clear screen
        char choice;
        cout<<"Input: ";
        cin>>choice;
        switch(context){
            case -1:
                //main screen
                switch(choice){
                    case 'a':
                        //List contacts
                        showList(1);
                        break;
                    case 'b':
                        //Search
                        searchContacts();
                        //showOptions(MAIN_SCREEN);
                        break;
                    case 'c':
                        //Create contact
                        editor.add();
                        break;
                    default:
                        //Bad choice
                        cout<<"Sorry. You entered an invalid option\n";
                        startSwitch(context);
                        break;
                }
                break;
            case -4:
                //Contact is being displayed abdhe
                switch(choice){
                    case 'a':
                        showList(1);
                        break;
                    case 'b':
                        //search
                        break;
                    case 'd':
                        //delete
                        editor.del(i_edit_num);
                        showOptions(MAIN_SCREEN);
                        break;
                    case 'e':
                        //edit
                        editor.edit(i_edit_num);
                        displayContact(i_edit_num);
                        break;
                    case 'h':
                        //go home
                        showOptions(MAIN_SCREEN);
                        break;
                    default:
                        cout<<"Sorry. You entered an invalid option\n";
                        startSwitch(context);
                        break;

                }

                break;
            default:
                cout<<"A contextual error occured\n";
                break;
        }
    }

    void displayContact(int index){
        string name = editor.getName(index);
        string phone = editor.phone.at(index);
        string email = editor.email.at(index);
        string address = editor.address.at(index);
        string city = editor.city.at(index);
        string state = editor.state.at(index);

        system("clear");

        //show a form
        showOptions(DISPLAY_CONTACT);
        cout<<"\n";
        cout<<"\t\tName:\t\t"<<name<<endl;
        cout<<"\t\tPhone:\t\t"<<phone<<endl;
        cout<<"\t\tEmail:\t\t"<<email<<endl;
        cout<<"\t\tAddress:\t"<<address<<endl;
        cout<<"\t\tCity:\t\t"<<city<<endl;
        cout<<"\t\tState:\t\t"<<state<<endl;
        cout<<"\n\n\t";
        startSwitch(CURRENT_CONTEXT);

    }

    public:

    int CURRENT_CONTEXT = 0;
    int MAIN_SCREEN = -1, LIST_CONTACTS=-2, CREATE_CONTACTS=-3, DISPLAY_CONTACT=-4;
    UI (){

        editor.loadFromFile();
        setOptions();

    }

    void showOptions(int context){
        string op;
        CURRENT_CONTEXT = context;
        switch (context)
        {
            case -1:
                //Main screen
                //Show List all, search, create, exit
                op = "abcx";
                system("clear");
                printOptions(op);
                startSwitch(context);
                break;
            case -2:
                break;
            case -3:
                break;
            case -4:
                //A contact is being displayed
                op = "abedh";
                printOptions(op);
                break;
            default:
                cout<<"Error while showing options";
                break;
        }
        //startSwitch(context);

    }

    void showList(int start){
        system("clear");
        int max = start + 50;
        int width = 120;
        for(int i=0;i<width;i++){
            cout<<"-";
        }
        cout<<"\n";
        cout<<setw((width/2)+5)<<right<<"//LIST//"<<endl;
        for(int i=0;i<width;i++){
            cout<<"-";
        }
        cout<<"\n\n";

        if(start>=editor.size()){
            start = editor.size() - 49;
            max = start + 50;
            cout<<"No more contacts to display\n\n";
        }else if(start < 0){
            start =1;
            max = start + 50;
        }
        for (int i =start; i <= editor.size(); i+=2){
            if(i >= max){
                break;
            }
            cout<<i<<".\t";
            cout<<editor.getName(i);
            if(i >= editor.size()){
                break;
            }
            if(i >= max){
                break;
            }
            if(editor.getName(i).length() >= 16){
                cout<<"\t\t\t\t"<<i+1<<".\t";
            }else{
                cout<<"\t\t\t\t\t"<<i+1<<".\t";
            }            
            cout<<editor.getName(i+1)<<endl;
        }
        cout<<"\n[type 'm' for more, 'p' for previous, 's' to select a contact\nType anything else to go to home screen]: ";
        char c;
        cin>>c;
        if(c=='m' || c == 'M'){
            showList(max);
        }else if(c == 'p' || c=='P'){
            showList(start-50);
        }else if(c == 's'){
            cout<<"Please enter the index:  ";
            // int i;
            cin>>i_edit_num;
            //system("clear");
            displayContact(i_edit_num);
        }else{
            cin.clear();
            system("clear");
            showOptions(MAIN_SCREEN);
        }
    }

    void searchContacts(){
        cout<<"Type anything: ";
        cin.clear();
        string temp;
        cin>>temp;
        //todo: convert all strings to lowercase
        set<int> res = sp.searchEverything(temp);
        set<int>::iterator it;
        cout<<endl;
        for (it = res.begin(); it != res.end(); ++it) { 
            cout<<editor.getName(*it)<<endl;
        }    
        //todo: write a custom showlist function
    }   
};
