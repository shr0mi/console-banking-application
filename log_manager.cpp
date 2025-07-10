#include "log_manager.hpp"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctime>

void LogManager::write_log(int accountNumber, int x, float amount){
    char fileName[150];
    sprintf(fileName, "Logs/account_%d.txt", accountNumber); 
    FILE* fptr = fopen(fileName, "a");

    time_t now = time(0);   // current time
    char* dt = ctime(&now); // convert to string
    dt[strcspn(dt, "\n")] = '\0';   // Replace \n with \0
    char log_msg[200];
    switch (x)
    {
    case 1:
        //Created Account
        sprintf(log_msg, "Date & Time: %s  :  Created Account with initial deposit %f amount", dt, amount);
        break;
    case 2:
        //Viewd Account
        sprintf(log_msg, "Date & Time: %s  :  Viewd Account", dt);
        break;
    case 3:
        //Deposited Money
        sprintf(log_msg, "Date & Time: %s  :  Deposited %f amount", dt, amount);
        break;
    case 4:
        //Withdrawed Money
        sprintf(log_msg, "Date & Time: %s  :  Withdrawed %f amount", dt, amount);
        break;
    
    default:
        break;
    }

    fprintf(fptr, "%s\n", log_msg);

    fclose(fptr);
}


void LogManager::read_log(int accountNumber){
    char fileName[150];
    sprintf(fileName, "Logs/account_%d.txt", accountNumber); 
    FILE* fptr = fopen(fileName, "r");

    char msg[200];
    while(fscanf(fptr, "%[^\n]", msg) == 1){
        fgetc(fptr);
        printf("%s\n", msg);
    }

    fclose(fptr);
}


bool LogManager::delete_log(int accountNumber){
    char fileName[150];
    sprintf(fileName, "Logs/account_%d.txt", accountNumber);

    if(remove(fileName) == 0) return true;
    return false;
}