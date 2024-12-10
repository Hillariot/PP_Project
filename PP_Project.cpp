#include "lib/interface_design.h"
#include "lib/logic.h"
#include "lib/registration.h"
#include <iostream>
#include <string>

using namespace std;



int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	registrate("loginsdada ", "passwordsdadas", "base.txt");
	
	system("pause");
	return 0;
}