#include "big_int.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int number_operations; scanf("%d", &number_operations);

	for (int i = 0; i < number_operations; i++)
	{
		char operation; scanf(" %c", &operation); // printf("read: %c\n", operation);
		big_int *A = create_big_int();
		big_int *B = create_big_int();

		char buffer_a[50], buffer_b[50];
		scanf("%s %s", buffer_a, buffer_b);

		string_to_big_int(buffer_a, strlen(buffer_a), A);
		string_to_big_int(buffer_b, strlen(buffer_b), B);

		big_int* result;

		switch (operation)
		{
			case '+':
				result = add(A, B);
				break;

			case '-':
				result = subtract(A, B);
				break;

			case '*':
				result = multiply(A, B);
				break;

			case '/':
				result = divide(A, B);
				break;

			default:
				printf("Invalid operation\n");
		}

		print_big_int(result);
		destroy_big_int(result);
	}

	return 0;
}