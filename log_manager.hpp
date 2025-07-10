#ifndef LOG_MANAGER_HPP
#define LOG_MANAGER_HPP

#include "account.hpp"
#include<stdio.h>
#include<stdlib.h>

class LogManager {
    public:
    void write_log(int accountNumber, int x, float amount);
    void read_log(int accountNumber);
    bool delete_log(int accountNumber);
};

#endif