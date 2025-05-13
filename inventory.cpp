#include <iostream>
using std::string;

class User{
private:
    string username;
    string password;
public:
    void setName(string name){
        username=name;
    }
    User(string name, string){
        username=name;

    }
};

class Movie{
    string title;
    bool isRented;

};

class System{

};

int main(){
    
    return 0;
}