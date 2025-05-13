#pragma once
#include<iostream>
using namespace std;

class Content{
    public:
        string title;
        string genre;
        int rating;
        bool is_rented=false;
        bool is_purchased=false;
        Content(string name, string type, int rated);
};