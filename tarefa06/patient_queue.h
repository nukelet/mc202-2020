#ifndef PATIENT_QUEUE
#define PATIENT_QUEUE

#include "patient.h"

typedef struct node_
{
	patient* item;

	struct node_* previous;
	struct node_* next;

} node;

typedef struct patient_queue_
{
	node* begin;
	node* back;
} patient_queue;

patient_queue* pq_new();
void pq_destroy(patient_queue* Obj);

int pq_is_empty(patient_queue* Obj);

void pq_push_front(patient_queue* Obj, patient* NewItem);
void pq_push_back(patient_queue* Obj, patient* NewItem);
patient* pq_pop_front(patient_queue* Obj);
patient* pq_pop_back(patient_queue* Obj);


#endif