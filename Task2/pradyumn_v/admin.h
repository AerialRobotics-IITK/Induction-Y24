#pragma once
#include<iostream>
#include "show_entry.h"
#include "movie_entry.h"
#include<fstream>
using namespace std;

class Admin{
    public:
        string username;
        string password;
        void save(const string& filename);
        void load(const string& filename);
        void save_catalogues(const string& filename, movie_entry* movie_cat, tv_show_entry* show_cat);
        movie_entry* add_movie(string title, string type, int rated, int time, int rent, int purchase, movie_entry* head);
        movie_entry* remove_movie(string name, movie_entry* head);
        tv_show_entry* add_show(string title, string type, int rated, int season, int ep_per_seasons, int time, int rent, int purchase, tv_show_entry* head);
        tv_show_entry* remove_show(string name, tv_show_entry* head);
};