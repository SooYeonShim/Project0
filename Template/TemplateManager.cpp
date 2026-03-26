#include "TemplateManager.h"

#include "Attack.h"
#include "Defence.h"
#include "Heal.h"

Goblin TemplateManager::GetMonsterByGoblin()
{
    Dice dice = GetDiceByGobline();


    return Goblin(dice);
}

Orc TemplateManager::GetMonsterByOrc()
{
    Dice dice = GetDiceByOrc();

    return Orc(dice);
}

Wolf TemplateManager::GetMonsterByWolf()
{
    Dice dice = GetDiceByWolf();

    return Wolf(dice);
}

Dice TemplateManager::GetDiceByGobline()
{
    Dice newdice;
    newdice.SetAction(2, new Attack);
    newdice.SetAction(3, new Attack);
    newdice.SetAction(4, new Attack);
    newdice.SetAction(5, new Heal);

    return newdice;
}

Dice TemplateManager::GetDiceByOrc()
{
    Dice newdice;
    newdice.SetAction(1, new Defence);
    newdice.SetAction(2, new Defence);
    newdice.SetAction(3, new Attack);
    newdice.SetAction(4, new Attack);
    newdice.SetAction(5, new Attack);

    return newdice;
}

Dice TemplateManager::GetDiceByWolf()
{
    Dice newdice;
    newdice.SetAction(0, new Attack);
    newdice.SetAction(1, new Attack);
    newdice.SetAction(2, new Attack);
    newdice.SetAction(3, new Attack);
    newdice.SetAction(4, new Attack);
    newdice.SetAction(5, new Attack);

    return newdice;
}
