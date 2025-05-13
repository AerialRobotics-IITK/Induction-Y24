#include "persistence.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void Persistence::saveUsers(const vector<User>& users, const string& filename) {
    ofstream out(filename);
    for (const auto& user : users) {
        out << user.serialize() << endl;
    }
    out.close();
}

vector<User> Persistence::loadUsers(const string& filename) {
    vector<User> users;
    ifstream in(filename);
    string line;
    while (getline(in, line)) {
        if (!line.empty())
            users.push_back(User::deserialize(line));
    }
    in.close();
    return users;
}

void Persistence::saveContent(const vector<shared_ptr<Content>>& content, const string& filename) {
    ofstream out(filename);
    for (const auto& item : content) {
        if (item->getType() == "Movie") {
            auto* m = dynamic_cast<Movie*>(item.get());
            out << "Movie|" << m->getTitle() << "|" << m->getGenre() << "|" << m->getRating()
                << "|" << m->getRentCost() << "|" << m->getPurchaseCost() << "|" << endl;
        } else if (item->getType() == "TVShow") {
            auto* t = dynamic_cast<TVShow*>(item.get());
            out << "TVShow|" << t->getTitle() << "|" << t->getGenre() << "|" << t->getRating()
                << "|" << t->getRentCostPerSeason() << "|" << t->getPurchaseCostPerSeason() << endl;
        }
    }
    out.close();
}

vector<shared_ptr<Content>> Persistence::loadContent(const string& filename) {
    vector<shared_ptr<Content>> content;
    ifstream in(filename);
    string line;

    while (getline(in, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string type, title, genre, temp;
        double rating, rent, purchase;

        getline(ss, type, '|');
        getline(ss, title, '|');
        getline(ss, genre, '|');
        getline(ss, temp, '|');
        rating = stod(temp);
        getline(ss, temp, '|');
        rent = stod(temp);
        getline(ss, temp, '|');
        purchase = stod(temp);

        if (type == "Movie") {
            int dummy_duration = 120;
            content.push_back(make_shared<Movie>(title, genre, rating, dummy_duration, rent, purchase));
        } else if (type == "TVShow") {
            int dummy_seasons = 3, dummy_eps = 10; 
            content.push_back(make_shared<TVShow>(title, genre, rating, dummy_seasons, dummy_eps, rent, purchase));
        }
    }

    in.close();
    return content;
}
