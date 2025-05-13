#ifndef MOVIE_H
#define MOVIE_H

#include "content.h"
#include <iostream>
#include <sstream>

class Movie : public Content {
private:
    int duration;
    float rent_cost;
    float purchase_cost;

public:
    Movie(string t, string g, float r, int d, float rent, float purchase)
        : Content(t, g, r), duration(d), rent_cost(rent), purchase_cost(purchase) {}

    void display() const override {
        cout << "Movie: " << title << " | Genre: " << genre << " | Rating: " << rating
             << " | Duration: " << duration << " mins | Rent: $" << rent_cost
             << " | Purchase: $" << purchase_cost << endl;
    }

    float getRentCost() const override { return rent_cost; }
    float getPurchaseCost() const override { return purchase_cost; }

    string serialize() const override {
        stringstream ss;
        ss << "Movie|" << title << "|" << genre << "|" << rating << "|" << duration
           << "|" << rent_cost << "|" << purchase_cost << "|" << is_rented << "|" << is_purchased;
        return ss.str();
    }

    static Movie* deserialize(const string& line) {
        stringstream ss(line);
        string type, t, g;
        float r;
        int d;
        float rent, purchase;
        bool rented, purchased;

        getline(ss, type, '|');
        getline(ss, t, '|');
        getline(ss, g, '|');
        ss >> r; ss.ignore();
        ss >> d; ss.ignore();
        ss >> rent; ss.ignore();
        ss >> purchase; ss.ignore();
        ss >> rented; ss.ignore();
        ss >> purchased;

        Movie* m = new Movie(t, g, r, d, rent, purchase);
        m->setRented(rented);
        m->setPurchased(purchased);
        return m;
    }
};

#endif
