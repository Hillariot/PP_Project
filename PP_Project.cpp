#include "lib/interface_design.h"
#include "lib/logic.h"

#include <random>
#include <iostream>

using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	vector<vector<int>> v;
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 2); // distribution in range [1, 6]

	for (int i = 0; i < 9; i++)
	{
		vector<int> tmp;
		for (int j = 0; j < i * 4; j++)
		{
			tmp.push_back(dist6(rng));
		}
		v.push_back(tmp);
		tmp.clear();
	}
	
	print_cinemahall(v);
	system("pause");
	return 0;
}