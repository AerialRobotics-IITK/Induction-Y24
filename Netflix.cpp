#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <limits>
#include <memory>
#include <sstream>

// Forward declarations
class Content;
class Movie;
class TVShow;
class User;
class Admin;
class System;

// Utility functions... could not do this by myself. Had to take help of Claude for this part
std::string getCurrentDate() {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << localTime->tm_mday << "/"
        << std::setfill('0') << std::setw(2) << (localTime->tm_mon + 1) << "/"
        << (localTime->tm_year + 1900);
    
    return oss.str();
}

std::string getFutureDate(int daysFromNow) {
    std::time_t now = std::time(nullptr);
    now += daysFromNow * 24 * 60 * 60; // Add days in seconds
    std::tm* futureTime = std::localtime(&now);
    
    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << futureTime->tm_mday << "/"
        << std::setfill('0') << std::setw(2) << (futureTime->tm_mon + 1) << "/"
        << (futureTime->tm_year + 1900);
    
    return oss.str();
}

//  Content class
class Content {
protected:
    std::string title;
    std::string genre;
    double rating;
    bool is_rented;
    bool is_purchased;
    std::string owner; // Username of the person who rented/purchased
    std::string rent_date;
    std::string return_date;

public:
    Content(const std::string& title, const std::string& genre, double rating)
        : title(title), genre(genre), rating(rating), is_rented(false), 
          is_purchased(false), owner(""), rent_date(""), return_date("") {}
    
    virtual ~Content() {}
    
    // Getters
    std::string getTitle() const { return title; }
    std::string getGenre() const { return genre; }
    double getRating() const { return rating; }
    bool isRented() const { return is_rented; }
    bool isPurchased() const { return is_purchased; }
    std::string getOwner() const { return owner; }
    std::string getRentDate() const { return rent_date; }
    std::string getReturnDate() const { return return_date; }
    
    // Rent/Purchase methods
    virtual bool rent(const std::string& username) {
        if (is_rented || is_purchased) {
            return false;
        }
        is_rented = true;
        owner = username;
        rent_date = getCurrentDate();
        return_date = getFutureDate(7); // Default 7-day rental
        return true;
    }
    
    virtual bool purchase(const std::string& username) {
        if (is_purchased) {
            return false;
        }
        if (is_rented && owner != username) {
            return false; // Cannot purchase if someone else has rented
        }
        is_purchased = true;
        is_rented = false; // No longer rented if purchased
        owner = username;
        rent_date = "";
        return_date = "";
        return true;
    }
    
    virtual bool returnContent() {
        if (!is_rented) {
            return false;
        }
        is_rented = false;
        owner = "";
        rent_date = "";
        return_date = "";
        return true;
    }
    
    virtual std::string getType() const = 0;
    virtual double getRentCost() const = 0;
    virtual double getPurchaseCost() const = 0;
    virtual void display() const = 0;
};

// Movie class
class Movie : public Content {
private:
    int duration; // in minutes
    double rent_cost;
    double purchase_cost;

public:
    Movie(const std::string& title, const std::string& genre, double rating, 
         int duration, double rent_cost, double purchase_cost)
        : Content(title, genre, rating), duration(duration), 
          rent_cost(rent_cost), purchase_cost(purchase_cost) {}
    
    std::string getType() const override { return "Movie"; }
    double getRentCost() const override { return rent_cost; }
    double getPurchaseCost() const override { return purchase_cost; }
    int getDuration() const { return duration; }
    
    void display() const override {
        std::cout << "Movie: " << title << std::endl;
        std::cout << "Genre: " << genre << std::endl;
        std::cout << "Rating: " << rating << "/10" << std::endl;
        std::cout << "Duration: " << duration << " minutes" << std::endl;
        std::cout << "Rent Cost: $" << rent_cost << std::endl;
        std::cout << "Purchase Cost: $" << purchase_cost << std::endl;
        std::cout << "Status: " << (is_purchased ? "Purchased" : (is_rented ? "Rented" : "Available")) << std::endl;
        if (is_rented) {
            std::cout << "Rented by: " << owner << std::endl;
            std::cout << "Rent Date: " << rent_date << std::endl;
            std::cout << "Return Date: " << return_date << std::endl;
        }
        std::cout << std::endl;
    }
};

// TV Show class
class TVShow : public Content {
private:
    int seasons;
    int episodes_per_season;
    double season_rent_cost;
    double season_purchase_cost;

public:
    TVShow(const std::string& title, const std::string& genre, double rating,
          int seasons, int episodes_per_season, 
          double season_rent_cost, double season_purchase_cost)
        : Content(title, genre, rating), seasons(seasons),
          episodes_per_season(episodes_per_season),
          season_rent_cost(season_rent_cost),
          season_purchase_cost(season_purchase_cost) {}
    
    std::string getType() const override { return "TV Show"; }
    double getRentCost() const override { return season_rent_cost * seasons; }
    double getPurchaseCost() const override { return season_purchase_cost * seasons; }
    int getSeasons() const { return seasons; }
    int getEpisodesPerSeason() const { return episodes_per_season; }
    double getSeasonRentCost() const { return season_rent_cost; }
    double getSeasonPurchaseCost() const { return season_purchase_cost; }
    
    void display() const override {
        std::cout << "TV Show: " << title << std::endl;
        std::cout << "Genre: " << genre << std::endl;
        std::cout << "Rating: " << rating << "/10" << std::endl;
        std::cout << "Seasons: " << seasons << std::endl;
        std::cout << "Episodes per Season: " << episodes_per_season << std::endl;
        std::cout << "Rent Cost per Season: $" << season_rent_cost << std::endl;
        std::cout << "Total Rent Cost: $" << getRentCost() << std::endl;
        std::cout << "Purchase Cost per Season: $" << season_purchase_cost << std::endl;
        std::cout << "Total Purchase Cost: $" << getPurchaseCost() << std::endl;
        std::cout << "Status: " << (is_purchased ? "Purchased" : (is_rented ? "Rented" : "Available")) << std::endl;
        if (is_rented) {
            std::cout << "Rented by: " << owner << std::endl;
            std::cout << "Rent Date: " << rent_date << std::endl;
            std::cout << "Return Date: " << return_date << std::endl;
        }
        std::cout << std::endl;
    }
};

// User class
class User {
protected:
    std::string username;
    std::string password;
    std::vector<std::shared_ptr<Content>> rented_content;
    std::vector<std::shared_ptr<Content>> purchased_content;
    double charges_due;

public:
    User(const std::string& username, const std::string& password)
        : username(username), password(password), charges_due(0.0) {}
    
    virtual ~User() {}
    
    std::string getUsername() const { return username; }
    double getChargesDue() const { return charges_due; }
    
    bool validatePassword(const std::string& input_password) const {
        return password == input_password;
    }
    
    bool hasRentedContent() const {
        return !rented_content.empty();
    }
    
    bool rentContent(std::shared_ptr<Content> content) {
        if (content->rent(username)) {
            rented_content.push_back(content);
            charges_due += content->getRentCost();
            return true;
        }
        return false;
    }
    
    bool purchaseContent(std::shared_ptr<Content> content) {
        if (content->purchase(username)) {
            // If previously rented, remove from rented list
            auto it = std::find(rented_content.begin(), rented_content.end(), content);
            if (it != rented_content.end()) {
                rented_content.erase(it);
            }
            
            purchased_content.push_back(content);
            charges_due += content->getPurchaseCost();
            return true;
        }
        return false;
    }
    
    bool returnContent(std::shared_ptr<Content> content) {
        auto it = std::find(rented_content.begin(), rented_content.end(), content);
        if (it != rented_content.end() && content->returnContent()) {
            rented_content.erase(it);
            return true;
        }
        return false;
    }
    
    void displayRentedContent() const {
        if (rented_content.empty()) {
            std::cout << "You haven't rented any content yet." << std::endl;
            return;
        }
        
        std::cout << "---- Your Rented Content ----" << std::endl;
        for (const auto& content : rented_content) {
            std::cout << "Title: " << content->getTitle() << std::endl;
            std::cout << "Type: " << content->getType() << std::endl;
            std::cout << "Rented on: " << content->getRentDate() << std::endl;
            std::cout << "Return by: " << content->getReturnDate() << std::endl;
            std::cout << "Cost: $" << content->getRentCost() << std::endl;
            std::cout << std::endl;
        }
    }
    
    void displayPurchasedContent() const {
        if (purchased_content.empty()) {
            std::cout << "You haven't purchased any content yet." << std::endl;
            return;
        }
        
        std::cout << "---- Your Purchased Content ----" << std::endl;
        for (const auto& content : purchased_content) {
            std::cout << "Title: " << content->getTitle() << std::endl;
            std::cout << "Type: " << content->getType() << std::endl;
            std::cout << "Cost: $" << content->getPurchaseCost() << std::endl;
            std::cout << std::endl;
        }
    }
    
    void displayChargesDue() const {
        std::cout << "Total charges due: $" << charges_due << std::endl;
    }
    
    virtual void displayMenu() const {
        std::cout << "\n----- User Menu -----" << std::endl;
        std::cout << "1. Browse content by category" << std::endl;
        std::cout << "2. Browse content by genre" << std::endl;
        std::cout << "3. Search content by title" << std::endl;
        std::cout << "4. Search content by genre" << std::endl;
        std::cout << "5. Rent content" << std::endl;
        std::cout << "6. Purchase content" << std::endl;
        std::cout << "7. Return rented content" << std::endl;
        std::cout << "8. View rented content" << std::endl;
        std::cout << "9. View purchased content" << std::endl;
        std::cout << "10. Check charges due" << std::endl;
        std::cout << "0. Logout" << std::endl;
        std::cout << "Enter your choice: ";
    }
};

// Admin class
class Admin : public User {
public:
    Admin(const std::string& username, const std::string& password)
        : User(username, password) {}
    
    void displayMenu() const override {
        std::cout << "\n----- Admin Menu -----" << std::endl;
        std::cout << "1. Add new movie" << std::endl;
        std::cout << "2. Add new TV show" << std::endl;
        std::cout << "3. Remove content" << std::endl;
        std::cout << "4. Check charges due for user" << std::endl;
        std::cout << "5. Browse all content" << std::endl;
        std::cout << "6. Search content" << std::endl;
        std::cout << "0. Logout" << std::endl;
        std::cout << "Enter your choice: ";
    }
};

// Netflix-like system
class System {
private:
    std::vector<std::shared_ptr<Content>> content_database;
    std::map<std::string, std::shared_ptr<User>> users;
    std::shared_ptr<User> current_user;
    
    // Initialize with sample data
    void initializeDatabase() {
        // Add 10 sample movies
        addContent(std::make_shared<Movie>("The Shawshank Redemption", "Drama", 9.3, 142, 3.99, 14.99));
        addContent(std::make_shared<Movie>("The Godfather", "Crime", 9.2, 175, 3.99, 14.99));
        addContent(std::make_shared<Movie>("The Dark Knight", "Action", 9.0, 152, 4.99, 15.99));
        addContent(std::make_shared<Movie>("Pulp Fiction", "Crime", 8.9, 154, 3.99, 12.99));
        addContent(std::make_shared<Movie>("Fight Club", "Drama", 8.8, 139, 3.99, 12.99));
        addContent(std::make_shared<Movie>("Inception", "Sci-Fi", 8.8, 148, 4.99, 15.99));
        addContent(std::make_shared<Movie>("The Matrix", "Sci-Fi", 8.7, 136, 3.99, 13.99));
        addContent(std::make_shared<Movie>("Interstellar", "Sci-Fi", 8.6, 169, 4.99, 16.99));
        addContent(std::make_shared<Movie>("Parasite", "Thriller", 8.5, 132, 4.99, 16.99));
        addContent(std::make_shared<Movie>("Joker", "Drama", 8.4, 122, 4.99, 15.99));
        
        // Add some sample TV shows
        addContent(std::make_shared<TVShow>("Breaking Bad", "Drama", 9.5, 5, 13, 2.99, 9.99));
        addContent(std::make_shared<TVShow>("Game of Thrones", "Fantasy", 9.2, 8, 10, 2.99, 12.99));
        addContent(std::make_shared<TVShow>("Stranger Things", "Sci-Fi", 8.7, 4, 8, 2.99, 9.99));
        addContent(std::make_shared<TVShow>("The Office", "Comedy", 8.9, 9, 24, 1.99, 7.99));
        addContent(std::make_shared<TVShow>("Friends", "Comedy", 8.5, 10, 24, 1.99, 8.99));
        
        // Add admin account
        users["admin"] = std::make_shared<Admin>("admin", "admin123");
    }
    
public:
    System() : current_user(nullptr) {
        initializeDatabase();
    }
    
    void addContent(std::shared_ptr<Content> content) {
        content_database.push_back(content);
    }
    
    bool removeContent(const std::string& title) {
        auto it = std::find_if(content_database.begin(), content_database.end(),
                              [&title](const std::shared_ptr<Content>& c) {
                                  return c->getTitle() == title;
                              });
        
        if (it != content_database.end()) {
            content_database.erase(it);
            return true;
        }
        return false;
    }
    
    std::shared_ptr<Content> findContentByTitle(const std::string& title) {
        auto it = std::find_if(content_database.begin(), content_database.end(),
                              [&title](const std::shared_ptr<Content>& c) {
                                  return c->getTitle() == title;
                              });
        
        if (it != content_database.end()) {
            return *it;
        }
        return nullptr;
    }
    
    std::vector<std::shared_ptr<Content>> findContentByGenre(const std::string& genre) {
        std::vector<std::shared_ptr<Content>> results;
        
        for (const auto& content : content_database) {
            if (content->getGenre() == genre) {
                results.push_back(content);
            }
        }
        
        return results;
    }
    
    std::vector<std::shared_ptr<Content>> getContentByType(const std::string& type) {
        std::vector<std::shared_ptr<Content>> results;
        
        for (const auto& content : content_database) {
            if (content->getType() == type) {
                results.push_back(content);
            }
        }
        
        return results;
    }
    
    std::vector<std::string> getUniqueGenres() {
        std::vector<std::string> genres;
        
        for (const auto& content : content_database) {
            if (std::find(genres.begin(), genres.end(), content->getGenre()) == genres.end()) {
                genres.push_back(content->getGenre());
            }
        }
        
        return genres;
    }
    
    bool isUsernameAvailable(const std::string& username) {
        return users.find(username) == users.end();
    }
    
    bool registerUser(const std::string& username, const std::string& password) {
        if (!isUsernameAvailable(username)) {
            return false;
        }
        
        users[username] = std::make_shared<User>(username, password);
        return true;
    }
    
    bool login(const std::string& username, const std::string& password) {
        auto it = users.find(username);
        if (it != users.end() && it->second->validatePassword(password)) {
            current_user = it->second;
            return true;
        }
        return false;
    }
    
    void logout() {
        current_user = nullptr;
    }
    
    bool isAdminLoggedIn() const {
        return current_user && dynamic_cast<Admin*>(current_user.get()) != nullptr;
    }
    
    bool isUserLoggedIn() const {
        return current_user != nullptr;
    }
    
    std::shared_ptr<User> getCurrentUser() const {
        return current_user;
    }
    
    std::shared_ptr<User> getUserByUsername(const std::string& username) {
        auto it = users.find(username);
        if (it != users.end()) {
            return it->second;
        }
        return nullptr;
    }
    
    void displayAllContent() const {
        std::cout << "----- Content Database -----" << std::endl;
        int index = 1;
        for (const auto& content : content_database) {
            std::cout << index++ << ". " << content->getTitle() 
                     << " (" << content->getType() << ", " << content->getGenre() << ")" 
                     << " - " << (content->isRented() || content->isPurchased() ? "Not Available" : "Available")
                     << std::endl;
        }
        std::cout << std::endl;
    }
    
    void run() {
        int choice;
        
        while (true) {
            if (!isUserLoggedIn()) {
                displayMainMenu();
                std::cin >> choice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                switch (choice) {
                    case 1:
                        handleLogin();
                        break;
                    case 2:
                        handleSignUp();
                        break;
                    case 3:
                        handleAdminLogin();
                        break;
                    case 0:
                        std::cout << "Thank you for using Netflix-Style Inventory System. Goodbye!" << std::endl;
                        return;
                    default:
                        std::cout << "Invalid choice. Please try again." << std::endl;
                }
            } else if (isAdminLoggedIn()) {
                current_user->displayMenu();
                std::cin >> choice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                switch (choice) {
                    case 1:
                        handleAddMovie();
                        break;
                    case 2:
                        handleAddTVShow();
                        break;
                    case 3:
                        handleRemoveContent();
                        break;
                    case 4:
                        handleCheckUserCharges();
                        break;
                    case 5:
                        displayAllContent();
                        break;
                    case 6:
                        handleAdminSearch();
                        break;
                    case 0:
                        logout();
                        std::cout << "Logged out successfully." << std::endl;
                        break;
                    default:
                        std::cout << "Invalid choice. Please try again." << std::endl;
                }
            } else {
                current_user->displayMenu();
                std::cin >> choice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                switch (choice) {
                    case 1:
                        handleBrowseByCategory();
                        break;
                    case 2:
                        handleBrowseByGenre();
                        break;
                    case 3:
                        handleSearchByTitle();
                        break;
                    case 4:
                        handleSearchByGenre();
                        break;
                    case 5:
                        handleRentContent();
                        break;
                    case 6:
                        handlePurchaseContent();
                        break;
                    case 7:
                        handleReturnContent();
                        break;
                    case 8:
                        current_user->displayRentedContent();
                        break;
                    case 9:
                        current_user->displayPurchasedContent();
                        break;
                    case 10:
                        current_user->displayChargesDue();
                        break;
                    case 0:
                        logout();
                        std::cout
                        << "Logged out successfully." << std::endl;
                        break;
                    default:
                        std::cout << "Invalid choice. Please try again." << std::endl;
                }
            }
        }
    }
    
private:
    void displayMainMenu() const {
        std::cout << "\n----- Netflix-Style Inventory System -----" << std::endl;
        std::cout << "1. User Login" << std::endl;
        std::cout << "2. User Sign Up" << std::endl;
        std::cout << "3. Admin Login" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter your choice: ";
    }
    
    void handleLogin() {
        std::string username, password;
        
        std::cout << "Enter username: ";
        std::getline(std::cin, username);
        std::cout << "Enter password: ";
        std::getline(std::cin, password);
        
        if (login(username, password)) {
            std::cout << "Login successful. Welcome, " << username << "!" << std::endl;
        } else {
            std::cout << "Login failed. Invalid username or password." << std::endl;
        }
    }
    
    void handleSignUp() {
        std::string username, password;
        
        std::cout << "Enter new username: ";
        std::getline(std::cin, username);
        
        if (!isUsernameAvailable(username)) {
            std::cout << "Username already taken. Please choose another one." << std::endl;
            return;
        }
        
        std::cout << "Enter password: ";
        std::getline(std::cin, password);
        
        if (registerUser(username, password)) {
            std::cout << "Registration successful! You can now login." << std::endl;
        } else {
            std::cout << "Registration failed. Please try again." << std::endl;
        }
    }
    
    void handleAdminLogin() {
        std::string username, password;
        
        std::cout << "Enter admin username: ";
        std::getline(std::cin, username);
        std::cout << "Enter admin password: ";
        std::getline(std::cin, password);
        
        if (login(username, password) && isAdminLoggedIn()) {
            std::cout << "Admin login successful. Welcome, " << username << "!" << std::endl;
        } else {
            std::cout << "Admin login failed. Invalid username or password." << std::endl;
            logout(); // In case a regular user tried to login as admin
        }
    }
    
    void handleBrowseByCategory() {
        std::cout << "\n----- Browse by Category -----" << std::endl;
        std::cout << "1. Movies" << std::endl;
        std::cout << "2. TV Shows" << std::endl;
        std::cout << "Enter your choice: ";
        
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        std::vector<std::shared_ptr<Content>> results;
        
        switch (choice) {
            case 1:
                results = getContentByType("Movie");
                break;
            case 2:
                results = getContentByType("TV Show");
                break;
            default:
                std::cout << "Invalid choice." << std::endl;
                return;
        }
        
        displayContentList(results);
    }
    
    void handleBrowseByGenre() {
        std::vector<std::string> genres = getUniqueGenres();
        
        std::cout << "\n----- Browse by Genre -----" << std::endl;
        for (size_t i = 0; i < genres.size(); ++i) {
            std::cout << (i + 1) << ". " << genres[i] << std::endl;
        }
        
        std::cout << "Enter your choice (1-" << genres.size() << "): ";
        
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (choice < 1 || choice > static_cast<int>(genres.size())) {
            std::cout << "Invalid choice." << std::endl;
            return;
        }
        
        std::vector<std::shared_ptr<Content>> results = findContentByGenre(genres[choice - 1]);
        displayContentList(results);
    }
    
    void handleSearchByTitle() {
        std::string title;
        
        std::cout << "Enter title to search for: ";
        std::getline(std::cin, title);
        
        std::shared_ptr<Content> content = findContentByTitle(title);
        
        if (content) {
            content->display();
        } else {
            std::cout << "Content not found." << std::endl;
        }
    }
    
    void handleSearchByGenre() {
        std::string genre;
        
        std::cout << "Enter genre to search for: ";
        std::getline(std::cin, genre);
        
        std::vector<std::shared_ptr<Content>> results = findContentByGenre(genre);
        
        if (results.empty()) {
            std::cout << "No content found for genre: " << genre << std::endl;
        } else {
            displayContentList(results);
        }
    }
    
    void displayContentList(const std::vector<std::shared_ptr<Content>>& content_list) {
        if (content_list.empty()) {
            std::cout << "No content available." << std::endl;
            return;
        }
        
        std::cout << "\n----- Content List -----" << std::endl;
        int index = 1;
        for (const auto& content : content_list) {
            std::cout << index++ << ". " << content->getTitle() 
                     << " (" << content->getType() << ", " << content->getGenre() << ")" 
                     << " - " << (content->isRented() || content->isPurchased() ? "Not Available" : "Available")
                     << std::endl;
        }
        
        std::cout << "\nEnter the number to view details (0 to cancel): ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (choice > 0 && choice <= static_cast<int>(content_list.size())) {
            content_list[choice - 1]->display();
        }
    }
    
    void handleRentContent() {
        std::string title;
        
        std::cout << "Enter the title of the content you want to rent: ";
        std::getline(std::cin, title);
        
        std::shared_ptr<Content> content = findContentByTitle(title);
        
        if (!content) {
            std::cout << "Content not found." << std::endl;
            return;
        }
        
        if (content->isRented() || content->isPurchased()) {
            std::cout << "This content is not available for rent." << std::endl;
            return;
        }
        
        std::cout << "Rent cost: $" << content->getRentCost() << std::endl;
        std::cout << "Do you want to rent this content? (y/n): ";
        
        char response;
        std::cin >> response;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (response == 'y' || response == 'Y') {
            if (current_user->rentContent(content)) {
                std::cout << "Content rented successfully!" << std::endl;
            } else {
                std::cout << "Failed to rent content." << std::endl;
            }
        }
    }
    
    void handlePurchaseContent() {
        std::string title;
        
        std::cout << "Enter the title of the content you want to purchase: ";
        std::getline(std::cin, title);
        
        std::shared_ptr<Content> content = findContentByTitle(title);
        
        if (!content) {
            std::cout << "Content not found." << std::endl;
            return;
        }
        
        if (content->isPurchased()) {
            std::cout << "This content is not available for purchase." << std::endl;
            return;
        }
        
        std::cout << "Purchase cost: $" << content->getPurchaseCost() << std::endl;
        std::cout << "Do you want to purchase this content? (y/n): ";
        
        char response;
        std::cin >> response;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (response == 'y' || response == 'Y') {
            if (current_user->purchaseContent(content)) {
                std::cout << "Content purchased successfully!" << std::endl;
            } else {
                std::cout << "Failed to purchase content." << std::endl;
            }
        }
    }
    
    void handleReturnContent() {
        current_user->displayRentedContent();
        
        if (current_user->hasRentedContent() == false) {
            return;
        }
        
        std::string title;
        std::cout << "Enter the title of the content you want to return: ";
        std::getline(std::cin, title);
        
        std::shared_ptr<Content> content = findContentByTitle(title);
        
        if (!content) {
            std::cout << "Content not found." << std::endl;
            return;
        }
        
        if (current_user->returnContent(content)) {
            std::cout << "Content returned successfully!" << std::endl;
        } else {
            std::cout << "Failed to return content. Make sure you've rented it." << std::endl;
        }
    }
    
    void handleAddMovie() {
        std::string title, genre;
        double rating, rent_cost, purchase_cost;
        int duration;
        
        std::cout << "Enter movie title: ";
        std::getline(std::cin, title);
        
        if (findContentByTitle(title)) {
            std::cout << "A movie with this title already exists." << std::endl;
            return;
        }
        
        std::cout << "Enter genre: ";
        std::getline(std::cin, genre);
        
        std::cout << "Enter rating (0-10): ";
        std::cin >> rating;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (rating < 0 || rating > 10) {
            std::cout << "Invalid rating. Must be between 0 and 10." << std::endl;
            return;
        }
        
        std::cout << "Enter duration (in minutes): ";
        std::cin >> duration;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (duration <= 0) {
            std::cout << "Invalid duration." << std::endl;
            return;
        }
        
        std::cout << "Enter rent cost: $";
        std::cin >> rent_cost;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (rent_cost < 0) {
            std::cout << "Invalid rent cost." << std::endl;
            return;
        }
        
        std::cout << "Enter purchase cost: $";
        std::cin >> purchase_cost;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (purchase_cost < 0) {
            std::cout << "Invalid purchase cost." << std::endl;
            return;
        }
        
        addContent(std::make_shared<Movie>(title, genre, rating, duration, rent_cost, purchase_cost));
        std::cout << "Movie added successfully!" << std::endl;
    }
    
    void handleAddTVShow() {
        std::string title, genre;
        double rating, season_rent_cost, season_purchase_cost;
        int seasons, episodes_per_season;
        
        std::cout << "Enter TV show title: ";
        std::getline(std::cin, title);
        
        if (findContentByTitle(title)) {
            std::cout << "A TV show with this title already exists." << std::endl;
            return;
        }
        
        std::cout << "Enter genre: ";
        std::getline(std::cin, genre);
        
        std::cout << "Enter rating (0-10): ";
        std::cin >> rating;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (rating < 0 || rating > 10) {
            std::cout << "Invalid rating. Must be between 0 and 10." << std::endl;
            return;
        }
        
        std::cout << "Enter number of seasons: ";
        std::cin >> seasons;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (seasons <= 0) {
            std::cout << "Invalid number of seasons." << std::endl;
            return;
        }
        
        std::cout << "Enter episodes per season: ";
        std::cin >> episodes_per_season;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (episodes_per_season <= 0) {
            std::cout << "Invalid number of episodes." << std::endl;
            return;
        }
        
        std::cout << "Enter rent cost per season: $";
        std::cin >> season_rent_cost;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (season_rent_cost < 0) {
            std::cout << "Invalid rent cost." << std::endl;
            return;
        }
        
        std::cout << "Enter purchase cost per season: $";
        std::cin >> season_purchase_cost;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if (season_purchase_cost < 0) {
            std::cout << "Invalid purchase cost." << std::endl;
            return;
        }
        
        addContent(std::make_shared<TVShow>(title, genre, rating, seasons, episodes_per_season, 
                                           season_rent_cost, season_purchase_cost));
        std::cout << "TV show added successfully!" << std::endl;
    }
    
    void handleRemoveContent() {
        displayAllContent();
        
        std::string title;
        std::cout << "Enter the title of the content you want to remove: ";
        std::getline(std::cin, title);
        
        if (removeContent(title)) {
            std::cout << "Content removed successfully!" << std::endl;
        } else {
            std::cout << "Failed to remove content. Title not found." << std::endl;
        }
    }
    
    void handleCheckUserCharges() {
        std::string username;
        std::cout << "Enter username: ";
        std::getline(std::cin, username);
        
        std::shared_ptr<User> user = getUserByUsername(username);
        
        if (user) {
            std::cout << "Charges due for user " << username << ": $" << user->getChargesDue() << std::endl;
        } else {
            std::cout << "User not found." << std::endl;
        }
    }
    
    void handleAdminSearch() {
        std::cout << "\n----- Search Content -----" << std::endl;
        std::cout << "1. Search by title" << std::endl;
        std::cout << "2. Search by genre" << std::endl;
        std::cout << "Enter your choice: ";
        
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        switch (choice) {
            case 1:
                handleSearchByTitle();
                break;
            case 2:
                handleSearchByGenre();
                break;
            default:
                std::cout << "Invalid choice." << std::endl;
        }
    }
};
// did not do hashing as did not have enough time for encryption. Created classes  myself and adding things like genre, rating etc throught GPT. 
int main() {
    System netflix_system;
    netflix_system.run();
    return 0;
}
