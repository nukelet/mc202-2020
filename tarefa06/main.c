#include "patient_queue.h"
#include "patient.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int patient_parse(patient* Obj)
{
	if (scanf("\"%[^\"]\" ", Obj->name) == EOF)
		return 0; 

	char tmp[20]; scanf("%s ", tmp);

	if (strcmp(tmp, "normal") == 0)
		Obj->priority = NORMAL;

	else if (strcmp(tmp, "preferencial") == 0)
		Obj->priority = PRIORITARY;

	// parse schedule

	Obj->schedule = ps_new();

	int t;

	// initializing this variable to prevent a potential 
	// conditional jump error in valgrind when a patient's
	// schedule has only one number to be read (and thus
	// no character is assigned to "c" since scanf reaches
	// EOF right after reading the int)
	char c = '0';

	while (scanf("%d%c", &t, &c) != EOF)
	{
		ps_push(Obj->schedule, t);
	
		if (c == '\n')
			break;
	}

	return 1;
}

void patient_print(patient* P)
{
	printf("name: %s\npriority: %d\nstatus: %d\n", P->name, P->priority, P->status);

	ps_print(P->schedule);

	return;
}

void patient_queue_parse(patient_queue* Obj)
{
	while(1)
	{
		patient* P = patient_new();

		if (patient_parse(P) == 0)
		{
			free(P);
			break;
		}

		pq_push_back(Obj, P);
	}

	return;
}

void pq_print(patient_queue* S)
{
	for (node* it = S->begin->next; it != NULL; it = it->next)
		patient_print(it->item);

	printf("----------------\n");

	return;
}

void time_print(int hour, int minute)
{
	if (hour < 10)
		printf("0%d:%d ", hour, minute);
	else if (hour > 9)
		printf("%d:%d ", hour, minute);
}

int main(int argc, char const *argv[])
{
	patient_queue* S = pq_new();
	int limit[11] = { 0 , 10, 2, 5, 3, 4, 7, 2, 1, 4 };

	patient_queue_parse(S);
	
	patient_queue* hospital[11];

	for (int i = 1; i < 11; i++)
	{
		hospital[i] = pq_new();
	}

	int hour = 8, minute = 0;

	while(1)
	{
		// update time
		minute += 10;
		int carry = minute/60;

		minute %= 60;
		hour += carry;

		int flag = 0;

		for (node* it = S->begin->next; it != NULL; it = it->next)
		{
			patient* P = it->item;

			if (P->status == FREE && !ps_is_empty(P->schedule))
			{
				int consultation = ps_pop(P->schedule);
				flag = 1;

				if (P->priority == NORMAL)
					pq_push_back(hospital[consultation], P);

				else if (P->priority == PRIORITARY)
					pq_push_front(hospital[consultation], P);

				P->status = WAITING;
			}
		}

		for (int i = 1; i < 11; i++)
		{
			for (int j = 0; j < limit[i]; j++)
			{
				if (!pq_is_empty(hospital[i]))
				{
					flag = 1;

					patient* P = pq_pop_front(hospital[i]);
					P->status = FREE;

					// patient_print(P);

					if (ps_is_empty(P->schedule))
						printf("%02d:%02d %s\n", hour, minute, P->name);
				}
			}
		}

		// break conditional for when all patient schedules are
		// empty and there are no patients in any of the consultation
		// queues
		if (flag == 0)
			break;
	}

	for (int i = 1; i < 11; i++)
	{
		for (node* it = hospital[i]->begin, *tmp; it != NULL; it = tmp)
		{
			tmp = it->next;
			free(it);
		}

		free(hospital[i]);
	}

	pq_destroy(S);
	
	return 0;
}