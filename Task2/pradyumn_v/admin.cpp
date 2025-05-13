#include "admin.h"

void Admin::save(const string& filename) {
    ofstream out(filename);
    if (!out) {
        cerr << "Could not open file for writing.\n";
        return;
    }
    out << username << '\n' << password << '\n';

    out.close();
}

void Admin::load(const string& filename) {
    ifstream in(filename);
    if (!in) {
        cerr << "Could not open file for reading.\n";
        return;
    }
    getline(in, username);
    getline(in, password);
    in.close();
}


void Admin::save_catalogues(const string& filename, movie_entry* movie_cat, tv_show_entry* show_cat){
    ofstream out(filename);
    if (!out) {
        cerr << "Error opening file for writing: " << filename << endl;
        return;
    }

    movie_entry* m = movie_cat;
    while (m) {
        Movie* movie = m->data;
        out << "MOVIE " << movie->title << " " 
            << movie->genre << " " << movie->rating << " "
            << movie->duration << " " << movie->rent_cost << " "
            << movie->purchase_cost << "\n";
        m = m->next;
    }

    tv_show_entry* s = show_cat;
    while (s) {
        Show* show = s->data;
        out << "SHOW " << show->title << " " 
            << show->genre << " " << show->rating << " "
            << show->seasons << " " << show->ep_per_season << " "
            << show->rent_cost << " " << show->purchase_cost << "\n";
        s = s->next;
    }

    out.close();
}




movie_entry* Admin::add_movie(string title, string type, int rated, int time, int rent, int purchase, movie_entry* head){
    movie_entry* entry = new movie_entry;
    entry->data = new Movie(title, type, rated, time, rent, purchase);
    entry->next=nullptr;
    bool added = false;

    if(!head){
        return entry;
    }

    movie_entry* curr = head;
    while(curr->next){
        if(curr->data->genre==entry->data->genre){
            entry->next=curr->next;
            curr->next = entry;
            added = true;
            break;
        }
        curr = curr->next;
    }
    if(!added){
        curr->next = entry;
    }
    return head;
}

movie_entry* Admin::remove_movie(string name, movie_entry* head){
    movie_entry* curr = head;
    movie_entry* prev = nullptr;
    if(curr->data->title==name){
        head = curr->next;
        return head;
    }
    while(curr->data->title!=name){
        prev = curr;
        curr = curr->next;
        if(curr==nullptr){
            return head;
        }
    }
    prev->next = curr->next;
    return head;
}

tv_show_entry* Admin::add_show(string title, string type, int rated, int season, int ep_per_seasons, int time, int rent, int purchase, tv_show_entry* head){
    tv_show_entry* entry = new tv_show_entry;
    entry->data = new Show(title, type, rated, season, ep_per_seasons, rent, purchase);
    entry->next=nullptr;
    bool added = false;

    if(!head){
        return entry;
    }

    tv_show_entry* curr = head;
    while(curr->next){
        if(curr->data->genre==entry->data->genre){
            entry->next=curr->next;
            curr->next = entry;
            added = true;
            break;
        }
        curr = curr->next;
    }
    if(!added){
        curr->next = entry;
    }
    return head;
}

tv_show_entry* Admin::remove_show(string name, tv_show_entry* head){
    tv_show_entry* curr = head;
    tv_show_entry* prev = nullptr;
    if(curr->data->title==name){
        head = curr->next;
        return head;
    }
    while(curr->data->title!=name){
        prev = curr;
        curr = curr->next;
        if(curr==nullptr){
            return head;
        }
    }
    prev->next = curr->next;
    return head;
}