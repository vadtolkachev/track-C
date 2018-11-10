#pragma once

#define CMD_DEF(name, num, asm_code, disasm_code, proc_code) \
const char N_##name = num;

#include "CmdDef.hpp"

#undef CMD_DEF

const char N_RAX = 20;
const char N_RBX = 21;
const char N_RCX = 22;
const char N_RDX = 23;