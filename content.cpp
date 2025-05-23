#include "content.h"

Content::Content(const std::string& t, const std::string& g, double r)
    : title(t), genre(g), rating(r), is_rented(false), is_purchased(false) {}

std::string Content::getTitle() const { return title; }
std::string Content::getGenre() const { return genre; }
double Content::getRating() const { return rating; }
bool Content::isRented() const { return is_rented; }
bool Content::isPurchased() const { return is_purchased; }

void Content::markRented() { is_rented = true; }
void Content::markReturned() { is_rented = false; }
void Content::markPurchased() { is_purchased = true; }

Movie::Movie(const std::string& t, const std::string& g, double r, int d, double rent, double purchase)
    : Content(t, g, r), duration(d), rent_cost(rent), purchase_cost(purchase) {}

void Movie::display() const {
    std::cout << "[Movie] " << title << " | Genre: " << genre << " | Rating: " << rating
              << " | Duration: " << duration << " min"
              << " | Rent: ₹" << rent_cost << " | Buy: ₹" << purchase_cost << "\n";
}

std::string Movie::getType() const { return "Movie"; }
double Movie::getRentCost() const { return rent_cost; }
double Movie::getPurchaseCost() const { return purchase_cost; }

TVShow::TVShow(const std::string& t, const std::string& g, double r, int s, int eps, double rent, double purchase)
    : Content(t, g, r), seasons(s), episodes_per_season(eps), rent_cost_per_season(rent), purchase_cost_per_season(purchase) {}

void TVShow::display() const {
    std::cout << "[TV Show] " << title << " | Genre: " << genre << " | Rating: " << rating
              << " | Seasons: " << seasons << " | Episodes/Season: " << episodes_per_season
              << " | Rent/Season: ₹" << rent_cost_per_season << " | Buy/Season: ₹" << purchase_cost_per_season << "\n";
}

std::string TVShow::getType() const { return "TVShow"; }
double TVShow::getRentCostPerSeason() const { return rent_cost_per_season; }
double TVShow::getPurchaseCostPerSeason() const { return purchase_cost_per_season; }
