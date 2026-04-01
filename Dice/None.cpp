#include "None.h"
#include <iostream>

using namespace std;

#include "Character.h"

None::None()
	:Action("None", TargetType::MYSELF)
{


}

void None::PrintInfo()
{
	cout << "아무런 효과가 없습니다." << endl;

}

void None::DoActive()
{
    string selfnames = "";

    // 공격자 이름 추출
    for (int i = 0; i < vecself.size(); ++i)
    {
        selfnames += vecself[i]->GetName();

        if (i < vecself.size() - 1)
            selfnames += ", ";
    }


    cout << selfnames <<"은/는 농땡이를 피우는 것 같다..." << endl;
}
