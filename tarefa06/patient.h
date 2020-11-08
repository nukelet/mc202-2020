#ifndef PATIENT
#define PATIENT

#include "patient_schedule.h"

typedef enum patient_priority_
{
	NORMAL,
	PRIORITARY
} patient_priority;

typedef enum patient_status_ 
{ 
	WAITING, 
	FREE
} patient_status;

typedef struct patient_
{
	char name[51];
	patient_priority priority;
	patient_schedule* schedule;  
	
	patient_status status;
} patient;

patient* patient_new();
void patient_destroy(patient* Obj);

#endif