#pragma once

#define DEF_S_DOUBLE_TEST 	\
{				\
	#ifndef S_DOUBLE	\
	assert(0);		\
	#endif			\
}

#define CMD_DEF(name, str, num, asm_code, disasm_code, proc_code) \
const char N_##name = num;

#include "CmdDef.hpp"

#define REG_DEF(big_name, small_name, numb) 	\
const char N_R##big_name##X = numb;
REGS_DEF
#undef REG_DEF

#undef CMD_DEF
