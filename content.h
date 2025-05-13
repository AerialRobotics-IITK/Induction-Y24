#ifndef CONTENT_H
#define CONTENT_H

#include <string>
#include <iostream>

using namespace std;

class Content {
protected:
    string title;
    string genre;
    double rating;
    bool is_rented;
    bool is_purchased;

public:
    Content(const string& t, const string& g, double r);

    virtual void display() const = 0;
    virtual string getType() const = 0;

    string getTitle() const;
    string getGenre() const;
    double getRating() const;
    bool isRented() const;
    bool isPurchased() const;

    void markRented();
    void markReturned();
    void markPurchased();

    virtual ~Content() = default;
};

class Movie : public Content {
private:
    int duration; // in minutes
    double rent_cost;
    double purchase_cost;

public:
    Movie(const string& t, const string& g, double r, int d, double rent, double purchase);

    void display() const override;
    string getType() const override;

    double getRentCost() const;
    double getPurchaseCost() const;
};

class TVShow : public Content {
private:
    int seasons;
    int episodes_per_season;
    double rent_cost_per_season;
    double purchase_cost_per_season;

public:
    TVShow(const string& t, const string& g, double r, int s, int eps, double rent, double purchase);

    void display() const override;
    string getType() const override;

    double getRentCostPerSeason() const;
    double getPurchaseCostPerSeason() const;
};

#endif // CONTENT_H
