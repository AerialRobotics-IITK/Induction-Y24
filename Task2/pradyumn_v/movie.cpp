#include "movie.h"

Movie::Movie(string name, string type, int rated, int time, int rent, int purchase):Content(name, type, rated){
    duration = time;
    rent_cost = rent;
    purchase_cost = purchase;
};