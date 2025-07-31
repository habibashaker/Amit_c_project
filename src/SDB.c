#include "SDB.h" 
#include "STD.h"
#include <stdio.h>
#include <stdlib.h>

#define max_students 10


uint32 studentCount = 0;
student database[10];


//helping functions

/*
this function clears input buffer so when user enters a letter instead of integer program doesn't crash .
When scanf fails, it does not remove the character from input buffer (It does remove data from buffer when it succeeds).
So, the next time scanf is triggered in the loop, it will not wait for user input at all (since it has an unread character in its buffer).
But it fails again, and again (since everytime it fails) and hence will go into an infinite loop.
*/
void clearInputBuffer(){
    int ch;
    while(getchar()!='\n' && ch != EOF);
}

//make sure input is not negative
Bool validate_ID(int32 id){
    if(id<=0){
        return False;
    }
    return True;
}

//limit grade 0 to 100
Bool validate_grade(int32 grade){
    if(grade<0 || grade>100){
        printf("\nInvalid input for grade\n");
        printf("Grade must be between 0 and 100.\n");
        return False;
    }
    return True;
}

//make sure that user doesn't enter same id for diff courses
Bool IsCourseIDExist(int32 id, int32 courseId[], int count){
    for(int i = 0;i<count;i++){
        if(courseId[i] == id){
            return True;
        }
    }
    return False;

}

Bool readInt(int32* value);

//----------------------------------------------------------------------------------------------------------------------------------------------


//user functions
Bool SDB_AddEntry(){
    if(SDB_IsFull()){
        printf("Database is Full.\n");
        return False;
    }
    student newStud;

    int32 ID;
    printf("Enter ID: \n");
        scanf("%d",&ID);
        if(!validate_ID(ID)|| SDB_IsIdExist((uint32)ID)){
            printf("\nInvalid input for ID\n");
            printf("ID must be a positive integer and unique. \n");
            clearInputBuffer();
            return False;
        }
    newStud.Student_ID = (uint32) ID;
    
    uint32 year;
    printf("Enter Year: \n");
        if(scanf("%d",&year)!=1 || year<1900){
            clearInputBuffer();
            printf("\nInvalid input for Year\n");
            return False;
        }
    newStud.Student_year =  year;
    
    int courseID[3];
    int courseGrade[3];
    for(int i =0;i<3;i++){

        printf("Enter Course %d ID: \n",i+1);
        scanf("%d",&courseID[i]);
        if(!validate_ID(courseID[i]) || IsCourseIDExist(courseID[i],courseID,i)){
            printf("\nInvalid input for Course ID\n");
            printf("Course ID must be a positive integer. \n");
            clearInputBuffer();
            return False;
        }

        printf("Enter Course %d grade: \n",i+1);
        scanf("%d",&courseGrade[i]);
        if(!validate_grade(courseGrade[i])){
            clearInputBuffer();
            return False;
        }
    }
    newStud.Course1_ID = courseID[0];  newStud.Course1_grade = courseGrade[0];
    newStud.Course2_ID = courseID[1];  newStud.Course2_grade = courseGrade[1];
    newStud.Course3_ID = courseID[2];  newStud.Course3_grade = courseGrade[2];

    database[studentCount] = newStud;
    studentCount++;
    return True;
}

Bool SDB_IsIdExist(uint32 id){
    for(int i =0;i<studentCount;i++){
        if(database[i].Student_ID == id){
            return True;
        }
    }
    return False;
}

Bool SDB_IsFull(){
    return studentCount>=max_students;
}

uint8 SDB_GetUsedSize(){
    return (uint8) studentCount;
}

void SDB_GetList(uint8 * count,uint32 * list){
    *count = 0;
    for(int i=0;i<studentCount;i++){
        list[*count] = database[i].Student_ID;
        (*count)++;
    }
}

void SDB_DeleteEntry(uint32 id){
    if(!SDB_IsIdExist(id)){
        printf("Student with ID %u not found.\n",id);
    }
    for(int i=0;i<studentCount;i++){
        if(database[i].Student_ID == id){
            for(int j = i;j<studentCount-1;j++){
                database[j] = database[j+1];
            }
            database[studentCount-1] = (student) {0};

            studentCount--;
        }
    }   
}

Bool SDB_ReadEntry(uint32 id){
    if(!SDB_IsIdExist(id)){
        printf("Student with ID %u not found.\n",id);
        return False;
    }
    for(int i=0;i<studentCount;i++){
        if(database[i].Student_ID == id){
            printf("Student ID: %u\nStudent Year: %u\n",database[i].Student_ID,database[i].Student_year);
            printf("Course1 ID: %u, Grade: %u\n",database[i].Course1_ID,database[i].Course1_grade);
            printf("Course2 ID: %u, Grade: %u\n",database[i].Course2_ID,database[i].Course2_grade);
            printf("Course3 ID: %u, Grade: %u\n",database[i].Course3_ID,database[i].Course3_grade);
            return True;
        }
    }

}

