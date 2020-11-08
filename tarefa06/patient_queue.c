#include <stdlib.h>

#include "patient_queue.h"
#include "handle_memory_error.h"

patient_queue* pq_new()
{
	node* DummyHead = malloc(sizeof(*DummyHead));
	handle_memory_error(DummyHead);

	DummyHead->item = NULL;

	DummyHead->previous = NULL;
	DummyHead->next = NULL;

	patient_queue* NewQueue = malloc(sizeof(*NewQueue));
	handle_memory_error(DummyHead);

	NewQueue->begin = DummyHead;

	NewQueue->back = DummyHead;

	return NewQueue; 
}

void pq_destroy(patient_queue* Obj)
{
	for (node* it = Obj->begin, *tmp; it != NULL; it = tmp)
	{
		tmp = it->next;

		// making sure not to try to free() the dummy head's
		// NULL patient pointer
		if (it != Obj->begin)
			patient_destroy(it->item);

		free(it);
	}

	free(Obj);
}

int pq_is_empty(patient_queue* Obj)
{
	if (Obj->begin->next == NULL)
		return 1;

	else
		return 0;
}

void pq_push_front(patient_queue* Obj, patient* NewItem)
{
	node* NewNode = malloc(sizeof(*NewNode));
	handle_memory_error(NewNode);

	// for push_front'ing in an empty list
	if (pq_is_empty(Obj))
		Obj->back = NewNode;

	node* front = Obj->begin->next;

	NewNode->item = NewItem;
	NewNode->previous = Obj->begin;
	NewNode->next = front;

	// insert new front patient
	Obj->begin->next = NewNode;
	
	if (front != NULL)
		front->previous = NewNode;

	return;
}

void pq_push_back(patient_queue* Obj, patient* NewItem)
{
	node* NewNode = malloc(sizeof(*NewNode));
	handle_memory_error(NewNode);

	NewNode->item = NewItem;
	NewNode->previous = Obj->back;
	NewNode->next = NULL;

	Obj->back->next = NewNode;
	
	Obj->back = NewNode;

	return;
}

patient* pq_pop_front(patient_queue* Obj)
{
	node* tmp = Obj->begin->next;

	// makes sure to reassign the back when popping the last
	// element
	if (tmp == Obj->back)
		Obj->back = Obj->begin;

	// unlink the front node
	Obj->begin->next = tmp->next;

	if (tmp->next != NULL)
		tmp->next->previous = Obj->begin;

	// copy ptr to front patient
	patient* FrontPatient = tmp->item;

	// destroy front node
	free(tmp);

	return FrontPatient;
}

patient* pq_pop_back(patient_queue* Obj)
{
	node* tmp = Obj->back;

	// unlink the back node
	tmp->previous->next = NULL;
	Obj->back = tmp->previous;

	// copy ptr to back patient
	patient* BackPatient = tmp->item;

	return BackPatient;
}
