#include "SDB.h" 
#include "STD.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * @brief 
 * This function is the main application loop for the Student Database (SDB).
 * It provides a menu for the user to interact with the database, allowing them to add entries, check the size, 
 * read student data, get a list of student IDs, check if an ID exists, delete student data, and check if the database is full.
 * The loop continues until the user chooses to exit by entering 0.
 */
void SDB_APP(){
    int32 choice;
    while(1){
        printf("--------------------\n");
        
        printf("To add entry,enter 1\n");
        printf("To get used size in database,enter 2\n");
        printf("To read student data,enter 3\n");
        printf("To get list of all student IDs,enter 4\n");
        printf("To check if ID exists,enter 5\n");
        printf("To delete student data,enter 6\n");
        printf("To check if database is full,enter 7\n");
        printf("To exit,enter 0\n");
        
        printf("--------------------\n");
        
        if(!getInput("Enter your choice: \n", &choice, validate_Integer)){
            printf("\nInvalid input. Please enter a valid choice.\n\n");
            continue;
        }
        if(choice ==0){
            printf("\nExiting...\n");
            break;
        }

        SDB_action((uint8) choice);
        printf("\n");
    }
}

/**
 * @brief This function performs an action based on the user's choice.
 *
 * @param choice 
 */
void SDB_action(uint8 choice){
        if (studentCount < 3 && choice > 2 && choice < 8) {
                printf("\nAt least 3 students are required to perform this action.\n");
                return;
        }
        switch(choice){
            case 1:
                if(SDB_AddEntry()){
                    printf("\nEntry added successfully.\n");
                } 
                else {
                    printf("\nFailed to add entry.\n");
                }
                break;
            case 2:
                printf("\nUsed size in database: %u\n", SDB_GetUsedSize());
                break;
            
            case 3: {
                int32 id;
                if(!getInput("Enter Student ID to read data: \n", &id, validate_Integer)){
                    printf("\nInvalid input for Student ID\n");
                    return;
                }

                if(SDB_ReadEntry((uint32) id)){
                    printf("\nData read successfully.\n");
                } 
                // else {
                //     printf("\nFailed to read data for ID %u.\n", id);
                // }
                break;
            }
            
            case 4: {
                uint8 count = 0;
                uint32 list[10]; 
                SDB_GetList(&count, list);

                printf("\nList of student IDs:\n");
                for(int i = 0; i < count; i++){
                    printf("Student %d: %u\n", i+1, list[i]);
                }
                break;
            }
            case 5:{
                int32 id;
                if(!getInput("Enter Student ID to check existence: \n", &id, validate_Integer)){
                    printf("\nInvalid input for Student ID\n");
                    return;
                }
                if(SDB_IsIdExist((uint32) id)){
                    printf("\nID %u exists in the database.\n", id);
                } else {
                    printf("ID %u does not exist in the database.\n", id);
                }
                break;
            }
            case 6: {
                int32 id;
                if(!getInput("Enter Student ID to delete data: \n", &id, validate_Integer)){
                    printf("\nInvalid input for Student ID\n");
                    return;
                }
                SDB_DeleteEntry((uint32) id);
                break;
            }
            
            case 7: 
                if(SDB_IsFull()){
                    printf("\nDatabase is full.\n");
                } else {
                    printf("\nDatabase is not full.\n");
                }
                break;
        
            default:
                clearInputBuffer();
                printf("\nInvalid choice. Please try again.\n");
                break;
         
        }

}