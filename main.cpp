#include <iostream>
#include <string>
#include <filesystem>
#include "Inventory.h"
#include "user.h"
#include "UserUtils.h"

using namespace std;
namespace fs = std::filesystem;

const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "admin123"; // For demo

void userMenu(User* user, Inventory& inventory) {
    int choice;
    while (true) {
        cout << "\nUSER MENU - " << user->getUsername() << "\n";
        cout << "1. Browse all content\n2. Search by title\n3. Rent\n4. Purchase\n5. Return\n6. View rented\n7. View purchased\n8. Charges due\n9. Logout\nChoice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            inventory.displayAll();
        } else if (choice == 2) {
            string title;
            cout << "Enter title: ";
            getline(cin, title);
            Content* c = inventory.searchByTitle(title);
            if (c) c->display();
            else cout << "Not found.\n";
        } else if (choice == 3) {
            string title;
            cout << "Enter title to rent: ";
            getline(cin, title);
            Content* c = inventory.searchByTitle(title);
            if (c) user->rent(c);
            else cout << "Not found.\n";
        } else if (choice == 4) {
            string title;
            cout << "Enter title to purchase: ";
            getline(cin, title);
            Content* c = inventory.searchByTitle(title);
            if (c) user->purchase(c);
            else cout << "Not found.\n";
        } else if (choice == 5) {
            string title;
            cout << "Enter title to return: ";
            getline(cin, title);
            Content* c = inventory.searchByTitle(title);
            if (c) user->returnItem(c);
            else cout << "Not found.\n";
        } else if (choice == 6) {
            user->viewRented();
        } else if (choice == 7) {
            user->viewPurchased();
        } else if (choice == 8) {
            user->viewCharges();
        } else if (choice == 9) {
            saveUser(user);
            cout << "Logged out.\n";
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }
}

void adminMenu(Inventory& inventory) {
    int choice;
    while (true) {
        cout << "\nADMIN MENU\n";
        cout << "1. Add Movie\n2. Add TV Show\n3. Remove Content\n4. View All Content\n5. Logout\nChoice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string title, genre;
            float rating, rent, purchase;
            int duration;
            cout << "Enter title, genre, rating, duration, rent cost, purchase cost:\n";
            getline(cin, title); getline(cin, genre);
            cin >> rating >> duration >> rent >> purchase; cin.ignore();
            inventory.addContent(new Movie(title, genre, rating, duration, rent, purchase));
            cout << "Movie added.\n";
        } else if (choice == 2) {
            string title, genre;
            float rating, rent, purchase;
            int seasons, eps;
            cout << "Enter title, genre, rating, seasons, eps/season, rent/season, purchase/season:\n";
            getline(cin, title); getline(cin, genre);
            cin >> rating >> seasons >> eps >> rent >> purchase; cin.ignore();
            inventory.addContent(new TVShow(title, genre, rating, seasons, eps, rent, purchase));
            cout << "TV Show added.\n";
        } else if (choice == 3) {
            string title;
            cout << "Enter title to remove: ";
            getline(cin, title);
            // Simplified: just mark as not available, or skip (you can implement actual removal later)
            cout << "Feature not implemented.\n";
        } else if (choice == 4) {
            inventory.displayAll();
        } else if (choice == 5) {
            cout << "Admin logged out.\n";
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }
}

int main() {
    fs::create_directory("users");

    Inventory inventory;
    inventory.loadFromFile("inventory.txt");

    while (true) {
        int option;
        cout << "\n--- NETFLIX CLI SYSTEM ---\n";
        cout << "1. User Sign Up\n2. User Login\n3. Admin Login\n4. Exit\nChoice: ";
        cin >> option;
        cin.ignore();

        if (option == 1) {
            string uname;
            cout << "Enter new username: ";
            getline(cin, uname);
            if (userExists(uname)) {
                cout << "Username already exists.\n";
            } else {
                User* u = new User(uname);
                saveUser(u);
                cout << "Sign-up successful. You can now log in.\n";
            }
        } else if (option == 2) {
            string uname;
            cout << "Enter username: ";
            getline(cin, uname);
            if (!userExists(uname)) {
                cout << "User not found.\n";
            } else {
                User* user = loadUser(uname);
                cout << "Welcome " << user->getUsername() << "!\n";
                userMenu(user, inventory);
            }
        } else if (option == 3) {
            string uname, pass;
            cout << "Enter admin username: ";
            getline(cin, uname);
            cout << "Enter admin password: ";
            getline(cin, pass);
            if (uname == ADMIN_USERNAME && pass == ADMIN_PASSWORD) {
                adminMenu(inventory);
            } else {
                cout << "Invalid admin credentials.\n";
            }
        } else if (option == 4) {
            inventory.saveToFile("inventory.txt");
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid input.\n";
        }
    }

    return 0;
}
