#include "SDB.h" 
#include "STD.h"
#include <stdio.h>
#include <stdlib.h>


int main(){
    SDB_APP();
    return 0;
}


//gcc main.c src/SDB.c src/SDBAPP.c -Iinclude -o program.exe  
//-I folder_name tells the compiler where to look for the header files.