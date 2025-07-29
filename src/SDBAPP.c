#include "SDB.h" 
#include "STD.h"
#include <stdio.h>
#include <stdlib.h>

void SDB_APP(){
    uint8 choice;
    do{
        printf("\n--------------------\n");
        
        printf("To add entry,enter 1\n");
        printf("To get used size in database,enter 2\n");
        printf("To read student data,enter 3\n");
        printf("To get list of all student IDs,enter 4\n");
        printf("To check if ID exists,enter 5\n");
        printf("To delete student data,enter 6\n");
        printf("To check if database is full,enter 7\n");
        printf("To exit,enter 0\n");
        
        printf("--------------------\n");
        printf("\nEnter your choice: \n");
        scanf("%u", &choice);
        SDB_action(choice);
    }

    while(choice != 0);
}

void SDB_action(uint8 choice){
    switch(choice){
        case 1:
            if(SDB_AddEntry()){
                printf("\nEntry added successfully.\n");
            } else {
                printf("\nFailed to add entry.\n");
            }
            break;
        case 2:
            printf("\nUsed size in database: %u\n", SDB_GetUsedSize());
            break;
        case 3: {
            uint32 id;
            printf("\nEnter Student ID to read data: \n");
            scanf("%u", &id);
            if(SDB_ReadEntry(id)){
                printf("\nData read successfully.\n");
            } else {
                printf("\nFailed to read data for ID %u.\n", id);
            }
            break;
        }
        case 4: {
            uint8 count;
            uint32 list[10]; // Assuming max 10 students
            SDB_GetList(&count, list);
            printf("List of student IDs:\n");
            for(int i = 0; i < count; i++){
                printf("%u\n", list[i]);
            }
            break;
        }
        case 5: {
            uint32 id;
            printf("Enter Student ID to check existence: \n");
            scanf("%u", &id);
            if(SDB_IsIdExist(id)){
                printf("ID %u exists in the database.\n", id);
            } else {
                printf("ID %u does not exist in the database.\n", id);
            }
            break;
        }
        case 6: {
            uint32 id;
            printf("Enter Student ID to delete data: \n");
            scanf("%u", &id);
            SDB_DeleteEntry(id);
            break;
        }
        case 7: {
            if(SDB_IsFull()){
                printf("Database is full.\n");
            } else {
                printf("Database is not full.\n");
            }
            break;
        }
        case 0:
            printf("Exiting the application.\n");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
    }
}
