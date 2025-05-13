#include "content.h"
#include <vector>
#include <memory>
#include "init_content.h"

using namespace std;

void initializeContent(vector<shared_ptr<Content>>& content_library) {

    content_library.push_back(make_shared<Movie>("Inception", "Sci-Fi", 8.8, 148, 50, 200));
    content_library.push_back(make_shared<Movie>("The Dark Knight", "Action", 9.0, 152, 45, 180));
    content_library.push_back(make_shared<Movie>("Interstellar", "Sci-Fi", 8.6, 169, 55, 220));
    content_library.push_back(make_shared<Movie>("Parasite", "Thriller", 8.6, 132, 40, 170));
    content_library.push_back(make_shared<Movie>("The Matrix", "Sci-Fi", 8.7, 136, 50, 190));
    content_library.push_back(make_shared<Movie>("Gladiator", "Action", 8.5, 155, 45, 175));
    content_library.push_back(make_shared<Movie>("Joker", "Drama", 8.4, 122, 40, 160));
    content_library.push_back(make_shared<Movie>("La La Land", "Musical", 8.0, 128, 35, 150));
    content_library.push_back(make_shared<Movie>("Titanic", "Romance", 7.9, 195, 50, 200));
    content_library.push_back(make_shared<Movie>("Shutter Island", "Mystery", 8.2, 138, 40, 170));
    content_library.push_back(make_shared<Movie>("The Godfather", "Crime", 9.2, 175, 55, 230));
    content_library.push_back(make_shared<Movie>("Avengers: Endgame", "Superhero", 8.4, 181, 60, 250));
    content_library.push_back(make_shared<Movie>("Forrest Gump", "Drama", 8.8, 142, 45, 180));
    content_library.push_back(make_shared<Movie>("Fight Club", "Thriller", 8.8, 139, 45, 190));
    content_library.push_back(make_shared<Movie>("The Prestige", "Mystery", 8.5, 130, 40, 170));
    content_library.push_back(make_shared<Movie>("Coco", "Animation", 8.4, 105, 35, 140));
    content_library.push_back(make_shared<Movie>("Whiplash", "Drama", 8.5, 107, 40, 160));
    content_library.push_back(make_shared<Movie>("Toy Story", "Animation", 8.3, 81, 30, 120));
    content_library.push_back(make_shared<Movie>("The Lion King", "Animation", 8.5, 88, 30, 130));
    content_library.push_back(make_shared<Movie>("The Social Network", "Biography", 7.7, 120, 35, 150));

    content_library.push_back(make_shared<TVShow>("Breaking Bad", "Crime", 9.5, 5, 13, 100, 400));
    content_library.push_back(make_shared<TVShow>("Stranger Things", "Sci-Fi", 8.7, 4, 9, 90, 350));
    content_library.push_back(make_shared<TVShow>("Game of Thrones", "Fantasy", 9.2, 8, 10, 110, 500));
    content_library.push_back(make_shared<TVShow>("Friends", "Comedy", 8.9, 10, 24, 70, 300));
    content_library.push_back(make_shared<TVShow>("The Office", "Comedy", 8.9, 9, 22, 70, 280));
    content_library.push_back(make_shared<TVShow>("Sherlock", "Mystery", 9.1, 4, 3, 90, 360));
    content_library.push_back(make_shared<TVShow>("Dark", "Sci-Fi", 8.8, 3, 8, 85, 320));
    content_library.push_back(make_shared<TVShow>("Narcos", "Crime", 8.8, 3, 10, 80, 300));
    content_library.push_back(make_shared<TVShow>("The Crown", "Drama", 8.6, 5, 10, 85, 320));
    content_library.push_back(make_shared<TVShow>("Money Heist", "Thriller", 8.3, 5, 10, 85, 330));
    content_library.push_back(make_shared<TVShow>("Peaky Blinders", "Crime", 8.8, 6, 6, 90, 340));
    content_library.push_back(make_shared<TVShow>("The Mandalorian", "Sci-Fi", 8.7, 3, 8, 90, 320));
    content_library.push_back(make_shared<TVShow>("Better Call Saul", "Crime", 8.9, 6, 10, 100, 380));
    content_library.push_back(make_shared<TVShow>("The Witcher", "Fantasy", 8.2, 3, 8, 85, 310));
    content_library.push_back(make_shared<TVShow>("Brooklyn Nine-Nine", "Comedy", 8.4, 8, 22, 75, 290));
    content_library.push_back(make_shared<TVShow>("The Boys", "Superhero", 8.7, 3, 8, 90, 340));
    content_library.push_back(make_shared<TVShow>("Lucifer", "Fantasy", 8.1, 6, 10, 85, 310));
    content_library.push_back(make_shared<TVShow>("House of Cards", "Drama", 8.7, 6, 13, 80, 300));
    content_library.push_back(make_shared<TVShow>("The 100", "Sci-Fi", 7.6, 7, 13, 75, 270));
    content_library.push_back(make_shared<TVShow>("Rick and Morty", "Animation", 9.2, 6, 10, 80, 320));
}
