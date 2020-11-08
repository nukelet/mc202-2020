#include "patient.h"
#include "handle_memory_error.h"

#include <stdlib.h>

patient* patient_new()
{
	patient* NewPatient = malloc(sizeof(*NewPatient));
	handle_memory_error(NewPatient);

	NewPatient->status = FREE;

	return NewPatient;
}

void patient_destroy(patient* Obj)
{
	ps_destroy(Obj->schedule);

	free(Obj);

	return;
}