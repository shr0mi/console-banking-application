#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include<stdio.h>
#include<stdlib.h>

struct Account {
    int accountNumber;
    char name[100];
    char email[100];
    char phoneNumber[100];
    char password[100];
    float balance;
    //int accountStatus;
};

#endif