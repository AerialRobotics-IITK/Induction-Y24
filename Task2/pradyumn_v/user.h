#pragma once
#include<iostream>
#include "show_entry.h"
#include "movie_entry.h"
#include<fstream>
using namespace std;

class User{
    private:
        movie_entry* rented=nullptr;
        movie_entry* purchased=nullptr;
        tv_show_entry* rented_show=nullptr;
        tv_show_entry* purchased_show=nullptr;
        int due = 0;
    public:
        string username;
        string password;
        void save(const string& filename);
        void load(const string& filename, movie_entry* movie_cat, tv_show_entry* show_cat);
        void search_title(string name, movie_entry* movie_catalog, tv_show_entry* show_catalog);
        void search_genre(string genre, movie_entry* movie_catalog, tv_show_entry* show_catalog);
        void rent(string name, movie_entry* movie_catalog, tv_show_entry* tv_catalog);
        void purchase(string name, movie_entry* movie_catalog, tv_show_entry* tv_catalog);
        void return_(string name);
        void dues();
        void view_purchased();
        void view_rented();
};

