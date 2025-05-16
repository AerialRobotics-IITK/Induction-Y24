#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class User {
    string username;
    string password;
    vector<string> rented_items;
    vector<string> purchased_items;
    float charges_due;

public:
    User(string uname, string pwd) : username(uname), password(pwd), charges_due(0) {}

    string getUsername() const { return username; }
    bool checkPassword(string pwd) const { return pwd == password; }

    void rentItem(string title, float cost) {
        rented_items.push_back(title);
        charges_due += cost;
    }

    void purchaseItem(string title, float cost) {
        purchased_items.push_back(title);
        charges_due += cost;
    }

    void returnItem(string title) {
        for (auto it = rented_items.begin(); it != rented_items.end(); ++it) {
            if (*it == title) {
                rented_items.erase(it);
                cout << title << " returned successfully.\n";
                return;
            }
        }
        cout << title << " not found in your rented list.\n";
    }

    void showRentedItems() const {
        cout << "Rented Items:\n";
        for (const auto& item : rented_items) {
            cout << "- " << item << endl;
        }
    }

    void showPurchasedItems() const {
        cout << "Purchased Items:\n";
        for (const auto& item : purchased_items) {
            cout << "- " << item << endl;
        }
    }

    float getChargesDue() const { return charges_due; }
};

#endif
