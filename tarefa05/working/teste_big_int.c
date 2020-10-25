#include "big_int.h"
#include <stdio.h>

int main(int argc, char const *argv[])
{
	big_int *MyBigInt = create_big_int(0);

	for (int i = 1; i < 10; i++)
	{
		append_to_last(MyBigInt, i);
	}

	node *it;
	for (it = MyBigInt->last; it != MyBigInt->first; it = it->previous)
		printf("%d", it->digit);

	printf("%d\n", it->digit);

	destroy_big_int(MyBigInt);

	return 0;
}