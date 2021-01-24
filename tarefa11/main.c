#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "safe_allocators.h"

typedef struct item_t_ 
{
	float x;
	float y; 
	int is_lugia;
} item_t;

typedef struct list_
{
	item_t* item;
	struct list_* next;
} list;

item_t* item_new(float x, float y, int is_lugia)
{
	item_t* new = safe_malloc(sizeof(*new));
	
	new->x = x;
	new->y = y;
	new->is_lugia = is_lugia;

	return new;
}

void item_destroy(item_t* item)
{
	free(item);
}

list* l_new(item_t* item)
{
	list* p = safe_malloc(sizeof(*p));
	
	p->item = item;
	p->next = NULL;

	return p;
}

void l_destroy(list* p)
{
	list* next;

	while (p != NULL)
	{
		next = p->next;

		item_destroy(p->item);
		free(p);
		
		p = next;
	}
}

void l_append(list* p, item_t* item)
{
	list* new = l_new(item);

	while (p->next != NULL) {p = p->next;}

	p->next = new;
}

// note: the array needs to be free'd
// int* l_to_array(list* p)
// {
// 	if (p == NULL)
// 	{
// 		fprintf(stderr, "Illegal conversion from NULL list to array; exiting...\n");
// 		exit(1);
// 	}

// 	int size = 0;

// 	for (list* it = p; it != NULL; it = it->next) size++;

// 	int* v = safe_malloc(size*sizeof(int));
// 	int* v_it = v;

// 	for (list* it = p; it != NULL; it = it->next)
// 	{
// 		*v_it = it->item;
// 		v_it++;
// 	}

// 	return v;
// }

float dist(float x1, float y1, float x2, float y2)
{
	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int dfs(int point, float** dist, int* lugia, int* visited, int size, float max)
{
	visited[point] = 1;

	for (int i = 0; i < size; i++)
	{
		if (!visited[i] && dist[i][point] < max)
		{
			if (lugia[i])
				return 1;

			visited[i] = 1;
			if (dfs(i, dist, lugia, visited, size, max))
				return 1;
		}
	}

	return 0;
}

int main(int argc, char const *argv[])
{
	// parse info about the points

	// read the starting point
	float x, y; scanf("%f %f", &x, &y);
	int is_lugia;
	char buf[10];
	
	// initialize list with the first point	
	list* points = l_new(item_new(x, y, 0));

	while (scanf("%f %f %s", &x, &y, buf) == 3)
	{
		is_lugia = strcmp(buf, "pokestop\0") ? 1 : 0;
		item_t* new = item_new(x, y, is_lugia);
		l_append(points, new);
	}

	// for (list* it = points; it != NULL; it = it->next)
		// printf("%f %f %s\n", it->item->x, it->item->y, it->item->is_lugia ? "Lugia\0" : "pokestop\0");

	int size = 0;

	// get the list size
	for (list* it = points; it != NULL; it = it->next)
		size++;

	// printf("size: %d\n", size);

	// allocates a matrix to store the distance between i and j
	// in distances[i][j]
	float** distances = safe_malloc(size*sizeof(*distances));

	for (int i = 0; i < size; i++)
		distances[i] = safe_malloc(size*sizeof(**distances));

	// is_lugia[i] == 1 means that the stop has a lugia
	int* lugia = safe_malloc(size*sizeof(is_lugia));
	
	list *it_i, *it_j;
	int i, j;
	
	// fill the matrix with the distances between points
	for (i = 0, it_i = points; i < size; i++, it_i = it_i->next)
	{
		lugia[i] = it_i->item->is_lugia;

		for (j = i, it_j = it_i; j < size; j++, it_j = it_j->next)
		{
			distances[i][j] = distances[j][i] = dist(it_i->item->x, it_i->item->y, it_j->item->x, it_j->item->y);
		}
	}

	// for (int i = 0; i < size; i++)
	// {
	// 	for (int j = 0; j < size; j++)
	// 	{
	// 		printf("%.2f ", distances[i][j]);
	// 	}

	// 	printf("\n");
	// }

	// for (int i = 0; i < size; i++)
	// 	printf("%d: %s\n", i, lugia[i] ? "Lugia\0" : "pokestop\0");

	float min = 0, max = 0, mid = 0;

	// get max distance between points
	for (int i = 0; i < size-1; i++)
	{
		for (int j = i+1; j < size; j++)
		{
			if (distances[i][j] > max)
				max = distances[i][j];			
		}
	}

	int* visited = calloc(size, sizeof(int));

	// run a "binary search" for the upper bound to
	// the max dist
	while ((int) min != (int) max)
	{
		mid = 0.5*(max+min);
		// printf("min: %f; mid: %f; max: %f\n", min, mid, max);
		
		if (dfs(0, distances, lugia, visited, size, mid))
			max = mid;
	
		else
			min = mid;

		// clean up the array
		for (int i = 0; i < size; i++)
			visited[i] = 0;
	}

	printf("%d\n", (int) max+1);

	l_destroy(points);

	for (int i = 0; i < size; i++)
		free(distances[i]);
	free(distances);

	free(lugia);
	free(visited);

	return 0;
}