#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <filesystem>
using namespace std;
namespace fs=std::filesystem;

class Content {
protected:
    string title;
    string genre;
    string rating;
    bool is_rented;
    bool is_purchased;

public:
    Content() : is_rented(false), is_purchased(false) {}
    Content(string t, string g, string r)
        : title(t), genre(g), rating(r), is_rented(false), is_purchased(false) {}
    virtual ~Content() {}
};

class Movie : public Content {
    int duration;          // in minutes
    double rent_cost;
    double purchase_cost;

public:
    Movie(string t, string g, string r, int d, double rc, double pc)
        : Content(t, g, r), duration(d), rent_cost(rc), purchase_cost(pc) {}

    void display() const override {
        cout << "Movie: " << title << "\nGenre: " << genre << "\nRating: " << rating<< "\nDuration: " << duration << " mins\nRent: ₹" << rent_cost<< "\nPurchase: ₹" << purchase_cost << endl;}
};

class TVShow : public Content {
    int seasons;
    int episodes_per_season;
    double rent_cost;
    double purchase_cost;

public:
    TVShow(string t, string g, string r, int s, int eps, double rc, double pc)
        : Content(t, g, r), seasons(s), episodes_per_season(eps), rent_cost(rc), purchase_cost(pc) {}

    void display() const override {
        cout << "TV Show: " << title << "\nGenre: " << genre << "\nRating: " << rating<< "\nSeasons: " << seasons << ", Episodes/Season: " << episodes_per_season << "\nRent (per season): ₹" << rent_cost << "\nPurchase (per season): ₹" << purchase_cost << endl;}
};

class ContentManager {
    vector<Content*> inventory;

public:
    ~ContentManager() {
        for (auto c : inventory) delete c;
    }

    void loadInventory() {
        ifstream fin("inventory.txt");
        string type, title, genre, rating;
        double rent, purchase;
        while (fin >> title >> genre >> type >> rating >> rent >> purchase) {
            if (type == "Movie") {
                inventory.push_back(new Movie(title, genre, rating, 120, rent, purchase)); // sample duration
            } else if (type == "TV") {
                inventory.push_back(new TVShow(title, genre, rating, 3, 10, rent, purchase)); // sample seasons/eps
            }
        }
        fin.close();
    }

    void listAll() {
        cout << "Available Content:\n";
        for (auto c : inventory) c->display();
    }

    void searchByGenre(const string& g) {
        for (auto c : inventory) {
            if (c->getGenre() == g) {
                c->display();
            }
        }
    }

    void rentContent(const string& title, const string& userFile) {
        for (auto c : inventory) {
            if (c->getTitle() == title) {
                ofstream fout(userFile, ios::app);
                fout << "RENTED: " << c->getTitle() << " Rent Cost: " << c->getRentCost() << "\n";
                fout.close();
                cout << "Rented successfully.\n";
                return;
            }
        }
        cout << "Content not found.\n";
    }

    void purchaseContent(const string& title, const string& userFile) {
        for (auto c : inventory) {
            if (c->getTitle() == title) {
                ofstream fout(userFile, ios::app);
                fout << "PURCHASED: " << c->getTitle() << " Cost: " << c->getPurchaseCost() << "\n";
                fout.close();
                cout << "Purchased successfully.\n";
                return;
            }
        }
        cout << "Content not found.\n";
    }
	Content* findByTitle(const string& t) {
        	for (auto c : inventory) {
     	       if (c->getTitle() == t) return c;
     	   }
     	   return nullptr;
    	}

};


class user {
protected: 
	string username;
	string password;
	ContentManager &manager;
public:
	User(const string &uname, const string &pwd, const ContentManager &m) : username(uname), password(pwd), ContentManager(m) {}
	string getusername() const {
	return username;}
	string getpassword() const {
	return password;}
	void rentContent() {
        string title;
        cout << "Enter title to rent: ";
        cin.ignore();
        getline(cin, title);

        ofstream fout(username + "_data.txt", ios::app);
        fout << "RENTED: " << title << " on " << time(0) << endl;
        cout << "Content rented successfully.\n";
    }

    void viewRented() {
        ifstream fin(username + "_data.txt");
        string line;
        cout << "--- Your Rented Content ---\n";
        while (getline(fin, line)) {
            if (line.find("RENTED") != string::npos)
                cout << line << endl;
        }
    }

    void viewCharges() {
    ifstream fin(username + "_data.txt");
    string line;
    double total = 0.0;

    while (getline(fin, line)) {
        size_t pos = line.find("Cost:");
        if (pos != string::npos) {
            string cost_str = line.substr(pos + 5); // Skip past "Cost:"
            try {
                total += stod(cost_str);
            } catch (...) {
                cerr << "Failed to parse cost in line: " << line << endl;
            }
        }
    }

    cout << "Total charges due: ₹" << total << endl;
}

    void browseContent() {
        ifstream fin("inventory.txt");
        if (!fin) {
            cout << "No content available.\n";
            return;
        }

        Content c;
        cout << "\n--- Available Content ---\n";
        while (fin >> c.title >> c.genre >> c.type >> c.rating >> c.rent_cost >> c.purchase_cost) {
            c.display();
        }
    }

    void usermenu() {
        int choice;
        do {
            cout << "\nUser Menu\n1. Browse Content\n2. Rent\n3. View Rented\n4. View Charges\n5. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1: browseContent(); break;
                case 2: rentContent(); break;
                case 3: viewRented(); break;
                case 4: viewCharges(); break;
                case 5: cout << "Logging out...\n"; break;
                default: cout << "Invalid option.\n";
            }
        } while (choice != 5);
    }
};

void menu();
bool uname_exist(string &username);
void signup();
void login();
void adminlogin(); 
void adminmenu();

int main(){
if (!fs::exists(data/users){
	fs::create(data/users);}
menu();
}

void menu(){
	int choice;
	do{
		cout<<"Netflix\n";
		cout<<"1. Login\n";
		cout<<"2. Signin\n";
		cout<<"3. Admin Login\n";
		cout<<"Enter your choice: ";
		cin>>choice;
		switch(choice){
			case 1:
				login();
				break;
			case 2:
				signup();
				break;
			case 3:
				adminlogin();
				break;
			default:
				cout<<"Invalid choice";

void signup(){
	string uname, pwd;
	cout<<"For signing up, enter a unique username :";
	cin>>uname;
	if (uname_exist(uname)){
		cout<<"Username exists, please enter another username";
		return;}
	
	cout<<"\nEnter password :";
	cin>>pwd;

	ofstream outfile("users.txt", std::ios::app);
	outfile<<uname<<" "pwd<<sdt::endl;
	string filename = uname+"_data.txt";
	ofstream userFile(filename);
	userFile << "User: "<<uname<<endl;
	userFile.close(); 
	cout<<"Registration complete."; 
	menu();}

void login(){
	string uname,pwd;
	cout<<"Enter your username :";
	cin>>uname;
	cout<<"Enter your password :";
	cin>>pwd;
	ifstream fin("users.txt");
	string u,p;
	while(fin>>u>>p)
		if(u==uname && p= pwd) {
			cout<<"Login successful.\n";
			User user(uname,pwd);
			user.menu();
			break;}
		else continue;
	cout<<"Invalid credentials. Try again\n";
	usermenu();}

	
void adminlogin(){
	string pwrd;
	cout<<"Enter password :";
	cin>>pwrd;
	if(pwrd==adminpassword)
		adminmenu();
	else{
		cout<<"Wrong password";
	adminlogin();}
	}

void adminmenu(){
	int choice;
        do {
            cout << "\n🎬 Admin Menu\n1. Add Content\n2. View User Charges\n3. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1: addContent(); break;
                case 2: {
                    string uname;
                    cout << "Enter username: ";
                    cin >> uname;
                    viewUserCharges(uname);
                    break;
                }
                case 3: cout << "Logging out...\n"; break;
                default: cout << "Invalid option.\n";
            }
        } while (choice != 3);
    }
};}


class Admin {
    const string admin_user = "admin";
    const string admin_pass = "admin123";

public:
    bool login(const string& u, const string& p) {
        return (u == admin_user && p == admin_pass);
    }

    void addContent() {
        Content c;
        cout << "Enter title: "; cin >> c.title;
        cout << "Enter genre: "; cin >> c.genre;
        cout << "Enter type (Movie/TV): "; cin >> c.type;
        cout << "Enter rating: "; cin >> c.rating;
        cout << "Enter rent cost: "; cin >> c.rent_cost;
        cout << "Enter purchase cost: "; cin >> c.purchase_cost;

        ofstream fout("inventory.txt", ios::app);
        fout << c.title << " " << c.genre << " " << c.type << " "
             << c.rating << " " << c.rent_cost << " " << c.purchase_cost << "\n";

        cout << "Content added.\n";
    }

    void viewUserCharges(const string& uname) {
        ifstream fin(uname + "_data.txt");
        if (!fin) {
            cout << "No such user.\n";
            return;
        }

        cout << "--- Transactions for " << uname << " ---\n";
        string line;
        while (getline(fin, line)) {
            cout << line << "\n";
        }
    }

    void menu() {
        int choice;
        do {
            cout << "\n🎬 Admin Menu\n1. Add Content\n2. View User Charges\n3. Logout\n";
            cout << "Enter choice: ";
            cin >> choice;

            switch (choice) {
                case 1: addContent(); break;
                case 2: {
                    string uname;
                    cout << "Enter username: ";
                    cin >> uname;
                    viewUserCharges(uname);
                    break;
                }
                case 3: cout << "Logging out...\n"; break;
                default: cout << "Invalid option.\n";
            }
        } while (choice != 3);
    }
};





