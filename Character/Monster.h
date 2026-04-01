#pragma once
#include "Character.h"


class Monster : public Character {
public:
	Monster(int HP, Dice& CharacterDice, string Name) : Character(HP, CharacterDice, Name), IsShieldTurn(false) {};
    virtual void TakeShield(int Shield_)
    {
            if (Shield_ <= 0) return; // 방어

            // 실드를 두 턴 연속으로 받을 경우 이전 턴 실드는 무효
            if (!IsShieldTurn)
            {
                this->Shield = 0;
            }

            this->Shield += Shield_;
            IsShieldTurn = true;

            std::cout << Name
                << " 방어도 증가: " << Shield_
                << " (현재 방어도: " << this->Shield << ")\n";
    }
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

            cout << Name <<  "의 출혈 피해: " << damage << endl;
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

        if (!IsShieldTurn)
        {
            this->Shield = 0;
        }
        else
        {
            IsShieldTurn = false;
        }
        CurrentAction = nullptr;
    }
    // virtual void DropItem() {}
    // virtual void DropAction() {}

private:
    // 현재 턴에 실드를 받았는지 판별하는 변수
    bool IsShieldTurn;
};
