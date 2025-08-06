#pragma once
#include "STD.h"

typedef struct SimpleDb
{
    uint32 Student_ID;
    uint32 Student_year;
    uint32 Course1_ID;
    uint32 Course1_grade;
    uint32 Course2_ID;
    uint32 Course2_grade;
    uint32 Course3_ID;
    uint32 Course3_grade;
}student;

extern uint32 studentCount;

Bool SDB_IsFull();
uint8 SDB_GetUsedSize();
Bool SDB_AddEntry();
void SDB_DeleteEntry(uint32 id);
Bool SDB_ReadEntry(uint32 id);
void SDB_GetList(uint8 * count,uint32 * list);
Bool SDB_IsIdExist(uint32 id);


void clearInputBuffer();
Bool validate_Integer(int32 id);
Bool validate_grade(int32 grade);
Bool validate_year(int32 year);
Bool CourseIDExist(int32 id, int32 courseId[], int count);
Bool getInput(const char * msg, int32 *value, Bool (*validator)(int32));


void SDB_APP();
void SDB_action(uint8 choice);