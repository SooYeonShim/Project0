#pragma once
#include <iostream>
#include <vector>

class Dice
{
public:
	vector<Action> GetActions();
	const Action& GetRandomAction();
	void SetActions(vector<Action> Actions);

private:
	vector<Action> Actions;

};