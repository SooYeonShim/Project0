#include "UIManager.h"

void UIManager::WaitForStart(std::string msg)
{
    std::cout << "\n" << BOLD << YELLOW << "  " << RESET << msg << CYAN << " [PRESS ENTER]" << RESET;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}

void UIManager::WaitForEnterInTempScreen(std::string msg)
{
    /*std::cout << "\n" << BOLD << YELLOW << "  " << RESET << msg << CYAN << " [PRESS ENTER]" << RESET;
    std::cout << std::endl;
    std::cout << std::endl;*/
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}


void UIManager::PrintMessage(std::string message)
{
    std::cout << BOLD << WHITE << " [SYSTEM] " << RESET << message << std::endl;
}

void UIManager::PrintHP(int HP)
{
    cout << "[";

    if (HP <= 0)
    {

        std::cout << RED << "   사망   " << RESET << " ]";
        return;
    }

    int subColor = HP / 10 + 1; // 0 -> BLACK 1 -> RED 2 -> YELLO, 3 -> GREEN;

    int remain = (HP % 10);


    for (int i = 0; i < remain; ++i)
    {
        std::cout << UIManager::HP_BLOCKS[subColor];
    }

    for (int i = 0; i < 10 - remain; ++i)
    {
        std::cout << UIManager::HP_BLOCKS[subColor - 1];
    }

    cout << "]";

}

void UIManager::PrintShield(int shield)
{
    if (shield <= 0)
    {
        return;
    }        

    cout << "[";
    int countRec = shield <= 10 ? shield : 10;
    for (int i = 0; i < countRec; ++i)
    {
        cout << BLOCK_SKY;
    }

    cout << "]";
}


void UIManager::PrintTarget(Action* action)
{

    cout << action->GetActionName() << " ";

    switch (action->GetTargetType())
    {
    case TargetType::ENEMYALL:
        cout << ")| 상대 전체 |(";
        break;
    case TargetType::FRIEDLYALL:
        cout << ")| 아군 전체 |(";
        break;
    case TargetType::MYSELF:
        /* FALLTHROUGH */
    case TargetType::ENEMY:
        /* FALLTHROUGH */
    case TargetType::FRIENDLY:

        // 플레이어 Action의 경우 Target이 아직 없는 상태에서 Action을 호출 할 일이 생김
        // ex) 주사위 페이즈 이후, 행동 페이즈 전            
        if (action->GetTatgerCharacters().size() == 0)
        {
            return;
        }

        cout << "| > " << action->GetTatgerCharacters()[0]->GetName() << " < |";
        break;

    default:
        break;
    }
}

void UIManager::PrintEffectStatus(const vector<StatusEffect>& effects)
{
    if (effects.size() == 0)
    {
        return;
    }    

    for (std::vector<StatusEffect>::const_iterator it = effects.begin(); it != effects.end(); ++it)
    {
        switch (it->kind)
        {
        case StateType::STUN:
            cout << YELLOW << " S (";
            cout << it->turnsRemaining;
            cout << ")" << RESET;
            break;
        case StateType::BLEED:
            cout << RED << " B (";
            cout << it->turnsRemaining;
            cout << ")" << RESET;
            break;
        }
    }

}

void UIManager::PrintBattleBoard(std::vector<Player>& players, std::vector<Monster>& monsters)
{
    std::cout << std::endl;

    for (int i = 0; i < monsters.size(); ++i)
    {
        if (i == 0)
        {
            PrintEffectStatus(monsters[i].GetStatusEffects());
            std::cout << std::endl;
            PrintMonsterSprite(monsters[i].GetName(), 0, true);
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[7A";
            PrintEffectStatus(monsters[i].GetStatusEffects());
            std::cout << "\x1b[1B";
            PrintMonsterSprite(monsters[i].GetName(), 40 * i);
            std::cout << "\x1b[1B";
            std::cout << "\x1b[" << 40 * i << "G";
            std::cout << "\x1b[6C";
        }

        PrintShield(monsters[i].GetShield());
        PrintHP(monsters[i].GetHP());


        if (i == 0)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[" << 40 * i << "G";
            std::cout << "\x1b[6C";
            std::cout << "\x1b[1B";
        }


        if (!monsters[i].GetIsDead())
        {
            PrintTarget(monsters[i].GetCurrentAction());
        }

    }

    std::cout << "\x1b[1B";
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    // PrintPlayerSprite
    for (int i = 0; i < players.size(); ++i)
    {
        if (i == 0)
        {
            std::cout << "\x1b[" << 0 << "C";
            PrintEffectStatus(players[i].GetStatusEffects());
            std::cout << std::endl;
            PrintPlayerSprite(players[i], 2, true);
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[7A";
            std::cout << "\x1b[" << 40 * i + 5 << "G";
            PrintEffectStatus(players[i].GetStatusEffects());
            std::cout << "\x1b[1B";
            PrintPlayerSprite(players[i], 40 * i + 4);
            std::cout << "\x1b[1B";
            std::cout << "\x1b[" << 40 * i << "G";
            std::cout << "\x1b[6C";
        }
        PrintShield(players[i].GetShield());
        PrintHP(players[i].GetHP());

        if (!players[i].GetIsDead())
        {

            if (i == 0)
            {
                std::cout << std::endl;
            }
            else
            {
                std::cout << "\x1b[1B";
                std::cout << "\x1b[" << 40 * i << "G";
                std::cout << "\x1b[6C";
            }


            // 액션 스킬 & 타겟 잇으면 그거 출력
            if (players[i].GetCurrentAction() != nullptr)
            {
                PrintTarget(players[i].GetCurrentAction());
            }
            else
            {
                std::cout << "|          |" << RESET;
            }
        }
    }

    std::cout << "\x1b[1B";
    std::cout << std::endl;
    std::cout << std::endl;
}

void UIManager::CursorScrollSet() const
{
    std::cout << "\x1b[" << StartStatusRow << ";" << LeftMargin << "H";
}

void UIManager::ClearMainWindowBox()
{
    DisableStreamMarginHook();

    // 기존 스크롤 해제
    std::cout << "\x1b[r";
    std::cout << "\x1b[" << 0 << ";" << "H";

    // 바깥 외곽
    for (int i = 0; i < Width; ++i)
    {
        std::cout << "=";
    }

    std::cout << "\x1b[1E";

    for (int i = 0; i < 36; ++i)
    {
        std::cout << "\x1b[2K";
        std::cout << "=" << "\x1b[" << Width << "G" << "=";
        std::cout << "\x1b[1E";
    }


    for (int i = 0; i < UIManager::Width; ++i)
    {
        std::cout << "=";
    }

    std::cout << "\x1b[1E";

    CursorScrollSet();
    EnableStreamMarginHook();
}

void UIManager::DrawBorder()
{
    DisableStreamMarginHook();

    // 기존 스크롤 해제
    std::cout << "\x1b[r";

    // TODO:: 시작 행 정해야 함.
    std::cout << "\x1b[" << 0 << ";" << "H";

    // 바깥 외곽
    for (int i = 0; i < Width; ++i)
    {
        std::cout << "=";
    }

    std::cout << "\x1b[1E";

    for (int i = 0; i < Height; ++i)
    {
        std::cout << "=" << "\x1b[" << Width << "G" << "=";
        std::cout << "\x1b[1E";
    }


    for (int i = 0; i < UIManager::Width; ++i)
    {
        std::cout << "=";
    }

    // TODO:: 중간 선, 시작 위치 갱신되면 바꿔줘야 함.

    std::cout << "\x1b[38H";

    for (int i = 0; i < Width; ++i)
    {
        std::cout << "=";
    }

    //std::cout << "\x1b["<< StartHeight + VERTICAL + 2 <<";1H";
    std::cout << "\x1b[1E";

    CursorScrollSet();
    EnableStreamMarginHook();
}

std::string UIManager::GetUserInput(std::string message)
{
    DrawBorder();

    DisableStreamMarginHook();

    InputLineClear();

    if (message.empty())
    {
        std::cout << "입력 : ";
    }
    else
    {
        std::cout << message;
    }

    std::string input;
    std::getline(std::cin, input);

    while (input.empty())
    {
        InputLineClear();
        if (message.empty())
        {
            std::cout << RED << "[!] " << "입력해주세요." << RESET;
        }
        else
        {
            std::cout << RED << "[!] " << message << RESET;
        }

        std::getline(std::cin, input);
    }


    CursorScrollSet();
    EnableStreamMarginHook();

    return input;
}

int UIManager::GetUserInputNumber(std::string message)
{
    DisableStreamMarginHook();
    DrawBorder();

    int choice;
    while (true) {

        InputLineClear();

        if (message.empty())
        {
            std::cout << BOLD << WHITE << "입력 : " << RESET;
        }
        else
        {
            std::cout << message;
        }

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            PrintInputWarning("[!] 숫자를 입력해주세요.");

            continue;
        }
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        break;
    }

    CursorScrollSet();

    EnableStreamMarginHook();

    return choice;
}

void UIManager::GetUserInputForWait(std::string msg)
{

    DisableStreamMarginHook();
    DrawBorder();
    InputLineClear();
    std::cout << BOLD << YELLOW << "  " << RESET << msg << CYAN << "[PRESS ENTER]" << RESET;
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

    CursorScrollSet();
    EnableStreamMarginHook();
}

void UIManager::PrintInputWarning(std::string msg)
{
    InputLineClear();

    std::cout << RED << msg << RESET << "\n";

    // TODO:: 엔터가 아니라 아무키나 눌러도 넘어가게 하고싶어
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}

void UIManager::InputLineClear() const
{
    // 입력창 위치로 커서 이동
    std::cout << "\x1b[" << InputRow << ";0H";

    // 기존 입력 지우기
    std::cout << "\x1b[2K";

    std::cout << "\x1b[" << (InputRow + 1) << ";0H";
    std::cout << "\x1b[2K";

    // InputLine 시작 위치로 변경
    std::cout << "\x1b[" << InputRow << ";0H";

    std::cout << std::flush;
}

void UIManager::ClearMenuBox() const
{

    std::cout << "\x1b[" << StartMenuRow << ";H";

    for (int i = 0; i < 8; ++i)
    {
        std::cout << "\x1b[2K";
        std::cout << "=" << "\x1b[" << Width << "G" << "=";
        std::cout << "\x1b[1E";
    }

    CursorScrollSet();
}

void UIManager::PrintMenuBox(const std::vector<std::string>& menus)
{
    DisableStreamMarginHook();

    // 기존 메뉴박스 삭제함
    ClearMenuBox();

    std::cout << "\x1b[" << StartMenuRow << ";" << LeftMargin << "H";

    for (std::vector<string>::const_iterator it = menus.begin(); it != menus.end(); ++it)
    {
        if (!it->empty())
        {
            std::cout << *it;
        }
        std::cout << "\x1b[1E";
        std::cout << "\x1b[" << LeftMargin << "G";
    }


    CursorScrollSet();
    EnableStreamMarginHook();
}

void UIManager::PrintMonsterSprite(std::string monsterType, int startColumn, bool isNewLine)
{
    // 커서 좌측으로 초기화
    std::cout << "\x1b[0G";
    std::cout << "\x1b[" << startColumn << "C";

    if (monsterType == "고블린")
    {
        std::cout << "\x1b[7C";
        std::cout << "(^_^)";
        if (isNewLine)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[6C";
        std::cout << "<)   )>";
        if (isNewLine)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[7C";
        std::cout << "/   \\";
        if (isNewLine)
        {
            std::cout << std::endl;
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[6C";
        std::cout << "고블린";
    }
    else if (monsterType == "늑대")
    {
        std::cout << "\x1b[9C";
        std::cout << "(0_0)";
        if (isNewLine)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[8C";
        std::cout << "<)   )>";
        if (isNewLine)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[9C";
        std::cout << "/   \\";
        if (isNewLine)
        {
            std::cout << std::endl;
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[6C";
        std::cout << "늑대";
    }
    else if (monsterType == "오크")
    {
        std::cout << "\x1b[7C";
        std::cout << "|V_V|";
        if (isNewLine)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[6C";
        std::cout << "ㅇ(   )ㅇ";
        if (isNewLine)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[7C";
        std::cout << "//  \\";
        if (isNewLine)
        {
            std::cout << std::endl;
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[6C";
        std::cout << "오크";
    }
    else if (monsterType == "트롤")
    {
        std::cout << "\x1b[9C";
        std::cout << "^!_!^";
        if (isNewLine)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[8C";
        std::cout << ">)|)(|>";
        if (isNewLine)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[9C";
        std::cout << "/   \\";
        if (isNewLine)
        {
            std::cout << std::endl;
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[6C";
        std::cout << "트롤";
        }

}

void UIManager::PrintPlayerSprite(Player& player, int startColumn, bool isNewLine) const
{
    // 커서 좌측으로 초기화
    std::cout << "\x1b[0G";
    std::cout << "\x1b[" << startColumn << "C";

    if (player.GetJobType() == JobType::Fighter)
    {
        std::cout << "\x1b[4C";
        std::cout << "O   +=";
        if (isNewLine)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[3C";
        std::cout << "/|\\ /";
        if (isNewLine)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[3C";
        std::cout << "/ \\";
        if (isNewLine)
        {
            std::cout << std::endl;
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[6C";
    }
    else if (player.GetJobType() == JobType::Archer)
    {
        std::cout << "\x1b[2C";
        std::cout << "O  ,----.";
        if (isNewLine)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[0C";
        std::cout << "/|\\   |--- |-ㅇ";
        if (isNewLine)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[0C";
        std::cout << "/ \\ `-----'";
        if (isNewLine)
        {
            std::cout << std::endl;
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[6C";
    }
    else if (player.GetJobType() == JobType::Defender)
    {
        std::cout << "\x1b[1C";
        std::cout << " O  |######| ";
        if (isNewLine)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[0C";
        std::cout << "/|\\ |######|";
        if (isNewLine)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[0C";
        std::cout << "/ \\ |######|";
        if (isNewLine)
        {
            std::cout << std::endl;
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[6C";
    }
    else if (player.GetJobType() == JobType::Rogue)
    {
        std::cout << "\x1b[0C";
        std::cout << " O";
        if (isNewLine)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[0C";
        std::cout << "/|\\-=";
        if (isNewLine)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[0C";
        std::cout << "/ \\";
        if (isNewLine)
        {
            std::cout << std::endl;
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[0C";
    }
    else if (player.GetJobType() == JobType::Cleric)
    {
        std::cout << "   O  _|_";
        if (isNewLine)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[0C";
        std::cout << " /|\\  |";
        if (isNewLine)
        {
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[0C";
        std::cout << " / \\  |";
        if (isNewLine)
        {
            std::cout << std::endl;
            std::cout << std::endl;
        }
        else
        {
            std::cout << "\x1b[1E";
            std::cout << "\x1b[1E";
        }

        std::cout << "\x1b[0G";
        std::cout << "\x1b[" << startColumn << "C";
        std::cout << "\x1b[0C";
    }
    else // 유효하지 않은 경우임, 애초에 호출되면 아예 안됌.
    {
        
        return;
    }

    std::cout << player.GetName() << " | " << "LV : " << player.GetLevel();
}

// stream Buffer 가로채기 활성화
void UIManager::EnableStreamMarginHook() {
    if (!IsIntercepting) {
        std::cout.rdbuf(StreamBuffer);
        IsIntercepting = true;
    }
}

// cout 가로채기 해제
void UIManager::DisableStreamMarginHook()
{
    if (IsIntercepting) {
        std::cout.rdbuf(mOriginalBuffer);
        IsIntercepting = false;
    }
}



void UIManager::CreateNewScreenForStoryPrint()
{    

    std::cout << SCREEN_ALT;    

    // Story출력 위치 설정
    StreamBuffer->SetParameterCursorPos(34, 30, 0, 30);   

    // Scrolling 동작하게 처리
    StreamBuffer->SetIsScrolling(true);

    // Enter 위치 설정
    StreamBuffer->SetPressEnterPos(34, 32);


    // 스토리 시작지점으로 커서를 바꿈
    std::cout << "\x1b[30;34H";
    std::cout.flush();

    std::cout.rdbuf(StreamBuffer);

    // TODO:: 최초 문장에 대해서 버그가 있어서 넣어둔 것
    // 최초의 \n은 스크롤링이 갱신되는 줄바꿈이 안돼서 시작때 넣어버림;
    // 근데 그거하면 빈 화면에 엔터를 입력받는 상태가 되니까, 그걸 비 활성화 했다가 이후에 활성화함

    StreamBuffer->SetPressEnterWhenNewLine(false);
    std::cout << "\n";
    StreamBuffer->SetPressEnterWhenNewLine(true);

    return;
}

void UIManager::CloseAnyTempScreen()
{
    std::cout << SCREEN_MAIN;    

    // 게임할때로 복귀
    StreamBuffer->SetParameterCursorPos(LeftMargin, StartStatusRow, 3, StartStatusRow);
    StreamBuffer->SetPressEnterWhenNewLine(false);


    CursorScrollSet();

    return;
}


UIManager::UIManager()
{
    mOriginalBuffer = std::cout.rdbuf();
    StreamBuffer = new CustomStreamBuf(mOriginalBuffer);


    // TODO:: 만약에 CreateNewScreenForStoryPrint() 열고 CloseAnyTempScreen() 닫으면 초기화 됨.    

    StreamBuffer->SetParameterCursorPos(LeftMargin, StartStatusRow, 3, StartStatusRow);
    StreamBuffer->SetIsScrolling(true);
    CursorScrollSet();
}
