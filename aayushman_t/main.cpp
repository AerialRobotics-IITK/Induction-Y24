
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <vector>
#include <limits>
#include "tvShows.cpp"
#include "movies.cpp"
using namespace std;
const string USER_DATA_FILE = "data/users.txt";
struct User{
    string username;
    string password;
    bool isAdmin;
};
class UserManager {
    string currentUsername;
    bool isAdmin;

    public:
        void signUp() {
            vector<User> users = loadusers();
            cout << "Choose a username: ";
            string username;
            cin >> username;
    
            if (usernameExists(users, username)) {
                cout << "Username already exists. Try logging in.\n";
                return;
            }
            cout<<"Enter a password: ";
            string pass;
            cin>>pass;
            char AdminChoice;

            cout<<"Is this an Admin Account? (y/n):"<<endl;
            cin>>AdminChoice;
            bool newAdmin = false;

            if(AdminChoice=='y'){
                 newAdmin = true;
            }
            else{
                 newAdmin =false;
            }
            ofstream file(USER_DATA_FILE, ios::app);
            if (file.is_open()) {
                file << username << ":"<<pass<<(newAdmin ? ":admin":"")<<endl;
                file.close();
                cout << "Sign-up successful. You can now log in.\n";
            } else {
                cout << "Error: Unable to write to user data file.\n";
            }
        }
        bool login() {
            vector<User> users = loadusers();
            cout << "Enter username: ";
            string username;
            string password;
            cin >> username;
            cout<<"Enter Password: ";
            cin>>password;
            for (const auto& user : users) {
                if (user.username == username && user.password == password) {
                    currentUsername = username;
                    isAdmin = user.isAdmin;
                    cout << "Login successful. Welcome, " << username << "!" 
                         << (isAdmin ? " (Admin)" : "") << "\n";
                    
                    return true;
                }
            }
            
    
            cout << "Login failed. Username not found.\n";
            return false;
        }
        string getCurrentUsername(){
            return currentUsername;
        }
        bool isCurrentUserAdmin() {
            return isAdmin;
        }
        void viewAllContent(MoviesManager & moviemanager,TVShowManager & tvshowmanager ){
            cout << "\n=========== All Available Movies ===========\n";       
            moviemanager.browse();
            cout << "\n=========== All Available Tv Shows ===========\n";       
            tvshowmanager.browse();

        }
             
    private:
        vector<User> loadusers() {
            vector<User> users;
            ifstream file(USER_DATA_FILE);
            string line;
            while (getline(file, line)) {
                size_t pos1 = line.find(":");
                if(pos1 == string::npos)continue; 
                size_t pos2 = line.find(":", pos1+1);
                string username = line.substr(0, pos1);
                string password;
                bool isAdmin =false;
                if(pos2 != string::npos){
                    password  = line.substr(pos1 +1 , pos2-pos1-1);
                    isAdmin = (line.substr(pos2) == ":admin");
                    
                }else{
                    password = line.substr(pos1+1);
                    
                }
                users.push_back({username, password,isAdmin});

            }
            file.close();
            return users;
            
        }
    
        bool usernameExists(const vector<User>& users, const string& username) {
            for (const auto& user: users) {
                if (user.username== username)
                    return true;
            }
            return false;
        }
        
        
    };
    
    
int main() {
    TVShowManager tvshowmanager;
    MoviesManager moviemanager;
    UserManager manager;
    bool isloggedin =false;
    while(!isloggedin){
    int choice;
    cout << "1. Login\n2. Sign-Up\nEnter choice: ";
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch (choice) {
        case 1:
           isloggedin= manager.login();
            break;
        case 2:
            manager.signUp();
            break;
        default:
            cout << "Invalid choice.\n";
    }}
    if(isloggedin == true && (!manager.isCurrentUserAdmin() )){
       while(true){
        int action;
        cout<<"1. Browse Movies\n2. Browse Tv Shows\n3. Search Content by title or genre"<<endl;
        cout<<"Enter choice:";
        cin>>action;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string purchaseFile = "data/purchased_" + manager.getCurrentUsername() + ".txt";
        string rentalFile = "data/rented_" + manager.getCurrentUsername() + ".txt";
        if(action ==2 ){
            cout<<"The format is: TITLE|GENRE|RATING|SEASONS|EPISODES PER SEASON|RENT COST|PURCHASE COST| AVAILABLE OR NOT"<<endl;
            tvshowmanager.browse();
            int pur_ren_choice_tv;
            cout<<"1. Rent a show \n2. Purchase a show\n3. Return rented show\n4. View all Rented shows"<<endl;
            cout<<"Enter Choice:";
            cin>>pur_ren_choice_tv;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if(pur_ren_choice_tv == 1){
                string show_to_be_rented;
                cout << "Enter show to rent: ";
                getline(cin, show_to_be_rented); 

                tvshowmanager.rentShow(show_to_be_rented);
                ofstream out(rentalFile, ios::app);
                if (out.is_open()) {
                    out << show_to_be_rented << endl;
                    out.close();
                    cout << "Successfully rented: " << show_to_be_rented << endl;
                } else {
                    cout << "Failed to save rental info.\n";
                }
            }
            else if(pur_ren_choice_tv == 2){
                string show_to_be_pur;
                cout << "Enter the name of the show to purchase: ";
                getline(cin, show_to_be_pur);
                tvshowmanager.purchaseShow(show_to_be_pur);
                ofstream out(purchaseFile, ios::app);
                if (out.is_open()) {
                    out << show_to_be_pur << endl;
                    out.close();
                    cout << "Successfully rented: " << show_to_be_pur << endl;
                } else {
                    cout << "Failed to save rental info.\n";
                }
            }
            else if(pur_ren_choice_tv == 3){
                string Show_to_be_returned;
                cout<<"Enter the Show to be returned: "<<endl;
                cin>>Show_to_be_returned;
                tvshowmanager.returnShow(Show_to_be_returned, manager.getCurrentUsername());
            }
            else if(pur_ren_choice_tv == 4){
                string rentalfile = "data/rented_"+manager.getCurrentUsername()+".txt";
                string line;
                ifstream in(rentalfile);
                cout << "\n=========== Your Rented Shows ===========\n";
                bool found= false;
                while(getline(in,line)){
                   
                    for(auto&show:tvshowmanager.getShows()){
                      if(show.title == line & show.isrented){
                          show.display();
                          found =true;
                          break;
                      }
                    }
              }
              if(!found){
                  cout<<"No rented  movie available"<<endl;
              }

            }
            else{
                cout<<"Invalid choice";
            }
        }
        else if(action ==1){
            cout<<"The format is: TITLE|GENRE|RATING|DURATION|RENT COST|PURCHASE COST| AVAILABLE OR NOT"<<endl;
           moviemanager.browse();
            int pur_ren_choice_mv;
            cout<<"1. Rent a movie \n2. Purchase a movie\n3. Return rented movies\n4. View all Rented movies"<<endl;
            cout<<"Enter Choice:";
            cin>>pur_ren_choice_mv;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if(pur_ren_choice_mv == 1){
                string movie_to_be_rented;
                cout << "Enter the name of the movie to rent: ";
                getline(cin, movie_to_be_rented); 
                moviemanager.rentmovie(movie_to_be_rented);
                ofstream out(rentalFile, ios::app);
                if (out.is_open()) {
                    out << movie_to_be_rented << endl;
                    out.close();
                    cout << "Successfully rented: " << movie_to_be_rented << endl;
                } else {
                    cout << "Failed to save rental info.\n";
                }
            }
            else if(pur_ren_choice_mv == 2){
                string movie_to_be_pur;
                cout << "Enter the name of the movie to purchase: ";
                getline(cin, movie_to_be_pur);
                moviemanager.purchasemovie(movie_to_be_pur);
                ofstream out(purchaseFile, ios::app);
                if (out.is_open()) {
                    out << movie_to_be_pur << endl;
                    out.close();
                    cout << "Successfully rented: " << movie_to_be_pur << endl;

                } else {
                    cout << "Failed to save rental info.\n";
                }
            }
            else if(pur_ren_choice_mv ==3){
                string movie_to_return;
                cout << "Enter the name of the movie to return: ";
                getline(cin, movie_to_return);
                moviemanager.returnMovie(movie_to_return,manager.getCurrentUsername());
            }
            else if (pur_ren_choice_mv == 4){
                  string rentalfile = "data/rented_"+manager.getCurrentUsername()+".txt";
                  string line;
                  ifstream in(rentalfile);
                  cout << "\n=========== Your Rented Movies ===========\n";
                  bool found= false;
                  while(getline(in,line)){
                     
                      for(auto&movie:moviemanager.getMovies()){
                        if(movie.title == line & movie.isrented){
                            movie.display();
                            found =true;
                            break;
                        }
                      }
                }
                if(!found){
                    cout<<"No rented  movie available"<<endl;
                }

            }
            else{
                cout<<"Invalid choice";
            }
        }
        else if (action == 3) {
            int type;
            cout << "Search in:\n1. Movies\n2. TV Shows\nEnter choice: ";
            cin >> type;
            cin.ignore();
        
            cout << "Enter search keyword (title or genre): ";
            string keyword;
            getline(cin, keyword);
        
            if (type == 1)
                moviemanager.searchMovie(keyword);
            else if (type == 2)
                tvshowmanager.searchShow(keyword);
            else
                cout << "Invalid search type.\n";
        }
        
        else{
            cout<<"Invalid Choice";
        }
    }}
    else if(isloggedin && manager.isCurrentUserAdmin()){
        while(true){
        int adminChoice;
        cout<<"1. Movies \n2. TvShows"<<endl;
        cout<<"Enter Choice:";
        cin>>adminChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if(adminChoice ==1){
            int rem_add_mv;
            cout<<"1. Add Movies \n2. Remove Movies\n3. List all Movies and Tv shows"<<endl;
            cout<<"Enter Choice:";
            cin>>rem_add_mv;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if(rem_add_mv ==1){
                string title, genre;
                float rating, rentCost, purchaseCost, duration;
                char ch = 'y';
              
             while(ch =='y'){
                cout << "Enter movie title: ";
                getline(cin, title);
                cout << "Enter genre: ";
                getline(cin, genre);
                cout << "Enter rating (0-10): ";
                cin >> rating;
                cout<<"Enter Duration ";
                cin>> duration;
                cout << "Enter rent cost: ";
                cin >> rentCost;
                cout << "Enter purchase cost: ";
                cin >> purchaseCost;
                
                moviemanager.addMovie(title, genre, rating, duration,  rentCost, purchaseCost);
                cout<<"Want to enter more:(y/n) ";
                cin>>ch;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

            }
        
        }
            else if (rem_add_mv == 2) {
                string title;
                cout << "Enter movie title to remove: ";
                getline(cin, title);
                moviemanager.removeMovie(title);
            }
            else if(rem_add_mv ==3){
                manager.viewAllContent(moviemanager, tvshowmanager);
            }
            else {
                cout << "Invalid admin choice.\n";
            }
        }
        else if(adminChoice == 2){
            int rem_add_sh;
            cout<<"1. Add TvShows \n2. Remove TvShows\n3. List all Tv Shows and movies"<<endl;
            cout<<"Enter Choice:";
            cin>>rem_add_sh;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if(rem_add_sh ==1){
                string title, genre;
                float rating, rentCost, purchaseCost, season , ep_s;
                char ch ='y';
                

            while(ch =='y'){
                cout << "Enter show title: ";
                getline(cin, title);
                cout << "Enter genre: ";
                getline(cin, genre);
                cout << "Enter rating (0-10): ";
                cin >> rating;
                cout << "Enter number of Seasons: ";
                cin >> season;
                cout << "Enter  episode per season ";
                cin >> ep_s;
                cout << "Enter rent cost: ";
                cin >> rentCost;
                cout << "Enter purchase cost: ";
                cin >> purchaseCost;
               
            
                tvshowmanager.addshow(title, genre, rating,season,ep_s, rentCost, purchaseCost);
                cout<<"Want to enter more:(y/n) ";
                cin>>ch;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

               
            }
            
            }
            else if (rem_add_sh == 2) {
                string title;
                cout << "Enter movie title to remove: ";
                getline(cin, title);
                tvshowmanager.removeShow(title);
            }
            else if(rem_add_sh ==3){
                manager.viewAllContent(moviemanager, tvshowmanager);
            }
            else {
                cout << "Invalid admin choice.\n";
            }
        }
        else{
            cout<<"Invalid Choice"<<endl;
            
        }
        }
    
    
    
    }
    return 0;
}