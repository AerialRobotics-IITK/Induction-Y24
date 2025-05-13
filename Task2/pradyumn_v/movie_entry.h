#pragma once
#include <iostream>
#include "movie.h"

struct movie_entry{
    Movie* data;
    movie_entry* next;
};