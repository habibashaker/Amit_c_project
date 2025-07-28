#include "SDB.h" 
#include "STD.h"
#include <stdio.h>
#include <stdlib.h>


student database[10];
static int studentCount = 0;

int main(){

    SDB_AddEntry();
    SDB_AddEntry();
    SDB_AddEntry();
    SDB_AddEntry();
    SDB_AddEntry();
    SDB_AddEntry();
    SDB_AddEntry();
    SDB_AddEntry();
    SDB_AddEntry();
    SDB_AddEntry();
    SDB_AddEntry();
    printf("-------------------\n");
    printf("\n%d\n",studentCount);
    printf("-------------------\n");
    printf(".......%d.......\n",SDB_GetUsedSize());
    printf((SDB_IsFull)? "Full":"Not Full");
    return 0;
}


Bool SDB_IsFull(){
    if(SDB_GetUsedSize()==10){
        return True;
    }
    return False;
}


uint8 SDB_GetUsedSize(){
    for(int i=0;i<10;i++){
        if(database[i].Student_ID == 0){
            return i;
        }
    }
    return 10;
}





Bool SDB_AddEntry(){//ID unique doesn't start with zero
        if(studentCount<10){
            int ID,year,c1_id,c1_grade,c2_id,c2_grade,c3_id,c3_grade;
            
            printf("Enter ID: \n");
                if(scanf("%d",&ID)!=1 || ID <=0){
                    printf("Invalid input for ID\n");
                    return False;
                }
                else{
                    database[studentCount].Student_ID = (uint32) ID;
                }

            printf("Enter Year: \n");
                if(scanf("%d",&year)!=1 || year<1900){
                    printf("Invalid input for Year\n");
                    return False;
                }
                else{
                database[studentCount].Student_year = (uint32) year;
            }

            printf("Enter Course1 ID: \n");
                if(scanf("%d",&c1_id)!=1 || c1_id<=0){
                    printf("Invalid input for Course1 ID\n");
                    return False;
                }
                else{
                database[studentCount].Course1_ID = (uint32) c1_id;
            }

            printf("Enter Course1 grade: \n");
            if(scanf("%d",&c1_grade) !=1 || c1_grade<0 || c1_grade>100){
                printf("Invalid input for Course1 grade\n");
                return False;
            }
            else{
                database[studentCount].Course1_grade = (uint32) c1_grade;
            }
            
            printf("Enter Course2 ID: \n");
                if(scanf("%d",&c2_id)!=1 || c2_id<=0){
                    printf("Invalid input for Course2 ID\n");
                    return False;
                }
                else{
                    database[studentCount].Course2_ID = (uint32) c2_id;
                }

            printf("Enter Course2 grade: \n");
                if(scanf("%d",&c2_grade) !=1 || c2_grade<0 || c2_grade>100){
                    printf("Invalid input for Course2 grade\n");
                    return False;
                }
                else{
                database[studentCount].Course2_grade = (uint32) c2_grade;
            }

            printf("Enter Course3 ID: \n");
                if(scanf("%d",&c3_id)!=1 || c3_id<=0){
                    printf("Invalid input for Course3 ID\n");
                    return False;
                }
                else{
                    database[studentCount].Course3_ID = (uint32) c3_id;
                }

            printf("Enter Course3 grade: \n");
                if(scanf("%d",&c3_grade) !=1 || c3_grade<0 || c3_grade>100){
                    printf("Invalid input for Course3 grade\n");
                    return False;
                }
                else{
                    database[studentCount].Course3_grade = (uint32) c3_grade;
                }

            studentCount++;
            return True;
        }

        else{
            printf("data base is full\n");
            return False;
        }
    }