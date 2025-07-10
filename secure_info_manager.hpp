#ifndef SECURE_INFO_MANAGER_HPP
#define SECURE_INFO_MANAGER_HPP

#include "account.hpp"
#include<stdio.h>
#include<stdlib.h>

class SecureInfoManager {
    public:
    void sha256_string(char *str, char hash_output[65]);
    void secure_info_writer(Account& account);
    void secure_info_reader(Account& account);
    bool secure_info_eraser(int accountNumber);
};

#endif