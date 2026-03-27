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

Dice TemplateManager::GetDiceByWarrior()
{
    Dice newdice;
    // 2뎀1 1뎀4 방어1
    newdice.SetAction(0, new Defence);
    newdice.SetAction(1, new Attack);
    newdice.SetAction(2, new Attack);
    newdice.SetAction(3, new Attack);
    newdice.SetAction(4, new Attack);
    newdice.SetAction(5, new Attack(2));

    return newdice;
}

Dice TemplateManager::GetDiceByArcher()
{
    Dice newdice;
    // 꽝2 2뎀3 1뎀1
    newdice.SetAction(2, new Attack);
    newdice.SetAction(3, new Attack(2));
    newdice.SetAction(4, new Attack(2));
    newdice.SetAction(5, new Attack(2));

    return newdice;
}

Dice TemplateManager::GetDiceByDefender()
{
    Dice newdice;
    // 꽝1 1뎀2 1힐1 2방어2
    newdice.SetAction(1, new Attack);
    newdice.SetAction(2, new Attack);
    newdice.SetAction(3, new Heal);
    newdice.SetAction(4, new Defence(2));
    newdice.SetAction(5, new Defence(2));

    return newdice;
}

Dice TemplateManager::GetDiceByRogue()
{
    Dice newdice;
    // 꽝1 1뎀3 2뎀2
    newdice.SetAction(1, new Attack);
    newdice.SetAction(2, new Attack);
    newdice.SetAction(3, new Attack);
    newdice.SetAction(4, new Attack(2));
    newdice.SetAction(5, new Attack(2));

    return newdice;
}

Dice TemplateManager::GetDiceByType(JobType _type)
{
    switch (_type)
    {
    case JobType::Fighter:
        return GetDiceByWarrior();
        break;

    case JobType::Defender:
        return GetDiceByDefender();
        break;

    case JobType::Archer:
        return GetDiceByArcher();
        break;

    case JobType::Rogue:
        return GetDiceByRogue();
        break;


    default:
        break;
    }


    return Dice();
}
