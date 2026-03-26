#include "None.h"
#include <iostream>

using namespace std;


None::None()
	:Action("None", TargetType::MYSELF)
{


}

void None::PrintInfo()
{
	cout << "아무런 효과가 없습니다." << endl;

}
