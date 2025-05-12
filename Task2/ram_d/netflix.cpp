#include <iostream>
#include <string>
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>
#include<fstream>
#include<filesystem>
#include<vector>

using namespace std;

string encrypt_password(const string& input_pass) {
// Initially tried a very simple hashing method but then moved to SHA256 in OpenSSL library for better password encryption on local device storage
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)input_pass.c_str(), input_pass.length(), hash);
    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}

string verify_credential(){
    string entered_user, entered_pass;
    cout<<"Enter your registered username"<<endl;
    cin>>entered_user;
    cout<<"Enter your registered password"<<endl;
    cin>>entered_pass;
    ifstream infile("password_db.txt");
    string stored_user, stored_pass;
    string hashed_entered_pass = encrypt_password(entered_pass);  
    while (infile >> stored_user >> stored_pass) {
        if (stored_user == entered_user && stored_pass == hashed_entered_pass) {
            cout<<"Welcome back, "<<entered_user<<endl;
            return entered_user;
        }
    }
    cout<<"Sorry, username and password are incorrect"<<endl;  
    return " ";
}  

void make_credential() {
    string init_user, init_pass, init_pass1;
//Initially considered a recursive method of restarting make credentials if a previously used username was entered 
// but to prevent stack overflow shifted to iterative method
    while (true) { 
        cout << "Enter your username: ";
        cin >> init_user;

        bool user_exists = false;
        ifstream infile("password_db.txt");
        string stored_user, stored_pass;
        while (infile >> stored_user >> stored_pass) {
            if (stored_user == init_user) {
                user_exists = true;
                break;
            }
        }
        infile.close();

        if (user_exists) {
            cout << "Username already exists. Please try a different one." << endl; 
            continue;
        }

        cout << "Enter your password: ";
        cin >> init_pass;
        cout << "Confirm your password: ";
        cin >> init_pass1;

        if (init_pass != init_pass1) {
            cout << "Passwords do not match. Please try again." << endl;
            continue;
        }

        ofstream outfile("password_db.txt", ios::app);
        if (outfile.is_open()) {
            string hashed = encrypt_password(init_pass);
            outfile << init_user << "  " << hashed << endl;
            outfile.close();
            string userFilePath = "users/" + init_user + ".txt";
            ofstream userFile(userFilePath);
            if (userFile.is_open()) {
                userFile << "Rented_Movies:\n";
                userFile << "Purchased_Movies:\n";
                userFile << "Rented_TV_Shows:\n";
                userFile << "Purchased_TV_Shows:\n";
                userFile << "Dues: 0\n";
                userFile.close();
            } 
            else {
                cerr << "Error creating user data file.\n";
}
            cout << "User saved successfully! Please log in now." << endl;
            break;
        } else {
            cerr << "Error: Could not open file." << endl;
            break;
        }
    }
}

class Content{
public:
    string Name;
    string Genre;
    int Rating;
    bool is_rented;
    bool is_purchased;
};

class TV_Show : public Content{
public:
    int Seasons;
    int Episodes_per_Season;
    int Per_Season_Rent_Cost;
    int Per_Season_Purchase_Cost;
};

class Movie : public Content{
public:
    int Duration;
    int Rent_Cost;
    int Purchase_Cost;
};

class Admin {
public:
// Used ChatGPT to generate a lot of such entries for both the database text files based on the formats in the function
    void addMovie() {
        Movie m;
        cout << "Enter movie name: ";
        cin >> ws;
        getline(cin, m.Name);
        cout << "Enter genre: ";
        cin >> m.Genre;
        cout << "Enter rating (0-10): ";
        cin >> m.Rating;
        m.is_rented = false;
        m.is_purchased = false;
        cout << "Enter duration (in minutes): ";
        cin >> m.Duration;
        cout << "Enter rent cost: ";
        cin >> m.Rent_Cost;
        cout << "Enter purchase cost: ";
        cin >> m.Purchase_Cost;

        ofstream out("movies_db.txt", ios::app);
        out << m.Name << "|" << m.Genre << "|" << m.Rating << "|" << m.is_rented << "|"
        << m.is_purchased << "|" << m.Duration << "|" << m.Rent_Cost << "|"
        << m.Purchase_Cost << "\n";

        out.close();

        cout << "Movie added successfully.\n";
    }

    void deleteMovie(const string& movieName) {
        ifstream in("movies_db.txt");
        ofstream temp("temp.txt");
        string line;
        bool found = false;
        while (getline(in, line)) {
            istringstream iss(line);
            string name;
            getline(iss, name, '|');  // updated delimiter from ' ' to '|'
    
            if (name != movieName) {
                temp << line << endl;
            } else {
                found = true;
            }
        }
        in.close();
        temp.close();
        remove("movies_db.txt");
        rename("temp.txt", "movies_db.txt");
        if (found)
            cout << "Movie deleted successfully.\n";
        else
            cout << "Movie not found.\n";
    }
    

    void addTVShow() {
        TV_Show tv;
        cout << "Enter TV show name: ";
        cin >> ws;
        getline(cin, tv.Name);
        cout << "Enter genre: ";
        cin >> tv.Genre;
        cout << "Enter rating (0-10): ";
        cin >> tv.Rating;
        tv.is_rented = false;
        tv.is_purchased = false;
        cout << "Enter number of seasons: ";
        cin >> tv.Seasons;
        cout << "Enter episodes per season: ";
        cin >> tv.Episodes_per_Season;
        cout << "Enter rent cost per season: ";
        cin >> tv.Per_Season_Rent_Cost;
        cout << "Enter purchase cost per season: ";
        cin >> tv.Per_Season_Purchase_Cost;

        ofstream out("tv_show_db.txt", ios::app);
        out << tv.Name << "|" << tv.Genre << "|" << tv.Rating << "|" << tv.is_rented << "|"
        << tv.is_purchased << "|" << tv.Seasons << "|" << tv.Episodes_per_Season << "|"
        << tv.Per_Season_Rent_Cost << "|" << tv.Per_Season_Purchase_Cost << "\n";

        out.close();

        cout << "TV Show added successfully.\n";
    }

    void deleteTVShow(const string& showName) {
        ifstream in("tv_show_db.txt");
        ofstream temp("temp.txt");
        string line;
        bool found = false;

        while (getline(in, line)) {
            istringstream iss(line);
            string name;
            iss >> ws;
            getline(iss, name, '|');
            if (name != showName) {
                temp << line << endl;
            } else {
                found = true;
            }
        }

        in.close();
        temp.close();
        remove("tv_show_db.txt");
        rename("temp.txt", "tv_show_db.txt");

        if (found)
            cout << "TV Show deleted successfully.\n";
        else
            cout << "TV Show not found.\n";
    }
};

class User{
    public:
    string current_username;
    User(const string& uname){
        current_username = uname;
    }
    
    void start_rent() {
        int choice;
        string preference;
        cout << "Press 0 to rent a Movie and Press 1 to rent a TV Show: ";
        cin >> choice;
        cin.ignore();
    
        cout << "Enter the name of the " << (choice ? "TV Show" : "Movie") << " you want to rent:\n";
        getline(cin, preference);
    
        string dbFile = choice == 0 ? "movies_db.txt" : "tv_show_db.txt";
        string line;
        bool found = false;
    
        ifstream in(dbFile);
        while (getline(in, line)) {
            stringstream ss(line);
            string title;
            getline(ss, title, '|');
    
            if (title == preference) {
                found = true;
                break;
            }
        }
        in.close();
    
        if (!found) {
            cout << (choice ? "TV Show" : "Movie") << " not found.\n";
            return;
        }
    
        // Calculate dues
        int duesAmount = (choice == 0) ? 100 : 50; 
        string userFilePath = "users/" + current_username + ".txt";
        ifstream userIn(userFilePath);
        vector<string> fileLines;
        string userLine;
        while (getline(userIn, userLine)) {
            fileLines.push_back(userLine);
        }
        userIn.close();
    
        ofstream userOut(userFilePath);
        bool inDuesSection = false;
        for (string& line : fileLines) {
            if (line == "Dues:") {
                inDuesSection = true;
                userOut << line << " " << duesAmount << "\n";  
            } else {
                userOut << line << "\n";
            }
        }
        userOut.close();
    
        cout << "Successfully rented: " << preference << endl;
    }
    
    void purchase() {
        int choice;
        string title;
        cout << "Press 0 to purchase a Movie and Press 1 to purchase a TV Show: ";
        cin >> choice;
        cin.ignore();
        cout << "Enter the name of the " << (choice ? "TV Show" : "Movie") << " you want to purchase:\n";
        getline(cin, title);
    
        string userFilePath = "users/" + current_username + ".txt";
        ifstream inFile(userFilePath);
        ofstream tempFile("temp_user.txt");
    
        string line;
        string section = choice == 0 ? "Rented_Movies:" : "Rented_TV_Shows:";
        string nextSection = choice == 0 ? "Purchased_Movies:" : "Purchased_TV_Shows:";
        bool inCorrectSection = false;
    
        bool found = false;
    
        while (getline(inFile, line)) {
            if (line == section) {
                tempFile << line << "\n";
                inCorrectSection = true;
                continue;
            }
    
            if (line == nextSection) {
                inCorrectSection = false;
                tempFile << line << "\n";
            }
    
            if (inCorrectSection && line == title) {
                found = true;
                tempFile << line << "\n";  
            } else {
                tempFile << line << "\n";
            }
        }
    
        // Calculate dues
        if (found) {
            int duesAmount = (choice == 0) ? 400 : 200; 
            inFile.close();
            tempFile.close();
    
            ifstream userIn(userFilePath);
            ofstream userOut("temp_user.txt");
            vector<string> fileLines;
            while (getline(userIn, line)) {
                fileLines.push_back(line);
            }
    
            userIn.close();
            bool inDuesSection = false;
            for (string& line : fileLines) {
                if (line == "Dues:") {
                    inDuesSection = true;
                    userOut << line << " " << duesAmount << "\n"; 
                } else {
                    userOut << line << "\n";
                }
            }
            remove(userFilePath.c_str());
            rename("temp_user.txt", userFilePath.c_str());
    
            cout << "Successfully purchased \"" << title << "\".\n";
        } else {
            cout << "The specified " << (choice ? "TV Show" : "Movie") << " was not found in your rented list.\n";
        }
    }
    
    void end_rent() {
        int choice;
        string title;
        cout << "Press 0 to return a Movie and Press 1 to return a TV Show: ";
        cin >> choice;
        cin.ignore();
        cout << "Enter the name of the " << (choice ? "TV Show" : "Movie") << " you want to return:\n";
        getline(cin, title);
    
        string userFilePath = "users/" + current_username + ".txt";
        ifstream inFile(userFilePath);
        ofstream tempFile("temp_user.txt");
    
        string line;
        string section = choice == 0 ? "Rented_Movies:" : "Rented_TV_Shows:";
        string nextSection = choice == 0 ? "Purchased_Movies:" : "Purchased_TV_Shows:";
    
        bool inCorrectSection = false;
        bool found = false;
    
        while (getline(inFile, line)) {
            if (line == section) {
                tempFile << line << "\n";
                inCorrectSection = true;
                continue;
            }
    
            if (line == nextSection) {
                inCorrectSection = false;
                tempFile << line << "\n";
                continue;
            }
    
            if (inCorrectSection && line == title) {
                found = true;
                continue;
            }
    
            tempFile << line << "\n";
        }
    
        inFile.close();
        tempFile.close();
    
        remove(userFilePath.c_str());
        rename("temp_user.txt", userFilePath.c_str());
    
        if (found)
            cout << "Successfully returned \"" << title << "\".\n";
        else
            cout << "The specified " << (choice ? "TV Show" : "Movie") << " was not found in your rented list.\n";
    }  

    void view_rent() {
        string userFilePath = "users/" + current_username + ".txt";
        ifstream inFile(userFilePath);
        string line;
        bool inRentedMovies = false;
        bool inRentedTVShows = false;
    
        cout << "Movies you have rented:\n";
        while (getline(inFile, line)) {
            if (line == "Rented_Movies:") {
                inRentedMovies = true;
                continue;
            }
            if (line == "Rented_TV_Shows:") {
                inRentedMovies = false;
                inRentedTVShows = true;
                continue;
            }
    
            if (inRentedMovies) {
                cout << line << "\n";
            } else if (inRentedTVShows) {
                cout << line << "\n";
            }
        }
    
        if (!inRentedMovies && !inRentedTVShows) {
            cout << "You haven't rented any movies or TV shows yet.\n";
        }
    
        inFile.close();
    }

    void view_purchase() {
        string userFilePath = "users/" + current_username + ".txt";
        ifstream inFile(userFilePath);
        string line;
        bool inPurchasedMovies = false;
        bool inPurchasedTVShows = false;
    
        cout << "Movies you have purchased:\n";
        while (getline(inFile, line)) {
            if (line == "Purchased_Movies:") {
                inPurchasedMovies = true;
                continue;
            }
            if (line == "Purchased_TV_Shows:") {
                inPurchasedMovies = false;
                inPurchasedTVShows = true;
                continue;
            }
    
            if (inPurchasedMovies) {
                cout << line << "\n";
            } else if (inPurchasedTVShows) {
                cout << line << "\n";
            }
        }
    
        if (!inPurchasedMovies && !inPurchasedTVShows) {
            cout << "You haven't purchased any movies or TV shows yet.\n";
        }
    
        inFile.close();
    }
    
    void check_dues() {
        string userFilePath = "users/" + current_username + ".txt";
        ifstream inFile(userFilePath);
        string line;
        bool inDuesSection = false;
        
        // Look for dues section and print the dues for the user
        while (getline(inFile, line)) {
            if (line.find("Dues:") != string::npos) {
                // Output dues by extracting the part after "Dues: "
                cout << "Dues for " << current_username << ": " << line.substr(5) << endl;
                inDuesSection = true;
                break;
            }
        }
        
        if (!inDuesSection) {
            cout << "No dues found for " << current_username << endl;
        }
        
        inFile.close();
    }    

};

int main() {
    int control;
    string logged_user;
    cout << "Welcome to Netflix. Press 0 if you are a user and Press 1 if you are an admin" << endl;
    cin >> control;

    if (control) {
        cout << "Welcome admin. Please log-in.";
        if (verify_credential() != "") {  // Only proceed if valid admin
            Admin adminUser;
            bool running = true;
            while (running) {
                cout << "\nAdmin Menu:" << endl;
                cout << "1. Add Movie" << endl;
                cout << "2. Delete Movie" << endl;
                cout << "3. Add TV Show" << endl;
                cout << "4. Delete TV Show" << endl;
                cout << "5. Exit" << endl;
                cin >> control;
                string contentName;
                
                switch(control) {
                    case 1:
                        adminUser.addMovie();
                        break;
                    case 2:
                        cout << "Enter movie name to delete: ";
                        cin.ignore();
                        getline(cin, contentName);
                        adminUser.deleteMovie(contentName);
                        break;
                    case 3:
                        adminUser.addTVShow();
                        break;
                    case 4:
                        cout << "Enter TV show name to delete: ";
                        cin.ignore();
                        getline(cin, contentName);
                        adminUser.deleteTVShow(contentName);
                        break;
                    case 5:
                        running = false;
                        break;
                }
            }
        }
    } else {
        cout << "Welcome user. Press 0 to sign-up and Press 1 to log-in" << endl;
        cin >> control;

        if (control) {
            // User logs in
            logged_user = verify_credential();
        } else {
            // New user sign-up
            make_credential();
            logged_user = verify_credential();
        }

        // Once logged in, create or get a reference to the User object
        User currentUser(logged_user);
        
        // User selects actions
        bool running = true;
        while (running) {
            cout << "\nWhat would you like to do?" << endl;
            cout << "1. Rent a movie or TV show" << endl;
            cout << "2. Purchase a movie or TV show" << endl;
            cout << "3. Return rented content" << endl;
            cout << "4. View rented content" << endl;
            cout << "5. View purchased content" << endl;
            cout << "6. Check total charges due" << endl;
            cout << "7. Exit" << endl;
            cin >> control;
            switch(control){
                case 1:
                    currentUser.start_rent();
                    break;
                case 2:
                    currentUser.purchase();
                    break;
                case 3:
                    currentUser.end_rent();
                    break;
                case 4:
                    currentUser.view_rent();
                    break;
                case 5:
                    currentUser.view_purchase();
                    break;
                case 6:
                    currentUser.check_dues();
                    break;
                case 7:
                    return 0;
            }
        }
    }
}
