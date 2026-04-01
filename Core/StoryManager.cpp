#include "StoryManager.h"
#include "UIManager.h"

using namespace std;

void StoryManager::StoryByIndex(int _idx)
{
    switch (_idx)
    {
    case 0:
        Prologue();
        break;
    case 1:
        Stage1Story();
        break;
    case 2:
        Stage2Story();
        break;
    case 3:
        Stage3Story();
        break;
    case 4:
        BossStageStory();
        break;
    case 98:
        EndingStory();
        break;
    case 99:
        GameOverStory();
        break;
    default:
        break;
    }



}

void StoryManager::Prologue()
{
    UIManager::getInstance().CreateNewScreenForStoryPrint();

    cout << "                # 프롤로그 #                " << endl;
    cout << "\"신은 주사위 놀이를 한다.\"" << endl;
    cout << "즐거움의 왕국 다이시아. 이곳은 그 옛날 누군가 남긴 한마디처럼 모두가 주사위 놀이를 즐깁니다." << endl;
    cout << "다들 주사위 눈에 울고, 웃고, 화내고… 활기로 가득한 곳으로 알려져 있죠." << endl;

    cout << "당신의 파티는 다이시아 왕국의 거리를 걸어가고 있습니다. 그런데 소문과 달리 거리의 분위기는 어딘지 침울해보입니다." << endl;
    cout << "노점 상인에게 이유를 물어봅니다." << endl;

    cout << "\"왕국에 대대로 전해져 오는 보물, 신비한 힘이 깃든 황금 주사위를 던전의 주인이 훔쳐 마물을 육성하는데 쓰고 있다네.\"" << endl;
    cout << "상인은 주변을 한 번 살피더니, 어깨를 으쓱하며 말을 이어갑니다." << endl;
    cout << "\"황금 주사위의 힘 때문에 마물들은 주사위를 통해서만 쓰러뜨릴 수 있게 됐어.\"\n" << endl;

    cout << "상인은 잠시 말을 멈추고 먼 산을 바라보며 깊은 한숨을 내쉽니다." << endl;
    cout << "\"다른 모험가들이 몇 번 목숨을 걸고 던전에 들어갔지만, 모두 불운한 결말을 맞았지." << endl;
    cout << "임금님께선 황금 주사위만 구해온다면 그에 걸맞은 보상을 약속하셨다네.\"" << endl;
    cout << "\"혹시 모르지, 운만 좋다면 자네들이 그 주인공이 될지도.\"" << endl;

    cout << "당신은 흥미를 느끼며, 자신의 운을 시험해보기로 결심하고 던전으로 향합니다." << endl;
    cout << "던전의 보스를 물리치고 황금 주사위를 획득하세요!" << endl;

    UIManager::getInstance().CloseAnyTempScreen();
}

void StoryManager::Stage1Story()
{
    UIManager::getInstance().CreateNewScreenForStoryPrint();


    cout << "몬스터를 해치우고 더 깊숙이 들어갔지만, 입구에서도 느낀 것처럼 던전은 마물이 산다는 것을 믿기 힘들 정도로 평화로워 보입니다." << endl;
    cout << "하지만 그런 생각도 잠시, 어디선가 소리 없이 나타난 늑대와 고블린에게 파티는 포위되었습니다." << endl;

    UIManager::getInstance().CloseAnyTempScreen();
}

void StoryManager::Stage2Story()
{
    UIManager::getInstance().CreateNewScreenForStoryPrint();

    cout << "주변은 빽빽한 나무들로 인해 상당히 어둡습니다." << endl;
    cout << "뿌리가 우거진 땅을 간신히 넘어서 나아가니, 앞에 희미한 불빛이 보입니다." << endl;
    cout << "당신의 파티는 조심스럽게 다가갑니다." << endl;
    cout << "그것은 오크가 피운 모닥불이었고, 오크 자신의 휴식을 방해한 자들을 용서할 기색이 없습니다." << endl;

    UIManager::getInstance().CloseAnyTempScreen();
}

void StoryManager::Stage3Story()
{
    UIManager::getInstance().CreateNewScreenForStoryPrint();

    cout << "쿵, 하는 위압적인 소리가 들려옵니다." << endl;
    cout << "당신의 파티는 갑자기 들려온 소리에 긴장하며 청각을 곤두세웁니다." << endl;
    cout << "나무 사이로 거대한 그림자가 비치는가 싶더니, 금세 트롤이 모습을 나타냅니다." << endl;
    cout << "트롤은 자신의 몸집에 어울리는 나무 한 그루만한 몽둥이를 들고," << endl;
    cout << "조그만 인간 따위는 파리나 다름없다는 듯 휘둘러대기 시작합니다." << endl;
    cout << "이 트롤이 바로 던전의 주인입니다. 당신의 파티는 전투 준비를 합니다." << endl;

    // 임시 ui
    UIManager::getInstance().CloseAnyTempScreen();
}

void StoryManager::BossStageStory()
{
    UIManager::getInstance().CreateNewScreenForStoryPrint();

    cout << "생각보다 위압적인 상대는 아니었지만, 운이 따르지 않았다면 죽을 수도 있었습니다." << endl;
    cout << "트롤의 시체를 뒤져보니, 다이시아 왕국의 황금 주사위가 반짝이는 것을 발견합니다." << endl;
    cout << "안도의 한숨을 내쉬며, 당신의 파티는 다친 몸을 이끌고 마을로 돌아갑니다." << endl;

    UIManager::getInstance().CloseAnyTempScreen();
}

void StoryManager::EndingStory()
{
    UIManager::getInstance().CreateNewScreenForStoryPrint();

    cout << "                # 엔 딩 #                \n" << endl;

    cout << "왕궁의 예법에 익숙지 않은 당신의 파티는 왕 앞에 나아가 어색하게 무릎을 꿇습니다." << endl;

    cout << "\"잘 왔네. 우리나라에 황금 주사위를 돌려준 자네들에게 감사를 표하지.\"" << endl;

    cout << "왕은 당신의 파티를 융숭히 대접하고, 넉넉한 상금을 지급합니다." << endl;
    cout << "잔치는 6일간 지속됩니다. 왕국에는 활기가 돌고, 거리는 즐거움이 가득해졌습니다." << endl;

    cout << "\n- 제작 : 팀 9조대 -" << endl;

    UIManager::getInstance().CloseAnyTempScreen();
}

void StoryManager::GameOverStory()
{
    UIManager::getInstance().CreateNewScreenForStoryPrint();

    cout << "당신의 파티는 다른 모험가들에 비해 운이 좋지는 않았던 모양입니다." << endl;
    cout << "당신은 몬스터의 공격에 쓰러지고 말았습니다." << endl;
    cout << "[ GAME OVER ]\n" << endl;

    UIManager::getInstance().CloseAnyTempScreen();
}

void StoryManager::IntroDungeon()
{
    UIManager::getInstance().CreateNewScreenForStoryPrint();

    cout << "숲 속의 던전은 고요하고, 가끔씩 새소리만 들려옵니다." << endl;
    cout << "던전 안쪽으로 좀 더 들어가자, 순찰 중인 듯한 고블린과 마주칩니다." << endl;
    cout << "고블린은 간만에 좋은 먹잇감을 발견했다는 듯, 망설임 없이 달려듭니다." << endl;

    UIManager::getInstance().CloseAnyTempScreen();
}

void StoryManager::MerchantIncounter()
{
    UIManager::getInstance().CreateNewScreenForStoryPrint();

    cout << "던전에는 어디서 솟았는지 모를 작은 가판대가 보입니다. 이런 곳에서 장사를 하는 건 위험하지 않을까요?" << std::endl;
    cout << "상점 주인은 이 상점의 존재에 의문을 가진 파티가 더 의아하다는 듯, 태연하게 물건을 보여줍니다." << endl;
    cout << "\"물건을 사지 않는다면, 쉬어가기만 해도 괜찮아요.\"" << endl;

    UIManager::getInstance().CloseAnyTempScreen();
}

void StoryManager::MechantStart()
{
    UIManager::getInstance().CreateNewScreenForStoryPrint();

    cout << "던전 입구에는 작은 가판대가 보입니다. 이 외진 곳에도 모험가가 자주 오는 걸까요?" << endl;
    cout << "상점 주인은 이 상점의 존재에 의문을 가진 파티가 더 의아하다는 듯, 태연하게 물건을 보여줍니다." << endl;
    cout << "\"바로가려고? 준비는 철저히 해야지.\"" << endl;

    UIManager::getInstance().CloseAnyTempScreen();
}
