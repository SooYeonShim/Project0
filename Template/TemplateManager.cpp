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
    newdice.SetAction(2, new Attack(3));
    newdice.SetAction(3, new Attack(3));
    newdice.SetAction(4, new Attack(3));
    newdice.SetAction(5, new Heal(3));

    return newdice;
}

Dice TemplateManager::GetDiceByOrc()
{
    Dice newdice;
    newdice.SetAction(1, new Defence(3));
    newdice.SetAction(2, new Defence(4));
    newdice.SetAction(3, new Attack(5));
    newdice.SetAction(4, new Attack(5));
    newdice.SetAction(5, new Attack(7));

    return newdice;
}

Dice TemplateManager::GetDiceByWolf()
{
    Dice newdice;
    newdice.SetAction(0, new Attack(2));
    newdice.SetAction(1, new Attack(3));
    newdice.SetAction(2, new Attack(3));
    newdice.SetAction(3, new Attack(3));
    newdice.SetAction(4, new Attack(3));
    newdice.SetAction(5, new Attack(5));

    return newdice;
}

Dice TemplateManager::GetDiceByWarrior()
{
    Dice newdice;
    
    newdice.SetAction(0, new Defence(2));
    newdice.SetAction(1, new Attack(3));
    newdice.SetAction(2, new Attack(3));
    newdice.SetAction(3, new Attack(3));
    newdice.SetAction(4, new Attack(3));
    newdice.SetAction(5, new Attack(5));

    return newdice;
}

Dice TemplateManager::GetDiceByArcher()
{
    Dice newdice;
   
    newdice.SetAction(2, new Attack(4));
    newdice.SetAction(3, new Attack(5));
    newdice.SetAction(4, new Attack(5));
    newdice.SetAction(5, new Attack(5));

    return newdice;
}

Dice TemplateManager::GetDiceByDefender()
{
    Dice newdice;
    
    newdice.SetAction(1, new Attack(3));
    newdice.SetAction(2, new Attack(3));
    newdice.SetAction(3, new Heal(3));
    newdice.SetAction(4, new Defence(4));
    newdice.SetAction(5, new Defence(5));

    return newdice;
}

Dice TemplateManager::GetDiceByRogue()
{
    Dice newdice;
    
    newdice.SetAction(1, new Attack(3));
    newdice.SetAction(2, new Attack(3));
    newdice.SetAction(3, new Attack(4));
    newdice.SetAction(4, new Attack(5));
    newdice.SetAction(5, new Attack(5));

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

Player TemplateManager::GetPlayerByType(string Nickname, JobType _type)
{
    int HP = 0;
    Dice dice;

    switch (_type)
    {
    case JobType::Fighter:
        HP = 10;
        dice = GetDiceByWarrior();
        break;

    case JobType::Defender:
        HP = 14;
        dice = GetDiceByDefender();
        break;

    case JobType::Archer:
        HP = 8;
        dice = GetDiceByArcher();
        break;

    case JobType::Rogue:
        HP = 8;
        dice = GetDiceByRogue();
        break;


    default:
        break;
    }

    return Player(HP, dice, Nickname, _type);
}

Item* TemplateManager::GetHealingPotion()
{
    HealingPotion* newPotion = new HealingPotion;

    return newPotion;
}
