#pragma once
#include<iostream>
#include "Content.h"

class Show: public Content{
    public:
        int seasons;
        int ep_per_season;
        int rent_cost;
        int purchase_cost;
        Show(string name, string type, int rated, int season, int ep_per_seasons, int rent, int purchase);
};