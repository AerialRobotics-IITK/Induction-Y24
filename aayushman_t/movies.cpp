#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Movies {
public:
    string title;
    string genre;
    float rating;
    float duration;
    
    float rentCost;
    float purchaseCost;
    bool isrented;
    bool ispurchased;

    Movies(string t, string g, float r, float d,  float rent, float buy)
     {
        title =t;
        genre =g;
        rating =r;
        duration =d ;
        rentCost =rent;
        purchaseCost =buy;
        isrented =false;
        ispurchased =false;
     }

    void display(){
       
        cout<<title<<"|"<<genre<<"|"<<rating<<"|"<<duration<<"|"<<rentCost<<"|"<<purchaseCost<<"|"<<(isrented?"Rented":ispurchased?"Purchased":"Available")<<endl;
    }
};
class MoviesManager {
    private:
        vector<Movies> Moviess;
        const string movieFile = "data/movies.txt";
        void loadFromFile() {
            Moviess.clear();
            ifstream in(movieFile);
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
                float duration = stof(tokens[3]);
                float rent = stof(tokens[4]);
                float buy = stof(tokens[5]);
                bool isRented = stoi(tokens[6]);
                bool isPurchased = stoi(tokens[7]);
                Movies m(title, genre, rating, duration, rent , buy );
                m.isrented = isRented;
                m.ispurchased = isPurchased;
                Moviess.push_back(m);
            }
            in.close();
        }
    
        void saveToFile() {
            ofstream out(movieFile);
            for (const auto& m : Moviess) {
                out << m.title << "|" << m.genre << "|" << m.rating << "|"
                    << m.duration << "|" << m.rentCost << "|"
                    << m.purchaseCost << "|" << m.isrented << "|"<< m.ispurchased<< "\n";
            }
            out.close();
        }
    public:
        MoviesManager() {
              loadFromFile();
        }
    
        void browse() {
            cout << "\nAvailable Movies:\n";
            for (auto& show : Moviess) {
                show.display();
            }
        }
    
        void rentmovie(string title) {
            for (auto& show : Moviess) {
                if (show.title == title && !show.isrented && !show.ispurchased) {
                    show.isrented = true;
                    saveToFile();
                    cout << title << " has been rented!"<<endl;
                    return;
                }
            }
            cout << "Movie not found or already rented/purchased.\n";
        }
    
        void purchasemovie(string title) {
            for (auto& show : Moviess) {
                if (show.title == title && !show.ispurchased) {
                    show.ispurchased = true;
                    saveToFile();
                    cout << title << " has been purchased successfully!\n";
                    return;
                }
            }
            cout << "Movie not found or already purchased.\n";
        }
        void addMovie(string title, string genre, float rating, float duration ,float rentCost, float purchaseCost) {
             
            for (const auto& movie : Moviess) {
                if (movie.title == title) {
                    cout << "Error: Movie '" << title << "' already exists.\n";
                    return;
                }
            }
            Moviess.push_back(Movies(title,genre,rating,duration,rentCost,purchaseCost));
            saveToFile();
            cout << "Movie '" << title << "' added successfully!\n";
        }
        
        void removeMovie(string title) {
            for (auto i = Moviess.begin(); i != Moviess.end(); ++i) {
                if (i->title == title) {
                    Moviess.erase(i);
                    cout << "Movie '" << title << "' removed successfully!\n";
                    return;
                }
            }
            cout << "Movie not found.\n";
        }
        void searchMovie(const string& query) {
            bool found = false;
            for (auto& movie : Moviess) {
                if (movie.title.find(query) != string::npos || movie.genre.find(query) != string::npos) {
                    movie.display();
                    found = true;
                }
            }
            if (!found) {
                cout << "No movie found matching: " << query << endl;
            }
        }
        void returnMovie(const string& title, const string& username) {
            string rentalFile = "data/rented_" + username + ".txt";
           
            bool found = false;
            for (auto& movie : Moviess) {
                if (movie.title == title && movie.isrented) {
                    movie.isrented = false;
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
     vector<Movies>& getMovies()  {
        return Moviess;
    }
};
