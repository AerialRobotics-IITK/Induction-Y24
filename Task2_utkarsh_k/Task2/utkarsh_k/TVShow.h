#ifndef TVSHOW_H
#define TVSHOW_H

#include "Content.h"
#include <iostream>

class TVShow : public Content {
    int seasons;
    int episodes_per_season;
    float rent_per_season;
    float purchase_per_season;

public:
    TVShow(string title, string genre, float rating, int seasons, int eps, float rent, float purchase)
        : Content(title, genre, rating), seasons(seasons), episodes_per_season(eps), 
          rent_per_season(rent), purchase_per_season(purchase) {}

    void display() override {
        cout << "TV Show: " << title << " | Genre: " << genre << " | Rating: " << rating
             << " | Seasons: " << seasons << " | Episodes/Season: " << episodes_per_season
             << " | Rent/Season: ₹" << rent_per_season << " | Buy/Season: ₹" << purchase_per_season << endl;
    }

    float getRentPerSeason() const { return rent_per_season; }
    float getPurchasePerSeason() const { return purchase_per_season; }
};

#endif
