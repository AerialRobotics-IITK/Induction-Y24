#ifndef CONTENT_H
#define CONTENT_H

#include <string>
using namespace std;

class Content {
protected:
    string title;
    string genre;
    float rating;
    bool is_rented;
    bool is_purchased;

public:
    Content(string title, string genre, float rating)
        : title(title), genre(genre), rating(rating), is_rented(false), is_purchased(false) {}

    virtual void display() = 0; // Pure virtual function

    string getTitle() const { return title; }
    string getGenre() const { return genre; }
    float getRating() const { return rating; }

    bool getIsRented() const { return is_rented; }
    bool getIsPurchased() const { return is_purchased; }

    void setRented(bool rented) { is_rented = rented; }
    void setPurchased(bool purchased) { is_purchased = purchased; }
};

#endif
