#include <iostream>
#include <vector>
#include <memory>
#include <limits>
#include "content.h"
#include "user.h"
#include "admin.h"
#include "persistence.h"
#include "init_content.h"

using namespace std;

vector<User> users;
vector<shared_ptr<Content>> content_library;
Admin admin;

void userMenu(User& user);
void adminMenu();

User* findUser(const string& username) {
    for (auto& u : users) {
        if (u.getUsername() == username)
            return &u;
    }
    return nullptr;
}

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void showContentByCategory(const string& type) {
    cout << "Available " << type << "s:\n";
    for (const auto& c : content_library) {
        if (c->getType() == type) {
            c->display();
            cout << "------------------\n";
        }
    }
}

void searchContent() {
    cout << "Search by:\n1. Title\n2. Genre\nChoice: ";
    int choice;
    cin >> choice;
    clearInput();
    string query;
    if (choice == 1) {
        cout << "Enter title: ";
        getline(cin, query);
        for (const auto& c : content_library)
            if (c->getTitle().find(query) != string::npos)
                c->display();
    } else {
        cout << "Enter genre: ";
        getline(cin, query);
        for (const auto& c : content_library)
            if (c->getGenre().find(query) != string::npos)
                c->display();
    }
}

void userMenu(User& user) {
    while (true) {
        cout << "\nUser Menu:\n";
        cout << "1. Browse Movies\n2. Browse TV Shows\n3. Search Content\n";
        cout << "4. Rent Content\n5. Return Content\n6. Purchase Content\n";
        cout << "7. View Rented Items\n8. View Purchased Items\n";
        cout << "9. View Charges\n10. Pay Charges\n0. Logout\nChoice: ";

        int ch;
        cin >> ch;
        clearInput();

        if (ch == 0) break;

        string title, rent_date = "2025-05-13", due_date = "2025-05-20";
        switch (ch) {
            case 1: showContentByCategory("Movie"); break;
            case 2: showContentByCategory("TVShow"); break;
            case 3: searchContent(); break;
            case 4:
                cout << "Enter title to rent: ";
                getline(cin, title);
                for (auto& c : content_library)
                    if (c->getTitle() == title && !c->isRented()) {
                        user.rentContent(c, rent_date, due_date);
                        user.addCharge((c->getType() == "Movie") ?
                            dynamic_cast<Movie*>(c.get())->getRentCost() :
                            dynamic_cast<TVShow*>(c.get())->getRentCostPerSeason());
                        break;
                    }
                break;
            case 5:
                cout << "Enter title to return: ";
                getline(cin, title);
                user.returnContent(title);
                break;
            case 6:
                cout << "Enter title to purchase: ";
                getline(cin, title);
                for (auto& c : content_library)
                    if (c->getTitle() == title) {
                        user.purchaseContent(c);
                        user.addCharge((c->getType() == "Movie") ?
                            dynamic_cast<Movie*>(c.get())->getPurchaseCost() :
                            dynamic_cast<TVShow*>(c.get())->getPurchaseCostPerSeason());
                        break;
                    }
                break;
            case 7: user.viewRentedItems(); break;
            case 8: user.viewPurchasedItems(); break;
            case 9: cout << "Total charges due: ₹" << user.getChargesDue() << endl; break;
            case 10: user.payCharges(); break;
            default: cout << "Invalid option.\n";
        }
    }
}

void adminMenu() {
    while (true) {
        cout << "\nAdmin Menu:\n";
        cout << "1. Add Movie\n2. Add TV Show\n3. Remove Content\n";
        cout << "4. Check User Charges\n0. Logout\nChoice: ";

        int ch;
        cin >> ch;
        clearInput();

        if (ch == 0) break;

        string title, uname;
        switch (ch) {
            case 1: admin.addMovie(content_library); break;
            case 2: admin.addTVShow(content_library); break;
            case 3:
                cout << "Enter title to remove: ";
                getline(cin, title);
                admin.removeContent(content_library, title);
                break;
            case 4:
                cout << "Enter username to check charges: ";
                getline(cin, uname);
                admin.checkUserCharges(users, uname);
                break;
            default: cout << "Invalid option.\n";
        }
    }
}

int main() {
    users = Persistence::loadUsers();
    content_library = Persistence::loadContent();
    if (content_library.empty()) {
        (content_library);
    }

    while (true) {
        cout << "\nWelcome to Netflix!\n";
        cout << "1. Sign Up\n2. Login\n3. Admin Login\n0. Exit\nChoice: ";
        int ch;
        cin >> ch;
        clearInput();

        if (ch == 0) break;

        string uname, pwd;
        switch (ch) {
            case 1:
                cout << "Choose username: ";
                getline(cin, uname);
                if (findUser(uname)) {
                    cout << "Username already exists!\n";
                    break;
                }
                cout << "Choose password: ";
                getline(cin, pwd);
                users.emplace_back(uname, pwd);
                cout << "User registered successfully!\n";
                break;

            case 2:
                cout << "Username: ";
                getline(cin, uname);
                cout << "Password: ";
                getline(cin, pwd);
                if (User* u = findUser(uname)) {
                    if (u->checkPassword(pwd)) {
                        cout << "Login successful!\n";
                        userMenu(*u);
                    } else cout << "Wrong password.\n";
                } else cout << "User not found.\n";
                break;

            case 3:
                cout << "Admin Username: ";
                getline(cin, uname);
                cout << "Admin Password: ";
                getline(cin, pwd);
                if (admin.login(uname, pwd)) {
                    cout << "Admin login successful!\n";
                    adminMenu();
                } else cout << "Invalid admin credentials.\n";
                break;

            default:
                cout << "Invalid option.\n";
        }

        Persistence::saveUsers(users);
        Persistence::saveContent(content_library);
    }
    return 0;
}
