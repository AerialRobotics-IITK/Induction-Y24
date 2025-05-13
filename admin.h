#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <vector>
#include <memory>
#include "content.h"
#include "user.h"

using namespace std;

class Admin {
private:
    string username;
    string password;

public:
    Admin(const string& uname = "admin", const string& pwd = "admin123");

    bool login(const string& uname, const string& pwd) const;

    void addMovie(vector<shared_ptr<Content>>& library);
    void addTVShow(vector<shared_ptr<Content>>& library);
    void removeContent(vector<shared_ptr<Content>>& library, const string& title);
    void checkUserCharges(const vector<User>& users, const string& username) const;
};

#endif // ADMIN_H
