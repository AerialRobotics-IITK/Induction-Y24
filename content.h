
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
    Content(string t, string g, float r) : title(t), genre(g), rating(r), is_rented(false), is_purchased(false) {}

    virtual void display() const = 0;
    virtual float getRentCost() const = 0;
    virtual float getPurchaseCost() const = 0;

    string getTitle() const { return title; }
    string getGenre() const { return genre; }
    float getRating() const { return rating; }
    bool getIsRented() const { return is_rented; }
    bool getIsPurchased() const { return is_purchased; }

    void setRented(bool val) { is_rented = val; }
    void setPurchased(bool val) { is_purchased = val; }

    virtual string serialize() const = 0;
    virtual ~Content() {}
};

#endif
