#include <stdlib.h>
#include <stdio.h>

#include "patient_schedule.h"
#include "handle_memory_error.h"

patient_schedule* ps_new()
{
	s_node* DummyHead = malloc(sizeof(*DummyHead));
	handle_memory_error(DummyHead);

	DummyHead->item = -1;
	DummyHead->next = NULL;

	patient_schedule* NewSchedule = malloc(sizeof(*NewSchedule));
	handle_memory_error(NewSchedule);

	NewSchedule->begin = DummyHead;
	NewSchedule->back = DummyHead;

	return NewSchedule;
}

void ps_destroy(patient_schedule* Obj)
{
	for (s_node *it = Obj->begin, *tmp; it != NULL; it = tmp)
	{
		tmp = it->next;
		free(it);
	}

	free(Obj);

	return;
}

int ps_is_empty(patient_schedule* Obj)
{
	if (Obj->begin->next == NULL)
		return 1;

	else
		return 0;
}

void ps_push(patient_schedule* Obj, int NewItem)
{
	s_node* NewNode = malloc(sizeof(*NewNode));
	handle_memory_error(NewNode);

	NewNode->item = NewItem;
	NewNode->next = NULL;

	Obj->back->next = NewNode;
	Obj->back = NewNode;

	return;
}

int ps_pop(patient_schedule* Obj)
{
	s_node* tmp = Obj->begin->next;

	Obj->begin->next = tmp->next;

	int Item = tmp->item;
	free(tmp);

	return Item;
}

// for debug purposes

void ps_print(patient_schedule* Obj)
{
	printf("Queue: ");
	for (s_node* it = Obj->begin; it != NULL; it = it->next)
		printf("%d ", it->item);

	printf("\n");

	return;
}