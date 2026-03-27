#include "HealingPotion.h"

void HealingPotion::Use(Character& target) {

    target.SetHP(max(target.GetMaxHP(), target.GetHP() + 5));

}
