#ifndef BASIC_INFO_MANAGER_HPP
#define BASIC_INFO_MANAGER_HPP

#include "account.hpp"
#include<stdio.h>
#include<stdlib.h>

class BasicInfoManager {
    public:
    void basic_info_writer(Account& account);
    Account basic_info_reader(int accountNumber);
    bool basic_info_eraser(int accountNumber);
};

#endif

