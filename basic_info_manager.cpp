#include "basic_info_manager.hpp"
#include<stdio.h>
#include<stdlib.h>

// Write Basic Info
void BasicInfoManager::basic_info_writer(Account& account){
    char fileName[150];
    sprintf(fileName, "Basic-Info/account_%d.txt", account.accountNumber); 
    FILE* fptr = fopen(fileName, "w");

    fprintf(fptr, "%s\n", account.name);  // Write Account Holder's Name
    fprintf(fptr, "%s\n", account.email);  // Write Account Holder's Email
    fprintf(fptr, "%s\n", account.phoneNumber);  // Write Account Holder's Phone Number

    fclose(fptr);
}


//Read Basic Info
Account BasicInfoManager::basic_info_reader(int accountNumber){
    Account account;
    account.accountNumber = accountNumber;
    char fileName[150];
    sprintf(fileName, "Basic-Info/account_%d.txt", account.accountNumber); 
    FILE* fptr = fopen(fileName, "r");

    fscanf(fptr, "%[^\n]", account.name); // Read Account Holder's Name
    fgetc(fptr);
    fscanf(fptr, "%[^\n]", account.email); // Read Account Holder's Email
    fgetc(fptr);
    fscanf(fptr, "%[^\n]", account.phoneNumber); // Read Account Holder's Phone Number
    fgetc(fptr);
    
    fclose(fptr);

    return account;
}


//Delete Basic Info
bool BasicInfoManager::basic_info_eraser(int accountNumber){
    char fileName[150];
    sprintf(fileName, "Basic-Info/account_%d.txt", accountNumber);

    if(remove(fileName) == 0) return true;
    return false;
}

