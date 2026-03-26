#pragma once
#include <iostream>
#include <vector>
#include "GameEnums.h"

class Action 
{
public:
	TargetType GetType();
	void DoAction(vector<Character>& Self, vector<Character>& Target);
	void PrintInfo();

private:
	TargetType Type;

	
};