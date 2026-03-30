#include "TemplateManager.h"

#include "Attack.h"
#include "Defence.h"
#include "Heal.h"
#include "InflictStatus.h"

TemplateManager::~TemplateManager()
{
    for (size_t i = 0; i < Actionlists.size(); ++i)
    {
        delete Actionlists[i];
    }
    Actionlists.clear();
}

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

Troll TemplateManager::GetMonsterByTroll()
{
    Dice dice = GetDiceByTroll();

    return Troll(dice);
}

Goblin TemplateManager::GetMonsterByElitGoblin()
{
    Dice dice = GetDiceByElitGobline();
    Goblin monster(dice);
    // 엘리트몹의 체력은 기존의 1.5배
    monster.SetMaxHP(monster.GetMaxHP() * 1.5);
    monster.SetHP(monster.GetMaxHP());
    monster.SetName("정예고블린");

    return monster;
}

Orc TemplateManager::GetMonsterByElitOrc()
{
    Dice dice = GetDiceByElitOrc();
    Orc monster(dice);
    // 엘리트몹의 체력은 기존의 1.5배
    monster.SetMaxHP(monster.GetMaxHP() * 1.5);
    monster.SetHP(monster.GetMaxHP());

    return monster;
}

Wolf TemplateManager::GetMonsterByElitWolf()
{
    Dice dice = GetDiceByElitWolf();
    Wolf monster(dice);
    // 엘리트몹의 체력은 기존의 1.2배
    monster.SetMaxHP(monster.GetMaxHP() * 1.2);
    monster.SetHP(monster.GetMaxHP());
    monster.SetName("정예늑대");

    return monster;
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

Dice TemplateManager::GetDiceByTroll()
{
    Dice newdice;
    newdice.SetAction(0, CreateActionByName("Stun(2)"));
    newdice.SetAction(1, CreateActionByName("AllAtk(3)"));
    newdice.SetAction(2, new Attack(3));
    newdice.SetAction(3, new Attack(3));
    newdice.SetAction(4, new Attack(5));
    newdice.SetAction(5, new Attack(5));

    return newdice;
}

Dice TemplateManager::GetDiceByElitGobline()
{
    Dice newdice;
    newdice.SetAction(0, new Attack(3));
    newdice.SetAction(1, new Attack(3));
    newdice.SetAction(2, new Attack(3));
    newdice.SetAction(3, new Attack(3));
    newdice.SetAction(4, new Attack(4));
    newdice.SetAction(5, CreateActionByName("AllHeal(3)"));

    return newdice;
}

Dice TemplateManager::GetDiceByElitWolf()
{
    Dice newdice;
    newdice.SetAction(0, CreateActionByName("Bleed(3)"));
    newdice.SetAction(1, CreateActionByName("Bleed(3)"));
    newdice.SetAction(2, new Attack(3));
    newdice.SetAction(3, new Attack(3));
    newdice.SetAction(4, new Attack(5));
    newdice.SetAction(5, new Attack(5));

    return newdice;
}

Dice TemplateManager::GetDiceByElitOrc()
{
    Dice newdice;
    newdice.SetAction(0, CreateActionByName("AllAtk(3)"));
    newdice.SetAction(1, new Attack(5));
    newdice.SetAction(2, new Attack(5));
    newdice.SetAction(3, new Attack(7));
    newdice.SetAction(4, new Attack(7));
    newdice.SetAction(5, CreateActionByName("Stun(2)"));

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
    
    newdice.SetAction(0, CreateActionByName("Bleed(3)"));
    newdice.SetAction(1, CreateActionByName("Bleed(3)"));
    newdice.SetAction(2, new Attack(3));
    newdice.SetAction(3, new Attack(3));
    newdice.SetAction(4, new Attack(5));
    newdice.SetAction(5, CreateActionByName("Stun(1)"));

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

void TemplateManager::InitActions()
{
    // 중복호출 오류시 메모리릭 발생원인제거용
    for (size_t i = 0; i < Actionlists.size(); ++i)
    {
        delete Actionlists[i];
    }
    Actionlists.clear();
    ShopActionlists.clear();

    // 기본 전투 액션
    Actionlists.push_back(new Attack(3));
    Actionlists.push_back(new Attack(4));
    Actionlists.push_back(new Attack(5));
    Actionlists.push_back(new Attack(6));
    Actionlists.push_back(new Attack(7));
    Actionlists.push_back(new Heal(3));
    Actionlists.push_back(new Heal(5));
    Actionlists.push_back(new Defence(2));
    Actionlists.push_back(new Defence(4));
    Actionlists.push_back(new Defence(6));

    // 광역공격
    Attack* atk = new Attack(3);
    atk->SetTargetType(TargetType::ENEMYALL);
    atk->SetActionName("AllAtk");
    Actionlists.push_back(atk);

    atk = new Attack(5);
    atk->SetTargetType(TargetType::ENEMYALL);
    atk->SetActionName("AllAtk");
    Actionlists.push_back(atk);

    // 광역 힐
    Heal* heal = new Heal(3);
    heal->SetTargetType(TargetType::FRIEDLYALL);
    heal->SetActionName("AllHeal");
    Actionlists.push_back(heal);

    // 광역 방어
    Defence* def = new Defence(5);
    def->SetTargetType(TargetType::FRIEDLYALL);
    def->SetActionName("AllDef");
    Actionlists.push_back(def);

    // 상태이상
    StatusEffect effect;
    effect.kind = StateType::BLEED;
    effect.name = "출혈";
    effect.turnsRemaining = 3;
    vector<StatusEffect> veceffect;
    veceffect.push_back(effect);
    InflictStatus* stat = new InflictStatus(veceffect);
    stat->SetActionName("Bleed");
    Actionlists.push_back(stat);

    effect.kind = StateType::STUN;
    effect.turnsRemaining = 2;
    effect.name = "기절";
    veceffect.clear();
    veceffect.push_back(effect);
    stat = new InflictStatus(veceffect);
    stat->SetActionName("Stun");
    Actionlists.push_back(stat);

    effect.kind = StateType::STUN;
    effect.turnsRemaining = 1;
    effect.name = "기절";
    veceffect.clear();
    veceffect.push_back(effect);
    stat = new InflictStatus(veceffect);
    stat->SetActionName("Stun");
    Actionlists.push_back(stat);



    // 상점 리스트 등록
    AddToShoplists("Attack(7)");
    AddToShoplists("Heal(5)");
    AddToShoplists("Defence(6)");
    AddToShoplists("AllAtk(5)");
    AddToShoplists("AllHeal(3)");
    AddToShoplists("AllDef(5)");
    AddToShoplists("Bleed(3)");
    AddToShoplists("Stun(1)");

    IsActionlists = true;
}

void TemplateManager::PrintShopActionList()
{
    // 리스트 초기화없이 호출된거 방지용
    if (!IsActionlists)
    {
        InitActions();
    }
    
    // 순회하며 상점의 액션리스트들을 알려줌
    for (int i = 0; i < ShopActionlists.size(); ++i)
    {
        if (ShopActionlists[i] == nullptr)
            continue;

        std::cout << i+1 << ". " << ShopActionlists[i]->GetActionName() << " : ";
        ShopActionlists[i]->PrintInfo();
    }
}

Action* TemplateManager::CreateActionByShopIndex(int _idx)
{
    // 범위초과한 인덱스를 요구한경우 nullptr
    if(ShopActionlists.size() < _idx || _idx < 0)
        return nullptr;

    return ShopActionlists[_idx]->Clone();
}

Action* TemplateManager::CreateActionByName(const std::string& actionName)
{
    // 리스트 초기화없이 호출된거 방지용
    if (!IsActionlists)
    {
        InitActions();
    }

    // 리스트에서 이름으로 검색 후 찾은 action 복사하여 반환
    for (int i = 0; i < Actionlists.size(); ++i)
    {
        Action* proto = Actionlists[i];
        if (proto == nullptr)
            continue;

        if (proto->GetActionName() == actionName)
            return proto->Clone();
    }

    return nullptr;
}

void TemplateManager::AddToShoplists(const string& actionName)
{
    for (Action* action : Actionlists)
    {
        if (action->GetActionName() == actionName)
        {
            ShopActionlists.push_back(action);
            return;
        }
    }
}
