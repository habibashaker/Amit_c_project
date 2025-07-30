#include "SDB.h" 
#include "STD.h"
#include <stdio.h>
#include <stdlib.h>

#define max_students 10


//.....................Problems........................
//program crashes when we enter letters (solved)

//When scanf fails, it does not remove the character from input buffer (It does remove data from buffer when it succeeds).
//So, the next time scanf is triggered in the loop, it will not wait for user input at all (since it has an unread character in its buffer).
//But it fails again, and again (since everytime it fails) and hence will go into an infinite loop.


uint32 studentCount = 0;
student database[10];


void clearInputBuffer(){
    int ch;
    while(getchar()!='\n' && ch != EOF);
}

Bool SDB_IsFull(){
    if(SDB_GetUsedSize()==max_students){
        return True;
    }
    return False;
}

void SDB_GetList(uint8 * count,uint32 * list){
    *count = 0;
    for(int i=0;i<studentCount;i++){
        list[*count] = database[i].Student_ID;
        (*count)++;
    }
}

uint8 SDB_GetUsedSize(){
    return studentCount;
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

Bool SDB_IsIdExist(uint32 id){
    for(int i =0;i<studentCount;i++){
        if(database[i].Student_ID == id){
            return True;
        }
    }
    return False;
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

Bool validateID(int32 id){
    if(id<=0 || SDB_IsIdExist((uint32)id)){
        printf("\nInvalid input for ID\n");
        printf("ID must be a positive integer and unique.\n");
        return False;
    }
    return True;
}

Bool validate_grade(int32 grade){
    if(grade<0 || grade>100){
        printf("\nInvalid input for grade\n");
        printf("Grade must be between 0 and 100.\n");
        return False;
    }
    return True;
}

Bool SDB_AddEntry(){//ID unique ,doesn't start with zero?
        if(studentCount<10){
            int32 ID,year,c1_id,c1_grade,c2_id,c2_grade,c3_id,c3_grade;
            
            printf("Enter ID: \n");
            scanf("%d",&ID);
            if(!validateID(ID)){
                clearInputBuffer();
                return False;
                }
            database[studentCount].Student_ID = (uint32) ID;

            printf("Enter Year: \n");
                if(scanf("%d",&year)!=1 || year<1900){
                    clearInputBuffer();
                    printf("\nInvalid input for Year\n");
                    return False;
            }
            database[studentCount].Student_year = (uint32) year;

            printf("Enter Course1 ID: \n");
                if(scanf("%d",&c1_id)!=1 || c1_id<=0){
                    clearInputBuffer();
                    printf("Invalid input for Course1 ID\n");
                    return False;
                }
                database[studentCount].Course1_ID = (uint32) c1_id;
            

            printf("Enter Course1 grade: \n");
            scanf("%d",&c1_grade);
            if(!validate_grade(c1_grade)){
                clearInputBuffer();
                return False;
            }
            database[studentCount].Course1_grade = (uint32) c1_grade;
            
            
            printf("Enter Course2 ID: \n");
                if(scanf("%d",&c2_id)!=1 || c2_id<=0){
                    clearInputBuffer();
                    printf("Invalid input for Course2 ID\n");
                    return False;
                }
                
                database[studentCount].Course2_ID = (uint32) c2_id;
        

            printf("Enter Course2 grade: \n");
            scanf("%d",&c2_grade);
                if(!validate_grade(c2_grade)){
                    clearInputBuffer();
                    return False;
                }
                database[studentCount].Course2_grade = (uint32) c2_grade;

            printf("Enter Course3 ID: \n");
                if(scanf("%d",&c3_id)!=1 || c3_id<=0){
                    clearInputBuffer();
                    printf("Invalid input for Course3 ID\n");
                    return False;
                }
                    database[studentCount].Course3_ID = (uint32) c3_id;
                

            printf("Enter Course3 grade: \n");
                if(scanf("%d",&c3_grade) !=1 || !validate_grade(c3_grade)){
                    return False;
                }
                database[studentCount].Course3_grade = (uint32) c3_grade;
               

            studentCount++;
            return True;
        }

        else{
            printf("\ndata base is full\n");
            return False;
        }
    }