#ifndef MOVIE_H
#define MOVIE_H

#include "Content.h"
#include <iostream>

class Movie : public Content {
    int duration;
    float rent_cost;
    float purchase_cost;

public:
    Movie(string title, string genre, float rating, int duration, float rent_cost, float purchase_cost)
        : Content(title, genre, rating), duration(duration), rent_cost(rent_cost), purchase_cost(purchase_cost) {}

    void display() override {
        cout << "Movie: " << title << " | Genre: " << genre << " | Rating: " << rating
             << " | Duration: " << duration << " min | Rent: ₹" << rent_cost << " | Buy: ₹" << purchase_cost << endl;
    }

    float getRentCost() const { return rent_cost; }
    float getPurchaseCost() const { return purchase_cost; }
};

#endif
