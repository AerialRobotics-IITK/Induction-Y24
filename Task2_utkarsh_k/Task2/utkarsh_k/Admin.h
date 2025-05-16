#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <iostream>
#include <vector>
#include "Movie.h"
#include "TVShow.h"

using namespace std;

class Admin {
    string username;
    string password;

public:
    Admin(string uname, string pwd) : username(uname), password(pwd) {}

    bool login(string uname, string pwd) {
        return (uname == username && pwd == password);
    }

    void addMovie(vector<Movie>& movies, Movie m) {
        movies.push_back(m);
        cout << "Movie added successfully.\n";
    }

    void addTVShow(vector<TVShow>& shows, TVShow s) {
        shows.push_back(s);
        cout << "TV Show added successfully.\n";
    }

    void removeMovie(vector<Movie>& movies, string title) {
        for (auto it = movies.begin(); it != movies.end(); ++it) {
            if (it->getTitle() == title) {
                movies.erase(it);
                cout << "Movie removed successfully.\n";
                return;
            }
        }
        cout << "Movie not found.\n";
    }

    void removeTVShow(vector<TVShow>& shows, string title) {
        for (auto it = shows.begin(); it != shows.end(); ++it) {
            if (it->getTitle() == title) {
                shows.erase(it);
                cout << "TV Show removed successfully.\n";
                return;
            }
        }
        cout << "TV Show not found.\n";
    }

    void checkUserDues(const User& u) {
        cout << u.getUsername() << " owes ₹" << u.getChargesDue() << endl;
    }
};

#endif
