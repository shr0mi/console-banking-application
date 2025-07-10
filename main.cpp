#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "account.hpp"
#include "basic_info_manager.hpp"
#include "secure_info_manager.hpp"
#include "log_manager.hpp"

BasicInfoManager BIM;
SecureInfoManager SIM;
LogManager LM;

void createAccount();
void viewAccount();
void deposit();
void withdraw();
void checkLogs();
void listAccounts();
void deleteAccount();

bool check_available_ac_nums(int ac_num);
void Enter_in_primarydb(Account ac);
Account user_authentication(Account ac);

void Write_account(Account ac);
//void Write_Basic_Info(Account ac);
//void Write_Account_Info(Account ac);

Account Read_account(int accountNumber);

int main() {
    int choice;

    do {
        printf("\n=== Banking System Menu ===\n");
        printf("1. Create Account\n");
        printf("2. View Account\n");
        printf("3. Deposit\n");
        printf("4. Withdraw\n");
        printf("5. Check Logs\n");
        printf("6. List All Accounts\n");
        printf("7. Delete Account\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice); getchar();

        switch (choice) {
            case 1: createAccount(); break;
            case 2: viewAccount(); break;
            case 3: deposit(); break;
            case 4: withdraw(); break;
            case 5: checkLogs(); break;
            case 6: listAccounts(); break;
            case 7: deleteAccount(); break;
            case 8: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 8);

    return 0;
}

// Function Definitions
void createAccount(){
    Account ac;
    printf("Enter an account number: ");
    scanf("%d", &ac.accountNumber);
    getchar();
    if(!check_available_ac_nums(ac.accountNumber)){
        printf("Enter your name: ");
        scanf("%[^\n]", ac.name);
        getchar();
        printf("Enter your email: ");
        scanf("%[^\n]", ac.email);
        getchar();
        printf("Enter your phone number: ");
        scanf("%s", ac.phoneNumber);
        getchar();
        printf("Enter your password: ");
        scanf("%s", ac.password);
        getchar();
        printf("Enter initial deposit: ");
        scanf("%f", &ac.balance);
        getchar();
        //ac.accountStatus = 1;

        // If initial deposit is less than or equal to 0
        if(ac.balance <= 0){
            printf("You need a positive initial deposit minimum to create an account!!!\n");
        }else{
            printf("Created account: %d %s %f\n", ac.accountNumber, ac.name, ac.balance);

            //Generate an account
            Write_account(ac);

            //Enter it into the primary database
            Enter_in_primarydb(ac);

            //Write Log
            LM.write_log(ac.accountNumber, 1, ac.balance);
        }

    }else{
        printf("This Account Number already exists. Please try another one.\n");
        //createAccount();
    }

    printf("--------------------------------------------\n");
    printf("Enter any key to continue\n");
    getchar();
}


// View Account Information
void viewAccount(){
    Account ac = user_authentication(ac);
    
    if(ac.accountNumber != -1){
        printf("Account Holder's Name: %s\n", ac.name);
        printf("Account Holder's Email: %s\n", ac.email);
        printf("Account Holder's Phone Number: %s\n", ac.phoneNumber);
        printf("Account Holder's Balance: %f\n", ac.balance);

        // Write in Log
        LM.write_log(ac.accountNumber, 2, ac.balance);
    }

    printf("--------------------------------------------\n");
    printf("Enter any key to continue\n");
    getchar();
}


// Deposit in account
void deposit(){
    Account ac = user_authentication(ac);

    if(ac.accountNumber != -1){
        float amount;
        printf("Enter Amount to deposit: ");
        scanf("%f", &amount);
        getchar();
        if(amount < 0){printf("Only positive money can be deposited!!!\n");}
        else{
            printf("Your old balance: %f\n", ac.balance);
            ac.balance += amount;
            Write_account(ac);
            printf("Your new balance: %f\n", ac.balance);

            // Write in Log
            LM.write_log(ac.accountNumber, 3, amount);
        }
    }

    printf("--------------------------------------------\n");
    printf("Enter any key to continue\n");
    getchar();
}


// Withdraw From an accout
void withdraw(){
    Account ac = user_authentication(ac);

    if(ac.accountNumber != -1){
        float amount;
        printf("Enter Amount to withdraw: ");
        scanf("%f", &amount);
        getchar();
        if(amount < 0){printf("Only positive money can be withdrawed!!!\n");}
        else{
            if(amount > ac.balance){
                printf("You don't have enough money!");
                printf("Your old balance: %f\n", ac.balance);
            }else{
                printf("Your old balance: %f\n", ac.balance);
                ac.balance -= amount;
                Write_account(ac);
                printf("Your new balance: %f\n", ac.balance);

                //Write in Log
                LM.write_log(ac.accountNumber, 4, amount);
            }         
        }
    }

    printf("--------------------------------------------\n");
    printf("Enter any key to continue\n");
    getchar();
}


void checkLogs(){
    Account ac = user_authentication(ac);

    if(ac.accountNumber != -1){
        LM.read_log(ac.accountNumber);
    }

    printf("--------------------------------------------\n");
    printf("Enter any key to continue\n");
    getchar();
}


// List All accounts
void listAccounts(){
    FILE* fptr = fopen("ac_numbers.dat", "rb");
    printf("account_number --- name --- email --- phone_number --- balance\n");
    int tmp;
    while(fread(&tmp, sizeof(int), 1 , fptr)){
        Account ac; ac.accountNumber = tmp;
        ac = Read_account(ac.accountNumber);
        printf("%d --- %s --- %s --- %s --- %f\n", ac.accountNumber, ac.name, ac.email, ac.phoneNumber, ac.balance);
    }
    fclose(fptr);

    printf("--------------------------------------------\n");
    printf("Enter any key to continue\n");
    getchar();
}


// Delete Account
void deleteAccount(){
    Account ac = user_authentication(ac);

    if(ac.accountNumber != -1){
        if(BIM.basic_info_eraser(ac.accountNumber) && SIM.secure_info_eraser(ac.accountNumber) && LM.delete_log(ac.accountNumber)){
            // Remove From Primary Database
            // Store All data in v except accountNumber
            std::vector<int> v;
            FILE* fptr = fopen("ac_numbers.dat", "rb");
            int tmp;
            while(fread(&tmp, sizeof(int), 1 , fptr)){
                if(tmp != ac.accountNumber) v.push_back(tmp);
            }
            fclose(fptr);

            fptr = fopen("ac_numbers.dat", "wb");
            for(int i=0;i<v.size();i++){
                fwrite(&v[i], sizeof(int), 1, fptr);
            }
            fclose(fptr);

            printf("Account was deleted successfully");
        }
        else
            printf("An error occured");

    }

    printf("--------------------------------------------\n");
    printf("Enter any key to continue\n");
    getchar();
}


// Check if Account number is valid
// Returns True if it exists in database, Returns False if it doesn't exist in database
bool check_available_ac_nums(int ac_num){
    FILE* fptr = fopen("ac_numbers.dat", "rb");
    bool ac_found = false;

    int tmp;
    while(fread(&tmp, sizeof(int), 1 , fptr)){
        if(tmp == ac_num){
            ac_found = true;
            break;
        }
    }
    fclose(fptr);
    return ac_found;
}

// Enter account number in primary database
void Enter_in_primarydb(Account ac){
    FILE* fptr = fopen("ac_numbers.dat", "ab");
    fwrite(&ac.accountNumber, sizeof(int), 1, fptr);
    fclose(fptr);
}


Account user_authentication(Account ac){
    printf("Enter an account number: ");
    scanf("%d", &ac.accountNumber); 
    getchar();

    if(check_available_ac_nums(ac.accountNumber)){
        //Read Account Info
        Account ac2 = Read_account(ac.accountNumber);

        // If account is locked take back
        // Only 5 password tries before account gets locked
        // if(ac2.accountStatus >= 5){
        //     printf("This account is locked!\n");
        //     ac.accountNumber = -1;
        //     return ac;
        // }

        //Password Input
        printf("Enter password: ");
        scanf("%s", ac.password);
        getchar();

        // Hash the password
        char hashed_pwd[65];
        SIM.sha256_string(ac.password, hashed_pwd);

        //Check Password
        if(strcmp(hashed_pwd, ac2.password)){
            printf("Wrong Password. Try again!\n");
            ac.accountNumber = -1; // Account Number -1 means this has failed
            //ac2.accountStatus++;
            //SIM.secure_info_writer(ac2);
            return ac;
        }else{
            //Password Matched!!!
            strcpy(ac2.password, ac.password);
            return ac2;
        }
    }else{
        printf("Account was not found\n");
        ac.accountNumber = -1;
        return ac;
    }
}


// Write an account
void Write_account(Account ac){
    BIM.basic_info_writer(ac);
    SIM.secure_info_writer(ac);
}


// Read an existing account information
Account Read_account(int accountNumber){
    Account ac;

    ac = BIM.basic_info_reader(accountNumber);
    SIM.secure_info_reader(ac);

    return ac;
}














