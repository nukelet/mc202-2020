#include <stdio.h>
#include <stdlib.h>

// returns: 1 if keyword is found starting at the given index, 0 otherwise
int recursive_search(char* str, /*int size_str,*/ int index_str, char** text, int size_rows, int size_columns, int index_row, int index_column, int** used_positions)
{

	// returns 1 if it has reached the end of the string; stopping condition for the recursion
	if (str[index_str] == '\0')
		return 1;

	// returns 0 if target is off-limits in the text; stopping condition for the recursion
	if (index_column < 0 || index_column > size_columns - 1 || index_row < 0 || index_row > size_rows - 1)
		return 0;
	
	// returns 0 if target is not equal to the char in the current index of str; stopping condition for the recursion
	if (text[index_row][index_column] != str[index_str])
		return 0;

	// returns 0 if letter at current index has been used before in this recursive search; stopping condition for recursion
	if (used_positions[index_row][index_column] == 1)
		return 0;

	// marks the letter at current index as used
	used_positions[index_row][index_column] = 1;

	// if current target letter matches the currently indexed char in str, looks for the next char among the neighbors
	if ( recursive_search(str, index_str+1, text, size_rows, size_columns, index_row-1, index_column, used_positions) ||
		 recursive_search(str, index_str+1, text, size_rows, size_columns, index_row+1, index_column, used_positions) ||
		 recursive_search(str, index_str+1, text, size_rows, size_columns, index_row, index_column-1, used_positions) ||
		 recursive_search(str, index_str+1, text, size_rows, size_columns, index_row, index_column+1, used_positions)	)
		return 1;

	else
	{
		// backtracks and marks letter at current index as unused
		used_positions[index_row][index_column] = 0;
		return 0;
	}
}

void search_routine(char* str, char** text, int size_rows, int size_columns)
{
	// flags whether the word has been found or not
	int flag = 0;

	// initialize the binary matrix that stores whether a character has been used
	// used_positions[i][j] == 1 if text[i][j] has been used and == 0 otherwise
	int **used_positions = malloc(size_rows*sizeof(int*));

	if (used_positions == NULL)
	{
		fprintf(stderr, "INSUFFICIENT MEMORY\n"); exit(1);
	}

	for (int i = 0; i < size_rows; i++)
	{
		used_positions[i] = calloc(size_columns, sizeof(int));
	
		if (used_positions[i] == NULL)
		{
			fprintf(stderr, "INSUFFICIENT MEMORY\n"); exit(1);
		}
	}

	for (int i = 0; i < size_rows && flag == 0; i++)
		for (int j = 0; j < size_columns; j++)
			if (recursive_search(str, 0, text, size_rows, size_columns, i, j, used_positions))
				{ 
					printf("sim\n"); flag = 1; break;
				}

	if (flag == 0)
		printf("nao\n");

	// free the binary matrix
	for (int i = 0; i < size_rows; i++)
		free(used_positions[i]);
	free(used_positions);
}

// allocate a character matrix for the text, read it from stdin and return a pointer to it
char** parse_text(int size_rows, int size_columns)
{
	char **text = malloc(size_rows*sizeof(char*));

	if (text == NULL)
	{
		fprintf(stderr, "INSUFFICIENT MEMORY\n"); exit(1);
	}

	for (int i = 0; i < size_rows; i++)
	{
		text[i] = malloc(size_columns*sizeof(char));
		if (text[i] == NULL)
		{
			fprintf(stderr, "INSUFFICIENT MEMORY\n"); exit(1);
		}
	}

	for (int i = 0; i < size_rows; i++)
		for (int j = 0; j < size_columns; j++)
			scanf(" %c", &text[i][j]);

	return text;
}

// deallocate the text matrix
void destroy_text(char** text, int size_rows, int size_columns)
{
	for (int i = 0; i < size_rows; i++)
		free(text[i]);

	free(text);
}

int main(int argc, char const *argv[])
{
	int size_rows, size_columns, number_searches;

	scanf("%d %d %d", &size_rows, &size_columns, &number_searches);

	char** text = parse_text(size_rows, size_columns);

	for (int num = 0; num < number_searches; num++)
	{
		char str[25]; scanf("%s", str);

		search_routine(str, text, size_rows, size_columns);
	}

	destroy_text(text, size_rows, size_columns);

	return 0;
}