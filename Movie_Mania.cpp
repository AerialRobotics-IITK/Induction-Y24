#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <algorithm>
#include <map>
#include <limits>

using namespace std;

// Base Content class
class Content {
protected:
    string title;
    string genre;
    float rating;
    bool is_rented;
    bool is_purchased;

public:
    Content(string t, string g, float r) : title(t), genre(g), rating(r), is_rented(false), is_purchased(false) {}
    virtual ~Content() {}

    string getTitle() const { return title; }
    string getGenre() const { return genre; }
    float getRating() const { return rating; }
    bool getIsRented() const { return is_rented; }
    bool getIsPurchased() const { return is_purchased; }

    void setIsRented(bool val) { is_rented = val; }
    void setIsPurchased(bool val) { is_purchased = val; }

    virtual void displayDetails() const = 0;
    virtual float getRentCost() const = 0;
    virtual float getPurchaseCost() const = 0;
    virtual string getType() const = 0;
};

// Movie class
class Movie : public Content {
    int duration; // in minutes
    float rent_cost;
    float purchase_cost;

public:
    Movie(string t, string g, float r, int d, float rc, float pc)
        : Content(t, g, r), duration(d), rent_cost(rc), purchase_cost(pc) {}

    void displayDetails() const override {
        cout << "Movie: " << title << "\nGenre: " << genre
             << "\nRating: " << rating << "\nDuration: " << duration << " minutes"
             << "\nRent Cost: $" << rent_cost << "\nPurchase Cost: $" << purchase_cost << endl;
    }

    float getRentCost() const override { return rent_cost; }
    float getPurchaseCost() const override { return purchase_cost; }
    string getType() const override { return "Movie"; }
};

// TVShow class
class TVShow : public Content {
    int seasons;
    int episodes_per_season;
    float per_season_rent_cost;
    float per_season_purchase_cost;

public:
    TVShow(string t, string g, float r, int s, int eps, float src, float spc)
        : Content(t, g, r), seasons(s), episodes_per_season(eps),
          per_season_rent_cost(src), per_season_purchase_cost(spc) {}

    void displayDetails() const override {
        cout << "TV Show: " << title << "\nGenre: " << genre
             << "\nRating: " << rating << "\nSeasons: " << seasons
             << "\nEpisodes per season: " << episodes_per_season
             << "\nPer Season Rent Cost: $" << per_season_rent_cost
             << "\nPer Season Purchase Cost: $" << per_season_purchase_cost << endl;
    }

    float getRentCost() const override { return per_season_rent_cost; }
    float getPurchaseCost() const override { return per_season_purchase_cost; }
    string getType() const override { return "TV Show"; }
    int getSeasons() const { return seasons; }
};

// User class
class User {
    string username;
    string password;
    vector<pair<Content*, time_t>> rented_items; // content and rental date
    vector<pair<Content*, time_t>> purchased_items; // content and purchase date
    float total_charges;

public:
    User(string u, string p) : username(u), password(p), total_charges(0) {}

    string getUsername() const { return username; }
    string getPassword() const { return password; }
    float getTotalCharges() const { return total_charges; }

    void addRentedItem(Content* item) {
        rented_items.emplace_back(item, time(nullptr));
        total_charges += item->getRentCost();
    }

    void addPurchasedItem(Content* item) {
        purchased_items.emplace_back(item, time(nullptr));
        total_charges += item->getPurchaseCost();
    }

    bool returnItem(const string& title) {
        auto it = find_if(rented_items.begin(), rented_items.end(),
            [&title](const pair<Content*, time_t>& item) {
                return item.first->getTitle() == title;
            });

        if (it != rented_items.end()) {
            it->first->setIsRented(false);
            rented_items.erase(it);
            return true;
        }
        return false;
    }

    void displayRentedItems() const {
        if (rented_items.empty()) {
            cout << "No items currently rented." << endl;
            return;
        }

        cout << "Rented Items:" << endl;
        for (const auto& item : rented_items) {
            cout << "-------------------" << endl;
            item.first->displayDetails();
            cout << "Date rented: " << ctime(&item.second);
            // Assuming rental period is 7 days
            time_t due_date = item.second + 7 * 24 * 60 * 60;
            cout << "Last date of return: " << ctime(&due_date);
        }
    }

    void displayPurchasedItems() const {
        if (purchased_items.empty()) {
            cout << "No items purchased." << endl;
            return;
        }

        cout << "Purchased Items:" << endl;
        for (const auto& item : purchased_items) {
            cout << "-------------------" << endl;
            item.first->displayDetails();
            cout << "Date purchased: " << ctime(&item.second);
        }
    }

    vector<pair<Content*, time_t>> getRentedItems() const { return rented_items; }
    vector<pair<Content*, time_t>> getPurchasedItems() const { return purchased_items; }
};

// Admin class
class Admin {
    string username;
    string password;

public:
    Admin(string u, string p) : username(u), password(p) {}

    string getUsername() const { return username; }
    string getPassword() const { return password; }
};

// Inventory Management System
class NetflixSystem {
    vector<Content*> content;
    vector<User*> users;
    vector<Admin*> admins;
    User* current_user;
    Admin* current_admin; // int* ptr = new int(5)  int* ptr = new int[5]  Movie* movies = new vector

public:
    NetflixSystem() : current_user(nullptr), current_admin(nullptr) {
        // Initialize with some default admin
        admins.push_back(new Admin("yashr", "yashr24"));
    }

    ~NetflixSystem() {
        for (auto c : content) delete c;
        for (auto u : users) delete u;
        for (auto a : admins) delete a;
    }

    void run() {
        while (true) {
            if (!current_user && !current_admin) {
                showMainMenu();
            } else if (current_user) {
                showUserMenu();
            } else if (current_admin) {
                showAdminMenu();
            }
        }
    }

private:
    void showMainMenu() {
        cout << "\nNetflix Inventory Management System" << endl;
        cout << "1. User Login" << endl;
        cout << "2. User Sign-Up" << endl;
        cout << "3. Admin Login" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: userLogin(); break;
            case 2: userSignUp(); break;
            case 3: adminLogin(); break;
            case 4: exit(0);
            default: cout << "Invalid choice. Please try again." << endl;
        }
    }

    void userLogin() {
        string username, password;
        cout << "Enter username: ";
        getline(cin, username);
        cout << "Enter password: ";
        getline(cin, password);

        for (User* user : users) {
            if (user->getUsername() == username && user->getPassword() == password) {
                current_user = user;
                cout << "Login successful!" << endl;
                return;
            }
        }
        cout << "Invalid username or password." << endl;
    }

    void userSignUp() {
        string username, password;
        cout << "Enter new username: ";
        getline(cin, username);

        // Check if username already exists
        for (User* user : users) {
            if (user->getUsername() == username) {
                cout << "Username already exists. Please choose another." << endl;
                return;
            }
        }

        cout << "Enter password: ";
        getline(cin, password);

        users.push_back(new User(username, password));
        cout << "Account created successfully!" << endl;
    }

    void adminLogin() {
        string username, password;
        cout << "Enter admin username: ";
        getline(cin, username);
        cout << "Enter admin password: ";
        getline(cin, password);

        for (Admin* admin : admins) {
            if (admin->getUsername() == username && admin->getPassword() == password) {
                current_admin = admin;
                cout << "Admin login successful!" << endl;
                return;
            }
        }
        cout << "Invalid admin credentials." << endl;
    }

    void showUserMenu() {
        cout << "\nWelcome, " << current_user->getUsername() << "!" << endl;
        cout << "1. Browse Content" << endl;
        cout << "2. Search Content" << endl;
        cout << "3. Rent Content" << endl;
        cout << "4. Return Content" << endl;
        cout << "5. View Rented Items" << endl;
        cout << "6. View Purchased Items" << endl;
        cout << "7. Check Total Charges" << endl;
        cout << "8. Logout" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: browseContent(); break;
            case 2: searchContent(); break;
            case 3: rentContent(); break;
            case 4: returnContent(); break;
            case 5: current_user->displayRentedItems(); break;
            case 6: current_user->displayPurchasedItems(); break;
            case 7: 
                cout << "Total charges due: $" << current_user->getTotalCharges() << endl;
                break;
            case 8: 
                current_user = nullptr;
                cout << "Logged out successfully." << endl;
                break;
            default: cout << "Invalid choice. Please try again." << endl;
        }
    }

    void browseContent() {
        cout << "\nBrowse Content By:" << endl;
        cout << "1. Category (Movies/TV Shows)" << endl;
        cout << "2. Genre" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "1. Movies" << endl;
            cout << "2. TV Shows" << endl;
            cout << "Enter your choice: ";
            int type;
            cin >> type;
            cin.ignore();

            cout << "\nAvailable ";
            if (type == 1) {
                cout << "Movies:" << endl;
                for (Content* c : content) {
                    if (dynamic_cast<Movie*>(c)) {
                        c->displayDetails();
                        cout << "-------------------" << endl;
                    }
                }
            } else if (type == 2) {
                cout << "TV Shows:" << endl;
                for (Content* c : content) {
                    if (dynamic_cast<TVShow*>(c)) {
                        c->displayDetails();
                        cout << "-------------------" << endl;
                    }
                }
            } else {
                cout << "Invalid choice." << endl;
            }
        } else if (choice == 2) {
            cout << "Enter genre to browse: ";
            string genre;
            getline(cin, genre);

            cout << "\nContent in genre '" << genre << "':" << endl;
            bool found = false;
            for (Content* c : content) {
                if (c->getGenre() == genre) {
                    c->displayDetails();
                    cout << "-------------------" << endl;
                    found = true;
                }
            }
            if (!found) {
                cout << "No content found in this genre." << endl;
            }
        } else {
            cout << "Invalid choice." << endl;
        }
    }

    void searchContent() {
        cout << "Search by:" << endl;
        cout << "1. Title" << endl;
        cout << "2. Genre" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "Enter title to search: ";
            string title;
            getline(cin, title);

            bool found = false;
            for (Content* c : content) {
                if (c->getTitle().find(title) != string::npos) {
                    c->displayDetails();
                    cout << "-------------------" << endl;
                    found = true;
                }
            }
            if (!found) {
                cout << "No content found with this title." << endl;
            }
        } else if (choice == 2) {
            cout << "Enter genre to search: ";
            string genre;
            getline(cin, genre);

            bool found = false;
            for (Content* c : content) {
                if (c->getGenre().find(genre) != string::npos) {
                    c->displayDetails();
                    cout << "-------------------" << endl;
                    found = true;
                }
            }
            if (!found) {
                cout << "No content found with this genre." << endl;
            }
        } else {
            cout << "Invalid choice." << endl;
        }
    }

    void rentContent() {
        cout << "Enter title of content to rent: ";
        string title;
        getline(cin, title);

        for (Content* c : content) {
            if (c->getTitle() == title && !c->getIsRented() && !c->getIsPurchased()) {
                cout << "Content found:" << endl;
                c->displayDetails();

                cout << "Choose action:" << endl;
                cout << "1. Rent" << endl;
                cout << "2. Purchase" << endl;
                cout << "Enter your choice: ";

                int action;
                cin >> action;
                cin.ignore();

                if (action == 1) {
                    c->setIsRented(true);
                    current_user->addRentedItem(c);
                    cout << "Content rented successfully!" << endl;
                } else if (action == 2) {
                    c->setIsPurchased(true);
                    current_user->addPurchasedItem(c);
                    cout << "Content purchased successfully!" << endl;
                } else {
                    cout << "Invalid choice." << endl;
                }
                return;
            } else if (c->getTitle() == title && (c->getIsRented() || c->getIsPurchased())) {
                cout << "This content is already rented or purchased." << endl;
                return;
            }
        }
        cout << "Content not found." << endl;
    }

    void returnContent() {
        cout << "Enter title of content to return: ";
        string title;
        getline(cin, title);

        if (current_user->returnItem(title)) {
            cout << "Content returned successfully!" << endl;
        } else {
            cout << "You haven't rented this content or it doesn't exist." << endl;
        }
    }

    void showAdminMenu() {
        cout << "\nAdmin Panel - Welcome, " << current_admin->getUsername() << "!" << endl;
        cout << "1. Add New Content" << endl;
        cout << "2. Remove Content" << endl;
        cout << "3. Check User Charges" << endl;
        cout << "4. Logout" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addContent(); break;
            case 2: removeContent(); break;
            case 3: checkUserCharges(); break;
            case 4: 
                current_admin = nullptr;
                cout << "Admin logged out successfully." << endl;
                break;
            default: cout << "Invalid choice. Please try again." << endl;
        }
    }

    void addContent() {
        cout << "Add New Content:" << endl;
        cout << "1. Movie" << endl;
        cout << "2. TV Show" << endl;
        cout << "Enter your choice: ";

        int type;
        cin >> type;
        cin.ignore();

        string title, genre;
        float rating;

        cout << "Enter title: ";
        getline(cin, title);
        cout << "Enter genre: ";
        getline(cin, genre);
        cout << "Enter rating: ";
        cin >> rating;
        cin.ignore();

        if (type == 1) {
            int duration;
            float rent_cost, purchase_cost;
            cout << "Enter duration (minutes): ";
            cin >> duration;
            cout << "Enter rent cost: ";
            cin >> rent_cost;
            cout << "Enter purchase cost: ";
            cin >> purchase_cost;
            cin.ignore();

            content.push_back(new Movie(title, genre, rating, duration, rent_cost, purchase_cost));
            cout << "Movie added successfully!" << endl;
        } else if (type == 2) {
            int seasons, episodes;
            float season_rent, season_purchase;
            cout << "Enter number of seasons: ";
            cin >> seasons;
            cout << "Enter episodes per season: ";
            cin >> episodes;
            cout << "Enter per season rent cost: ";
            cin >> season_rent;
            cout << "Enter per season purchase cost: ";
            cin >> season_purchase;
            cin.ignore();

            content.push_back(new TVShow(title, genre, rating, seasons, episodes, season_rent, season_purchase));
            cout << "TV Show added successfully!" << endl;
        } else {
            cout << "Invalid choice." << endl;
        }
    }

    void removeContent() {
        cout << "Enter title of content to remove: ";
        string title;
        getline(cin, title);

        for (auto it = content.begin(); it != content.end(); ++it) {
            if ((*it)->getTitle() == title) {
                // Check if the content is currently rented or purchased by any user
                bool in_use = false;
                for (User* user : users) {
                    for (const auto& rented : user->getRentedItems()) {
                        if (rented.first->getTitle() == title) {
                            in_use = true;
                            break;
                        }
                    }
                    if (!in_use) {
                        for (const auto& purchased : user->getPurchasedItems()) {
                            if (purchased.first->getTitle() == title) {
                                in_use = true;
                                break;
                            }
                        }
                    }
                    if (in_use) break;
                }

                if (in_use) {
                    cout << "Cannot remove content that is currently rented or purchased." << endl;
                } else {
                    delete *it;
                    content.erase(it);
                    cout << "Content removed successfully!" << endl;
                }
                return;
            }
        }
        cout << "Content not found." << endl;
    }

    void checkUserCharges() {
        cout << "Enter username to check charges: ";
        string username;
        getline(cin, username);

        for (User* user : users) {
            if (user->getUsername() == username) {
                cout << "Total charges for " << username << ": $" << user->getTotalCharges() << endl;
                return;
            }
        }
        cout << "User not found." << endl;
    }
};

int main() {
    NetflixSystem system;
    system.run();
    return 0;
}