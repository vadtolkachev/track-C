#ifndef REGS_DEF
#define REGS_DEF 		\
	REG_DEF(A, a, 20)	\
	REG_DEF(B, b, 21)	\
	REG_DEF(C, c, 22)	\
	REG_DEF(D, d, 23)	\
	REG_DEF(E, e, 24)
#endif


#define DEFAULT_ASM_CODE(nCmd) 		\
{					\
	fprintf(txtFile, "%x\n", nCmd);	\
	fprintf(binFile, "%c", nCmd);	\
					\
	m_index++;			\
}


#define J_DEFAULT_ASM_CODE(nCmd, str) 			\
{							\
	int len = (int)strlen(str);			\
	char label[MAX_LABEL_LEN] = "";			\
	strcpy(label, &m_buf[len]);			\
							\
	findLabel(txtFile, binFile, label, nCmd);	\
							\
	m_index += 1 + sizeof(int);			\
}

#define PUSH_ASM_CODE 							\
{									\
	if((isdigit(m_buf[5])) || (m_buf[5] == '-'))			\
	{								\
		double d;						\
		char *pPosition = strchr(m_buf, '\n');			\
		if(pPosition == nullptr)				\
			assert(pPosition != nullptr);			\
									\
		d = strtod(&m_buf[5], &pPosition);			\
									\
		if((errno != 0) || (pPosition == &m_buf[5]) || 		\
					(*pPosition != '\n'))		\
		{							\
			printf("asm push err\n");			\
			printf("pPos = %c = %d\n", *pPosition, *pPosition);\
			assert(0);					\
			return PARSE_ERR;				\
		}							\
									\
		char *tmp = (char *)&d;					\
		fprintf(txtFile, "%x %lg\n", N_PUSH, d);		\
		fprintf(binFile, "%c", N_PUSH);				\
		for(int i = 0; i < (int)sizeof(double); i++)		\
			fprintf(binFile, "%c", tmp[i]);			\
									\
		m_index += 1 + sizeof(double);				\
	}								\
}


#define PUSH_P_ASM_CODE 							\
{										\
	if((m_buf[5] == '[') && ((isdigit(m_buf[6])) || (m_buf[6] == '-')))	\
	{									\
		char* pPosition = strchr(m_buf, '\n');				\
		if(pPosition == nullptr)					\
			assert(pPosition != nullptr);				\
										\
		long l_numb = strtol(&m_buf[6], &pPosition, 10);		\
										\
		if((errno != 0) || (pPosition == &m_buf[6]) || 			\
			(*pPosition != ']') || (*(pPosition+1) != '\n'))	\
		{								\
			printf("pPos = %c = %d\n", *pPosition, *pPosition);	\
			assert(0);						\
			return PARSE_ERR;					\
		}								\
										\
		char *tmp = (char *)&l_numb;					\
		fprintf(txtFile, "%x %ld\n", N_PUSH_P, l_numb);			\
		fprintf(binFile, "%c", N_PUSH_P);				\
		for(int i = 0; i < (int)sizeof(long); i++)			\
			fprintf(binFile, "%c", tmp[i]);				\
										\
		m_index += 1 + sizeof(long);					\
	}									\
}


#define PUSH_R_ASM_CODE 					\
{								\
	if(m_buf[5] == 'r')					\
	{							\
		char nReg;					\
		getNReg(6, &nReg);				\
								\
		fprintf(txtFile, "%x %x\n", N_PUSH_R, nReg);	\
		fprintf(binFile, "%c%c", N_PUSH_R, nReg);	\
								\
		m_index += 2;					\
	}							\
}


#define PUSH_PR_ASM_CODE 					\
{								\
	if((m_buf[5] == '[') && (m_buf[6] == 'r'))		\
	{							\
		if(m_buf[9] != ']')				\
			assert((printf("asm pushPR err\n"),0));	\
								\
		char nReg;					\
		getNReg(7, &nReg);				\
								\
		fprintf(txtFile, "%x %x\n", N_PUSH_PR, nReg);	\
		fprintf(binFile, "%c%c", N_PUSH_PR, nReg);	\
								\
		m_index += 2;					\
	}							\
}


#define POP_P_ASM_CODE 								\
{										\
	if((m_buf[4] == '[') && ((isdigit(m_buf[5])) || (m_buf[5] == '-')))	\
	{									\
		char* pPosition = strchr(m_buf, '\n');				\
		if(pPosition == nullptr)					\
			assert(pPosition != nullptr);				\
										\
		long l_numb = strtol(&m_buf[5], &pPosition, 10);		\
										\
		if((errno != 0) || (pPosition == &m_buf[5]) || 			\
			(*pPosition != ']') || (*(pPosition+1) != '\n'))	\
		{								\
			printf("pPos = %c = %d\n", *pPosition, *pPosition);	\
			assert(0);						\
			return PARSE_ERR;					\
		}								\
										\
		char *tmp = (char *)&l_numb;					\
		fprintf(txtFile, "%x %ld\n", N_POP_P, l_numb);			\
		fprintf(binFile, "%c", N_POP_P);				\
		for(int i = 0; i < (int)sizeof(long); i++)			\
			fprintf(binFile, "%c", tmp[i]);				\
										\
		m_index += 1 + sizeof(long);					\
	}									\
}


#define POP_R_ASM_CODE 						\
{								\
	if(m_buf[4] == 'r')					\
	{							\
		char nReg;					\
		getNReg(5, &nReg);				\
								\
		fprintf(txtFile, "%x %x\n", N_POP_R, nReg);	\
		fprintf(binFile, "%c%c", N_POP_R, nReg);	\
								\
		m_index += 2;					\
	}							\
}

#define POP_PR_ASM_CODE 					\
{								\
	if((m_buf[4] == '[') && (m_buf[5] == 'r'))		\
	{							\
		char nReg;					\
		getNReg(6, &nReg);				\
								\
		fprintf(txtFile, "%x %x\n", N_POP_PR, nReg);	\
		fprintf(binFile, "%c%c", N_POP_PR, nReg);	\
								\
		m_index += 2;					\
	}							\
}


#define LAB_ASM_CODE 							\
{									\
	int checkErr = OVERFLOW_ERR;					\
									\
	for(int i = 0; i < ASM_LABELS_SIZE; i++)			\
	{								\
		if(!strlen(m_labels[i].m_name))				\
		{							\
			m_labels[i].m_numb = m_index;			\
			strcpy(m_labels[i].m_name, &m_buf[1]);		\
									\
			char *tmp = (char *)&m_index;			\
			fprintf(txtFile, "%x %d\n", N_LAB, m_index);	\
			fprintf(binFile, "%c", N_LAB);			\
			for(int j = 0; j < (int)sizeof(int); j++)	\
				fprintf(binFile, "%c", tmp[j]);		\
									\
			checkErr = SUCCESS;				\
			break;						\
		}							\
	}								\
									\
	m_index += 1 + sizeof(int);					\
	if(checkErr != SUCCESS)						\
		m_errno = checkErr;					\
}


#define DEFAULT_DASM_CODE(nCmd, str) 	\
{					\
	fprintf(txtFile, "%x\n", nCmd);	\
	fprintf(asmFile, "%s\n", str);	\
					\
	m_index++;			\
}


#define J_DEFAULT_DASM_CODE(nCmd, str) 		\
{						\
	int *tmp = (int *)&m_buf[m_index+1];	\
						\
	fprintf(txtFile, "%x %d\n", nCmd, *tmp);\
	fprintf(asmFile, "%s%d\n", str, *tmp);	\
						\
	m_index += 1 + sizeof(int);		\
}


#define PUSH_DASM_CODE		 			\
{							\
	double *tmp = (double *)&m_buf[m_index+1];	\
	fprintf(txtFile, "%x %lg\n", N_PUSH, *tmp);	\
	fprintf(asmFile, "push %lg\n", *tmp);		\
							\
	m_index += 1 + sizeof(double);			\
}


#define PUSH_P_DASM_CODE		 		\
{							\
	long *tmp = (long *)&m_buf[m_index+1];		\
	fprintf(txtFile, "%x %ld\n", N_PUSH_P, *tmp);	\
	fprintf(asmFile, "push [%ld]\n", *tmp);		\
							\
	m_index += 1 + sizeof(long);			\
}


#define PUSH_R_DASM_CODE		 			\
{								\
	char cReg;						\
	getCReg(m_index+1, &cReg);				\
								\
	fprintf(txtFile, "%x %x\n", N_PUSH_R, m_buf[m_index+1]);\
	fprintf(asmFile, "push r%cx\n", cReg);			\
								\
	m_index += 2;						\
}


#define PUSH_PR_DASM_CODE		 			\
{								\
	char cReg;						\
	getCReg(m_index+1, &cReg);				\
								\
	fprintf(txtFile, "%x %x\n", N_PUSH_PR, m_buf[m_index+1]);\
	fprintf(asmFile, "push [r%cx]\n", cReg);		\
								\
	m_index += 2;						\
}


#define POP_P_DASM_CODE		 			\
{							\
	long *tmp = (long *)&m_buf[m_index+1];		\
	fprintf(txtFile, "%x %ld\n", N_POP_P, *tmp);	\
	fprintf(asmFile, "pop [%ld]\n", *tmp);		\
							\
	m_index += 1 + sizeof(long);			\
}


#define POP_R_DASM_CODE		 			\
{							\
	char cReg;					\
	getCReg(m_index+1, &cReg);			\
							\
	fprintf(txtFile, "%x %x\n", N_POP_R, 		\
		m_buf[m_index+1]);			\
	fprintf(asmFile, "pop r%cx\n", cReg);		\
							\
	m_index += 2;					\
}


#define POP_PR_DASM_CODE		 		\
{							\
	char cReg;					\
	getCReg(m_index+1, &cReg);			\
							\
	fprintf(txtFile, "%x %x\n", N_POP_PR, 		\
		m_buf[m_index+1]);			\
	fprintf(asmFile, "pop [r%cx]\n", cReg);		\
							\
	m_index += 2;					\
}


#define ADD_PROC_CODE				\
{						\
	if(m_stack.getSize() < 2)		\
	{					\
		m_errno = EMPTY_ERR;		\
		return EMPTY_ERR;		\
	}					\
						\
	data_t data1;				\
	data_t data2;				\
						\
	m_stack.getTop(&data1);			\
	m_stack.pop();				\
	m_stack.getTop(&data2);			\
	m_stack.pop();				\
						\
	int checkErr = m_stack.push(data1 + data2);\
						\
	dumpProc("Proc add");			\
	m_index++;				\
	m_errno = checkErr;			\
}


#define SUB_PROC_CODE				\
{						\
	if(m_stack.getSize() < 2)		\
	{					\
		m_errno = EMPTY_ERR;		\
		return EMPTY_ERR;		\
	}					\
						\
	data_t data1;				\
	data_t data2;				\
						\
	m_stack.getTop(&data1);			\
	m_stack.pop();				\
	m_stack.getTop(&data2);			\
	m_stack.pop();				\
						\
	int checkErr = m_stack.push(data2 - data1);\
						\
	dumpProc("Proc sub");			\
	m_index++;				\
	m_errno = checkErr;			\
}


#define MUL_PROC_CODE				\
{						\
	if(m_stack.getSize() < 2)		\
	{					\
		m_errno = EMPTY_ERR;		\
		return EMPTY_ERR;		\
	}					\
						\
	data_t data1;				\
	data_t data2;				\
						\
	m_stack.getTop(&data1);			\
	m_stack.pop();				\
	m_stack.getTop(&data2);			\
	m_stack.pop();				\
						\
	int checkErr = m_stack.push(data2*data1);\
						\
	dumpProc("Proc mul");			\
	m_index++;				\
	m_errno = checkErr;			\
}


#define DIV_PROC_CODE				\
{						\
	if(m_stack.getSize() < 2)		\
	{					\
		m_errno = EMPTY_ERR;		\
		return EMPTY_ERR;		\
	}					\
						\
	data_t data1;				\
	data_t data2;				\
						\
	m_stack.getTop(&data1);			\
	m_stack.pop();				\
	m_stack.getTop(&data2);			\
	m_stack.pop();				\
						\
	int checkErr = m_stack.push(data2/data1);\
						\
	dumpProc("Proc div");			\
	m_index++;				\
	m_errno = checkErr;			\
}


#define SIN_PROC_CODE				\
{						\
	if(m_stack.getSize() < 1)		\
	{					\
		m_errno = EMPTY_ERR;		\
		return EMPTY_ERR;		\
	}					\
						\
	data_t data;				\
	m_stack.getTop(&data);			\
	m_stack.pop();				\
						\
	dumpProc("Proc sin");			\
	m_index++;				\
						\
	int checkErr = m_stack.push(sin(data));	\
						\
	m_errno = checkErr;			\
}


#define COS_PROC_CODE				\
{						\
	if(m_stack.getSize() < 1)		\
	{					\
		m_errno = EMPTY_ERR;		\
		return EMPTY_ERR;		\
	}					\
						\
	data_t data;				\
	m_stack.getTop(&data);			\
	m_stack.pop();				\
						\
	dumpProc("Proc cos");			\
	m_index++;				\
						\
	int checkErr = m_stack.push(cos(data));	\
						\
	m_errno = checkErr;			\
}


#define SQRT_PROC_CODE				\
{						\
	if(m_stack.getSize() < 1)		\
	{					\
		m_errno = EMPTY_ERR;		\
		return EMPTY_ERR;		\
	}					\
						\
	data_t data;				\
	m_stack.getTop(&data);			\
	m_stack.pop();				\
						\
	dumpProc("Proc sqrt");			\
	m_index++;				\
						\
	int checkErr = m_stack.push(sqrt(data));\
						\
	m_errno = checkErr;			\
}


#define OUT_PROC_CODE			\
{					\
	if(m_stack.getSize() < 1)	\
	{				\
		m_errno = EMPTY_ERR;	\
		return EMPTY_ERR;	\
	}				\
					\
	data_t data;			\
	m_stack.getTop(&data);		\
	m_stack.pop();			\
					\
	dumpProc("Proc out");		\
	m_index++;			\
					\
	printf("Proc out : %lg\n", data);\
}


#define IN_PROC_CODE				\
{						\
	double tmp;				\
	bool isDone = false;			\
						\
	while(!isDone)				\
	{					\
		if(readDouble(&tmp) == SUCCESS)	\
			isDone = true;		\
	}					\
						\
	int checkErr = m_stack.push(tmp);	\
	if(checkErr != SUCCESS)			\
		return checkErr;		\
						\
	char str[25] = "";			\
	sprintf(str, "Proc in : %lg", tmp);	\
	dumpProc(str);				\
	m_index++;				\
}


#define END_PROC_CODE		\
{				\
	m_index = size; 	\
	dumpProc("Proc end");	\
}

#define PUSH_PROC_CODE					\
{							\
	double *pTmp = (double *)&m_code[m_index+1];	\
	double data = *pTmp;				\
							\
	int checkErr = m_stack.push(data);		\
	assert(checkErr == SUCCESS);			\
							\
	char str[30] = "";				\
							\
	m_index += 1 + sizeof(double);			\
	sprintf(str, "Proc push %lg", data);		\
							\
	dumpProc(str);					\
	m_errno = checkErr;				\
}


#define PUSH_P_PROC_CODE					\
{								\
	long pointer = *((long *)&m_code[m_index+1]);		\
	if(pointer >= m_ramSize)				\
		return OVERFLOW_ERR;				\
								\
	double data = m_RAM[pointer];				\
								\
	int checkErr = m_stack.push(data);			\
	assert(checkErr == SUCCESS);				\
								\
	char str[40] = "";					\
								\
	m_index += 1 + sizeof(long);				\
	sprintf(str, "Proc pushP m_RAM[%ld] %lg", pointer, data);\
								\
	dumpProc(str);						\
	m_errno = checkErr;					\
}


#define PUSH_R_PROC_CODE				\
{							\
	data_t *data;					\
	char cReg;					\
	char dumpStr[20];				\
							\
	getNReg(m_index+1, &data, &cReg);		\
	sprintf(dumpStr, "Proc push r%cx", cReg);	\
							\
	int checkErr = m_stack.push(*data);		\
	assert(checkErr == SUCCESS);			\
							\
	dumpProc(dumpStr);				\
	m_index += 2;					\
	m_errno = checkErr;				\
}


#define PUSH_PR_PROC_CODE				\
{							\
	data_t *dPointer;				\
	char cReg;					\
	char dumpStr[20];				\
							\
	getNReg(m_index+1, &dPointer, &cReg);		\
	sprintf(dumpStr, "Proc push [r%cx]", cReg);	\
							\
	long pointer = (long)*dPointer;			\
	if(pointer >= m_ramSize)			\
	{						\
		printf("pointer = %ld\nm_ramSize = %ld\n",\
			pointer, m_ramSize);		\
		return OVERFLOW_ERR;			\
	}						\
							\
	double data = m_RAM[pointer];			\
							\
	int checkErr = m_stack.push(data);		\
	assert(checkErr == SUCCESS);			\
							\
	m_index += 2;					\
	dumpProc(dumpStr);				\
							\
	m_errno = checkErr;				\
}


#define POP_PROC_CODE			\
{					\
	int checkErr;			\
					\
	checkErr = m_stack.pop();	\
					\
	assert(checkErr == SUCCESS);	\
	m_index++;			\
	dumpProc("Proc pop");		\
	m_errno = checkErr;		\
}


#define POP_P_PROC_CODE					\
{							\
	if(m_stack.getSize() == 0)			\
		m_errno = EMPTY_ERR;			\
							\
	long pointer = *((long *)&m_code[m_index+1]);	\
	if(pointer >= m_ramSize)			\
		return OVERFLOW_ERR;			\
							\
	double data; 					\
	m_stack.getTop(&data);				\
	m_stack.pop();					\
	m_RAM[pointer] = data;				\
							\
	assert(checkErr == SUCCESS);			\
							\
	char str[40] = "";				\
	m_index += 1 + sizeof(long);			\
	sprintf(str, "Proc popP m_RAM[%ld] %lg", 	\
		pointer, data);				\
	dumpProc(str);					\
}


#define POP_R_PROC_CODE				\
{						\
	if(m_stack.getSize() == 0)		\
		return EMPTY_ERR;		\
						\
	data_t *data;				\
	char cReg;				\
	char dumpStr[20];			\
						\
	getNReg(m_index+1, &data, &cReg);	\
	sprintf(dumpStr, "Proc pop r%cx", cReg);\
						\
	m_stack.getTop(data);			\
	int checkErr = m_stack.pop();		\
	assert(checkErr == SUCCESS);		\
						\
	dumpProc(dumpStr);			\
	m_index += 2;				\
	m_errno = checkErr;			\
}


#define POP_PR_PROC_CODE				\
{							\
	if(m_stack.getSize() == 0)			\
		return EMPTY_ERR;			\
							\
	data_t *dPointer;				\
	char cReg;					\
	char dumpStr[20];				\
							\
	getNReg(m_index+1, &dPointer, &cReg);		\
	sprintf(dumpStr, "Proc pop [r%cx]", cReg);	\
							\
	long pointer = (long)*dPointer;			\
	if(pointer >= m_ramSize)			\
	{						\
		printf("pointer = %ld\nm_ramSize = %ld\n",\
			pointer, m_ramSize);		\
		return OVERFLOW_ERR;			\
	}						\
							\
	data_t data;					\
	m_stack.getTop(&data);				\
	m_stack.pop();					\
							\
	m_RAM[pointer] = data;				\
							\
	dumpProc(dumpStr);				\
	m_index += 2;					\
}


#define JMP_PROC_CODE					\
{							\
	int numb = *(int *)&(m_code[m_index+1]);	\
	m_index = numb;					\
							\
	char dumpStr[60] = "";				\
	sprintf(dumpStr, "Proc jmp : %d", numb);	\
	dumpProc(dumpStr);				\
}


#define J_DEFAULT_PROC_CODE(str, sign)			\
{							\
	int *pTmp = (int *)&(m_code[m_index+1]);	\
	int numb = *pTmp;				\
	if(m_stack.getSize() < 2)			\
	{						\
		m_errno = EMPTY_ERR;			\
		return EMPTY_ERR;			\
	}						\
							\
	data_t data1;					\
	data_t data2;					\
							\
	m_stack.getTop(&data1);				\
	m_stack.pop();					\
	m_stack.getTop(&data2);				\
	m_stack.pop();					\
							\
	if(data1 sign data2)				\
		m_index = numb;				\
	else 						\
		m_index += 1 + sizeof(int);		\
							\
	char dumpStr[60] = "";				\
	sprintf(dumpStr, "Proc %s: %d if(%lg %s %lg)", \
		str, numb, data1, #sign, data2);	\
	dumpProc(dumpStr);				\
}


#define JW_PROC_CODE					\
{							\
	int *pTmp = (int *)&(m_code[m_index+1]);	\
	int numb = *pTmp;				\
	if(1)						\
		m_index = numb;				\
	else						\
		m_index += 1 + sizeof(int);		\
							\
	char dumpStr[20] = "";				\
	sprintf(dumpStr, "Proc jw : %d", numb);		\
	dumpProc(dumpStr);				\
}


#define LAB_PROC_CODE			\
{					\
	dumpProc("Proc label");		\
	m_index += 1 + sizeof(int);	\
}


#define RET_PROC_CODE				\
{						\
	if(m_retStack.getSize() == 0)		\
	{					\
		assert(0);			\
		return EMPTY_ERR;		\
	}					\
						\
	data_t data;				\
	m_retStack.getTop(&data);		\
	m_retStack.pop();			\
						\
	int numb = (int)data;			\
	if(numb < 0)				\
	{					\
		assert(0);			\
		return OVERFLOW_ERR;		\
	}					\
						\
	m_index = numb;				\
						\
	char dumpStr[20] = "";			\
	sprintf(dumpStr, "Proc ret : %d", numb);\
	dumpProc(dumpStr);			\
}


#define CALL_PROC_CODE				\
{						\
	int numb = m_index + 1 + sizeof(int);	\
	data_t tmp = (data_t)numb;		\
	int checkErr = m_retStack.push(tmp);	\
						\
	if(checkErr != SUCCESS)			\
		m_errno = checkErr;		\
						\
	int *pTmp = (int *)&(m_code[m_index+1]);\
	m_index = *pTmp;			\
						\
	char dumpStr[20] = "";			\
	sprintf(dumpStr, "Proc call : %d", numb);\
	dumpProc(dumpStr);			\
}


CMD_DEF(ADD, "add", 1, DEFAULT_ASM_CODE(N_ADD), DEFAULT_DASM_CODE(N_ADD, "add"), ADD_PROC_CODE)

CMD_DEF(SUB, "sub", 2, DEFAULT_ASM_CODE(N_SUB), DEFAULT_DASM_CODE(N_SUB, "sub"), SUB_PROC_CODE)

CMD_DEF(MUL, "mul", 3, DEFAULT_ASM_CODE(N_MUL), DEFAULT_DASM_CODE(N_MUL, "mul"), MUL_PROC_CODE)

CMD_DEF(DIV, "div", 4, DEFAULT_ASM_CODE(N_DIV), DEFAULT_DASM_CODE(N_DIV, "div"), DIV_PROC_CODE)

CMD_DEF(SIN, "sin", 40, DEFAULT_ASM_CODE(N_SIN), DEFAULT_DASM_CODE(N_SIN, "sin"), SIN_PROC_CODE)

CMD_DEF(COS, "cos", 41, DEFAULT_ASM_CODE(N_COS), DEFAULT_DASM_CODE(N_COS, "cos"), COS_PROC_CODE)

CMD_DEF(SQRT, "sqrt", 42, DEFAULT_ASM_CODE(N_SQRT), DEFAULT_DASM_CODE(N_SQRT, "sqrt"), SQRT_PROC_CODE)

CMD_DEF(OUT, "out", 5, DEFAULT_ASM_CODE(N_OUT), DEFAULT_DASM_CODE(N_OUT, "out"), OUT_PROC_CODE)

CMD_DEF(IN, "in", 50, DEFAULT_ASM_CODE(N_IN), DEFAULT_DASM_CODE(N_IN, "in"), IN_PROC_CODE)

CMD_DEF(END, "end", 6, DEFAULT_ASM_CODE(N_END), DEFAULT_DASM_CODE(N_END, "end"), END_PROC_CODE)

CMD_DEF(PUSH, "push", 7, PUSH_ASM_CODE, PUSH_DASM_CODE, PUSH_PROC_CODE)

CMD_DEF(PUSH_P, "push", 9, PUSH_P_ASM_CODE, PUSH_P_DASM_CODE, PUSH_P_PROC_CODE)

CMD_DEF(PUSH_R, "push", 10, PUSH_R_ASM_CODE, PUSH_R_DASM_CODE, PUSH_R_PROC_CODE)

CMD_DEF(PUSH_PR, "push", 11, PUSH_PR_ASM_CODE, PUSH_PR_DASM_CODE, PUSH_PR_PROC_CODE)

CMD_DEF(POP, "pop\n", 8, DEFAULT_ASM_CODE(N_POP), DEFAULT_DASM_CODE(N_POP, "pop"), POP_PROC_CODE)

CMD_DEF(POP_P, "pop ", 14, POP_P_ASM_CODE, POP_P_DASM_CODE, POP_P_PROC_CODE)

CMD_DEF(POP_R, "pop", 12, POP_R_ASM_CODE, POP_R_DASM_CODE, POP_R_PROC_CODE)

CMD_DEF(POP_PR, "pop", 13, POP_PR_ASM_CODE, POP_PR_DASM_CODE, POP_PR_PROC_CODE)

CMD_DEF(JMP, "jmp ", 30, J_DEFAULT_ASM_CODE(N_JMP, "jmp "), J_DEFAULT_DASM_CODE(N_JMP, "jmp "), JMP_PROC_CODE)

CMD_DEF(JA, "ja ", 31, J_DEFAULT_ASM_CODE(N_JA, "ja "), J_DEFAULT_DASM_CODE(N_JA, "ja "), J_DEFAULT_PROC_CODE("ja ", >))

CMD_DEF(JB, "jb ", 32, J_DEFAULT_ASM_CODE(N_JB, "jb "), J_DEFAULT_DASM_CODE(N_JB, "jb "), J_DEFAULT_PROC_CODE("jb ", <))

CMD_DEF(JE, "je ", 33, J_DEFAULT_ASM_CODE(N_JE, "je "), J_DEFAULT_DASM_CODE(N_JE, "je "), J_DEFAULT_PROC_CODE("jne ", ==))

CMD_DEF(JAE, "jae ", 34, J_DEFAULT_ASM_CODE(N_JAE, "jae "), J_DEFAULT_DASM_CODE(N_JAE, "jae "), J_DEFAULT_PROC_CODE("jae ", >=))

CMD_DEF(JBE, "jbe ", 35, J_DEFAULT_ASM_CODE(N_JBE, "jbe "), J_DEFAULT_DASM_CODE(N_JBE, "jbe "), J_DEFAULT_PROC_CODE("jbe ", <=))

CMD_DEF(JNE, "jne ", 36, J_DEFAULT_ASM_CODE(N_JNE, "jne "), J_DEFAULT_DASM_CODE(N_JNE, "jne "), J_DEFAULT_PROC_CODE("jne ", !=))

CMD_DEF(JW, "jw ", 37, J_DEFAULT_ASM_CODE(N_JW, "jw "), J_DEFAULT_DASM_CODE(N_JW, "jw "), JW_PROC_CODE)

CMD_DEF(LAB, ":", 38, LAB_ASM_CODE, J_DEFAULT_DASM_CODE(N_LAB, ":"), LAB_PROC_CODE)

CMD_DEF(CALL, "call ", 43, J_DEFAULT_ASM_CODE(N_CALL, "call "), J_DEFAULT_DASM_CODE(N_CALL, "call "), CALL_PROC_CODE)

CMD_DEF(RET, "ret", 44, DEFAULT_ASM_CODE(N_RET), DEFAULT_DASM_CODE(N_RET, "ret"), RET_PROC_CODE)
