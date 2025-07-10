#include "secure_info_manager.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

void SecureInfoManager::sha256_string(char *str, char hash_output[65]){
    // Create a 32 byte array that stores binary form of hashed input
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)str, strlen(str), hash);

    //Conver the binary for to 2 digit hex and store it in hash_output
    for(int i=0;i<SHA256_DIGEST_LENGTH; i++){
        sprintf(hash_output + (i*2), "%02x", hash[i]);
    }

    // Add a \0 in end
    hash_output[64] = 0;
}

void SecureInfoManager::secure_info_writer(Account& account){
    char fileName[150];
    sprintf(fileName, "Accounts/account_%d.dat", account.accountNumber); 
    FILE* fptr = fopen(fileName, "wb");

    char hashed_pwd[65];
    sha256_string(account.password, hashed_pwd);

    fwrite(&hashed_pwd, sizeof(char), 65, fptr); // Write Password
    fwrite(&account.balance, sizeof(float), 1, fptr); // Write Balance
    //fwrite(&account.accountStatus, sizeof(int), 1, fptr); // Write Account Status

    fclose(fptr);
}


void SecureInfoManager::secure_info_reader(Account& account){
    char fileName[150];
    sprintf(fileName, "Accounts/account_%d.dat", account.accountNumber); 
    FILE* fptr = fopen(fileName, "rb");

    fread(&account.password, sizeof(char), 65, fptr);
    fread(&account.balance, sizeof(float), 1, fptr);
    //fread(&account.accountStatus, sizeof(int), 1, fptr);

    fclose(fptr);
}


//Delete Secure Info
bool SecureInfoManager::secure_info_eraser(int accountNumber){
    char fileName[150];
    sprintf(fileName, "Accounts/account_%d.dat", accountNumber);

    if(remove(fileName) == 0) return true;
    return false;
}
