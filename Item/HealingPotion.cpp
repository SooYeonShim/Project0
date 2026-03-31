#include "HealingPotion.h"

bool HealingPotion::Use(Character& target) {
    if (target.GetHP() != 0)
    {
        target.SetHP(min(target.GetMaxHP(), target.GetHP() + 5));
        return true;
    }
    else
    {
        cout << "사용 불가능한 대상입니다." << endl;
        return false;
    }

}
