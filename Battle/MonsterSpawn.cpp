#include "MonsterSpawn.h"

#include "../Template/TemplateManager.h"
#include "Goblin.h"
#include "Orc.h"
#include "Wolf.h"

MonsterSpawn::MonsterSpawn()
{
    // 지금은 비엇으나 혹시모르니 만들어둠
}

vector<Monster> MonsterSpawn::StageSpawner(int _stage)
{
    vector<Monster> vecmst;

    switch (_stage)
    {
    // stage1 : 고블린 1마리
    case 1:
        vecmst.push_back(TemplateManager::getInstance().GetMonsterByGoblin());
        break;

    // stage2 : 늑대 1마리 고블린 1마리
    case 2:
        vecmst.push_back(TemplateManager::getInstance().GetMonsterByGoblin());
        vecmst.push_back(TemplateManager::getInstance().GetMonsterByWolf());
        break;

    // stage3 : 오크 1마리
    case 3:
        vecmst.push_back(TemplateManager::getInstance().GetMonsterByOrc());
        break;

    // 없는스테이지요청이다? 빈거반환
    default:
        break;
    }



    return vecmst;
}
