/*#include <iostream>//public : accessible everywhere
#include <queue>//private : accessible only inside the class 
#include <vector>//protected : accessible inside class and to its derived classes 
#include <tuple>//constructor is automatically called everytime a new object is created 
#include <climits>
using namespace std;

class Student {
public:
    Student() {
        cout<<"constructor called";
    }
    int rollNo;
    string name;
    void changeName(string newName) {
        name = newName;
    }
};
int main() {
    Student s1;//constructor called
    s1.name = "riyansh";
    string name2 = "vidhyan";
    s1.changeName(name2);
    cout<<s1.name;
    cout<<"hello";
    return 0;
}*/
// movies, tv shows, browse, rent and return, store a memory of what has been done, CLI, login/sign up, uniqueness of
//usernames, browse content by category or genre, */
#include <iostream>
#include <vector>
#include <map>
#include <ctime>
using namespace std;
//Base Content Class
class Content {
public :
    string title;
    string genre;
    float rating;
    bool is_rented = false;
    bool is_purchased = false;
    Content(string t, string g, float r) { //constuctor
        title = t;
        genre = g;
        rating = r;
    }
    virtual void showInfo() = 0;
    virtual float getRentCost() = 0;
    virtual float getPurchaseCost() = 0;
};
//Movie Class
class Movie : public Content {
public :
    int duration;
    float rentCost;
    float purchaseCost;
    Movie(string t, string g, float r, int d, float rC, float pC)
        : Content(t, g, r) {//constructor1
        duration = d;
        rentCost = rC;
        purchaseCost = pC;
    }
    void showInfo() {
        cout<<"Movie Name : "<<title<<"\n";
        cout<<"Genre : "<<genre<<"\n";
        cout<<"Rating : "<<rating<<"\n";
        cout<<"Duration : "<<duration <<"mins"<<"\n";
    }
    float getRentCost() {
        return rentCost;
    }
    float getPurchaseCost() {
        return purchaseCost;
    }
};
// class TVShow 
class TVShow : public Content {
public :
    int seasons;
    int epPerSeason;
    float perSeasonRentC;
    float perSeasonPurchaseC;
    TVShow(string t, string g, float r, int s, int ep, float perSeasonRC, float perSeasonPC) 
        : Content(t, g, r) {//constructor
        seasons = s;
        epPerSeason = ep;
        perSeasonRentC = perSeasonRC;
        perSeasonPurchaseC = perSeasonPC;
    }
    void showInfo() {
        cout<<"TV Show Name : "<<title<<"\n";
        cout<<"Genre : "<<genre<<"\n";
        cout<<"Rating : "<<rating<<"\n";
        cout<<"Seasons : "<<seasons<<" x "<<epPerSeason << "eps\n";
    }
    float getRentCost() {
        return perSeasonRentC*seasons;
    }
    float getPurchaseCost() {
        return perSeasonPurchaseC*seasons;
    }
};
class User {
public :
    string userName;
    map<string, time_t> rented;
    vector<string> purchased;
    float charges = 0.0;
    User(string name) {
        userName = name;
    }
    void rentContent(Content* content) {
        if(!content->is_rented) {
            content->is_rented = true;
            rented[content->title] = time(0);
            charges = charges+content->getRentCost();
            cout<<"Rented successfully!\n";
        }else {
            cout<<"Already rented.\n";
        }
    }
    void purchaseContent(Content* content) {
        if(!content->is_purchased) {
            content->is_purchased = true;
            purchased.push_back(content->title);
            charges = charges+content->getPurchaseCost();
            cout<<"Purchased successfully!\n";
        }else {
            cout<<"Already purchased.\n";
        }
    }
    void returnContent(Content* content) {
        if(content->is_rented) {
            content->is_rented = false;
            rented.erase(content->title);
            cout<<"Returned successfully!\n";
        }else {
            cout<<"Not rented.\n";
        }
    }
    void viewCurrStatus() {
        cout<<"Username : "<< userName<<"\n";
        cout<<"Rented : \n";
        for(auto& r : rented) {
            cout<<r.first<<" "<<"Rented on : "<<ctime(&r.second);
        }
        cout<<"Purchased : \n";
        for(string m : purchased) {
            cout<<m<<"\n";
        }
        cout<<"Total charges due : "<<charges<<"\n";
    }
};
class Admin {
public :
    string adminName;
    Admin(string adName) {
        adminName = adName;
    }
    void addNewContent(vector<Content*>& newAddition, Content* content) {
        newAddition.push_back(content);
        cout<<"New Content added!\n";
    }
    void deleteContent(vector<Content*>& newAddition, string t) {
        for(auto i = newAddition.begin(); i!=newAddition.end(); i++) {
            if((*i)->title == t) {
                delete *i;
                newAddition.erase(i);
                cout<<"Content removed!\n";
                return;
            }
        }
        cout<<"Content not found!\n";
    }
    void checkCharges(User& user) {
        cout<<user.userName<<"\n";
        cout<<"Charges : "<<user.charges<<"\n";
    }
};
void showAllContent(vector<Content*> &List) {
    cout<<"All available content\n";
    cout<<"Pre-added content : \n";
    cout<<"1. Marvel : Avengers\n";
    cout<<"Sci-fi\n";
    cout<<"8.9\n";
    cout<<"Not rented\n";
    cout<<"Not purchased\n";
    cout<<"2. The Conjuring\n";
    cout<<"Horror\n";
    cout<<"9.2\n";
    cout<<"Not rented\n";
    cout<<"Not purchased\n";

    for(Content* c : List) {
        c->showInfo();
    }
} 
int main() {
    vector<Content*> allAdditions;
    map<string, User*> users;
    string str = "netflixAdmin";
    Admin admin(str);
    while(1) {
        cout<<"Press digit to perform the corresponding operation.\n";

        cout<<"1. User Login\n";
        cout<<"2. User Signup\n";
        cout<<"3. Admin Login\n";
        cout<<"4. Exit\n";
        int choice;
        cin>>choice;
        if(choice == 4) {
            break;
        }
        if(choice == 1 || choice == 2) {
            string uName;
            cout<<"Enter Username : ";
            cin>>uName;
            if(choice == 2) {
                if(users.find(uName)!=users.end()) {
                    cout<<"Username taken.\n";
                    continue;
                }else {
                    users[uName] = new User(uName);
                    cout<<"User created!\n";
                }
            }
            if(!users.count(uName)) {
                cout<<"No such user.\n";
                continue;
            }
            User* current = users[uName];
            while(1) {
                cout<<"User Menu : \n";
                cout<<"Press digit key to perform corresponding operation.\n";
                cout<<"1. Browse\n2. Rent\n3. Return\n4. Purchase\n5. View Status\n";
                cout<<"6.Logout\n";
                int uChoice;
                cin>>uChoice;
                if(uChoice == 6) {
                    break;
                }
                if(uChoice == 1) {
                    showAllContent(allAdditions);
                }else if(uChoice == 2 || uChoice == 3 || uChoice == 4) {
                    string title;
                    cout<<"Enter title : \n";
                    cin.ignore();
                    getline(cin, title);
                    bool found = false;
                    for(Content* c : allAdditions) {
                        if(c->title == title) {
                            if(uChoice == 2) {
                                current->rentContent(c);
                            }else if(uChoice == 3) {
                                current->returnContent(c);
                            }else if(uChoice == 4) {
                                current->purchaseContent(c);
                            }
                            found = true;
                                break;
                        }
                    }
                    if(!found) {
                        cout<<"Content not found\n";
                    }
                }else if(uChoice == 6) {
                    current->viewCurrStatus();
                }

            }
        }else if(choice == 3) {
            string passWord;
            cout<<"Enter admin password : \n";
            cin>>passWord;
            if(passWord!="defaultPass123") {
                cout<<"Incorrect Password\n";//default password by system that admin must enter
                continue;
            }
            while(1) {
                cout<<"Admin Menu : \n";
                cout<<"Press digit key to perform corresponding operation\n";
                cout<<"1. Add content\n2. Remove Content\n3. Check User charges\n4. Logout\n";
                int aChoice;
                cin>>aChoice;
                if(aChoice == 4) {
                    break;
                }
                if(aChoice == 1) {
                    cout<<"1. Movie\n"<<"2. TV Show";
                    int k;
                    cin>>k;
                    string title, genre;
                    float rating;
                    cin.ignore();
                    cout<<"Title : ";
                    getline(cin, title);
                    cout<<"Genre : ";
                    getline(cin, genre);
                    cout<<"Rating : ";
                    cin>>rating;
                    if(k == 1) {
                        int dur; float r,p;
                        cout<<"Duration : "; cin>>dur;
                        cout<<"Rent Cost : "; cin>>r;
                        cout<<"Purchase Cost : "; cin>>p;
                        admin.addNewContent(allAdditions, new Movie(title, genre, rating, dur, r, p));
                    }else {
                        int seasons, eps; float r, p;
                        cout<<"Seasons : "; cin>> seasons;
                        cout<<"Episodes/Season : "; cin>> eps;
                        cout<<"Rent/Season : "; cin>> r;
                        cout<<"Purchase/Season : "; cin>>p;
                        admin.addNewContent(allAdditions, new TVShow(title, genre, rating, seasons, eps, r, p));
            
                    }
                }else if(aChoice == 2) {
                    string title;
                    cout<<"Enter title to remove : "; 
                    cin.ignore();
                    getline(cin, title);
                    admin.deleteContent(allAdditions, title);
                }else if(aChoice == 3) {
                    string uname;
                    cout<<"Enter Username : ";
                    cin>>uname;
                    if(users.count(uname)) {
                        admin.checkCharges(*users[uname]);
                    }else {
                        cout<<"User Not found.\n";
                    }
                }
            }
        }
    }
    return 0;

}
