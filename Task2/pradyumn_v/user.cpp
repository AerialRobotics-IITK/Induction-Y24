#include "user.h"
#include<sstream>

void User::search_title(string name, movie_entry* movie_catalog, tv_show_entry* show_catalog){
    tv_show_entry* iter = show_catalog;
    movie_entry* iter_movie = movie_catalog;
    bool printed=false;
    while(iter){
        if(iter->data->title==name){
            cout<<"--------------------"<<endl<<endl;
            cout<<"Title: "<<iter->data->title<<endl;
            cout<<"Genre: "<<iter->data->genre<<endl;
            cout<<"Seasons: "<<iter->data->seasons<<endl;
            cout<<"Episodes: "<<iter->data->ep_per_season<<endl;
            cout<<"Rented Cost: "<<iter->data->rent_cost<<endl;
            cout<<"Purchase Cost: "<<iter->data->purchase_cost<<endl<<endl;
            cout<<"--------------------"<<endl<<endl;
            printed=true;
        }

        iter = iter->next;
    }

    while(iter_movie){
        if(iter_movie->data->title==name){
            cout<<"--------------------"<<endl<<endl;
            cout<<"Title: "<<iter_movie->data->title<<endl;
            cout<<"Genre: "<<iter_movie->data->genre<<endl;
            cout<<"Duration: "<<iter_movie->data->duration<<endl;
            cout<<"Rented Cost: "<<iter_movie->data->rent_cost<<endl;
            cout<<"Purchase Cost: "<<iter_movie->data->purchase_cost<<endl<<endl;
            cout<<"--------------------"<<endl<<endl;
            printed=true;
        }

        iter_movie = iter_movie->next;
    }
    if(!printed){
        cout<<"Could not find title";
    }
}

void User::search_genre(string genres, movie_entry* movie_catalog, tv_show_entry* show_catalog){
    tv_show_entry* iter = show_catalog;
    movie_entry* iter_movie = movie_catalog;
    bool printed = false;
    while(iter){
        if(iter->data->genre==genres){
            cout<<"--------------------"<<endl<<endl;
            cout<<"Title: "<<iter->data->title<<endl;
            cout<<"Genre: "<<iter->data->genre<<endl;
            cout<<"Seasons: "<<iter->data->seasons<<endl;
            cout<<"Episodes: "<<iter->data->ep_per_season<<endl;
            cout<<"Rented Cost: "<<iter->data->rent_cost<<endl;
            cout<<"Purchase Cost: "<<iter->data->purchase_cost<<endl<<endl;
            cout<<"--------------------"<<endl<<endl;
            printed=true;
        }

        iter = iter->next;
    }

    while(iter_movie){
        if(iter_movie->data->genre==genres){
            cout<<"--------------------"<<endl<<endl;
            cout<<"Title: "<<iter_movie->data->title<<endl;
            cout<<"Genre: "<<iter_movie->data->genre<<endl;
            cout<<"Duration: "<<iter_movie->data->duration<<endl;
            cout<<"Rented Cost: "<<iter_movie->data->rent_cost<<endl;
            cout<<"Purchase Cost: "<<iter_movie->data->purchase_cost<<endl<<endl;
            cout<<"--------------------"<<endl<<endl;
            printed=true;
        }

        iter_movie = iter_movie->next;
    }
    if(!printed){
        cout<<"Could not find title\n";
    }
}

void User::return_(string name){
    movie_entry* curr = rented;
    movie_entry* prev = nullptr;
    while(curr){
        if(curr->data->title == name){
            if(prev) prev->next = curr->next;
            else rented = curr->next;
            delete curr;
            cout << "Movie returned"<<endl<<endl;
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    tv_show_entry* curr_show = rented_show;
    tv_show_entry* prev_show = nullptr;
    while(curr_show){
        if(curr_show->data->title == name){
            if(prev_show) prev_show->next = curr_show->next;
            else rented_show = curr_show->next;
            delete curr_show;
            cout << "Show returned"<<endl<<endl;
            return;
        }
        prev_show = curr_show;
        curr_show = curr_show->next;
    }
    
    cout << "Item not found\n";
}


void User::dues(){
    cout<<endl<<"--------------------"<<endl<<"Dues"<<endl;
    cout<<due;
    cout<<endl<<"--------------------"<<endl<<endl;
}

void User::rent(string name, movie_entry* movie_catalog, tv_show_entry* tv_catalog){
    movie_entry* curr = movie_catalog;
    tv_show_entry* curr_show = tv_catalog;
    bool found;
    while(curr!=nullptr){
        if(curr->data->title==name){
            found=true;
            break;
        }
        curr=curr->next;
    }

    while(curr_show!=nullptr){
        if(curr_show->data->title==name){
            found=true;
            break;
        }
        curr_show=curr_show->next;
    }
    
    if(curr&&found){
        movie_entry* new_head = new movie_entry;
        new_head->data = curr->data;
        new_head->next = nullptr;
        curr = new_head;
        if(!rented){
            rented = curr;
        }
        else{
            curr->next=rented;
            rented=curr;
        }

        due+=curr->data->rent_cost;
    }
    else if(curr_show&&found){
        tv_show_entry* new_head = new tv_show_entry;
        new_head->data = curr_show->data;
        new_head->next = nullptr;
        curr_show = new_head;
        if(!rented_show){
            rented_show = curr_show;
        }
        else{
            curr_show->next=rented_show;
            rented_show=curr_show;
        }

        due+=curr_show->data->rent_cost;
    }
    else{
        cout<<"Could not find the title you searched for\n";
    }
}

void User::purchase(string name, movie_entry* movie_catalog, tv_show_entry* tv_catalog){
    movie_entry* curr = movie_catalog;
    tv_show_entry* curr_show = tv_catalog;
    bool found;
    while(curr!=nullptr){
        if(curr->data->title==name){
            found=true;
            break;
        }
        curr=curr->next;
    }

    while(curr_show!=nullptr){
        if(curr_show->data->title==name){
            found=true;
            break;
        }
        curr_show=curr_show->next;
    }
    
    if(curr&&found){
        movie_entry* new_head = new movie_entry;
        new_head->data = curr->data;
        new_head->next = nullptr;
        curr = new_head;
        if(!purchased){
            purchased = curr;
        }
        else{
            curr->next=rented;
            purchased=curr;
        }

        due+=curr->data->rent_cost;
    }
    else if(curr_show&&found){
        tv_show_entry* new_head = new tv_show_entry;
        new_head->data = curr_show->data;
        new_head->next = nullptr;
        curr_show = new_head;
        if(!purchased_show){
            purchased_show = curr_show;
        }
        else{
            curr_show->next=purchased_show;
            purchased_show=curr_show;
        }

        due+=curr_show->data->rent_cost;
    }
    else{
        cout<<"Could not find the title you searched for\n";
    }
}

void User::view_purchased(){
    movie_entry* iter = purchased;
    tv_show_entry* iter_show = purchased_show;
    cout<<"Purchased Titles"<<endl<<"--------------------"<<endl;

    while(iter!=nullptr){
        cout<<"Title: "<<iter->data->title<<endl;
        cout<<"Genre: "<<iter->data->genre<<endl;
        cout<<"Cost: "<<iter->data->purchase_cost<<endl<<endl;
        iter = iter->next;
    }

    while(iter_show!=nullptr){
        cout<<"Title: "<<iter_show->data->title<<endl;
        cout<<"Genre: "<<iter_show->data->genre<<endl;
        cout<<"Cost: "<<iter_show->data->purchase_cost<<endl;
        iter_show = iter_show->next;
    }
    cout<<"--------------------"<<endl;
}

void User::view_rented(){
    movie_entry* iter = rented;
    tv_show_entry* iter_show = rented_show;
    cout<<"Rented Titles"<<endl<<"--------------------"<<endl;

    while(iter){
        cout<<"Title: "<<iter->data->title<<endl;
        cout<<"Genre: "<<iter->data->genre<<endl;
        cout<<"Cost: "<<iter->data->purchase_cost<<endl<<endl;
        iter = iter->next;
    }

    while(iter_show){
        cout<<"Title: "<<iter_show->data->title<<endl;
        cout<<"Genre: "<<iter_show->data->genre<<endl;
        cout<<"Cost: "<<iter_show->data->purchase_cost<<endl;
        iter_show = iter_show->next;
    }
    cout<<"--------------------"<<endl;
}

void User::save(const string& filename) {
    ofstream out(filename);
    if (!out) {
        cerr << "Could not open file for writing.\n";
        return;
    }
    out << username << '\n' << password << '\n' << due << '\n';

    movie_entry* m = rented;
    while (m) {
        out << "RENTED_MOVIE " << m->data->title<<'\n';
        m = m->next;
    }
    m = purchased;
    while (m) {
        out << "PURCHASED_MOVIE " << m->data->title <<'\n';
        m = m->next;
    }
    tv_show_entry* s = rented_show;
    while (s) {
        out << "RENTED_SHOW " << s->data->title << '\n';
        s = s->next;
    }
    s = purchased_show;
    while (s) {
        out << "PURCHASED_SHOW " << s->data->title << '\n';
        s = s->next;
    }
    out.close();
}

void User::load(const string& filename, movie_entry* movie_cat, tv_show_entry* show_cat) {
    ifstream in(filename);
    if (!in) {
        cerr << "Could not open file for reading.\n";
        return;
    }
    getline(in, username);
    getline(in, password);

    string due_line;
    getline(in, due_line);
    due = stoi(due_line);

    string line;
    while (getline(in, line)) {
        istringstream iss(line);
        string type, title, genre;
        int rating;
        iss >> type >> title >> genre >> rating;
        if (type == "RENTED_MOVIE") {
            rent(title, movie_cat, show_cat);
        } else if (type == "PURCHASED_MOVIE") {
            purchase(title, movie_cat, show_cat);
        } else if (type == "RENTED_SHOW") {
            rent(title, movie_cat, show_cat);
        } else if (type == "PURCHASED_SHOW") {
            purchase(title, movie_cat, show_cat);
        }
    }
    in.close();
}

