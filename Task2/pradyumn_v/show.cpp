#include "show.h"

Show::Show(string name, string type, int rated, int season, int ep_per_seasons, int rent, int purchase):Content(name, type, rated){
    seasons = season;
    ep_per_season = ep_per_seasons;
    rent_cost = rent;
    purchase_cost = purchase;
};