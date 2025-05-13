#pragma once
#include<iostream>
#include "show.h"
using namespace std;

struct tv_show_entry{
    Show* data;
    tv_show_entry* next;
};