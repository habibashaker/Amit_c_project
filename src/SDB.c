#include "SDB.h" 
#include "STD.h"
#include <stdio.h>
#include <stdlib.h>

#define max_students 10


uint32 studentCount = 0;
student database[10];


//helping functions



/**
 * @brief Clears input buffer so when user enters invalid input program doesn't crash.
 * 
 * @note This function is necessary because when scanf fails (for example: user types a letter instead of a number)
 * it doesn't clear the invalid input. If we don’t clear the buffer, the next scanf will keep failing, 
 * creating an infinite loop. This ensures reliable input handling. 
 * 
 * @note why i implemented this function this way? 
 * get char is used to read characters from the input buffer until a newline character is encountered.
 * EOF is used to check if the end of the file has been reached, which can happen if the input stream is closed or if there is an error.
 * 
 */
void clearInputBuffer(){
    int ch;
    while((ch = getchar()) != '\n' && ch != EOF);
}


/**
 * @brief Checks input negative or not
 * @param id Student ID
 * @return Bool (false if negative true if positive)
 */
Bool validate_Integer(int32 id){
    if(id<0){
        return False;
    }
    return True;
}

/**
 * @brief limits grade between 0 and 100
 * @param grade 
 * @return Bool False(if grade out of range)
 */
Bool validate_grade(int32 grade){
    if(grade<0 || grade>100){
        return False;
    }
    return True;
}

/**
 * @brief checks if year is valid or not
 * @param year 
 * @return Bool False(if year is less than 1900)
 */
Bool validate_year(int32 year){
    if(year<1900){
        return False;
    }
    return True;
}
                                             
/**
 * @brief make sure that user doesn't enter same id for different courses
 * first: it loops through the array of course IDs and count is used to limit the loop to the number of students added.
 * second: it checks if the course ID exists in the array.
 * 
 * @note why i implemented this function this way? 
 * i used "for" loop to iterate through the array of course IDs and check if the given ID exists in the array.
 * i used another parameter "count" to limit the loop to the number of students added.
 * 
 * @param id 
 * @param courseId array of ID
 * @param count to only loop number of students added times
 * @return Bool 
 */
Bool CourseIDExist(int32 id, int32 courseId[], int count){
    for(int i = 0;i<count;i++){
        if(courseId[i] == id){
            return True;
        }
    }
    return False;

}

/**
 * @brief Gets input from the user and validates it using a provided validator function.
 * 
 * @param msg The message to display to the user.
 * @param value Pointer to store the input value.
 * @param validator Function pointer to a validation function that checks the input.
 * @return Bool True if input is valid, False otherwise.
 */
Bool getInput(const char * msg, int32 *value, Bool (*validator)(int32)) { 
    printf("%s", msg);
    if (scanf("%d", value) != 1 || !validator(*value)) {
        clearInputBuffer();
        return False;
    }
    return True;
}

//----------------------------------------------------------------------------------------------------------------------------------------------


//user functions

/**
 * @brief This function adds students to database. 
 * 1. It first checks if the database is full using SDB_IsFull() function. 
 * 2. it asks user to enter id then validate it and checks does it exist or no if it exists/ wrong input it returns false.
 * 3. it asks user to enter year then validate it
 * 4. it asks user to enter 3 courses ID and grades then validate them
 * Finally: it adds the student to the database and returns true if all inputs are valid.
 * If any input is invalid, it will print an error message and return False.
 * 
 * @note If the database is full, it will print a message and return False.
 * 
 * @return Bool True if the student is added successfully, False otherwise.
 */
Bool SDB_AddEntry(){
    // Check if the database is full
    if(SDB_IsFull()){
        printf("Database is Full.\n");
        return False;
    }
    student newStud;


    // Get and validate Student ID
    int32 ID;
    if(!getInput("Enter Student ID: \n",&ID,validate_Integer)){
        printf("\nInvalid input for ID\n");
        printf("ID must be a positive integer and unique. \n");
        return False;
    }
    if(SDB_IsIdExist((uint32) ID)){
        printf("\nID already exists.\n");
        return False;
    }
    newStud.Student_ID = (uint32) ID;
   

    // Get and validate Student Year
    int32 year;
    if(!getInput("Enter Year: \n",&year,validate_year)){
        printf("\nInvalid input for Year\n");
        printf("Year must be a greater than 1900.\n");
        return False;
    }
    newStud.Student_year = (uint32) year;


    //Get and validate Course IDs and Grades
    int courseID[3];
    int courseGrade[3];
    char msg[50];
    for(int i =0;i<3;i++){
        sprintf(msg, "Enter Course %d ID: \n", i+1);
        if(!getInput(msg, &courseID[i], validate_Integer)){
            printf("\nInvalid input for Course ID\n");
            printf("Course ID must be a positive integer and unique. \n");
            return False;
        }

        if(CourseIDExist(courseID[i], courseID, i)){
            printf("\nCourse ID %d already exists.\n", courseID[i]);
            return False;
        }
        sprintf(msg, "Enter Course %d Grade: \n", i+1);
        if(!getInput(msg, &courseGrade[i], validate_grade)){
            printf("\nInvalid input for Course Grade\n");
            printf("Grade must be between 0 and 100.\n");
            return False;
        }
    }
    newStud.Course1_ID = courseID[0];  newStud.Course1_grade = courseGrade[0];
    newStud.Course2_ID = courseID[1];  newStud.Course2_grade = courseGrade[1];
    newStud.Course3_ID = courseID[2];  newStud.Course3_grade = courseGrade[2];

    // Add the new student to the database
    database[studentCount] = newStud;
    studentCount++;
    return True;
}


/**
 * @brief Checks if a student ID exists in the database.
 * 
 * @param id The student ID to check.
 * @return Bool True if the ID exists, False otherwise.
 */
Bool SDB_IsIdExist(uint32 id){
    for(int i =0;i<studentCount;i++){
        if(database[i].Student_ID == id){
            return True;
        }
    }
    return False;
}


/**
 * @brief Checks if the database is full.
 * 
 * @return Bool True if the database is full, False otherwise.
 */
Bool SDB_IsFull(){
    return studentCount>=max_students;
}


/**
 * @brief Gets the number of students in the database.
 * 
 * @return uint8 The number of students.
 */
uint8 SDB_GetUsedSize(){
    return (uint8) studentCount;
}


/**
 * @brief Get the list of student IDs in the database.
 * 
 * @param count Pointer to store the number of students.
 * @param list Pointer to an array to store the student IDs.
 */
void SDB_GetList(uint8 * count,uint32 * list){
    *count = 0;
    for(int i=0;i<studentCount;i++){
        list[*count] = database[i].Student_ID;
        (*count)++;
    }
}


/**
 * @brief Delete a student entry from the database.
 * This function searches for a student by ID and removes their entry from the database.
 * If the student ID does not exist, it prints an error message.
 * The function shifts the remaining entries left to fill the gap by the deleted entry.
 * After deletion, the last entry in the database is set to zero.
 * The student count is decremented after a successful deletion.
 * 
 * @param id The student ID to delete.
 */
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
            printf("Student with ID %u deleted successfully.\n", id); 
            studentCount--;
        }
    }
} 
    


/**
 * @brief Read and display a student's entry by ID.
 * 
 * This function searches for a student by their ID and prints their details.
 * If the student ID does not exist, it prints an error message.
 * 
 * @param id The student ID to read.
 * @return Bool True if the student entry is found and displayed, False otherwise.
 */
Bool SDB_ReadEntry(uint32 id){
    if(!SDB_IsIdExist(id)){
        printf("\nStudent with ID %u not found.\n",id);
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

