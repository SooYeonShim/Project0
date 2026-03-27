#pragma once
#include <vector>
#include <iostream>
#include <string>
#include "Character.h"

using namespace std;

class Item
{
public:
    virtual void Use(Character& target) = 0;

private:
    string Name;

};

