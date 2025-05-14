

#include <iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;


class Movie {
    public:
        string Name;
        int Rating;
        int Duration;
        int Rent_Cost;
        int Purchase_Cost;
        bool is_rented;
        bool is_purchased;

        
    };

class Admin {
    public:
    void add_movie() {
        ofstream out("movies.txt", ios::app);
        Movie m;
    
        cout << "Enter movie name: ";
        cin >> ws;
        getline(cin, m.Name);
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

        out << m.Name << " "<< m.Rating << " " << m.Duration << " "<< m.Rent_Cost << " " << m.Purchase_Cost << " " << m.is_rented << " " << m.is_purchased << "\n";
        
        out.close();

        cout << "Movie added successfully.\n";
    }

    void delete_movie() {
        string movie_to_delete;
        cout << "Enter movie name to delete: ";
        cin >> ws;
        getline(cin, movie_to_delete);
    
        ifstream infile("movies.txt");
        ofstream temp("temp.txt");
    
        bool found = false;
        string line;
        while (getline(infile, line)) {
            stringstream ss(line);
            string name;
            ss >> name;
            if (name != movie_to_delete) {
                temp << line << endl;
            } else {
                found = true;
            }
        }
    
        infile.close();
        temp.close();
    
        if (found) {
            remove("movies.txt");
            rename("temp.txt", "movies.txt");
            cout << "Movie deleted successfully." << endl;
        } else {
            remove("temp.txt");
            cout << "Movie not found in database." << endl;
        }
    }
    
};
    




void signup() {
    string username, password, confirm_password;
    cout << "Enter your username: ";
    cin >> username;
    ifstream infile("users.txt");
    if(infile.is_open()) {
        string temp_username, temp_password;
        bool user_exists = false;
        while (infile >> temp_username >> temp_password && !user_exists) {
            if (temp_username == username) {
                cout << "Username already exists. Please try a different one." << endl;
                cout << "Enter a new username: ";
                cin >> username;
                user_exists = true;
            }
        }
    }
    infile.close();
    cout << "Enter your password: ";
    cin >> password;
    cout << "Confirm your password: ";
    cin >> confirm_password;
    if (password != confirm_password) {
        cout << "Passwords do not match. Please try again." << endl;
        
    }
    
    ofstream outfile("users.txt", ios::app);
    outfile << username << " " << password << endl;
    outfile.close();  
    string filepath = username + ".txt";
    ofstream user_file(filepath, ios::app) ;
    
        user_file << "Rented_Movies:\n";
        user_file << "Purchased_Movies:\n";
        user_file << "Dues: 0\n";
        user_file.close();
   
    cout << "User saved successfully! Please log in now." << endl;


}

int verify(string username, string password) {
    ifstream infile("users.txt");
    if(infile.is_open()) {
        string temp_username, temp_password;
        while (infile >> temp_username >> temp_password) {
            if (temp_username == username && temp_password == password) {
                cout << "Login successful!" << endl;
                return 1; // Login successful
            }
        }
    }
    cout << "Invalid username or password." << endl;
    return 0; // Login failed
}

class User {
    public:
    string curr_user;
    User(const string& name) {
        curr_user = name;
    }
    
    void rent_movie() {
        string preference;
        cout << "Enter the name of the movie you want to rent: ";
        cin >> ws;
        getline(cin, preference);
    
        vector<string> movie_lines;
        ifstream movies("movies.txt");
        string line;
        bool found = false;
    
        while (getline(movies, line)) {
            stringstream ss(line);
            string name;
            int rating, duration, rent_cost, purchase_cost;
            bool is_rented, is_purchased;
            ss >> name >> rating >> duration >> rent_cost >> purchase_cost >> is_rented >> is_purchased;
    
            if (name == preference) {
                if (is_rented) {
                    cout << "Movie already rented." << endl;
                    return;
                }
    
                // Update user file
                fstream user_file(curr_user + ".txt");
                vector<string> user_lines;
                while (getline(user_file, line)) user_lines.push_back(line);
                user_file.close();
    
                ofstream user_file_out(curr_user + ".txt");
                for (string& l : user_lines) {
                    user_file_out << l << "\n";
                    if (l == "Rented_Movies:") {
                        user_file_out << name << "\n";
                    }
                    if (l.rfind("Dues:", 0) == 0) {
                        int prev_dues = stoi(l.substr(5));
                        user_file_out << "Dues: " << (prev_dues + rent_cost) << "\n";
                    }
                }
                user_file_out.close();
    
                // Update is_rented in movie
                stringstream updated;
                updated << name << " " << rating << " " << duration << " " << rent_cost << " " << purchase_cost << " 1 " << is_purchased;
                movie_lines.push_back(updated.str());
                found = true;
            } else {
                movie_lines.push_back(line);
            }
        }
        movies.close();
    
        ofstream out("movies.txt");
        for (string& l : movie_lines) out << l << "\n";
        out.close();
    
        if (found) cout << "Movie rented successfully.\n";
        else cout << "Movie not found.\n";
    }
    
    
    void view_rented_movies() {
        ifstream user_file(curr_user + ".txt");
        string line;
        bool print = false;
    
        cout << "Your Rented Movies:\n";
        while (getline(user_file, line)) {
            if (line == "Rented_Movies:") {
                print = true;
                continue;
            } else if (line == "Purchased_Movies:" || line == "Dues:" || line == "Rented_TV_Shows:" || line == "Purchased_TV_Shows:") {
                break;
            }
            if (print && !line.empty()) {
                cout << "- " << line << "\n";
            }
        }
        user_file.close();
    }

    void purchase_movie() {
        string preference;
        cout << "Enter the name of the movie you want to purchase: ";
        cin >> ws;
        getline(cin, preference);
    
        vector<string> movie_lines;
        ifstream movies("movies.txt");
        string line;
        bool found = false;
    
        while (getline(movies, line)) {
            stringstream ss(line);
            string name;
            int rating, duration, rent_cost, purchase_cost;
            bool is_rented, is_purchased;
            ss >> name >> rating >> duration >> rent_cost >> purchase_cost >> is_rented >> is_purchased;
    
            if (name == preference) {
                if (is_purchased) {
                    cout << "Movie already purchased." << endl;
                    return;
                }
    
                // Update user file
                fstream user_file(curr_user + ".txt");
                vector<string> user_lines;
                while (getline(user_file, line)) user_lines.push_back(line);
                user_file.close();
    
                ofstream user_file_out(curr_user + ".txt");
                for (string& l : user_lines) {
                    user_file_out << l << "\n";
                    if (l == "Purchased_Movies:") {
                        user_file_out << name << "\n";
                    }
                    if (l.rfind("Dues:", 0) == 0) {
                        int prev_dues = stoi(l.substr(5));
                        user_file_out << "Dues: " << (prev_dues + purchase_cost) << "\n";
                    }
                }
                user_file_out.close();
    
                // Update is_purchased in movie
                stringstream updated;
                updated << name << " " << rating << " " << duration << " " << rent_cost << " " << purchase_cost << " " << is_rented << " 1";
                movie_lines.push_back(updated.str());
                found = true;
            } else {
                movie_lines.push_back(line);
            }
        }
        movies.close();
    
        ofstream out("movies.txt");
        for (string& l : movie_lines) out << l << "\n";
        out.close();
    
        if (found) cout << "Movie purchased successfully.\n";
        else cout << "Movie not found.\n";
    }
    

    void view_purchased_movies() {
        ifstream user_file(curr_user + ".txt");
        string line;
        bool print = false;
    
        cout << "Your Purchased Movies:\n";
        while (getline(user_file, line)) {
            if (line == "Purchased_Movies:") {
                print = true;
                continue;
            } else if (line == "Purchased_Movies:" || line == "Dues:" || line == "Rented_TV_Shows:" || line == "Purchased_TV_Shows:") {
                break;
            }
            
            if (print && !line.empty()) {
                cout << "- " << line << "\n";
            }
        }
        user_file.close();
    }

    void check_dues() {
        ifstream user_file(curr_user + ".txt");
        string line;
        while (getline(user_file, line)) {
            if (line.rfind("Dues:", 0) == 0) { // line starts with "Dues:"
                cout << line << endl;
                user_file.close();
                return;
            }
        }
        user_file.close();
        cout << "No dues information found." << endl;
    }
    

};

int main() {
    string admin_username, admin_password;
    // Admin credentials
    // These should be stored securely in a real application
    admin_username = "soumya";
    admin_password = "soumya123";
    

    int n = 1;

    while(n) {
        cout<<"Welcome to Netflix"<<endl;
        cout<<"1. User SignUp"<<endl;
        cout<<"2. User SignIn"<<endl;
        cout<<"3. Admin Login"<<endl;
        cout<<"4. Exit"<<endl;
        cout<<"Enter your choice: ";
        int a;
        cin>>a;
        switch(a) {
            case 1: {
            // Adding a block scope to avoid bypassing initialization
            signup();
            break;
            }
            case 2: {
            // User sign-in logic
            string temp_username, temp_password;
            cout << "Enter your username: ";
            cin >> temp_username;
            cout << "Enter your password: ";
            cin >> temp_password;
            int choice;
            int k = 1;
            if (verify(temp_username, temp_password)) {
                User curr_user(temp_username);
                cout << "Welcome " << temp_username << endl;

                while(k) {
                
                cout << "1. Rent a Movie" << endl;
                cout << "2. Purchase a Movie" << endl;
                cout << "3. View rented movies" << endl;
                cout << "4. View purchased movies" << endl;
                cout << "5. Check dues" << endl;
                cout << "6. Exit" << endl;
                cout << "Enter your choice: "<<endl;
            cin >> choice;
           
            switch(choice) {
                case 1: {
                    // Rent a movie logic (to be implemented)
                    curr_user.rent_movie();
                    break;
                }
                case 2: {
                    // Purchase a movie logic (to be implemented)
                    curr_user.purchase_movie();
                    break;
                }
                case 3: {
                    // View rented movies logic (to be implemented)
                    curr_user.view_rented_movies();
                    break;
                }
                case 4: {
                    // View purchased movies logic (to be implemented)
                    curr_user.view_purchased_movies();
                    break;
                }
                case 5: {
                    // Check dues logic (to be implemented)
                    curr_user.check_dues();
                    break;
                }
                case 6: {
                    k = 0; // Exit the loop
                    break;
                }
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    break;
            }

        }
               }
               break;
            } 
            
            case 3: {
            // Admin login logic (to be implemented)
            string admin_username_confirm, admin_password_confirm;
            cout << "Enter admin username: ";
            cin >> admin_username_confirm;
            cout << "Enter admin password: ";
            cin >> admin_password_confirm;
            if (admin_username_confirm == admin_username && admin_password_confirm == admin_password) {
                Admin adminUser;
                bool continued = true;
                while (continued) {
                    cout << "\nAdmin Menu:" << endl;
                    cout << "1. Add Movie" << endl;
                    cout << "2. Delete Movie" << endl;         
                    cout << "3. Exit" << endl;
                    int a;
                    cin >> a;

                    switch(a) {
                        case 1:
                            adminUser.add_movie();
                            break;
                        case 2:
                        { 
                            
                            adminUser.delete_movie();
                            
                            break;

                        }
                        case 3:
                            continued = false;
                            break;
                        default:
                            cout << "Invalid choice. Please try again." << endl;
                    }
                }
            } else {
                cout << "Invalid admin credentials. Please try again." << endl;
            }

            break;
            }
            case 4: {
            n = 0; // Exit the loop
            break;
            }
            default: {
            cout << "Invalid choice. Please try again." << endl;
            break;
            }
        }
    }
}