#include <iostream>
#include <vector>
#include <string>

using namespace std;

class TVShow {
public:
    string title;
    string genre;
    float rating;
    int seasons;
    int episodesPerSeason;
    float rentCost;
    float purchaseCost;
    bool isrented;
    bool ispurchased;

    TVShow(string t, string g, float r, int s, int eps, float rent, float buy)
     {
        title =t;
        genre =g;
        rating =r;
        seasons =s;
        episodesPerSeason =eps;
        rentCost =rent;
        purchaseCost =buy;
        isrented =false;
        ispurchased = false;
     }

    void display(){
      
        cout<<title<<"|"<<genre<<"|"<<rating<<"|"<<seasons<<"|"<<episodesPerSeason<<"|"<<rentCost<<"|"<<purchaseCost<<"|"<<(isrented?"Rented":ispurchased?"Purchased":"Available")<<endl;
    }
};
class TVShowManager {
    private:
        vector<TVShow> tvshows;
        const string showFile = "data/Tvshows.txt";
        void loadFromFile() {
            tvshows.clear();
            ifstream in(showFile);
            string line;
            while (getline(in, line)) {
                size_t pos = 0;
                string token;
                vector<string> tokens;
                while ((pos = line.find('|')) != string::npos) {
                    token = line.substr(0, pos);
                    tokens.push_back(token);
                    line.erase(0, pos + 1);
                }
                tokens.push_back(line); 
                
                string title = tokens[0];
                string genre = tokens[1];
                float rating = stof(tokens[2]);
                float seasons = stof(tokens[3]);
                float ep_s = stof(tokens[4]);
                float rent = stof(tokens[5]);
                float buy = stof(tokens[6]);
                bool isRented = stoi(tokens[7]);
                bool isPurchased = stoi(tokens[8]);
                TVShow m(title, genre, rating, seasons,ep_s, rent , buy);
                m.isrented = isRented;
                m.ispurchased = isPurchased;
                tvshows.push_back(m);
            }
            in.close();
        }
    
        void saveToFile() {
            ofstream out(showFile);
            for (const auto& m : tvshows) {
                out << m.title << "|" << m.genre << "|" << m.rating << "|"
                    << m.seasons << "|" <<m.episodesPerSeason<<"|"<< m.rentCost << "|"
                    << m.purchaseCost << "|" << m.isrented << "|"<< m.ispurchased<< "\n";
            }
            out.close();
        }
    public:
        TVShowManager() {
         loadFromFile();
        }
    
        void browse() {
            cout << "\nAvailable TV Shows:\n";
            for (auto& show : tvshows) {
                show.display();
            }
        }
    
        void rentShow(string title) {
            for (auto& show : tvshows) {
                if (show.title == title && !show.isrented && !show.ispurchased) {
                    show.isrented = true;
                    saveToFile();
                    cout << title << " has been rented!"<<endl;
                    return;
                }
            }
            cout << "TV Show not found or already rented/purchased.\n";
        }
    
        void purchaseShow(string title) {
            for (auto& show : tvshows) {
                if (show.title == title && !show.ispurchased) {
                    show.ispurchased = true;
                    saveToFile();

                    cout << title << " has been purchased successfully!\n";
                    return;
                }
            }
            cout << "TV Show not found or already purchased.\n";
        }
        void addshow(string title, string genre, float rating,float season, float ep_s, float rentCost, float purchaseCost) {
            for (const auto& show : tvshows) {
                if (show.title == title) {
                    cout << "Error: Movie '" << title << "' already exists.\n";
                    return;
                }
            }
            tvshows.push_back(TVShow(title, genre, rating, season, ep_s, rentCost, purchaseCost));
            cout << "Show '" << title << "' added successfully!\n";
        }
        
        void removeShow(string title) {
            for (auto i = tvshows.begin(); i != tvshows.end(); ++i) {
                if (i->title == title) {
                    tvshows.erase(i);
                    cout << "Show '" << title << "' removed successfully!\n";
                    return;
                }
            }
            cout << "Show not found.\n";
        }
        void searchShow(const string& query) {
            bool found = false;
            for ( auto& show : tvshows) {
                if (show.title.find(query) != string::npos || show.genre.find(query) != string::npos) {
                    show.display();
                    found = true;
                }
            }
            if (!found) {
                cout << "No TV show found matching: " << query << endl;
            }
        }
        void returnShow(const string& title, const string& username) {
            string rentalFile = "data/rented_" + username + ".txt";
           
            bool found = false;
            for (auto show : tvshows) {
                if (show.title == title && show.isrented) {
                    show.isrented = false;
                    saveToFile();
                    found = true;
                    cout << title << " has been returned successfully!\n";
                    break;
                }
            }
            if (!found) {
                cout << "Movie not found or not rented.\n";
                return;
            }
            vector<string> rentals;
            ifstream in(rentalFile);
            string line;
            while (getline(in, line)) {
                if (line != title) {
                    rentals.push_back(line);
                }
            }
            in.close();
            ofstream out(rentalFile);
          
            for (const auto& rental : rentals) {
                out << rental << "\n";
            }
            out.close();
        
            
    } 
    vector<TVShow>& getShows() {
        return tvshows;
    }
    };
    

