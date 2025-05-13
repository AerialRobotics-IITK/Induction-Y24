#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Content;
class Movie;
class TVShow;
class User;
class Admin;

struct RentalUser {
    User* user;
    time_t rentDate;
    time_t returnDate;
};

class Content {
    protected:
        string title;
        string genre;
        double rating;
        vector <RentalUser> rented_by;
        vector <User*> purchased_by;

    public:
        //constructor
        Content(string title, string genre, double rating) {
            this->title = title;
            this->genre = genre;
            this->rating = rating;
            cout << this->title << "has been successfully created" << endl;
        }
        //destructor
        ~Content() {
            cout << this->title << "has been succesfully deleted" << endl;
        }
    
        string getTitle() { return title; }
        string getGenre() { return genre; }
        double getRating() { return rating; }
        //User getRented_by() { return rented_by; }
        //User getPurchased_by() { return purchased_by; }

        void setTitle(string title) { this->title = title; }
        void setGenre(string genre) { this->genre = genre; }
        void setRating(double rating) { this->rating = rating; }
    
        //virtual function (will be defined for movie and tv show differently)
        virtual double getRentCost() = 0; //per season for tv shows
        virtual double getPurchaseCost() = 0; //per season for tv shows
        virtual int getDuration() = 0;
        virtual int getSeasons() = 0;
        virtual int getEpisodes_per_season() = 0;
        virtual string getType() = 0;
    };

class Movie : public Content {

};

class TVShow : public Content {

};

struct RentedContent {
    Content* content;
    time_t rentDate;
    time_t returnDate;
};
    
class User {
    protected:
        string username;
        string password;
        vector<RentedContent> rented_items;
        vector<Content*> purchased_items;

};

class admin : public User {

};

