#include<iostream>
#include "user.h"
#include "admin.h"
#include<bits/stdc++.h>
using namespace std;

void load_cat(const string& filename, movie_entry** movie_cat, tv_show_entry** show_cat) {
    ifstream in(filename);
    if (!in) {
        cerr << "Error opening file for reading: " << filename << endl;
        return;
    }

    *movie_cat = nullptr;
    *show_cat = nullptr;

    string line;
    while (getline(in, line)) {
        istringstream iss(line);
        string type;
        iss >> type;

        if (type == "MOVIE") {
            string title, genre;
            int rating, duration, rent_cost, purchase_cost;
            iss >> title >> genre >> rating >> duration >> rent_cost >> purchase_cost;

            Movie* new_movie = new Movie(title, genre, rating, duration, rent_cost, purchase_cost);
            movie_entry* new_entry = new movie_entry{new_movie, nullptr};
            
            if (!*movie_cat) {
                *movie_cat = new_entry;
            } else {
                movie_entry* current = *movie_cat;
                while (current->next) current = current->next;
                current->next = new_entry;
            }

        } else if (type == "SHOW") {
            string title, genre;
            int rating, seasons, ep_per_season, rent_cost, purchase_cost;
            iss >> title >> genre >> rating >> seasons >> ep_per_season >> rent_cost >> purchase_cost;

            Show* new_show = new Show(title, genre, rating, seasons, ep_per_season, rent_cost, purchase_cost);
            tv_show_entry* new_entry = new tv_show_entry{new_show, nullptr};
            
            if (!*show_cat) {
                *show_cat = new_entry;
            } else {
                tv_show_entry* current = *show_cat;
                while (current->next) current = current->next;
                current->next = new_entry;
            }
        }
    }
    in.close();
}

int main(){
    int logged_in = 0, rated, duration, rent, purchase, seasons, episodes;
    string user, pswd, input, title, type;
    int decision = 0, decision_ua=0;
    movie_entry* movie_cat = nullptr;
    tv_show_entry* show_cat = nullptr;
    load_cat("catalogues/data.dat", &movie_cat, &show_cat);
    User* active_user=nullptr;
    Admin* active_admin=nullptr;
    while(true){
        if(!logged_in){
            cout<<"[1] Login"<<endl;
            cout<<"[2] Create new account"<<endl;
            cout<<"[3] Quit program"<<endl;
            cin>>decision;
            if(decision==1){
                cout<<"Enter Username: "<<endl;
                cin>>user;
                cout<<"Enter Password: "<<endl;
                cin>>pswd;
                cout<<"[1] Admin"<<endl;
                cout<<"[2] User"<<endl;
                cin>>decision_ua;
                if(decision_ua==1){
                    active_admin = new Admin;
                    active_admin->load("admin/"+user+".dat");
                    if(active_admin->password==pswd){
                        logged_in=2;
                    }
                    else{
                        cout<<"Username or password is incorrect.\n";
                        active_admin = nullptr;
                        logged_in=0;
                    }
                }
                if(decision_ua==2){
                    active_user = new User;
                    active_user->load("users/"+user+".dat", movie_cat, show_cat);
                    if(active_user->password==pswd){
                        logged_in=1;
                    }
                    else{
                        cout<<"Username or password is incorrect.\n";
                        active_admin = nullptr;
                        logged_in=0;
                    }
                }
            }
            else if(decision==2){
                cout<<"[1] Admin"<<endl;
                cout<<"[2] User"<<endl;
                cin>>decision;
                if(decision==1){
                    cout<<"Enter Admin Username"<<endl;
                    cin>>user;
                    cout<<"Enter Admin Password"<<endl;
                    cin>>pswd;
                    active_admin = new Admin;
                    active_admin->username = user;
                    active_admin->password = pswd;
                    logged_in=2;
                }
                else{

                    cout<<"Enter Username"<<endl;
                    cin>>user;
                    cout<<"Enter Password"<<endl;
                    cin>>pswd;
                    active_user = new User;
                    active_user->username = user;
                    active_user->password = pswd;
                    logged_in=1;
                }
            }

            else{
                break;
            }
            
        }

        if(logged_in==1){
            cout<<"[1] Search by title\n[2] Search by genre\n[3] Rent a title\n[4] Purchase a title\n[5] View Purchased\n[6] View Rented\n[7] Show dues\n[8] Return title\n[9] Log out\n";
            cin>>decision;
            switch(decision){
                case 1:
                    cout<<"Enter the title: \n";
                    cin>>input;
                    active_user->search_title(input, movie_cat, show_cat);
                    break;
                case 2:
                    cout<<"Enter the genre: \n";
                    cin>>input;
                    active_user->search_genre(input, movie_cat, show_cat);
                    break;
                case 3:
                    cout<<"Enter the title you wish to rent: \n";
                    cin>>input;
                    active_user->rent(input, movie_cat, show_cat);
                    break;
                case 4:
                    cout<<"Enter the title you wish to purchase: \n";
                    cin>>input;
                    active_user->purchase(input, movie_cat, show_cat);
                    break;
                case 5:
                    active_user->view_purchased();
                    break;
                case 6:
                    active_user->view_rented();
                    break;
                case 7:
                    active_user->dues();
                    break;
                case 8:
                    cout<<"Enter the title you wish to return: \n";
                    cin>>input;
                    active_user->return_(input);
                    break;
                case 9:
                    logged_in = false;
                    
                    active_user->save("users/"+active_user->username+".dat");
                    active_user=nullptr;
                    cout<<"Successfuly logged out\n";
                    break;
                
            }
        }
        else if(logged_in==2){
            cout<<"[1] Add a movie\n[2] Add a show\n[3] Remove a movie\n[4] Remove a show\n[5] Log out\n";
            cin>>decision;
            switch(decision){
                case 1:
                    cout<<"Title: ";
                    cin>>title;
                    cout<<"\nGenre: ";
                    cin>>type;
                    cout<<"\nRating: ";
                    cin>>rated;
                    cout<<"\nDuration: ";
                    cin>>duration;
                    cout<<"\nRent Cost: ";
                    cin>>rent;
                    cout<<"\nPurchase Cost: ";
                    cin>>purchase;
                    movie_cat = active_admin->add_movie(title, type, rated, duration, rent, purchase, movie_cat);
                    cout<<"Movie has been added\n";
                    break;
                case 2:
                    cout<<"Title: ";
                    cin>>title;
                    cout<<"\nGenre: ";
                    cin>>type;
                    cout<<"\nRating: ";
                    cin>>rated;
                    cout<<"\nSeasons: ";
                    cin>>seasons;
                    cout<<"\nEpisodes: ";
                    cin>>episodes;
                    cout<<"\nDuration Per Episode: ";
                    cin>>duration;
                    cout<<"\nRent Cost: ";
                    cin>>rent;
                    cout<<"\nPurchase Cost: ";
                    cin>>purchase;
                    show_cat = active_admin->add_show(title, type, rated, seasons, episodes, duration, rent, purchase, show_cat);
                    cout<<"Show has been added\n";
                    break;
                case 3:
                    cout<<"Enter Title to remove: ";
                    cin>>title;
                    movie_cat = active_admin->remove_movie(title, movie_cat);
                    break;
                case 4:
                    cout<<"Enter Title to remove: ";
                    cin>>title;
                    show_cat = active_admin->remove_show(title, show_cat);
                    break;
                case 5:
                    logged_in = false;
                    active_admin->save("admin/"+active_admin->username+".dat");
                    active_admin->save_catalogues("catalogues/data.dat", movie_cat, show_cat);
                    active_admin=nullptr;
                    cout<<"Successfully logged out\n";
                    break;
            }
        }
}

    return 0;
    
}

//docker