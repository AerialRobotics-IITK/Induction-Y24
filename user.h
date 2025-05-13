#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "content.h"

using namespace std;

struct RentalInfo {
    shared_ptr<Content> content;
    string rent_date;
    string return_due_date;
};

class User {
private:
    string username;
    string password;
    vector<RentalInfo> rented_items;
    vector<shared_ptr<Content>> purchased_items;
    double charges_due;

public:
    User(const string& uname, const string& pwd);

    string getUsername() const;
    bool checkPassword(const string& pwd) const;

    // Core functionalities
    void rentContent(shared_ptr<Content> content, const string& rent_date, const string& return_due_date);
    bool returnContent(const string& title);
    void purchaseContent(shared_ptr<Content> content);

    void viewRentedItems() const;
    void viewPurchasedItems() const;

    double getChargesDue() const;
    void addCharge(double amount);
    void payCharges();

    // Persistence support
    string serialize() const;
    static User deserialize(const string& line);
};

#endif // USER_H
