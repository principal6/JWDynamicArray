#include "JWDynamicArray.h"

using namespace JWEngine;

int main()
{
	JWDynamicArray<int> my_da;

	my_da.push_back(1);
	my_da.push_back(3);
	my_da.push_back(5);
	my_da.push_back(7);
	my_da.pop_back();
	my_da.push_back(9);
	my_da.pop_back();
	my_da.empty();
	my_da.push_back(11);
	my_da.clear();

	return 0;
}