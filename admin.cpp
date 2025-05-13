#include "admin.h"
#include <iostream>

using namespace std;

Admin::Admin(const string& uname, const string& pwd)
    : username(uname), password(pwd) {}

bool Admin::login(const string& uname, const string& pwd) const {
    return uname == username && pwd == password;
}

void Admin::addMovie(vector<shared_ptr<Content>>& library) {
    string title, genre;
    double rating, rent_cost, purchase_cost;
    int duration;

    cout << "Enter Movie Title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Genre: ";
    getline(cin, genre);
    cout << "Rating (0.0 - 10.0): ";
    cin >> rating;
    cout << "Duration (minutes): ";
    cin >> duration;
    cout << "Rent Cost: ₹";
    cin >> rent_cost;
    cout << "Purchase Cost: ₹";
    cin >> purchase_cost;

    library.push_back(make_shared<Movie>(title, genre, rating, duration, rent_cost, purchase_cost));
    cout << "Movie added successfully.\n";
}

void Admin::addTVShow(vector<shared_ptr<Content>>& library) {
    string title, genre;
    double rating, rent_cost, purchase_cost;
    int seasons, episodes;

    cout << "Enter TV Show Title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Genre: ";
    getline(cin, genre);
    cout << "Rating (0.0 - 10.0): ";
    cin >> rating;
    cout << "Number of Seasons: ";
    cin >> seasons;
    cout << "Episodes per Season: ";
    cin >> episodes;
    cout << "Rent Cost per Season: ₹";
    cin >> rent_cost;
    cout << "Purchase Cost per Season: ₹";
    cin >> purchase_cost;

    library.push_back(make_shared<TVShow>(title, genre, rating, seasons, episodes, rent_cost, purchase_cost));
    cout << "TV Show added successfully.\n";
}

void Admin::removeContent(vector<shared_ptr<Content>>& library, const string& title) {
    for (auto it = library.begin(); it != library.end(); ++it) {
        if ((*it)->getTitle() == title) {
            library.erase(it);
            cout << "Content \"" << title << "\" removed successfully.\n";
            return;
        }
    }
    cout << "Content titled \"" << title << "\" not found.\n";
}

void Admin::checkUserCharges(const vector<User>& users, const string& uname) const {
    for (const auto& user : users) {
        if (user.getUsername() == uname) {
            cout << "User \"" << uname << "\" has ₹" << user.getChargesDue() << " due.\n";
            return;
        }
    }
    cout << "User \"" << uname << "\" not found.\n";
}
