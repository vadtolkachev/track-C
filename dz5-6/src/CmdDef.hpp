#ifndef REGS_DEF
#define REGS_DEF 		\
	REG_DEF(A, 'a', 20)	\
	REG_DEF(B, 'b', 21)	\
	REG_DEF(C, 'c', 22)	\
	REG_DEF(D, 'd', 23)	\
	REG_DEF(E, 'e', 24)
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

CMD_DEF(PUSH, "push", 7,
	{
		if((isdigit(m_buf[5])) || (m_buf[5] == '-'))
		{
			double d;
			char *pPosition = strchr(m_buf, '\n');
			if(pPosition == nullptr)
				assert(pPosition != nullptr);

			d = strtod(&m_buf[5], &pPosition);

			if((errno != 0) || (pPosition == &m_buf[5]) || (*pPosition != '\n'))
			{
				printf("asm push err\n");
				printf("pPos = %c = %d\n", *pPosition, *pPosition);	
				assert(0);
				return PARSE_ERR;
			}

			char *tmp = (char *)&d;			
			fprintf(txtFile, "%x %lg\n", N_PUSH, d);
			fprintf(binFile, "%c", N_PUSH);
			for(int i = 0; i < (int)sizeof(double); i++)
				fprintf(binFile, "%c", tmp[i]);

			m_index += 1 + sizeof(double);
		}
	},
	{
		double *tmp = (double *)&m_buf[m_index+1];
		fprintf(txtFile, "%x %lg\n", N_PUSH, *tmp);
		fprintf(asmFile, "push %lg\n", *tmp);

		m_index += 1 + sizeof(double);
	},
	{
		double *pTmp = (double *)&m_code[m_index+1];
		double data = *pTmp;	

		int checkErr = m_stack.push(data);
		assert(checkErr == SUCCESS);

		char str[30] = "";

		m_index += 1 + sizeof(double);
		sprintf(str, "Proc push %lg", data);

		dumpProc(str);
		m_errno = checkErr;
	})


CMD_DEF(PUSH_P, "push", 9,
	{
		if((m_buf[5] == '[') && ((isdigit(m_buf[6])) || (m_buf[6] == '-')))
		{
			char* pPosition = strchr(m_buf, '\n');
			if(pPosition == nullptr)
				assert(pPosition != nullptr);

			long l_numb = strtol(&m_buf[6], &pPosition, 10);

			if((errno != 0) || (pPosition == &m_buf[6]) || (*pPosition != ']') || (*(pPosition+1) != '\n'))
			{
				printf("pPos = %c = %d\n", *pPosition, *pPosition);
				assert(0);
				return PARSE_ERR;
			}

			char *tmp = (char *)&l_numb;			
			fprintf(txtFile, "%x %ld\n", N_PUSH_P, l_numb);
			fprintf(binFile, "%c", N_PUSH_P);
			for(int i = 0; i < (int)sizeof(long); i++)
				fprintf(binFile, "%c", tmp[i]);	

			m_index += 1 + sizeof(long);
		}
	},
	{
		long *tmp = (long *)&m_buf[m_index+1];
		fprintf(txtFile, "%x %ld\n", N_PUSH_P, *tmp);
		fprintf(asmFile, "push [%ld]\n", *tmp);

		m_index += 1 + sizeof(long);
	},
	{
		long pointer = *((long *)&m_code[m_index+1]);
		if(pointer >= m_ramSize)
			return OVERFLOW_ERR;
		
		double data = m_RAM[pointer];
	
		int checkErr = m_stack.push(data);
		assert(checkErr == SUCCESS);

		char str[40] = "";

		m_index += 1 + sizeof(long);
		sprintf(str, "Proc pushP m_RAM[%ld] %lg", pointer, data);

		dumpProc(str);
		m_errno = checkErr;
	})


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


CMD_DEF(PUSH_R, "push", 10, PUSH_R_ASM_CODE,
	{
		fprintf(txtFile, "%x ", N_PUSH_R);
		fprintf(asmFile, "push ");
		switch(m_buf[m_index+1])
		{
			case N_RAX : 
			fprintf(txtFile, "%x\n", N_RAX);
			fprintf(asmFile, "rax\n");
			break;
			
			case N_RBX : 
			fprintf(txtFile, "%x\n", N_RBX);
			fprintf(asmFile, "rbx\n");
			break;

			case N_RCX : 
			fprintf(txtFile, "%x\n", N_RCX);
			fprintf(asmFile, "rcx\n");
			break;

			case N_RDX : 
			fprintf(txtFile, "%x\n", N_RDX);
			fprintf(asmFile, "rdx\n");
			break;

			case N_REX : 
			fprintf(txtFile, "%x\n", N_REX);
			fprintf(asmFile, "rex\n");
			break;

			default : printf("disasm pushR err\n"); assert(0);
		}

		m_index += 2;
	},
	{
		char nReg = m_code[m_index+1];
		data_t data;
		char dumpStr[20];

		switch(nReg)
		{
			case N_RAX : data = m_rax; sprintf(dumpStr, "Proc push rax"); break;
			case N_RBX : data = m_rbx; sprintf(dumpStr, "Proc push rbx"); break;
			case N_RCX : data = m_rcx; sprintf(dumpStr, "Proc push rcx"); break;
			case N_RDX : data = m_rdx; sprintf(dumpStr, "Proc push rdx"); break;
			case N_REX : data = m_rex; sprintf(dumpStr, "Proc push rex"); break;

			default : printf("proc pushR err\n"); assert(0);
		}
			

		int checkErr = m_stack.push(data);
		assert(checkErr == SUCCESS);

		dumpProc(dumpStr);
		m_index += 2;
		m_errno = checkErr;
	})


CMD_DEF(PUSH_PR, "push", 11,
	{
		if((m_buf[5] == '[') && (m_buf[6] == 'r'))
		{
			if((m_buf[8] != 'x') || (m_buf[9] != ']') || (m_buf[10] != '\n'))
				assert((printf("asm pushPR err\n"),0));			

			if((m_buf[7] != 'a') && (m_buf[7] != 'b') && (m_buf[7] != 'c') && (m_buf[7] != 'd') && (m_buf[7] != 'e'))
				assert((printf("asm pushPR err\n"),0));	

			char nReg;

			if(m_buf[7] == 'a')
				nReg = N_RAX;
			if(m_buf[7] == 'b')
				nReg = N_RBX;
			if(m_buf[7] == 'c')
				nReg = N_RCX;
			if(m_buf[7] == 'd')
				nReg = N_RDX;
			if(m_buf[7] == 'e')
				nReg = N_REX;

			fprintf(txtFile, "%x %x\n", N_PUSH_PR, nReg);
			fprintf(binFile, "%c%c", N_PUSH_PR, nReg);
			
			m_index += 2;
		}
	},
	{
		fprintf(txtFile, "%x ", N_PUSH_PR);
		fprintf(asmFile, "push [");
		switch(m_buf[m_index+1])
		{
			case N_RAX : 
			fprintf(txtFile, "%x\n", N_RAX);
			fprintf(asmFile, "rax]\n");
			break;
			
			case N_RBX : 
			fprintf(txtFile, "%x\n", N_RBX);
			fprintf(asmFile, "rbx]\n");
			break;

			case N_RCX : 
			fprintf(txtFile, "%x\n", N_RCX);
			fprintf(asmFile, "rcx]\n");
			break;

			case N_RDX : 
			fprintf(txtFile, "%x\n", N_RDX);
			fprintf(asmFile, "rdx]\n");
			break;

			case N_REX : 
			fprintf(txtFile, "%x\n", N_REX);
			fprintf(asmFile, "rex]\n");
			break;

			default : assert((printf("disasm pushPR err\n"),0));	
		}

		m_index += 2;
	},
	{
		char nReg = m_code[m_index+1];

		data_t *dPointer;
		char dumpStr[20];

		switch(nReg)
		{
			case N_RAX : dPointer = &m_rax; sprintf(dumpStr, "Proc pop [rax]"); break;
			case N_RBX : dPointer = &m_rbx; sprintf(dumpStr, "Proc pop [rbx]"); break;
			case N_RCX : dPointer = &m_rcx; sprintf(dumpStr, "Proc pop [rcx]"); break;
			case N_RDX : dPointer = &m_rdx; sprintf(dumpStr, "Proc pop [rdx]"); break;
			case N_REX : dPointer = &m_rex; sprintf(dumpStr, "Proc pop [rex]"); break;

			default : assert((printf("proc pushPR err\n"),0));
		}

		long pointer = (long)*dPointer;
		if(pointer >= m_ramSize)
		{
			printf("pointer = %ld\nm_ramSize = %ld\n", pointer, m_ramSize);
			return OVERFLOW_ERR;
		}

		double data = m_RAM[pointer];
		
		int checkErr = m_stack.push(data);
		assert(checkErr == SUCCESS);

		m_index += 2;
		dumpProc(dumpStr);

		m_errno = checkErr;
	})


CMD_DEF(POP, "pop", 8,
	{
		if(m_buf[3] == '\n')
		{
			fprintf(txtFile, "%x\n", N_POP);
			fprintf(binFile, "%c", N_POP);

			m_index++;
		}
	},
	{
		fprintf(txtFile, "%x\n", N_POP);
		fprintf(asmFile, "pop\n");

		m_index++;
	},
	{	
		int checkErr;
		
		checkErr = m_stack.pop();

		assert(checkErr == SUCCESS);
		m_index++;
		dumpProc("Proc pop");
		m_errno = checkErr;
	})



CMD_DEF(POP_P, "pop ", 14, 
	{
		if((m_buf[4] == '[') && ((isdigit(m_buf[5])) || (m_buf[5] == '-')))
		{
			char* pPosition = strchr(m_buf, '\n');
			if(pPosition == nullptr)
				assert(pPosition != nullptr);

			long l_numb = strtol(&m_buf[5], &pPosition, 10);

			if((errno != 0) || (pPosition == &m_buf[5]) || (*pPosition != ']') || (*(pPosition+1) != '\n'))
			{
				printf("pPos = %c = %d\n", *pPosition, *pPosition);
				assert(0);
				return PARSE_ERR;
			}

			char *tmp = (char *)&l_numb;			
			fprintf(txtFile, "%x %ld\n", N_POP_P, l_numb);
			fprintf(binFile, "%c", N_POP_P);
			for(int i = 0; i < (int)sizeof(long); i++)
				fprintf(binFile, "%c", tmp[i]);	

			m_index += 1 + sizeof(long);
		}
	},
	{
		long *tmp = (long *)&m_buf[m_index+1];
		fprintf(txtFile, "%x %ld\n", N_POP_P, *tmp);
		fprintf(asmFile, "pop [%ld]\n", *tmp);

		m_index += 1 + sizeof(long);
	},
	{
		if(m_stack.getSize() == 0)
		{
			m_errno = EMPTY_ERR;
		}

		long pointer = *((long *)&m_code[m_index+1]);
		if(pointer >= m_ramSize)
			return OVERFLOW_ERR;
		
		double data; 
		m_stack.getTop(&data);
		m_stack.pop();
		m_RAM[pointer] = data;
	
		
		assert(checkErr == SUCCESS);

		char str[40] = "";

		m_index += 1 + sizeof(long);
		sprintf(str, "Proc popP m_RAM[%ld] %lg", pointer, data);

		dumpProc(str);
	})


CMD_DEF(POP_R, "pop", 12,
	{
		if(m_buf[4] == 'r')
		{
			if((m_buf[6] != 'x') || (m_buf[7] != '\n'))
				assert((printf("Proc popR err"), 0));			

			if((m_buf[5] != 'a') && (m_buf[5] != 'b') && (m_buf[5] != 'c') && (m_buf[5] != 'd') && (m_buf[5] != 'e'))
				assert((printf("Proc popR err"), 0));	

			char nReg;

			if(m_buf[5] == 'a')
				nReg = N_RAX;
			if(m_buf[5] == 'b')
				nReg = N_RBX;
			if(m_buf[5] == 'c')
				nReg = N_RCX;
			if(m_buf[5] == 'd')
				nReg = N_RDX;
			if(m_buf[5] == 'e')
				nReg = N_REX;

			fprintf(txtFile, "%x %x\n", N_POP_R, nReg);
			fprintf(binFile, "%c%c", N_POP_R, nReg);

			m_index += 2;
		}
	},
	{
		fprintf(txtFile, "%x ", N_POP_R);
		fprintf(asmFile, "pop ");
		switch(m_buf[m_index+1])
		{
			case N_RAX : 
			fprintf(txtFile, "%x\n", N_RAX);
			fprintf(asmFile, "rax\n");
			break;
			
			case N_RBX : 
			fprintf(txtFile, "%x\n", N_RBX);
			fprintf(asmFile, "rbx\n");
			break;

			case N_RCX : 
			fprintf(txtFile, "%x\n", N_RCX);
			fprintf(asmFile, "rcx\n");
			break;

			case N_RDX : 
			fprintf(txtFile, "%x\n", N_RDX);
			fprintf(asmFile, "rdx\n");
			break;

			case N_REX : 
			fprintf(txtFile, "%x\n", N_REX);
			fprintf(asmFile, "rex\n");
			break;

			default : assert(0);
		}

		m_index += 2;
	},
	{
		char nReg = m_code[m_index+1];
		if(m_stack.getSize() == 0)
		{
			m_errno = EMPTY_ERR;
			return EMPTY_ERR;
		}
		data_t *data;
		char dumpStr[20];

		switch(nReg)
		{
			case N_RAX : data = &m_rax; sprintf(dumpStr, "Proc pop rax"); break;
			case N_RBX : data = &m_rbx; sprintf(dumpStr, "Proc pop rbx"); break;
			case N_RCX : data = &m_rcx; sprintf(dumpStr, "Proc pop rcx"); break;
			case N_RDX : data = &m_rdx; sprintf(dumpStr, "Proc pop rdx"); break;
			case N_REX : data = &m_rex; sprintf(dumpStr, "Proc pop rex"); break;

			default : assert(0);
		}
			
		m_stack.getTop(data);
		int checkErr = m_stack.pop();
		assert(checkErr == SUCCESS);

		dumpProc(dumpStr);
		m_index += 2;
		m_errno = checkErr;
	})


CMD_DEF(POP_PR, "pop", 13,
	{
		if((m_buf[4] == '[') && (m_buf[5] == 'r'))
		{
			if((m_buf[7] != 'x') || ((m_buf[8] != ']')) || (m_buf[9] != '\n'))
				assert((printf("Proc popPR error1\n"), 0));			

			if((m_buf[6] != 'a') && (m_buf[6] != 'b') && (m_buf[6] != 'c') && (m_buf[6] != 'd') && (m_buf[6] != 'e'))
				assert((printf("Proc popPR error2\n"), 0));

			char nReg;

			if(m_buf[6] == 'a')
				nReg = N_RAX;
			if(m_buf[6] == 'b')
				nReg = N_RBX;
			if(m_buf[6] == 'c')
				nReg = N_RCX;
			if(m_buf[6] == 'd')
				nReg = N_RDX;
			if(m_buf[6] == 'e')
				nReg = N_REX;

			fprintf(txtFile, "%x %x\n", N_POP_PR, nReg);
			fprintf(binFile, "%c%c", N_POP_PR, nReg);

			m_index += 2;
		}
	},
	{
		fprintf(txtFile, "%x ", N_POP_PR);
		fprintf(asmFile, "pop [");
		switch(m_buf[m_index+1])
		{
			case N_RAX : 
			fprintf(txtFile, "%x\n", N_RAX);
			fprintf(asmFile, "rax]\n");
			break;
			
			case N_RBX : 
			fprintf(txtFile, "%x\n", N_RBX);
			fprintf(asmFile, "rbx]\n");
			break;

			case N_RCX : 
			fprintf(txtFile, "%x\n", N_RCX);
			fprintf(asmFile, "rcx]\n");
			break;

			case N_RDX : 
			fprintf(txtFile, "%x\n", N_RDX);
			fprintf(asmFile, "rdx]\n");
			break;

			case N_REX : 
			fprintf(txtFile, "%x\n", N_REX);
			fprintf(asmFile, "rex]\n");
			break;

			default : assert((printf("Proc popPR error3\n"), 0));
		}

		m_index += 2;
	},
	{
		if(m_stack.getSize() == 0)
		{
			return EMPTY_ERR;
		}
	
		char nReg = m_code[m_index+1];

		data_t *dPointer;
		char dumpStr[20];

		switch(nReg)
		{
			case N_RAX : dPointer = &m_rax; sprintf(dumpStr, "Proc pop [rax]"); break;
			case N_RBX : dPointer = &m_rbx; sprintf(dumpStr, "Proc pop [rbx]"); break;
			case N_RCX : dPointer = &m_rcx; sprintf(dumpStr, "Proc pop [rcx]"); break;
			case N_RDX : dPointer = &m_rdx; sprintf(dumpStr, "Proc pop [rdx]"); break;
			case N_REX : dPointer = &m_rex; sprintf(dumpStr, "Proc pop [rex]"); break;

			default : assert(0);
		}

		long pointer = (long)*dPointer;
		if(pointer >= m_ramSize)
		{
			printf("pointer = %ld\nm_ramSize = %ld\n", pointer, m_ramSize);
			return OVERFLOW_ERR;
		}

		data_t data;
		m_stack.getTop(&data);
		m_stack.pop();

		m_RAM[pointer] = data;

		dumpProc(dumpStr);
		m_index += 2;
	})


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
