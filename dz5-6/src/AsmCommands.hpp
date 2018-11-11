#pragma once

#define CMD_DEF(name, num, asm_code, disasm_code, proc_code) \
const char N_##name = num;

#include "CmdDef.hpp"

#undef CMD_DEF


#define REG_DEF(big_name, small_name, numb) \
const char N_R##big_name##X = numb;

#include "RegDef.hpp"

#undef REG_DEF

