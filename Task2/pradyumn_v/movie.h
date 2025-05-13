#pragma once
#include<iostream>
#include "Content.h"

using namespace std;

class Movie: public Content{
    public:
        int duration;
        int rent_cost;
        int purchase_cost;
        Movie(string name, string type, int rated, int time, int rent, int purchase);
};