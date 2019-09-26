#include <iostream>
#include <stdbool.h>
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
bool invalid_choice = 0;
int i_edit_num;  //global variable used for edit Contact functionality now can be used for all places where array index is required
 class UI{

    //private members
    //create a map for all options
    map<char,string> optionMap;
    //DataProvider dp;
    Editor editor;
    string currentQuery;
    void setOptions(){
        optionMap.insert(pair<char,string>('a',"List Contacts"));
        optionMap.insert(pair<char,string>('b',"Search"));
        optionMap.insert(pair<char,string>('c',"Create a contact"));
        optionMap.insert(pair<char,string>('e',"Edit contact"));
        optionMap.insert(pair<char,string>('d',"Delete contact"));
        optionMap.insert(pair<char,string>('h',"Home"));
        optionMap.insert(pair<char,string>('m',"Show More"));
        optionMap.insert(pair<char,string>('p',"Show Previous"));
        optionMap.insert(pair<char,string>('s',"Select"));

        optionMap.insert(pair<char,string>('x',"Exit"));
    }

    void printOptions(string op, string title){
        int width = 120;
        int len = 7;
        for(int i=0;i<width;i++){
            cout<<"-";
        }
        cout<<"\n";
        cout<<setw((width/2)+len/2)<<right<<"//"<<title<<"//"<<endl;

        cout<<endl;
        string opConstructor="";
        for(int i=0;i<op.length();i++){
            //cout<<op[i]<<". "<<optionMap.at(op[i])<<"\t";
            opConstructor += op[i];
            opConstructor += ". ";
            opConstructor+= optionMap.at(op[i])+ "     ";
            /*if(optionMap.at(op[i]).length() > 15){
                cout<<'\t';
            }*/
        }
        cout<<setw((width/2)+opConstructor.length()/2 + 7)<<right<<opConstructor<<endl;
        for(int i=0;i<width;i++){
            cout<<"-";
        }
        cout<<"\n\n\n";
    }

    void startSwitch(int context){
        CURRENT_CONTEXT = context;
        //clear screen
        string choice;
        if(invalid_choice){cout<<"Invalid Choice was entered please try again\n\n";invalid_choice=0;}
        cout<<"Input: ";
        getline(cin,choice);
        //cin.ignore(numeric_limits<streamsize>::max(),'\n'); 
        switch(context){
            case -1:
                //main screen
                if(choice.length()==1){              

                    switch(choice[0]){
                        case 'a':
                            //List contacts
                            showList(1);
                            break;
                        case 'b':
                            //Search
                            searchContacts();
                            //showOptions(MAIN_SCREEN);
                            break;
                        case 'c': {
                            //Create contact
                            int s = editor.size();                        
                            editor.add();
                            if(s < editor.size()){
                                //new contact was added
                                displayContact(editor.size());
                            }else{
                                showOptions(MAIN_SCREEN);
                            }
                            
                            break;
                        }
                        case 'x':
                            cout<<"User chose to exit\nBye :)\n\n";
                            exit(0);
                        default:
                            //Bad choice

                           invalid_choice = 1;
                        showOptions(MAIN_SCREEN); 
                            break;
                    }
                    
                }
                else{
                  
                    invalid_choice = 1;
                    showOptions(MAIN_SCREEN); 
                    //Bad choice
                    
                             
                }
                break;
            case -4:
                //Contact is being displayed abdhex
               if(choice.length()==1){

                    switch(choice[0]){
                        case 'a':
                            showList(1);
                            break;
                        case 'b':
                            //search
                            searchContacts();
                            break;
                        case 'd':
                            //delete
                            editor.del(i_edit_num);
                            showOptions(MAIN_SCREEN);
                            break;
                        case 'e':
                            //edit
                            if(!editor.edit(i_edit_num)){
                                editor.loadFromFile();
                            }
                            displayContact(i_edit_num);
                            
                            break;
                        case 'h':
                            //go home
                            showOptions(MAIN_SCREEN);
                            break;
                        case 'x':
                            cout<<"User chose to exit\nBye :)\n\n";
                            exit(0);
                        default:
                            invalid_choice = 1;
                            showOptions(MAIN_SCREEN); 
                            break;

                    }
                }
                else{
                    invalid_choice = 1;
                    cout<<"Sorry. You entered an invalid option\n";
                    startSwitch(context);

                }
                break;
            default:
                cout<<"A contextual error occured\n";
                break;
        }
    }

    void displayContact(int index){
        i_edit_num = index;
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

    void showList(set<int> res, int start){
        
        //cout<<endl;
        system("clear");
        //boiler plate
        int width = 120, max = 25;
        
        cout<<res.size()<<" search results"<<endl;
        showOptions(SEARCH_CONTACTS);
        cout<<"";
        if(res.size() == 0){
            cout<<"No results to display :(\nWould you like to search for something else?[y/n]:  ";
            string c; 
            getline(cin,c);
            //cin.ignore(numeric_limits<streamsize>::max(),'\n'); 
            if(c =="y" || c=="Y"){
                searchContacts();
            }else{
                showOptions(MAIN_SCREEN);
            }
        }
        set<int>::iterator it, itEnd;
        it = res.begin();
        itEnd = res.begin();
        if(res.size()>max){
            advance(it,start);
            advance(itEnd,start+max);
        }else{
            itEnd = res.end();
        }
       
        cout<<"\t\t"<<"Name\t\t\tPhone\t\tEmail\t\t\t\tCity\t\t\tState\n\n";
        for (; it != itEnd; ++it) { 
            int dist = distance(res.begin(),it)+1;
            cout<<"\t"<<dist<<"\t";
            cout<<editor.getName(*it)<<"\t";
            if(editor.getName(*it).length() < 16){
                cout<<"\t";
            }
            cout<<editor.phone.at(*it)<<"\t";
            cout<<editor.email.at(*it)<<"\t";
            if(editor.email.at(*it).length() < 24){
                cout<<'\t';
            }if(editor.email.at(*it).length() < 16){
                cout<<'\t';
            }
            cout<<editor.city.at(*it)<<"\t\t";
            if(editor.city.at(*it).length() < 8){
                cout<<"\t";
            }
            cout<<editor.state.at(*it)<<endl;
        }  

        cout<<"\n\n";
        cout<<"Input:  ";
        string c;
        getline(cin,c);
        //cin.ignore(numeric_limits<streamsize>::max(),'\n'); 
        if(c=="m" || c== "M"){
            system("clear");
            if(start+max >= res.size()){
                start = res.size() - 2*max;
            }            
            showList(res,start+max);
        }else if(c=="p" || c=="P"){
            system("clear");
            if(start - max < 0){
                start = max;
            }
            showList(res,start - max);
        }else if(c =="s"||c=="S"){
            cout<<"Please enter the index:  ";
            int i = thisIsANumber(res.size());        
            
            it = res.begin();
            advance(it,i-1);
            displayContact(*it);
        }else if(c == "b" || c=="B"){
            searchContacts();
        }else{
            showOptions(MAIN_SCREEN);
        }
    }

    int thisIsANumber(int max){
        int value;
        cin >> value;
        while(cin.fail() || value > max)
        {
            cout << "Invalid Entry. Please enter a number between 1 and "<<max<<": ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> value;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return value;
    }

    public:

    int CURRENT_CONTEXT = 0;
    int MAIN_SCREEN = -1, LIST_CONTACTS=-2, SEARCH_CONTACTS=-3, DISPLAY_CONTACT=-4;
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
                printOptions(op, "HOME");
                startSwitch(context);
                break;
            case -2:
                //list contacts
                op = "mpsh";
                system("clear");
                printOptions(op, "LIST");
                //startSwitch(context);
                break;
            case -3:
                //search results
                op = "mpshb";
                //system("clear");
                printOptions(op, "SEARCH RESULTS");
                break;
            case -4:
                //A contact is being displayed
                op = "abedhx";
                printOptions(op, "View contact");
                break;
            default:
                cout<<"Error while showing options";
                break;
        }
        //startSwitch(context);

    }

    void showList(int start){
        //system("clear");
        
        int max = start + 50;
       
        showOptions(LIST_CONTACTS);
        //cout<<"\n\n";
        if(start>=editor.size()){
            start = editor.size() - 49;
            max = start + 50;
            //cout<<"No more contacts to display\n\n";
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
        //cout<<"\n[type 'm' for more, 'p' for previous, 's' to select a contact\nType anything else to go to home screen]: ";
        cout<<"\nInput:  ";
        string c;
        getline(cin,c);
        //cin.ignore(numeric_limits<streamsize>::max(),'\n'); 
        if(c=="m" || c == "M"){
            showList(max);
        }else if(c == "p" || c=="P"){
            showList(start-50);
        }else if(c == "s" || c=="S"){
            cout<<"Please enter the index:  ";
            // int i;
            i_edit_num = thisIsANumber(editor.size());
            //system("clear");
            displayContact(i_edit_num);
        }else if(c=="h" || c=="H"){
            
            system("clear");
            showOptions(MAIN_SCREEN);
        }
        else{
            invalid_choice = 1;
            system("clear");
            showOptions(MAIN_SCREEN);
        }
    }

    void searchContacts(){
        system("clear");
        int width = 120;
        for(int i=0;i<width;i++){
            cout<<"-";
        }
        cout<<"\n";
        cout<<setw((width/2)+6)<<right<<"//SEARCH//"<<endl;
        for(int i=0;i<width;i++){
            cout<<"-";
        }
        cout<<"\n\n";
        cout<<"Type anything: ";
        //
        string temp;
        
        getline(cin,temp);
        SearchProvider sp;
        set<int> res = sp.searchEverything(temp);        
        
        //todo: write a custom showlist function
        showList(res,0);
    }

       
};

