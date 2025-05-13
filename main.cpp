#include <unordered_map>
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <functional>
#include <vector>
#include <fstream>
#include <filesystem>
#include <utility>


//user list with hashes
/* user individual files with their shows and other stuffs
any change in name or password will edit this user file name, and the user_list file
The user file will contain the shows name, alongside rented time and or purchased
The string name of all shows must be cleaned, or checked for wierd names
The catalog files will contain contain show or movie. and contain all related info, regarding that. Any change in rating, or by admin must be
reflected IMMEDIATELY in the files
// keep a copy of the file system, update to that, and before exiting, just save once. Much faster and efficient
TODO : Allow buying individual seasons, instead of whole shows
TODO : Currently rent and date system. and return(what the hell it even is ??)
TODO : just logout feature, without exiting the whole code
TODO : all sorts of memory freeing at end.
TODO : study type casts, and their forms, to safely do inheritance related stuff. Also learn about those tables which are used for inheritance and virtual funcs
TODO : Purchase history of each user
Whenever adding a content, make sure its updated flag is set to true, for it to be written to the filesystem !!
*/

class Content;
class User;
std::hash<std::string> hasher;
std::vector<std::string> all_genres;
std::string admin_name;
std::string admin_pass;
std::size_t admin_hash;
std::unordered_map<std::string, std::size_t> all_users;
std::unordered_map<std::string, Content*> all_shows;
User* cur_user;

class Content {
    public:
    std::string title;
    bool is_movie;
    std::vector<std::string> genre;
    int tot_rating = 0;
    int users = 0;
    bool updated = false;
    //bool is_purchased;
    //bool is_rented;
    //date of rental

    float rating(){ if(!users) return 0; else return (float)tot_rating/users; }
};

class Movie : public Content {
    public:

    int duration; //in minutes
    //float rent_rate;
    float rate;
};

class Show : public Content {
    public:

    int seasons;
    std::vector<int> eps;
    //std::vector<float> rent_rate;
    std::vector<float> rate;
};

//make a bunch of functions or class to effortlessly update the files, wherever needed

class User {
    //different logical functions for admin and normal user
    void admin();
    void user();
    void purchase(std::string); //show or movie purchase, updates the charges. update the file, and update shows and shows_list
    //void purchase_history();
    void remove(std::string, bool ret = false); //removes show, if ret is true, money is returned, else not
    void update_pass(std::string);
    void update_username(std::string); //careful that no clashes in username occur here either. Remove old from all_users map !! 
    void clear_dues();
    float charge_calc();
    void star(std::string, int); //rate movie out of 5 stars
    
    public:
    User(std::string user, std::size_t passhash, bool admin = false) : username(user), pass_hash(passhash), is_admin(admin) {}
    // the main printing and logical unit
    void loop(){ if(is_admin) admin(); else user(); }
    void populate(); // fills the shows vector and charges, accessing file system. Check if its already NOT populated. Run at start, but not in constuctor, as shows_list is not filled then

    bool is_admin;
    std::unordered_map<std::string, Content*> shows; //show is populated by populate() and shows_list only ONCE, at beginning. All other changes must with purchase and remove
    std::unordered_map<std::string, bool> shows_list; // also update this with each purchase and deletion. Can use set, but map are easier
    std::size_t pass_hash;
    std::string username;
    float charges = 0.0f;
};

namespace ContentManager { //checks clashing content names, case unsensitive and space and special characters allowed
    void load(); //populated all_shows map
    std::vector<std::string> search(std::string); //returns names of shows, can be accessed from the all_shows list
    std::vector<std::string> search(std::vector<std::string>, bool intersect = false); //search by genre, intersect, or atleast one match
    std::vector<std::string> search(bool show = false); // show or movie
    bool content_exist(std::string); // checks if a content exists or not

    //TODO : Implement method to populate the all_genres vector(can make it case unsensitive later)
};

//put all file access, helper functions, update, deletion functions here, for easier access.
namespace FileSys { //all file accesses are made through functions in this, not any other function
    User* readUser(std::string); // writes to the user files, NOT FOR ADMIN
    void writeUser(User&); // if username or passward is changed, update that too(the pass username file is auto updated in update_passlist())
    Content* readMovie(std::string);
    void writeMovie(Movie*);
    Content* readShow(std::string);
    void writeShow(Show*);
    //std::vector<std::string> list(void);
    //std::vector<Content*> listContent(void);
    size_t get_passhash(std::string usern); // just all_users[usern], with current design
    bool name_exist(std::string); //checks if the username already exists or not
    bool valid_pass_name(std::string); //checks if the password and username are valid, not empty, doesn't have spaces and certain special characters
    void load_user(); //populates the all_user vector from the files. just loads in user_pass file, not data about each user
    void update_passlist(); // updates the username passhash file
    void update_catalog(); // goes through all_shows, checks if the content is updated and updates using writeShow or writeMovie
    void clean_users(); // cleans removed usernames from the users folder
};

int main(){

    ContentManager::load();
    FileSys::load_user();
    std::ifstream admin_file("admin.txt");
    admin_file >> admin_name;
    admin_file >> admin_pass;
    admin_hash = hasher(admin_pass);
    all_users[admin_name] = admin_hash;
    admin_file.close();
    
    // TODO: implement the logout, checking is user exist, and other exit options
    // TODO: implement the signin and signup options
    while(1){
        std::cout << "1 : Signin    2 : Signup   3 : Exit" << std::endl;
        int choice;
        std::cin >> choice;
        std::getchar(); // this is to eat the final \n
        switch(choice) {
            case 1 :
            {
                // TODO : input error handles, so the program doesnt crash
                std::cout << "Username: ";
                std::string usern;
                std::getline(std::cin, usern);
                std::cout << "Password: ";
                std::string passw;
                std::getline(std::cin, passw);
                if(!FileSys::name_exist(usern)){
                    std::cout << "User doesn't exist, use Signup to create new account..." << std::endl;
                    continue;
                }
                if(!FileSys::valid_pass_name(usern) || !FileSys::valid_pass_name(passw)){
                    std::cout << "Username or password are invalid, retry..." << std::endl;
                    continue;
                }
                auto passhash = FileSys::get_passhash(usern);
                if(passhash == hasher(passw)){
                    if(!cur_user) delete cur_user;
                    cur_user = FileSys::readUser(usern);
                    std::cout << "Logged in..." << std::endl;
                    cur_user->loop();
                }
                else {
                    std::cout << "Wrong password or username, retry..." << std::endl;
                    continue;
                }
                delete cur_user;
            } break;

            case 2 :
            {
                while(1){
                    std::cout << "Username: ";
                    std::string usern; 
                    std::getline(std::cin, usern);
                    if(FileSys::name_exist(usern)){
                        std::cout << "Username already in use, retry..." << std::endl;
                        continue;
                    }
                    std::cout << "Password: ";
                    std::string passw;
                    std::getline(std::cin, passw);
                    if(!FileSys::valid_pass_name(passw) || !FileSys::valid_pass_name(usern)){
                        std::cout << "Username or password is invalid, try again..." << std::endl;
                        continue;
                    }
                    auto passhash = hasher(passw);
                    cur_user = new User(usern, false); // cannot add admin account
                    all_users[usern] = passhash; // new user added
                    FileSys::writeUser(*cur_user);
                    delete cur_user;
                    std::cout << "Account created, now signin with the same credentials..." << std::endl;
                    break;
                }
            } break;

            case 3 : 
            {
                //TODO : pass change in admin file
                FileSys::writeUser(*cur_user);
                FileSys::clean_users();
                FileSys::update_passlist();
                FileSys::update_catalog();
                return 0;
            }break;

            default : 
            {
                std::cout << "Invalid response, retry..." << std::endl;
                continue;
            }
        }
    }
}


// Implementation of all above methods 

User* FileSys::readUser(std::string name) { // the file has the number of total content, followed by same number of lines of shows' names
    if(!FileSys::name_exist(name)) {
        std::cerr << "No user with that name";
        return nullptr;
    }
    std::string filename = "users/" + name + ".txt";
    std::string temp;
    std::ifstream streem(filename);
    auto passh = FileSys::get_passhash(name);
    User* new_user = new User(name, passh, (name == admin_name) ? true : false);
    if(streem.is_open()) {
        std::getline(streem, temp);
        int num_shows = std::stoi(temp);
        while(num_shows--) {
            std::getline(streem, temp);
            if(ContentManager::content_exist(temp))
                new_user->shows_list[temp] = 1;
            //this check above is important, as shows are remmved by admin
        }
    }
    new_user->populate();
    streem.close();
    return new_user;
}
void FileSys::writeUser(User &user) {
    std::string filename = "users/" + user.username + ".txt";
    std::ofstream file(filename);
    file << user.shows_list.size() << std::endl;
    for(const auto& pairr : user.shows_list) {
        file << pairr.first << std::endl;
    }
} // if username, update that too(the pass username file is auto updated in update_passlist())
Content* FileSys::readMovie(std::string title) {
    Movie* sho = new Movie;
    std::string filename = "catalog/" + title + ".txt";
    std::ifstream file(filename);
    std::string temp;
    sho->title = title;
    file >> sho->is_movie;
    file >> sho->tot_rating;
    file >> sho->users;
    file >> sho->duration;
    file >> sho->rate;

    int num_g;
    file>>num_g;
    sho->genre = std::vector<std::string>(num_g, "");
    for(int i = 0; i < sho->genre.size(); i++) file >> sho->genre[i];

    file.close();
    return sho;
}
void FileSys::writeMovie(Movie* sho) {
    std::string filename = "catalog/" + sho->title + ".txt";
    std::ofstream file(filename);
    
    file << sho->is_movie << std::endl;
    file << sho->tot_rating << std::endl;
    file << sho->users << std::endl;
    file << sho->duration << std::endl;
    file << sho->rate << std::endl; 

    file << sho->genre.size() << std::endl;
    for(int i = 0; i < sho->genre.size(); i++) file << sho->genre[i] << std::endl;
    file.close();
}
Content* FileSys::readShow(std::string title) {
    Show* sho = new Show;
    std::string filename = "catalog/" + title + ".txt";
    std::ifstream file(filename);
    std::string temp;
    sho->title = title;
    file >> sho->is_movie;
    file >> sho->tot_rating;
    file >> sho->users;
    file >> sho->seasons;
    sho->eps = std::vector<int>(sho->seasons, 0);
    sho->rate = std::vector<float>(sho->seasons, 0.0f);
    for(int i = 0; i < sho->seasons; i++) file >> sho->eps[i];
    for(int i = 0; i < sho->seasons; i++) file >> sho->rate[i];

    int num_g;
    file>>num_g;
    sho->genre = std::vector<std::string>(num_g, "");
    for(int i = 0; i < sho->genre.size(); i++) file >> sho->genre[i];

    file.close();
    return sho;
}
void FileSys::writeShow(Show* sho) { // TODO : implement feature to show the number of users who gave reviews
    std::string filename = "catalog/" + sho->title + ".txt";
    std::ofstream file(filename);

    file << sho->is_movie << std::endl;
    file << sho->tot_rating << std::endl;
    file << sho->users << std::endl;
    file << sho->seasons << std::endl;
    for(int i = 0; i < sho->seasons; i++) file << sho->eps[i] << " "; file << std::endl;
    for(int i = 0; i < sho->seasons; i++) file << sho->rate[i] << " "; file << std::endl;

    file << sho->genre.size() << std::endl;
    for(int i = 0; i < sho->genre.size(); i++) file << sho->genre[i] << std::endl;
    file.close();
}
size_t FileSys::get_passhash(std::string usern) {
    if(!FileSys::name_exist(usern)){
        std::cerr << "No such user exists\n";
        return 0;
    }
    else return all_users[usern];
} // just all_users[usern], with current design
bool FileSys::name_exist(std::string name) {
    return all_users.find(name) != all_users.end();
} //checks if the username already exists or not
bool FileSys::valid_pass_name(std::string str) {
    bool flag = 1;
    std::string allowed = "1234567890!@#$%^&*()+=<>/?;:{}[]|qwertyasdfghjklzxcvbnmuiopQWERTYUIOPASDFGHJKLZXCVBNM";
    if(str.find_first_not_of(allowed) != std::string::npos) flag = 0;
    if(str.length() == 0) flag = 0;
    return flag;
} //checks if the password and username are valid, not empty, doesn't have spaces and certain special characters
void FileSys::load_user() {
    std::ifstream file("user_pass.txt");
    std::string temp, temp2;
    while(std::getline(file, temp)) {
        std::getline(file, temp2);
        all_users[temp] = std::stoull(temp2); //as size_t is 64 bits, I use STOULL, NOT STOI
    }
    file.close();
} //populates the all_user map from the files
void FileSys::update_passlist() {
    std::ofstream file("user_pass.txt", std::ios::trunc); // check that this doesn't append
    for(const auto &pairr : all_users) {
        file << pairr.first << "\n" << pairr.second << std::endl;
    }
    file.close();
} // updates the username passhash file
void FileSys::update_catalog() {
    std::ofstream file("content.txt");
    for(const auto &pairr : all_shows) {
        file << pairr.first << std::endl;
        if(pairr.second->updated)
            if(pairr.second->is_movie){
                FileSys::writeMovie(static_cast<Movie*>(pairr.second));
            } else {
                FileSys::writeShow(static_cast<Show*>(pairr.second));
            }
    }
    file.close();
} // goes through all_shows, checks if the content is updated and updates using writeShow or writeMovie
void FileSys::clean_users() {
    namespace fs = std::filesystem;
    // TODO : implement this to remove all usernames files which do not exist in all_users map, similary clean catalog method, needs implementation!!
}

//................................................................................................

void ContentManager::load() { 
    std::ifstream file1("content.txt");
    std::string sho;
    while(getline(file1, sho)){
        auto filename = "catalog/" + sho + ".txt";
        std::ifstream file2(filename);
        bool is_movie;
        file2>>is_movie;
        Content* con;
        if(is_movie) {
            con = FileSys::readMovie(sho);
        } else {
            con = FileSys::readShow(sho);
        }
        all_shows[sho] = con;
    }
} //populated all_shows map
std::vector<std::string> ContentManager::search(std::string name) {
    std::vector<std::string> vec;
    for(auto &pair : all_shows) {
        if(pair.first.find(name) != std::string::npos) vec.push_back(pair.first);
    }
    return vec;
} //returns names of shows, can be accessed from the all_shows list
std::vector<std::string> ContentManager::search(std::vector<std::string> names, bool intersect) {
    std::vector<std::string> vec;
    if(intersect) {
        for(auto &pair : all_shows) {
            bool flag = 1;
            for(const auto &gen : names) {
                if(std::find(pair.second->genre.begin(), pair.second->genre.end(), gen) == pair.second->genre.end()) flag = 0;
            }
            if(flag) vec.push_back(pair.first);
        }
    } else {
        for(auto &pair : all_shows) {
            for(const auto &gen : names) {
                if(std::find(pair.second->genre.begin(), pair.second->genre.end(), gen) != pair.second->genre.end()) vec.push_back(pair.first);
            }
        }
    }
    return vec;
} //search by genre, intersect, or atleast one match
std::vector<std::string> ContentManager::search(bool show) {
    std::vector<std::string> vec;
    for(auto &pair : all_shows) {
        if(pair.second->is_movie == show) vec.push_back(pair.first);
    }
    return vec;
} // lists all shows OR movies
bool ContentManager::content_exist(std::string name) {
    return all_shows.find(name) != all_shows.end();
}// checks if a content exists or not

//.................................................................................................................

void User::populate() {
    for(auto str : shows_list) {
        shows[str.first] = all_shows[str.first];
    }
    charges = charge_calc();
}
float User::charge_calc() {
    float ch = 0;
    for(auto sho : shows) {
        if(sho.second->is_movie) {
            auto shoo = static_cast<Movie*>(sho.second);
            ch += shoo->rate;
        } else {
            auto shoo = static_cast<Show*>(sho.second);
            for(int i = 0; i < shoo->seasons; i++)
                ch += shoo->rate[i]; //assuming all seasons are bought in pack
        }
    }
    return ch;
}
void User::admin() {
    while(1) {
    int choice;
    std::cout << "\nAdmin Options:\n"
              << "1. Remove Content\n"
              << "2. Add Content\n"
              << "3. Check All Users' Pending Charges\n"
              << "4. Check Specific User's Pending Charges\n"
              << "5. Change Password\n"
              << "6. Logout\n"
              << "Enter your choice: ";
    std::cin >> choice;
    getchar();

    switch (choice) {
        case 1: { // Remove Content
            std::string contentToRemove;
            std::cout << "Enter content to remove: ";
            std::getline(std::cin, contentToRemove);
            if (ContentManager::content_exist(contentToRemove)) {
                all_shows.erase(contentToRemove);
                FileSys::update_catalog(); // this updates the content file, so the show file in catalog stays, if just forgets about it(TODO : can clean such files...)
                std::cout << "Content \"" << contentToRemove << "\" removed successfully.\n";
            } else {
                std::cout << "Content not found.\n";
            }
            break;
        }
        case 2: { // Add Content
            std::string title;
            std::cout << "Enter content title to add: ";
            std::getline(std::cin, title);
            if (ContentManager::content_exist(title)) {
                std::cout << "Content already exists.";
                break;
            }
            // Determine type
            int t;
            std::cout << "Enter 0 for Movie, 1 for Show: ";
            std::cin >> t;
            getchar();
            if (t == 0) {
                // Movie
                auto *m = new Movie();
                m->title = title;
                m->is_movie = true;
                std::cout << "Enter duration (minutes): ";
                std::cin >> m->duration;
                getchar();
                std::cout << "Enter rental rate: ";
                std::cin >> m->rate;
                getchar();
                // Genres
                std::string line;
                std::cout << "Enter genres (comma-separated): ";
                std::getline(std::cin, line);
                size_t pos = 0;
                while ((pos = line.find(',')) != std::string::npos) {
                    m->genre.push_back(line.substr(0, pos));
                    line.erase(0, pos + 1);
                }
                if (!line.empty()) m->genre.push_back(line);
                m->updated = true;
                all_shows[title] = m;
                FileSys::writeMovie(m);
                break;
            } else {
                // Show
                auto *s = new Show();
                s->title = title;
                s->is_movie = false;
                std::cout << "Enter number of seasons: ";
                std::cin >> s->seasons;
                getchar();
                s->eps.resize(s->seasons);
                s->rate.resize(s->seasons);
                for (int i = 0; i < s->seasons; ++i) {
                    std::cout << "Season " << i+1 << " - episodes: ";
                    std::cin >> s->eps[i];
                    getchar();
                    std::cout << "Season " << i+1 << " - rate: ";
                    std::cin >> s->rate[i];
                    getchar();
                }
                // Genres
                std::string line;
                std::cout << "Enter genres (comma-separated): ";
                std::getline(std::cin, line);
                size_t pos = 0;
                while ((pos = line.find(',')) != std::string::npos) {
                    s->genre.push_back(line.substr(0, pos));
                    line.erase(0, pos + 1);
                }
                if (!line.empty()) s->genre.push_back(line);
                s->updated = true;
                all_shows[title] = s;
                FileSys::writeShow(s);
                break;
            }
        }
        case 3: { // Check all users' charges
            std::cout << "All users' pending charges:\n";
            for (auto &pair : all_users) {
                User* u = FileSys::readUser(pair.first);
                if (u) {
                    std::cout << "  " << pair.first << ": " << u->charges << "\n";
                    delete u;
                }
            }
            break;
        }
        case 4: { // Check specific user's charges
            std::string uname;
            std::cout << "Enter username: ";
            std::getline(std::cin, uname);
            if (FileSys::name_exist(uname)) {
                User* u = FileSys::readUser(uname);
                std::cout << uname << "'s pending charges: " << u->charges << "\n";
                delete u;
            } else {
                std::cout << "User not found.\n";
            }
            break;
        }
        case 5: { // Change password // TODO : Admin password is saved seperately in admin file, so change this to reflect that
            std::string newPass;
            std::cout << "Enter new password: ";
            std::getline(std::cin, newPass);
            update_pass(newPass);
            FileSys::update_passlist();
            std::cout << "Password updated.\n";
            break;
        }
        case 6: { // Logout // TODO : change this to somehow set a flag or something, so it exits the Loop() function in User class, too, to prevent inability of signing out
            std::cout << "Logging out...\n";
            return;  // exit admin() back to main loop
        }
        default:
            std::cout << "Invalid choice.\n";
    }
    }
}

void User::user() {
    while(1) {
    int choice;
    std::cout << "\nUser Options:\n"
              << "1. Search by Substring\n"
              << "2. Search by Genre\n"
              << "3. Change Password\n"
              << "4. Change Username\n"
              << "5. Search by Type (Movie/Show)\n"
              << "6. Purchase\n"
              << "7. Remove\n"
              << "8. See Charges\n"
              << "9. Clear Dues\n"
              << "10. Rate Movie\n"
              << "11. Logout\n"
              << "Enter your choice: ";
    std::cin >> choice;
    getchar();

    switch (choice) {
        case 1: { // Search by substring
            std::string substr;
            std::cout << "Enter search string: ";
            std::getline(std::cin, substr);
            auto results = ContentManager::search(substr);
            std::cout << "Matches:\n";
            for (auto &title : results) {
                auto *c = all_shows[title];
                std::cout << "  " << title << " (Rating: " << c->rating() << ")\n";
            }
            break;
        }
        case 2: { // Search by genre
            std::string line;
            std::cout << "Enter genres (comma-separated): ";
            std::getline(std::cin, line);
            std::vector<std::string> genres;
            size_t pos = 0;
            while ((pos = line.find(',')) != std::string::npos) {
                genres.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            genres.push_back(line);
            auto results = ContentManager::search(genres, false);
            std::cout << "Matches:\n";
            for (auto &title : results) {
                std::cout << "  " << title << "\n";
            }
            break;
        }
        case 3: { // Change password
            std::string newPass;
            std::cout << "Enter new password: ";
            std::getline(std::cin, newPass);
            update_pass(newPass);
            FileSys::update_passlist();
            std::cout << "Password updated.\n";
            break;
        }
        case 4: { // Change username
            std::string newName;
            std::cout << "Enter new username: ";
            std::getline(std::cin, newName);
            update_username(newName);
            FileSys::update_passlist();
            std::cout << "Username updated to " << username << ".\n";
            break;
        }
        case 5: { // Search by type
            int t;
            std::cout << "Enter 0 for movies, 1 for shows: ";
            std::cin >> t;
            getchar();
            auto results = ContentManager::search(static_cast<bool>(t));
            std::cout << (t == 0 ? "Movies:\n" : "Shows:\n");
            for (auto &title : results) {
                std::cout << "  " << title << "\n";
            }
            break;
        }
        case 6: { // Purchase
            std::string title;
            std::cout << "Enter title to purchase: ";
            std::getline(std::cin, title);
            purchase(title);
            std::cout << "Purchased \"" << title << "\". Current charges: " << charges << "\n";
            break;
        }
        case 7: { // Remove
            std::string title;
            std::cout << "Enter title to remove: ";
            std::getline(std::cin, title);
            remove(title, false);
            std::cout << "Removed \"" << title << "\" from your list.\n";
            break;
        }
        case 8: // See charges
            std::cout << "Your pending charges: " << charges << "\n";
            break;
        case 9: // Clear dues
            clear_dues();
            std::cout << "Dues cleared.\n";
            break;
        case 10: { // Rate movie
            std::string title;
            int stars;
            std::cout << "Enter movie title to rate: ";
            std::getline(std::cin, title);
            std::cout << "Enter stars (1-5): ";
            std::cin >> stars; getchar();
            if(stars < 0  || stars > 5) {
                std::cerr << "Invalid rating..." << std::endl;
                break;
            }
            star(title, stars);
            all_shows[title]->updated = true;
            std::cout << "Rated \"" << title << "\" with " << stars << " stars.\n";
            break;
        }
        case 11: // Logout // TODO : change this to somehow set a flag or something, so it exits the Loop() function in User class, too, to prevent inability of signing out
            std::cout << "Logging out...\n";
            return;
        default:
            std::cout << "Invalid choice.\n";
    }
    }
}
 // loop function for normal user options. This basically prints all options for the user, search by substring, search by genre, change pass and username, search by type(movie or show)(in searches, prints content in formatted form with rating, duration, no of seasons, etc), purchase. remove, see chrages, clear dues, rate movie

void User::purchase(std::string sho) {
    if(!ContentManager::content_exist(sho)){
        std::cerr << "No content with this name to purchase..." << std::endl;
        return;
    }
    shows[sho] = all_shows[sho];
    shows_list[sho] = 1;
    charges = charge_calc();
} //show or movie purchase, updates the charges. update the file, and update shows and shows_list
//void User::purchase_history() { }
void User::remove(std::string sho, bool ret) {
    if(!ContentManager::content_exist(sho)){
        std::cerr << "No content with this name to remove..." << std::endl;
        return;
    }
    if(ret) {
        if(shows[sho]->is_movie) {
            charges -= static_cast<Movie*>(shows[sho])->rate;
        } else {
            auto shoo = static_cast<Show*>(shows[sho]);
            for(int i = 0; i < shoo->seasons; i++)
                charges -= shoo->rate[i];
        }
    }
    shows_list.erase(sho);
    shows.erase(sho);
} //removes show, if ret is true, money is returned, else not
void User::update_pass(std::string pass) {
    if(!FileSys::valid_pass_name(pass)) {
        std::cerr << "Invalid password change request..." << std::endl;
        return;
    }
    all_users[username] = hasher(pass);
    this->pass_hash = hasher(pass);
} // update the password in the all_users map
void User::update_username(std::string new_name) {
    if(FileSys::valid_pass_name(new_name) && !FileSys::name_exist(new_name)) {
        std::string old_name = this->username;
        all_users[new_name] = all_users[old_name];
        all_users.erase(old_name);
        this->username = new_name;
    } else {
        std::cerr << "Invalid username change request..." << std::endl;
    }
} //careful that no clashes in username occur here either. Remove old from all_users map !! NEeds saving of old username, so it can be removed
void User::clear_dues() {
    charges=0;
}
void User::star(std::string sho, int stars) {
    if(!ContentManager::content_exist(sho)){
        std::cerr << "No content with this name to rate..." << std::endl;
        return;
    }
    all_shows[sho]->users++;
    all_shows[sho]->tot_rating+=stars;
} //rate movie out of 5 stars
