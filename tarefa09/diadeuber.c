#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "priority_queue.h"

#define CAR_RENT_FEE 57.00
#define CAR_KM_PER_L 10.0
#define GAS_COST_PER_L 4.104

#define UBERX_EARNINGS_FEE_FACTOR 0.25
#define UBERX_CANCELLATION_REFUND 7.0
#define UBERX_EARNINGS_PER_KM 1.40

// in a max heap, we must have
// compare(t, t_parent) == 1 whenever
// t->rating < t_parent->rating and 0 otherwise
int is_leq(Item* a, Item* b)
{
	// the "<=" makes sure that is_leq(a, a) == 1
	if (a->rating <= b->rating)
		return 1;

	else
		return 0;
}

// for debug purposes
void pq_print(priority_queue* p)
{
	printf("----------------\n");

	for (Item** it = p->heap; *it != NULL; it++)
	{
		printf("name:%s\nrating: %f\norigin: %d, %d\ndestination: %d, %d\n",
			(*it)->name,
			(*it)->rating,
			(*it)->origin_x, (*it)->origin_y,
			(*it)->destination_x, (*it)->destination_y);
	}

	printf("----------------\n");
}

// parses info from stdin into an Item object
Item* item_parse()
{
	char str[16];
	double rating;
	int dest_x, dest_y, orig_x, orig_y;
	scanf(" %s %lf %d %d %d %d", str, &rating, &dest_x, &dest_y, &orig_x, &orig_y);
	// printf("%s %f %d %d %d %d\n", str, rating, dest_x, dest_y, orig_x, orig_y);
	Item* t = item_new(str, rating, dest_x, dest_y, orig_x, orig_y);
	
	return t;
}

// manhattan distance
int distance(int x1, int y1, int x2, int y2)
{
	return abs(x1-x2) + abs(y1-y2);
}

int main(int argc, char const *argv[])
{
	// creates a max heap with capacity for 250 clients,
	// since there are at most 500 operations and there
	// are exactly 2 operations per client (A/F or A/C)
	priority_queue* p = pq_new(250, &is_leq);

	char c;
	char buf[16];

	Item *tmp, *current = NULL;

	int total_ride_km = 0, total_between_rides_km = 0, total_refunds = 0;

	// keeps track of the driver's current coordinates
	int x = 0, y = 0;

	while (1)
	{
		scanf("%c", &c);

		if (c == 'T')
			break;

		switch (c)
		{
			case 'A':
				tmp = item_parse();
				printf("Cliente %s foi adicionado(a)\n", tmp->name);

				if (current == NULL)
					current = tmp;

				else
					pq_insert(p, tmp);

				break;

			case 'F':
				printf("A corrida de %s foi finalizada\n", current->name);

				total_between_rides_km += distance(x, y, current->origin_x, current->origin_y);

				total_ride_km += distance(current->origin_x, current->origin_y,
									 current->destination_x, current->destination_y);

				// update current driver location
				x = current->destination_x;
				y = current->destination_y;

				free(current);

				// makes sure not to pop in an empty queue
				if (!pq_is_empty(p))
					current = pq_pop(p);

				else
					current = NULL;
				
				break;

			case 'C':
				scanf(" %s", buf);
				printf("%s cancelou a corrida\n", buf);

				total_refunds += UBERX_CANCELLATION_REFUND;

				tmp = pq_delete(p, pq_find_by_name(p, buf));
				free(tmp);
				break;
		}

	}

	int total_km = total_ride_km + total_between_rides_km;

	double gross_income = total_ride_km * UBERX_EARNINGS_PER_KM + total_refunds;

	double expenses = CAR_RENT_FEE + (total_km/ CAR_KM_PER_L) * GAS_COST_PER_L;
	double net_income = gross_income * (1 - UBERX_EARNINGS_FEE_FACTOR) - expenses;

	printf("\nJornada finalizada. Aqui esta o seu rendimento de hoje\n");
	printf("Km total: %d\n", total_km);
	printf("Rendimento bruto: %.2lf\n", gross_income);
	printf("Despesas: %.2lf\n", expenses);
	printf("Rendimento liquido: %.2lf\n", net_income);
	
	pq_destroy(p);
	
	return 0;
}