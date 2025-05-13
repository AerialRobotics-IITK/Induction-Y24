#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


class User {
private:
    string Username;
    string Password;
    vector<string>Rents;
    vector<string>Buys;
    float Dues;

public:

    string getUsername() { return Username; }
    string getPassword() { return Password; }
    void setUsername(string user) { Username = user; }
    void setPassword(string pass) { Password = pass; }
    void setdues(float money){ Dues=Dues+money;  }
    float getdues(){ return Dues;}
    string getrents(){
        for(int i=0;i<Rents.size();i++){
            cout<<Rents[i]<<endl;
        }
    }
     string getbuys(){
        for(int i=0;i<Buys.size();i++){
            cout<<Buys[i]<<endl;
        }
    }
    void setrents(string s){
        Rents.push_back(s);

    }
    void setbuys(string s){
        Buys.push_back(s);
    }
    User(string name, string pass,string rent,string buy,float m){
        Username = name;
        Password = pass;
        Rents.push_back(rent);
        Buys.push_back(buy);
        Dues=m;

    }



};

vector<User> users; 

bool unquser(string name) {
    ifstream userfile("users.txt");
    if (!userfile) {
        return false;
    }

    string line;
    while (getline(userfile, line)) {    
        stringstream ss(line);
        string username;
        if (getline(ss, username, '-')) {
            if (username == name) {
                userfile.close();
                return true;
            }
        }
    }

    userfile.close();
    return false;
}

bool correctpass(string name, string pass) {
    ifstream userfile("users.txt");
    if (!userfile) {
        return false;
    }

    string line;
    while (getline(userfile, line)) {
        stringstream ss(line);
        string username, password;
        if (getline(ss, username, '-') && getline(ss, password, '-')) {
            if (username == name && password == pass) {
                userfile.close();
                return true;
            }
        }
    }

    userfile.close();
    return false;
}



void saveUser(string name, string pass, vector<string> rit, vector<string> by, float du) {
 ofstream userfile("users.txt", ios::app);



    userfile << name << "-" << pass << "-";

    
    for (int i = 0; i < rit.size(); i++) {
        userfile << rit[i];
        userfile << ",";
    }
    userfile << "-";

    
    for (int i = 0; i < by.size(); i++) {
        userfile << by[i];
        if (i != by.size() - 1) userfile << ",";
    }
    userfile << "-";

    
    userfile << du << endl;

    userfile.close(); 
}


class content {
    string Title;
    string Genre;
    float Rent_rate;
    float Buy_rate;

public:
    string gettitle() {
         return Title;
         }
    string getgenre() { 
        return Genre;
     }
     float getrent() { 
        return Rent_rate;
     }
     float getbuy() { 
        return Buy_rate;
     }

    content(string show, string genre, float rent, float purchase) {
        Title = show;
        Genre = genre;
        Rent_rate = rent;
        Buy_rate = purchase;
    }

    void show() {
        cout << "Title: " << Title
             << ", Genre: " << Genre
             << ", Rent: $$$" << Rent_rate
             << ", Purchase: $$$" << Buy_rate << endl;
    }
};



vector<content> movies = {
    content("Inception", "SciFi", 4.99, 14.99),
    content("The Godfather", "Crime", 3.99, 12.99),
    content("Interstellar", "SciFi", 4.49, 13.99),
    content("The Dark Knight", "Action", 3.99, 11.99)
};
       
void mainpage(int userno){

     cout << "top shows \n";
    for (content& m : movies) {
        m.show();        
    }
    while(true){
                  cout<<"Hello-"<<users[userno].getUsername()<<"\n\ncurrent dues = " <<users[userno].getdues()<<endl;
                  cout << "enter 4 to log out"<<endl;

     cout<<"\n\n\nseaarch.__________."<<endl;
        string search;
        cin.ignore(); 
        getline(cin, search);
            if(search=="4"){
                        break;
                }

        ifstream file("movies.txt");

    string title, genre;
    float rent, buy;
    bool found = false;
         string curr_name ;
            float curr_rent ;
            float curr_buy ;
            string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string title, genre, rentStr, buyStr;

        getline(ss, title, '-');
        getline(ss, genre, '-');
        getline(ss, rentStr, '-');
        getline(ss, buyStr, '-');

        float rent = stof(rentStr);
        float buy = stof(buyStr);

        if (title == search || genre == search) {
            cout << "Title: " << title
                 << ", Genre: " << genre
                 << ", Rent: $$$" << rent
                 << ", Purchase: $$$" << buy << endl;

             curr_name = title;
             curr_rent = rent;
             curr_buy = buy;
            found = true;
        }
    }

    if (!found) {
        cout << "No match found.\n";
        file.close();
        continue;
    }

    file.close();
  

      cout<<"1. rent\n2. buy\n3. back\n4. logout "<<endl;
    int i;
      cin >> i;
       if(i==1){
        users[userno].setdues(curr_rent);
        users[userno].setrents(curr_name);
        continue;
       }
       else if(i==2){
        users[userno].setdues(curr_buy);
        users[userno].setbuys(curr_name);
        continue;
       }
       else if(i==3){
        continue;
       }
       else if(i==4){
        break;
       }
     }
    }


void repo() {

    cout << "1. Sign up here\n";
    cout << "2. Log in\n";
    cout << "3. admin access"<<endl;
    int response ;
    cin>>response;
    if (response == 1) {  
        string name, pass;
        cout << "Enter your username: ";
        cin >> name;

        
        if (unquser(name)) {
            cout << "create a unique username.\n";
            return;
        }

        cout << "Enter your password: ";
        cin >> pass;

        string none;
        User newUser(name, pass,none,none,0);
    
        users.push_back(newUser);
            vector<string>zero;
        
        saveUser(name, pass,zero,zero,0);

        cout << " Welcome " << name << "!\n";
        int i=users.size();
        mainpage(--i);
    } 
    else if (response == 2) {  
        string name, pass;
        cout << "Enter your username: ";
        cin >> name;
        cout << "Enter your password: ";
        cin >> pass;

        if (correctpass(name,pass)) {
            string none;
             User newUser(name, pass,none,none,0);
    
        users.push_back(newUser);
           int i=users.size();
        mainpage(--i);
        }
        else{

          cout<<"incorrect username orr password"<<endl;
            
        }
    } 
        else if(response==3){
            cout<<"1. add more shows"<<endl;
            cout<<"2. list users \n3 log out"<<endl;
            int wish;
            cin>>wish;
            if(wish==1){
                
                string title, genre;
                float rent, buy;
                cout << "Enter title: ";
                cin.ignore(); 
                getline(cin, title);
                cout << "Enter genre: ";
                getline(cin, genre);
                cout << "Enter rent rate: ";
                cin >> rent;
                cout << "Enter buy rate: ";
                cin >> buy;
                ofstream file("movies.txt", ios::app); 
                file << title << '-'
                << genre << '-'
                << rent << '-'
                << buy << '-\n';
                file.close();
        cout << "Show added successfully.\n";
            }
            else if(wish==2){
              ifstream userfile("users.txt");
              string line;
              while (getline(userfile, line)) {
              cout << line << endl;
                     }
              userfile.close();
            }
    }
    else {
        cout << "Invalid option. Please choose 1 or 2 or 3.\n";
    }
}


int main() {
    cout << "Welcome to the  NETFLIX\n";
 ofstream file("movies.txt");
    file << "Inception-SciFi-4.99-14.99" << endl;
    file << "The Godfather-Crime-3.99-12.99" << endl;
    file << "Interstellar-SciFi-4.49-13.99" << endl;
    file << "The Dark Knight-Action-3.99-11.99" << endl;
    file << "Forrest Gump-Drama-2.99-9.99" << endl;
    file << "Avengers: Endgame-Action-5.99-17.99" << endl;
    file << "Parasite-Thriller-3.49-10.99" << endl;
    file << "Coco-Animation-2.49-8.99" << endl;
    file << "Joker-Crime-3.99-13.49" << endl;
    file << "La La Land-Musical-3.49-10.49" << endl;
    file.close();

    while (true) {
        cout << "\nMain Menu:\n";
        cout << "1. Sign up / Log in\n";
        cout << "0. Exit\n";
        int choice;
        cin >> choice;

        if (choice == 1) {
            repo();
        } else if (choice == 0) {
            cout << "Exiting\n";
            break;
        } else {
            cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
