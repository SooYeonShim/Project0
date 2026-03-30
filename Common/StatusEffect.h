#pragma once

#include <string>
#include <vector>

enum class StateType
{
	NONE,
	STUN,
	ATTACKBONUS,
    DEMAGEINCREASE,
	BLEED,
};

struct StatusEffect
{
    StateType kind = StateType::NONE;
	std::string name;
	int turnsRemaining = 0;
	int magnitude = 0;
};
