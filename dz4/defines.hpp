#pragma once

typedef int data_t;

const int STACK_OK = 0;
const int CANARY1_ERR = -1;
const int CANARY2_ERR = -2;
const int CANARY3_ERR = -3;
const int CANARY4_ERR = -4;
const int SIZE_ERR = -5;
const int CAPACITY_ERR = -6;
const int POISON_ERR = -7;
const int SUM1_ERR = -8;
const int SUM2_ERR = -9;


const int ALLOC_ERR = -20;
const int NULLPTR_ERR = -21;
const int EMPTY_ERR = -22;
const int SUCCESS = 1;

const int BUF = 2;

const int NORM_F = 10;
const int HEX_F = 16;
const int SUM1_F = 17;
const int SUM2_F = 18;

const data_t POISON1 = 666;
const data_t POISON2 = 667;
const data_t POISON3 = 668;

const data_t CANARY3 = 0xDEADBEEF;
const data_t CANARY4 = 0xBEDABEDA;


const char GREEN[] = "\033[1;32m";
const char RED[] = "\033[1;31m";
const char WHITE[] = "\033[1;37m";
const char NORM[] = "\033[0m";