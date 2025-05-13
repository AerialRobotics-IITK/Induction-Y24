#ifndef USER_H
#define USER_H

#include "content.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class User {
private:
    string username;
    vector<string> rented_titles;
    vector<string> purchased_titles;
    float charges_due;

public:
    // Constructor
    User(const string& uname) : username(uname), charges_due(0.0f) {}

    // Getters
    string getUsername() const { return username; }
    float getChargesDue() const { return charges_due; }

    // Rent content
    void rent(Content* item) {
        if (item->getIsRented()) {
            cout << "This item is already rented.\n";
            return;
        }
        item->setRented(true);
        rented_titles.push_back(item->getTitle());
        charges_due += item->getRentCost();
        cout << "Rented successfully. $" << item->getRentCost() << " added to charges.\n";
    }

    // Purchase content
    void purchase(Content* item) {
        if (item->getIsPurchased()) {
            cout << "This item is already purchased.\n";
            return;
        }
        item->setPurchased(true);
        purchased_titles.push_back(item->getTitle());
        charges_due += item->getPurchaseCost();
        cout << "Purchased successfully. $" << item->getPurchaseCost() << " added to charges.\n";
    }

    // Return rented content
    void returnItem(Content* item) {
        if (!item->getIsRented()) {
            cout << "This item was not rented.\n";
            return;
        }
        item->setRented(false);
        auto it = find(rented_titles.begin(), rented_titles.end(), item->getTitle());
        if (it != rented_titles.end()) {
            rented_titles.erase(it);
        }
        cout << "Returned successfully.\n";
    }

    // View currently rented titles
    void viewRented() const {
        cout << "Rented Items:\n";
        if (rented_titles.empty()) {
            cout << "None\n";
        } else {
            for (const auto& title : rented_titles)
                cout << "- " << title << endl;
        }
    }

    // View purchased titles
    void viewPurchased() const {
        cout << "Purchased Items:\n";
        if (purchased_titles.empty()) {
            cout << "None\n";
        } else {
            for (const auto& title : purchased_titles)
                cout << "- " << title << endl;
        }
    }

    // View due charges
    void viewCharges() const {
        cout << "Total Charges Due: $" << charges_due << endl;
    }

    // Convert to string for file storage
    string serialize() const {
        stringstream ss;
        ss << username << "|" << charges_due << "|";

        for (const auto& r : rented_titles)
            ss << r << ",";
        ss << "|";

        for (const auto& p : purchased_titles)
            ss << p << ",";
        return ss.str();
    }

    // Restore from file
    static User* deserialize(const string& line) {
        stringstream ss(line);
        string uname, charge_str, rented_str, purchased_str;

        getline(ss, uname, '|');
        getline(ss, charge_str, '|');
        getline(ss, rented_str, '|');
        getline(ss, purchased_str, '|');

        User* u = new User(uname);
        u->charges_due = stof(charge_str);

        stringstream rented_stream(rented_str);
        string title;
        while (getline(rented_stream, title, ',')) {
            if (!title.empty()) u->rented_titles.push_back(title);
        }

        stringstream purchased_stream(purchased_str);
        while (getline(purchased_stream, title, ',')) {
            if (!title.empty()) u->purchased_titles.push_back(title);
        }

        return u;
    }
};

#endif
