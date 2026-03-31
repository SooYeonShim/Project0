#pragma once
#include "Character.h"


class Monster : public Character {
public:
	Monster(int HP, Dice& CharacterDice, string Name) : Character(HP, CharacterDice, Name) {};
    void EndTurn() override
    {
        // 출혈 체크
        auto it = std::find_if(StatusEffects.begin(), StatusEffects.end(),
            [](const StatusEffect& effect) {
                return effect.kind == StateType::BLEED
                    && effect.turnsRemaining > 0;
            }
        );

        // 출혈 중이면 피해 적용
        if (it != StatusEffects.end())
        {
            int damage = this->MaxHP / 10;

            if (damage <= 0)
                damage = 1;

            this->HP -= damage;

            cout << "출혈 피해: " << damage << endl;
        }

        // 상태 이상 남은 턴 감소
        for (auto it = StatusEffects.begin(); it != StatusEffects.end(); )
        {
            if (it->turnsRemaining > 0)
            {
                --(it->turnsRemaining);
            }

            if (it->turnsRemaining == 0)
            {
                it = StatusEffects.erase(it);
            }
            else
            {
                ++it;
            }
        }

        CurrentAction = nullptr;
    }
    // virtual void DropItem() {}
    // virtual void DropAction() {}

private:

};
