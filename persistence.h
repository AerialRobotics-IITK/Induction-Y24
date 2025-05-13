#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <vector>
#include <string>
#include <memory>
#include "user.h"
#include "content.h"

using namespace std;

class Persistence {
public:
    static void saveUsers(const vector<User>& users, const string& filename = "users.txt");
    static vector<User> loadUsers(const string& filename = "users.txt");

    static void saveContent(const vector<shared_ptr<Content>>& content, const string& filename = "content.txt");
    static vector<shared_ptr<Content>> loadContent(const string& filename = "content.txt");
};

#endif // PERSISTENCE_H
