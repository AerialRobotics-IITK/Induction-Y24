#include "user.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

User::User(const string& uname, const string& pwd)
    : username(uname), password(pwd), charges_due(0.0) {}

string User::getUsername() const {
    return username;
}

bool User::checkPassword(const string& pwd) const {
    return pwd == password;
}

void User::rentContent(shared_ptr<Content> content, const string& rent_date, const string& return_due_date) {
    content->markRented();
    rented_items.push_back({content, rent_date, return_due_date});
    cout << "Rented \"" << content->getTitle() << "\" until " << return_due_date << "\n";
}

bool User::returnContent(const string& title) {
    for (auto it = rented_items.begin(); it != rented_items.end(); ++it) {
        if (it->content->getTitle() == title) {
            it->content->markReturned();
            rented_items.erase(it);
            cout << "Returned \"" << title << "\" successfully.\n";
            return true;
        }
    }
    cout << "No rented item found with title: " << title << "\n";
    return false;
}

void User::purchaseContent(shared_ptr<Content> content) {
    content->markPurchased();
    purchased_items.push_back(content);
    cout << "Purchased \"" << content->getTitle() << "\" successfully.\n";
}

void User::viewRentedItems() const {
    if (rented_items.empty()) {
        cout << "No items currently rented.\n";
        return;
    }
    cout << "Rented Items:\n";
    for (const auto& item : rented_items) {
        cout << "- " << item.content->getTitle()
                  << " | Rented On: " << item.rent_date
                  << " | Return By: " << item.return_due_date << "\n";
    }
}

void User::viewPurchasedItems() const {
    if (purchased_items.empty()) {
        cout << "No items purchased.\n";
        return;
    }
    cout << "Purchased Items:\n";
    for (const auto& item : purchased_items) {
        cout << "- " << item->getTitle() << "\n";
    }
}

double User::getChargesDue() const {
    return charges_due;
}

void User::addCharge(double amount) {
    charges_due += amount;
}

void User::payCharges() {
    cout << "Paid ₹" << charges_due << " successfully.\n";
    charges_due = 0.0;
}

string User::serialize() const {
    ostringstream oss;
    oss << username << "|" << password << "|" << charges_due;
    return oss.str();
}

User User::deserialize(const string& line) {
    istringstream iss(line);
    string uname, pwd;
    double charges;
    getline(iss, uname, '|');
    getline(iss, pwd, '|');
    iss >> charges;

    User user(uname, pwd);
    user.addCharge(charges);
    return user;
}
