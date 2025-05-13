#include "Content.h"

Content::Content(string name, string type, int rated){
    title = name;
    genre = type;
    rating = (rated<=5)?rated:0;
}