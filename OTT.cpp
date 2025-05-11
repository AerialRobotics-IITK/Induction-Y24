#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

class User {
public:
    string name;
    string password;
    vector<string> rentedMovies;
    vector<string> purchasedItems;
    int chargeDues;

    User() {
        chargeDues = 0;
    }
};

class Admin {
public:
    string name;
    string password;
    vector<string> movieList;
    vector<string> TVshows;

    Admin() {
        
        movieList= {
            "The Shawshank Redemption",
            "The Godfather",
            "The Dark Knight",
            "Pulp Fiction",
            "Schindler's List",
            "The Lord of the Rings: The Return of the King",
            "Fight Club",
            "Forrest Gump",
            "Inception",
            "The Matrix",
            "Goodfellas",
            "The Godfather: Part II",
            "Interstellar",
            "Gladiator",
            "The Silence of the Lambs",
            "Titanic",
            "Saving Private Ryan",
            "The Green Mile",
            "Avengers: Endgame",
            "The Lion King (1994)"
        };
        TVshows = {
            "Breaking Bad",
            "Game of Thrones",
            "Stranger Things",
            "The Boys",
            "The Crown",
            "The Last of Us",
            "Peaky Blinders",
            "Money Heist",
            "Dark",
            "Chernobyl",
            "The Mandalorian",
            "The Witcher",
            "The Office",
            "Friends",
            "Narcos",
            "Better Call Saul",
            "Loki",
            "The Queen's Gambit",
            "House of the Dragon",
            "Wednesday"
        };
    }
};
//using file handling to save the data of users
void saveUserToFile(const User& user) {
    ofstream file("users.txt", ios::app); // Append mode
    file << user.name << "," << user.password << "," << user.chargeDues << ",";

    for (size_t i = 0; i < user.rentedMovies.size(); ++i) {
        file << user.rentedMovies[i];
        if (i != user.rentedMovies.size() - 1) file << "|";
    }
    file << ",";

    for (size_t i = 0; i < user.purchasedItems.size(); ++i) {
        file << user.purchasedItems[i];
        if (i != user.purchasedItems.size() - 1) file << "|";
    }
    file << "\n";
    file.close();
}

vector<User> loadUsersFromFile() {
    vector<User> users;
    ifstream file("users.txt");
    string line;

    while (getline(file, line)) {
        User user;
        stringstream ss(line);
        string rented, purchased;

        getline(ss, user.name, ',');
        getline(ss, user.password, ',');
        string dues;
        getline(ss, dues, ',');
        user.chargeDues = stoi(dues);

        getline(ss, rented, ',');
        stringstream rs(rented);
        string item;
        while (getline(rs, item, '|')) {
            if (!item.empty()) user.rentedMovies.push_back(item);
        }

        getline(ss, purchased);
        stringstream ps(purchased);
        while (getline(ps, item, '|')) {
            if (!item.empty()) user.purchasedItems.push_back(item);
        }

        users.push_back(user);
    }
    file.close();
    return users;
}

void callOtt(string msn) {
    vector<User> persons = loadUsersFromFile();
    Admin admin;

    while (true) {
        cout << "... ....... WELCOME ....... ...\n";
        cout << ".........SIGN UP......" << endl;
        cout << "Want to sign up as user? Type user\n";
        cout << "Want to sign up as admin? Type admin\n";
        string s;
        getline(cin, s);

        if (s == "user") {
            string p, q;
            cout << "Enter your name: (use Snakecase eg. user_case)" << endl;
            getline(cin, p);
            // Check if user already exists
            User* userPtr = nullptr;
            for (auto& user : persons) {
                 if (user.name == p) {
                     userPtr = &user;
                     break;
                 }
             }
             
            // If user doesn't exist, create new user
            bool isNewUser = (userPtr == nullptr);
            if (isNewUser) {
                 persons.push_back(User());
                 userPtr = &persons.back();
                 userPtr->name = p;
             }
             
             User& user = *userPtr; // Reference to either existing or new user
            
            
            cout << "Enter your password (default: 1234): " << endl;
            cin >> q;
            cin.ignore();
            user.password = q;
            if (q != "1234") {
                cout << "Incorrect password ,try again" << endl;
                return;
            }

            cout << "......WELCOME........" << endl;
            cout << "Press 1 -> Browse content\n";
            cout << "Press 2 -> Rent movies\n";
            cout << "Press 3 -> Return rented content\n";
            cout << "Press 4 -> View rented items\n";
            cout << "Press 5 -> View purchased items\n";
            cout << "Press 6 -> Check charges due\n";

            int choice;
            cin >> choice;
            cin.ignore();

            if (choice == 1) {
                string content;
                cout << "Search your content (Movie/TV Show),(use Snakecase eg. user_case): ";
                cin >> content;

                int press;
                cout << "Press 1 to rent"<<endl;
                cout<< "Press 2 to purchase"<<endl;
                cout<< "Press 3 to watch"<<endl;
                cin >> press;

                if (press == 1) {
                    cout << "Rent price: 120\n Rent period: 1 year\nType 'ok' to rent: ";
                    string rent;
                    cin >> rent;
                    if (rent == "ok") {
                        user.rentedMovies.push_back(content);
                        cout << content << " is added to your rented list\n";
                    }
                } else if (press == 2) {
                    cout << "Pay 200 through UPI\nType 'ok' to buy: ";
                    string purchase;
                    cin >> purchase;
                    if (purchase == "ok") {
                        user.purchasedItems.push_back(content);
                        cout << "Thanks for shopping here\n";
                    }
                } else if (press == 3) {
                    cout<<"duration of movie 3hrs"<<endl;
                    cout << "Enjoy your movie!\n";
                }
            } else if (choice == 2) {
                cout << "Enter movie name: ,(use Snakecase eg. user_case)"<<endl;
                string movie;
                cin >> movie;
                cout << "Rent price: 120\nPay now or add to dues? (NOW/LATER): "<<endl;
                string pay;
                cin >> pay;
                if (pay == "NOW") {
                    cout << "Paying 120 via UPI...\n";
                    user.rentedMovies.push_back(movie);
                } else if (pay == "LATER") {
                    user.chargeDues += 120;
                    cout << "Added to charge dues\n";
                }
            } else if (choice == 3) {
                cout << "Enter movie name to return:,(use Snakecase eg. user_case) "<<endl;
                string movie;
                getline(cin, movie);
                auto it = find(user.rentedMovies.begin(), user.rentedMovies.end(), movie);
                if (it != user.rentedMovies.end()) {
                    user.rentedMovies.erase(it);
                    cout << "Returned successfully\n";
                } else {
                    cout << "Movie not found in rented list!\n";
                }
            } else if (choice == 4) {
                cout << "Rented movies:\n";
                for (auto& m : user.rentedMovies) cout << m << "\n";
            } else if (choice == 5) {
                cout << "Purchased items:\n";
                for (auto& p : user.purchasedItems) cout << p << "\n";
            } else if (choice == 6) {
                cout << "Total charges due: " << user.chargeDues << "\n";
            }

            // Save the user and add to memory
            persons.push_back(user);
            saveUserToFile(user);
        }

        else if (s == "admin") {
            cout << "Enter name: ";
            string name;
            getline(cin, name);
            admin.name = name;

            cout << "Enter password (default 4321): "<<endl;
            string pass;
            cin >> pass;
            cin.ignore();

            if (pass == "4321") {
                cout << "Press 1 -> Add movie\n";
                cout << "Press 2 -> Remove movie\n";
                cout << "Press 3 -> View dues\n";
                cout << "Press 4 -> View users profile\n";
                cout<< "Press 5 -> view list of all movies and tv shows \n";


                int press;
                cin >> press;
                cin.ignore();

                if (press == 1) {
                    string movie;
                    cout << "Movie/TV show to add:,(use Snakecase eg. admin_case) "<<endl;
                    getline(cin, movie);
                    admin.movieList.push_back(movie);
                    cout << "Added successfully.\n";
                } else if (press == 2) {
                    string movie;
                    cout << "Movie/TV show to remove:(use Snakecase eg. admin_case) "<<endl;
                    getline(cin, movie);
                    auto it = find(admin.movieList.begin(), admin.movieList.end(), movie);
                    if (it != admin.movieList.end()) {
                        admin.movieList.erase(it);
                        cout << "Removed successfully.\n";
                    } else {
                        cout << "Not found in list.\n";
                    }
                } else if (press == 3) {
                    for (auto& u : persons) {
                        cout << u.name << " : " << u.chargeDues << endl;
                    }
                } else if (press == 4) {
                    for (auto& u : persons) {
                        cout << u.name << endl;
                    }
                }
                else if(press==5){
                    cout<<"all movies: "<<endl;
                    for(int i=0;i<admin.movieList.size();i++){
                        cout<<admin.movieList[i]<<endl;
                    }
                    cout<<endl<<endl;
                    cout<<"all tv shows: "<<endl;
                    for(int i=0;i<admin.TVshows.size();i++){
                        cout<<admin.TVshows[i]<<endl;
                    }
                    cout<<endl;
                    
                }
            } else {
                cout << "Wrong password!\n";
            }
        }

        string choice;
        cout << "\nExit platform? (yes/no): ";
        cin >> choice;
        cin.ignore();
        if (choice == "yes" || choice == "YES") break;
    }
}

int main() {
    callOtt("OTT");
    return 0;
}
