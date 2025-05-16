#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include "User.h"
#include "Admin.h"
#include "Movie.h"
#include "TVShow.h"

using namespace std;

vector<User> users;
vector<Movie> movies;
vector<TVShow> tvshows;
Admin admin("admin", "admin123"); // Default admin

void clearInput() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

User* userLogin(string uname, string pwd) {
    for (auto& u : users) {
        if (u.getUsername() == uname && u.checkPassword(pwd)) {
            return &u;
        }
    }
    return nullptr;
}

void signup() {
    string uname, pwd;
    cout << "Choose username: ";
    cin >> uname;
    for (auto& u : users) {
        if (u.getUsername() == uname) {
            cout << "Username already exists.\n";
            return;
        }
    }
    cout << "Choose password: ";
    cin >> pwd;
    users.emplace_back(uname, pwd);
    cout << "User created successfully!\n";
}

void browseContent() {
    cout << "\n--- Movies ---\n";
    for (auto& m : movies) m.display();

    cout << "\n--- TV Shows ---\n";
    for (auto& s : tvshows) s.display();
}

void userDashboard(User* u) {
    int choice;
    do {
        cout << "\nUser Menu for " << u->getUsername() << "\n";
        cout << "1. Browse Content\n2. Rent Movie\n3. Rent TV Show\n4. Purchase Movie\n5. Purchase TV Show\n6. View Rentals\n7. View Purchases\n8. Return Item\n9. Check Dues\n0. Logout\nChoice: ";
        cin >> choice;

        string title;
        switch (choice) {
            case 1:
                browseContent();
                break;
            case 2:
                cout << "Enter movie title to rent: ";
                clearInput(); getline(cin, title);
                for (auto& m : movies) {
                    if (m.getTitle() == title) {
                        u->rentItem(title, m.getRentCost());
                        m.setRented(true);
                        break;
                    }
                }
                break;
            case 3:
                cout << "Enter TV show title to rent: ";
                clearInput(); getline(cin, title);
                for (auto& s : tvshows) {
                    if (s.getTitle() == title) {
                        u->rentItem(title, s.getRentPerSeason());
                        s.setRented(true);
                        break;
                    }
                }
                break;
            case 4:
                cout << "Enter movie title to purchase: ";
                clearInput(); getline(cin, title);
                for (auto& m : movies) {
                    if (m.getTitle() == title) {
                        u->purchaseItem(title, m.getPurchaseCost());
                        m.setPurchased(true);
                        break;
                    }
                }
                break;
            case 5:
                cout << "Enter TV show title to purchase: ";
                clearInput(); getline(cin, title);
                for (auto& s : tvshows) {
                    if (s.getTitle() == title) {
                        u->purchaseItem(title, s.getPurchasePerSeason());
                        s.setPurchased(true);
                        break;
                    }
                }
                break;
            case 6:
                u->showRentedItems(); break;
            case 7:
                u->showPurchasedItems(); break;
            case 8:
                cout << "Enter title to return: ";
                clearInput(); getline(cin, title);
                u->returnItem(title);
                break;
            case 9:
                cout << "Total due: ₹" << u->getChargesDue() << endl;
                break;
            case 0:
                cout << "Logging out...\n"; break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 0);
}

void adminDashboard() {
    int choice;
    do {
        cout << "\nAdmin Menu\n1. Add Movie\n2. Add TV Show\n3. Remove Movie\n4. Remove TV Show\n5. Check User Dues\n0. Logout\nChoice: ";
        cin >> choice;

        string title, genre;
        float rating;
        switch (choice) {
            case 1: {
                int dur; float rent, buy;
                cout << "Title: "; clearInput(); getline(cin, title);
                cout << "Genre: "; getline(cin, genre);
                cout << "Rating: "; cin >> rating;
                cout << "Duration (min): "; cin >> dur;
                cout << "Rent ₹: "; cin >> rent;
                cout << "Purchase ₹: "; cin >> buy;
                Movie m(title, genre, rating, dur, rent, buy);
                admin.addMovie(movies, m);
                break;
            }
            case 2: {
                int seasons, eps; float rent, buy;
                cout << "Title: "; clearInput(); getline(cin, title);
                cout << "Genre: "; getline(cin, genre);
                cout << "Rating: "; cin >> rating;
                cout << "Seasons: "; cin >> seasons;
                cout << "Episodes/season: "; cin >> eps;
                cout << "Rent/Season ₹: "; cin >> rent;
                cout << "Buy/Season ₹: "; cin >> buy;
                TVShow s(title, genre, rating, seasons, eps, rent, buy);
                admin.addTVShow(tvshows, s);
                break;
            }
            case 3:
                cout << "Enter movie title to remove: ";
                clearInput(); getline(cin, title);
                admin.removeMovie(movies, title);
                break;
            case 4:
                cout << "Enter TV show title to remove: ";
                clearInput(); getline(cin, title);
                admin.removeTVShow(tvshows, title);
                break;
            case 5: {
                cout << "Enter username to check dues: ";
                clearInput(); getline(cin, title);
                for (auto& u : users) {
                    if (u.getUsername() == title) {
                        admin.checkUserDues(u);
                        break;
                    }
                }
                break;
            }
            case 0:
                cout << "Admin logout...\n"; break;
            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 0);
}

void preloadContent() {
    movies.push_back(Movie("Inception", "Sci-Fi", 8.8, 148, 50, 300));
    movies.push_back(Movie("Interstellar", "Sci-Fi", 8.6, 169, 55, 320));
    movies.push_back(Movie("The Dark Knight", "Action", 9.0, 152, 40, 280));
    movies.push_back(Movie("Fight Club", "Drama", 8.8, 139, 45, 250));
    movies.push_back(Movie("The Matrix", "Action", 8.7, 136, 50, 270));
    movies.push_back(Movie("Parasite", "Thriller", 8.6, 132, 35, 230));
    movies.push_back(Movie("Avengers: Endgame", "Superhero", 8.4, 181, 60, 350));
    movies.push_back(Movie("The Godfather", "Crime", 9.2, 175, 45, 300));
    movies.push_back(Movie("Joker", "Crime", 8.4, 122, 40, 260));
    movies.push_back(Movie("Shawshank Redemption", "Drama", 9.3, 142, 40, 280));

    tvshows.push_back(TVShow("Breaking Bad", "Crime", 9.5, 5, 13, 100, 500));
    tvshows.push_back(TVShow("Stranger Things", "Sci-Fi", 8.7, 4, 10, 80, 400));
    tvshows.push_back(TVShow("Money Heist", "Thriller", 8.3, 5, 8, 90, 420));
    tvshows.push_back(TVShow("Game of Thrones", "Fantasy", 9.2, 8, 10, 110, 550));
    tvshows.push_back(TVShow("Friends", "Comedy", 8.9, 10, 24, 60, 300));
    tvshows.push_back(TVShow("The Office", "Comedy", 8.9, 9, 22, 50, 250));
    tvshows.push_back(TVShow("The Witcher", "Fantasy", 8.2, 3, 8, 75, 370));
    tvshows.push_back(TVShow("Peaky Blinders", "Crime", 8.8, 6, 6, 85, 400));
    tvshows.push_back(TVShow("Lucifer", "Fantasy", 8.1, 6, 10, 70, 360));
    tvshows.push_back(TVShow("Wednesday", "Horror", 8.2, 1, 8, 65, 300));
}


int main() {
    preloadContent();
    int choice;
    do {
        cout << "\n--- Netflix CLI ---\n1. User Login\n2. Sign Up\n3. Admin Login\n0. Exit\nChoice: ";
        cin >> choice;

        string uname, pwd;
        switch (choice) {
            case 1:
                cout << "Username: "; cin >> uname;
                cout << "Password: "; cin >> pwd;
                if (User* u = userLogin(uname, pwd)) {
                    userDashboard(u);
                } else {
                    cout << "Invalid credentials!\n";
                }
                break;
            case 2:
                signup(); break;
            case 3:
                cout << "Admin Username: "; cin >> uname;
                cout << "Admin Password: "; cin >> pwd;
                if (admin.login(uname, pwd)) {
                    adminDashboard();
                } else {
                    cout << "Wrong admin credentials.\n";
                }
                break;
            case 0:
                cout << "Bye!\n"; break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
