#ifndef PATIENT_SCHEDULE
#define PATIENT_SCHEDULE

typedef struct s_node_
{
	int item;
	struct s_node_* next;
} s_node;

typedef struct patient_schedule_
{
	s_node* begin;

	s_node* back;
} patient_schedule;

patient_schedule* ps_new();
void ps_destroy(patient_schedule* Obj);

int ps_is_empty(patient_schedule* Obj);

void ps_push(patient_schedule* Obj, int NewItem);
int ps_pop(patient_schedule* Obj);

// for debug purposes
void ps_print(patient_schedule* Obj);

#endif