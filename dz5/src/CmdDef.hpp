CMD_DEF(ADD, 1,	
	if(strncmp("add", m_buf, 3) == 0)
	{
		if(m_buf[3] != '\n')
		{
			printf("asm add err\n");
			assert(0);
			m_errno = PARSE_ERR;
		}

		fprintf(txtFile, "%x\n", N_ADD);
		fprintf(binFile, "%c", N_ADD);		
	
		m_index++;
	},
	{
		fprintf(txtFile, "%x\n", N_ADD);
		fprintf(asmFile, "add\n");

		m_index++;
	},
	{
		if(m_stack.getSize() < 2)
		{
			m_errno = EMPTY_ERR;
			return EMPTY_ERR;
		}

		data_t data1;
		data_t data2;
		
		m_stack.getTop(&data1);
		m_stack.pop();
		m_stack.getTop(&data2);
		m_stack.pop();

		
		int checkErr = m_stack.push(data1 + data2);

		dumpProc("Proc add");
		m_index++;
		m_errno = checkErr;
	})


CMD_DEF(SUB, 2,
	if(strncmp("sub", m_buf, 3) == 0)
	{
		if(m_buf[3] != '\n')
		{
			printf("asm sub err\n");
			assert(0);
			m_errno = PARSE_ERR;
		}

		fprintf(txtFile, "%x\n", N_SUB);
		fprintf(binFile, "%c", N_SUB);

		m_index++;
	},
	{
		fprintf(txtFile, "%x\n", N_SUB);
		fprintf(asmFile, "sub\n");

		m_index++;
	},
	{
		if(m_stack.getSize() < 2)
		{
			m_errno = EMPTY_ERR;
			return EMPTY_ERR;
		}

		data_t data1;
		data_t data2;
		
		m_stack.getTop(&data1);
		m_stack.pop();
		m_stack.getTop(&data2);
		m_stack.pop();

		
		int checkErr = m_stack.push(data2 - data1);

		dumpProc("Proc sub");
		m_index++;
		m_errno = checkErr;
	})


CMD_DEF(MUL, 3,
	if(strncmp("mul", m_buf, 3) == 0)
	{
		if(m_buf[3] != '\n')
		{
			printf("asm mul err\n");
			assert(0);
			m_errno = PARSE_ERR;
		}

		fprintf(txtFile, "%x\n", N_MUL);
		fprintf(binFile, "%c", N_MUL);	

		m_index++;	
	},
	{
		fprintf(txtFile, "%x\n", N_MUL);
		fprintf(asmFile, "mul\n");

		m_index++;
	},
	{
		if(m_stack.getSize() < 2)
		{
			m_errno = EMPTY_ERR;
			return EMPTY_ERR;
		}

		data_t data1;
		data_t data2;
		
		m_stack.getTop(&data1);
		m_stack.pop();
		m_stack.getTop(&data2);
		m_stack.pop();

		
		int checkErr = m_stack.push(data1 * data2);

		dumpProc("Proc mul");
		m_index++;
		m_errno = checkErr;
	})


CMD_DEF(DIV, 4,
	if(strncmp("div", m_buf, 3) == 0)
	{
		if(m_buf[3] != '\n')
		{
			printf("asm div err\n");
			assert(0);
			m_errno = PARSE_ERR;
		}

		fprintf(txtFile, "%x\n", N_DIV);
		fprintf(binFile, "%c", N_DIV);	

		m_index++;	
	},
	{
		fprintf(txtFile, "%x\n", N_DIV);
		fprintf(asmFile, "div\n");

		m_index++;
	},
	{
		if(m_stack.getSize() < 2)
		{
			m_errno = EMPTY_ERR;
			return EMPTY_ERR;
		}

		data_t data1;
		data_t data2;
		
		m_stack.getTop(&data1);
		m_stack.pop();
		m_stack.getTop(&data2);
		m_stack.pop();


		dumpProc("Proc div");
		m_index++;	
		#ifdef S_DOUBLE
		int checkErr = m_stack.push(data2/data1);

		m_errno = checkErr;
		#else
		m_errno = TYPE_ERR;
		return TYPE_ERR;
		#endif
	})


CMD_DEF(SIN, 40,
	if(strncmp("sin", m_buf, 3) == 0)
	{
		if(m_buf[3] != '\n')
		{
			printf("asm sin err\n");
			assert(0);
			m_errno = PARSE_ERR;
		}

		fprintf(txtFile, "%x\n", N_SIN);
		fprintf(binFile, "%c", N_SIN);	

		m_index++;	
	},
	{
		fprintf(txtFile, "%x\n", N_SIN);
		fprintf(asmFile, "sin\n");

		m_index++;
	},
	{
		if(m_stack.getSize() < 1)
		{
			m_errno = EMPTY_ERR;
			return EMPTY_ERR;
		}

		data_t data;
		m_stack.getTop(&data);
		m_stack.pop();


		dumpProc("Proc sin");
		m_index++;
		#ifdef S_DOUBLE
		int checkErr = m_stack.push(sin(data));

		m_errno = checkErr;
		#else
		m_errno = TYPE_ERR;
		return TYPE_ERR;
		#endif
	})


CMD_DEF(COS, 41,
	if(strncmp("cos", m_buf, 3) == 0)
	{
		if(m_buf[3] != '\n')
		{
			printf("asm cos err\n");
			assert(0);
			m_errno = PARSE_ERR;
		}

		fprintf(txtFile, "%x\n", N_COS);
		fprintf(binFile, "%c", N_COS);	

		m_index++;	
	},
	{
		fprintf(txtFile, "%x\n", N_COS);
		fprintf(asmFile, "cos\n");

		m_index++;
	},
	{
		if(m_stack.getSize() < 1)
		{
			m_errno = EMPTY_ERR;
			return EMPTY_ERR;
		}

		data_t data;
		m_stack.getTop(&data);
		m_stack.pop();

		dumpProc("Proc cos");	
		m_index++;
		#ifdef S_DOUBLE
		int checkErr = m_stack.push(cos(data));

		m_errno = checkErr;
		#else
		m_errno = TYPE_ERR;
		return TYPE_ERR;
		#endif
	})


CMD_DEF(SQRT, 42,
	if(strncmp("sqrt", m_buf, 4) == 0)
	{
		if(m_buf[4] != '\n')
		{
			printf("asm sqrt err\n");
			assert(0);
			m_errno = PARSE_ERR;
		}

		fprintf(txtFile, "%x\n", N_SQRT);
		fprintf(binFile, "%c", N_SQRT);	

		m_index++;	
	},
	{
		fprintf(txtFile, "%x\n", N_SQRT);
		fprintf(asmFile, "sqrt\n");

		m_index++;
	},
	{
		if(m_stack.getSize() < 1)
		{
			m_errno = EMPTY_ERR;
			return EMPTY_ERR;
		}

		data_t data;
		m_stack.getTop(&data);
		m_stack.pop();

		dumpProc("Proc sqrt");	
		m_index++;
		#ifdef S_DOUBLE
		int checkErr = m_stack.push(sqrt(data));

		m_errno = checkErr;
		#else
		m_errno = TYPE_ERR;
		return TYPE_ERR;
		#endif
	})


CMD_DEF(OUT, 5,
	({if(strncmp("out", m_buf, 3) == 0)
	{
		if(m_buf[3] != '\n')
		{
			printf("asm out err\n");
			assert(0);
			m_errno = PARSE_ERR;
		}

		fprintf(txtFile, "%x\n", N_OUT);
		fprintf(binFile, "%c", N_OUT);	

		m_index++;	
	}}),
	({
		fprintf(txtFile, "%x\n", N_OUT);
		fprintf(asmFile, "out\n");

		m_index++;
	}),
	({
		if(m_stack.getSize() < 1)
		{
			m_errno = EMPTY_ERR;
			return EMPTY_ERR;
		}

		data_t data;
		m_stack.getTop(&data);
		m_stack.pop();

		dumpProc("Proc out");
		m_index++;
		#ifdef S_DOUBLE
		printf("Proc out : %lg\n", data);
		#else
		m_errno = TYPE_ERR;
		return TYPE_ERR;
		#endif
	}))


CMD_DEF(IN, 50,
	if(strncmp("in", m_buf, 2) == 0)
	{
		if(m_buf[2] != '\n')
		{
			printf("asm in err\n");
			assert(0);
			m_errno = PARSE_ERR;
		}

		fprintf(txtFile, "%x\n", N_IN);
		fprintf(binFile, "%c", N_IN);		

		m_index++;
	},
	{
		fprintf(txtFile, "%x\n", N_IN);
		fprintf(asmFile, "in\n");

		m_index++;
	},
	{
		double tmp;
		scanf("%lg", &tmp);

		int checkErr = m_stack.push(tmp);
		if(checkErr != SUCCESS)
			return checkErr;

		char str[25] = "";
		sprintf(str, "Proc in : %lg", tmp);
		dumpProc(str);
		m_index++;
	})


CMD_DEF(END, 6,
	if(strncmp("end", m_buf, 3) == 0)
	{
		if(m_buf[3] != '\n')
		{
			printf("asm end err\n");
			assert(0);
			m_errno = PARSE_ERR;
		}

		fprintf(txtFile, "%x\n", N_END);
		fprintf(binFile, "%c", N_END);	

		m_index++;	
	},
	{
		fprintf(txtFile, "%x\n", N_END);
		fprintf(asmFile, "end\n");

		m_index++;
	},
	{
		m_index = size; 
		dumpProc("Proc end");
	})


CMD_DEF(PUSH, 7,
	if(strncmp("push", m_buf, 4) == 0)
	{
		if((isdigit(m_buf[5])) || (m_buf[5] == '-'))
		{
			double d;
			char* pPosition = strchr(m_buf, '\n');
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

			#ifdef S_DOUBLE
			m_index += 1 + sizeof(double);
			#else
			assert(0);
			#endif
		}
	},
	{
		double *tmp = (double *)&m_buf[m_index+1];
		fprintf(txtFile, "%x %lg\n", N_PUSH, *tmp);
		fprintf(asmFile, "push %lg\n", *tmp);

		#ifdef S_DOUBLE
		m_index += 1 + sizeof(double);
		#else
		assert(0);
		#endif
	},
	{
		double *pTmp = (double *)&m_code[m_index+1];
		double data = *pTmp;	

		int checkErr = m_stack.push(data);
		assert(checkErr == SUCCESS);

		char str[30] = "";

		#ifdef S_DOUBLE
		m_index += 1 + sizeof(double);
		sprintf(str, "Proc push %lg", data);
		#else
		m_errno = TYPE_ERR;
		assert(0);
		return TYPE_ERR;
		#endif

		dumpProc(str);
		m_errno = checkErr;
	})


CMD_DEF(PUSH_P, 9,
	if(strncmp("push", m_buf, 4) == 0)
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
		#ifndef S_DOUBLE
		m_errno = TYPE_ERR;
		assert(0);
		return TYPE_ERR;
		#endif

		long pointer = *((long *)&m_code[m_index+1]);
		if(pointer >= m_ramSize)
			return OVERFLOW_ERR;
		
		double data;
		char *pTmp = (char *)&data;
		for(int i = 0; i < (int)sizeof(double); i++)
			pTmp[i] = m_RAM[pointer+i];
		
		int checkErr = m_stack.push(data);
		assert(checkErr == SUCCESS);

		char str[40] = "";

		m_index += 1 + sizeof(long);
		sprintf(str, "Proc pushP m_RAM[%ld] %lg", pointer, data);

		dumpProc(str);
		m_errno = checkErr;
	})

CMD_DEF(PUSH_R, 10,
	if(strncmp("push", m_buf, 4) == 0)
	{
		if(m_buf[5] == 'r')
		{
			if((m_buf[7] != 'x') || (m_buf[8] != '\n'))
			{
				printf("asm pushR err\n");
				assert(0);			
			}
			if((m_buf[6] != 'a') && (m_buf[6] != 'b') && (m_buf[6] != 'c') && (m_buf[6] != 'd') && (m_buf[6] != 'e'))
			{
				printf("asm pushR err\n");
				assert(0);
			}
			char nReg;
			//#define REG_DEF(a,b,c) nReg = 1;
			//#include "RegDef.hpp"
			//#undef REG_DEF

			/*char tmps[2] = ""
			#define REG_DEF(big_name, small_name, numb) 	\
			strcpy(tmps, #small_name);			\
			if(m_buf[6] == tmps[0])				\
				nReg = N_R##big_name##X;

			#include "RegDef.hpp"

			#undef REG_DEF*/
						
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

			fprintf(txtFile, "%x %x\n", N_PUSH_R, nReg);
			fprintf(binFile, "%c%c", N_PUSH_R, nReg);

			m_index += 2;
		}
	},
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


CMD_DEF(PUSH_PR, 11,
	if(strncmp("push", m_buf, 4) == 0)
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
		#ifndef S_DOUBLE
		m_errno = TYPE_ERR;
		assert(0);
		return TYPE_ERR;
		#endif

		char nReg = m_code[m_index+1];
		if(m_stack.getSize() == 0)
		{
			m_errno = EMPTY_ERR;
			return EMPTY_ERR;
		}
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

		long pointer = (long)dPointer;
		if(pointer >= m_ramSize)
			return OVERFLOW_ERR;
		
		double data;
		char *pTmp = (char *)&data;
		for(int i = 0; i < (int)sizeof(double); i++)
			pTmp[i] = m_RAM[pointer+i];
		
		int checkErr = m_stack.push(data);
		assert(checkErr == SUCCESS);

		m_index += 1 + sizeof(long);
		dumpProc(dumpStr);

		m_errno = checkErr;
	})


CMD_DEF(POP, 8,
	if(strncmp("pop", m_buf, 3) == 0)
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


CMD_DEF(POP_R, 12,
	if(strncmp("pop", m_buf, 3) == 0)
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


CMD_DEF(POP_PR, 13,
	if(strncmp("pop", m_buf, 3) == 0)
	{
		if(m_buf[4] == '[')
		{
			if((m_buf[5] != 'r') || (m_buf[7] != 'x') || ((m_buf[8] != ']')) || (m_buf[9] != '\n'))
				assert(0);			

			if((m_buf[6] != 'a') && (m_buf[6] != 'b') && (m_buf[6] != 'c') && (m_buf[6] != 'd') && (m_buf[6] != 'e'))
				assert(0);

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

			default : assert(0);
		}

		m_index += 2;
	},
	{
		#ifndef S_DOUBLE
		m_errno = TYPE_ERR;
		assert(0);
		return TYPE_ERR;
		#endif

		char nReg = m_code[m_index+1];
		if(m_stack.getSize() == 0)
		{
			m_errno = EMPTY_ERR;
			return EMPTY_ERR;
		}
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

		long pointer = (long)dPointer;
		if(pointer >= m_ramSize)
			return OVERFLOW_ERR;
		
		data_t data;
		m_stack.getTop(&data);
		m_stack.pop();

		char *pTmp = (char *)&data;
		for(int i = 0; i < (int)sizeof(double); i++)
			m_RAM[pointer+i] = pTmp[i];

		dumpProc(dumpStr);
		m_index += 1 + sizeof(long);
	})


CMD_DEF(JMP, 30,
	if(strncmp("jmp ", m_buf, 4) == 0)
	{
		char label[MAX_LABEL_LEN] = "";
		strcpy(label, &m_buf[4]);
		
		findLabel(txtFile, binFile, label, N_JMP);
		
		m_index += 1 + sizeof(int);
	},
	{
		int *tmp = (int *)&m_buf[m_index+1];

		fprintf(txtFile, "%x %d\n", N_JMP, *tmp);
		fprintf(asmFile, "jmp %d\n", *tmp);

		m_index += 1 + sizeof(int);
	},
	{
		int *pTmp = (int *)&(m_code[m_index+1]);
		int numb = *pTmp;
		m_index = numb;

		char dumpStr[20] = "";
		sprintf(dumpStr, "Proc jmp : %d", numb);
		dumpProc(dumpStr);
	})


CMD_DEF(JA, 31,
	if(strncmp("ja ", m_buf, 3) == 0)
	{
		char label[MAX_LABEL_LEN] = "";
		strcpy(label, &m_buf[3]);
		
		findLabel(txtFile, binFile, label, N_JA);
		
		m_index += 1 + sizeof(int);
	},
	{
		int *tmp = (int *)&m_buf[m_index+1];

		fprintf(txtFile, "%x %d\n", N_JA, *tmp);
		fprintf(asmFile, "ja %d\n", *tmp);

		m_index += 1 + sizeof(int);
	},
	{
		int *pTmp = (int *)&(m_code[m_index+1]);
		int numb = *pTmp;
		if(m_stack.getSize() < 2)
		{
			m_errno = EMPTY_ERR;
			return EMPTY_ERR;
		}

		data_t data1;
		data_t data2;
		
		m_stack.getTop(&data1);
		m_stack.pop();
		m_stack.getTop(&data2);
		m_stack.pop();

		if(data1 > data2)
			m_index = numb;
		else 
			m_index += 1 + sizeof(int);

		char dumpStr[60] = "";
		sprintf(dumpStr, "Proc ja : %d if(%lg > %lg)", numb, data1, data2);
		dumpProc(dumpStr);
	})


CMD_DEF(JB, 32,
	if(strncmp("jb ", m_buf, 3) == 0)
	{
		char label[MAX_LABEL_LEN] = "";
		strcpy(label, &m_buf[3]);
		
		findLabel(txtFile, binFile, label, N_JB);
		
		m_index += 1 + sizeof(int);
	},
	{
		int *tmp = (int *)&m_buf[m_index+1];

		fprintf(txtFile, "%x %d\n", N_JB, *tmp);
		fprintf(asmFile, "jb %d\n", *tmp);

		m_index += 1 + sizeof(int);
	},
	{
		int *pTmp = (int *)&(m_code[m_index+1]);
		int numb = *pTmp;
		if(m_stack.getSize() < 2)
		{
			m_errno = EMPTY_ERR;
			return EMPTY_ERR;
		}

		data_t data1;
		data_t data2;
		
		m_stack.getTop(&data1);
		m_stack.pop();
		m_stack.getTop(&data2);
		m_stack.pop();

		if(data1 < data2)
			m_index = numb;
		else 
			m_index += 1 + sizeof(int);

		char dumpStr[60] = "";
		sprintf(dumpStr, "Proc jb : %d if(%lg < %lg)", numb, data1, data2);
		dumpProc(dumpStr);
	})


CMD_DEF(JE, 33,
	if(strncmp("je ", m_buf, 3) == 0)
	{
		char label[MAX_LABEL_LEN] = "";
		strcpy(label, &m_buf[3]);
		
		findLabel(txtFile, binFile, label, N_JE);
		
		m_index += 1 + sizeof(int);
	},
	{
		int *tmp = (int *)&m_buf[m_index+1];

		fprintf(txtFile, "%x %d\n", N_JE, *tmp);
		fprintf(asmFile, "je %d\n", *tmp);

		m_index += 1 + sizeof(int);
	},
	{
		int *pTmp = (int *)&(m_code[m_index+1]);
		int numb = *pTmp;
		if(m_stack.getSize() < 2)
		{
			m_errno = EMPTY_ERR;
			return EMPTY_ERR;
		}

		data_t data1;
		data_t data2;
		
		m_stack.getTop(&data1);
		m_stack.pop();
		m_stack.getTop(&data2);
		m_stack.pop();

		if(data1 == data2)
			m_index = numb;
		else 
			m_index += 1 + sizeof(int);

		char dumpStr[60] = "";
		sprintf(dumpStr, "Proc je : %d if(%lg == %lg)", numb, data1, data2);
		dumpProc(dumpStr);
	})


CMD_DEF(JAE, 34,
	if(strncmp("jae ", m_buf, 4) == 0)
	{
		char label[MAX_LABEL_LEN] = "";
		strcpy(label, &m_buf[4]);
		
		findLabel(txtFile, binFile, label, N_JAE);
		
		m_index += 1 + sizeof(int);
	},
	{
		int *tmp = (int *)&m_buf[m_index+1];

		fprintf(txtFile, "%x %d\n", N_JAE, *tmp);
		fprintf(asmFile, "jae %d\n", *tmp);

		m_index += 1 + sizeof(int);
	},
	{
		int *pTmp = (int *)&(m_code[m_index+1]);
		int numb = *pTmp;
		if(m_stack.getSize() < 2)
		{
			m_errno = EMPTY_ERR;
			return EMPTY_ERR;
		}

		data_t data1;
		data_t data2;
		
		m_stack.getTop(&data1);
		m_stack.pop();
		m_stack.getTop(&data2);
		m_stack.pop();

		if(data1 >= data2)
			m_index = numb;
		else 
			m_index += 1 + sizeof(int);

		char dumpStr[60] = "";
		sprintf(dumpStr, "Proc jae : %d if(%lg >= %lg)", numb, data1, data2);
		dumpProc(dumpStr);
	})


CMD_DEF(JBE, 35,
	if(strncmp("jbe ", m_buf, 4) == 0)
	{
		char label[MAX_LABEL_LEN] = "";
		strcpy(label, &m_buf[4]);
		
		findLabel(txtFile, binFile, label, N_JBE);
		
		m_index += 1 + sizeof(int);
	},
	{
		int *tmp = (int *)&m_buf[m_index+1];

		fprintf(txtFile, "%x %d\n", N_JBE, *tmp);
		fprintf(asmFile, "jbe %d\n", *tmp);

		m_index += 1 + sizeof(int);
	},
	{
		int *pTmp = (int *)&(m_code[m_index+1]);
		int numb = *pTmp;
		if(m_stack.getSize() < 2)
		{
			m_errno = EMPTY_ERR;
			return EMPTY_ERR;
		}

		data_t data1;
		data_t data2;
		
		m_stack.getTop(&data1);
		m_stack.pop();
		m_stack.getTop(&data2);
		m_stack.pop();

		if(data1 <= data2)
			m_index = numb;
		else 
			m_index += 1 + sizeof(int);

		char dumpStr[60] = "";
		sprintf(dumpStr, "Proc jbe : %d if(%lg <= %lg)", numb, data1, data2);
		dumpProc(dumpStr);
	})


CMD_DEF(JNE, 36,
	if(strncmp("jne ", m_buf, 4) == 0)
	{
		char label[MAX_LABEL_LEN] = "";
		strcpy(label, &m_buf[4]);
		
		findLabel(txtFile, binFile, label, N_JNE);
		
		m_index += 1 + sizeof(int);
	},
	{
		int *tmp = (int *)&m_buf[m_index+1];

		fprintf(txtFile, "%x %d\n", N_JNE, *tmp);
		fprintf(asmFile, "jne %d\n", *tmp);

		m_index += 1 + sizeof(int);
	},
	{
		int *pTmp = (int *)&(m_code[m_index+1]);
		int numb = *pTmp;
		if(m_stack.getSize() < 2)
		{
			m_errno = EMPTY_ERR;
			return EMPTY_ERR;
		}

		data_t data1;
		data_t data2;
		
		m_stack.getTop(&data1);
		m_stack.pop();
		m_stack.getTop(&data2);
		m_stack.pop();

		if(data1 != data2)
			m_index = numb;
		else 
			m_index += 1 + sizeof(int);

		char dumpStr[60] = "";
		sprintf(dumpStr, "Proc jne : %d if(%lg != %lg)", numb, data1, data2);
		dumpProc(dumpStr);
	})


CMD_DEF(JW, 37,
	if(strncmp("jw ", m_buf, 3) == 0)
	{
		char label[MAX_LABEL_LEN] = "";
		strcpy(label, &m_buf[3]);
		
		findLabel(txtFile, binFile, label, N_JW);
		
		m_index += 1 + sizeof(int);
	},
	{
		int *tmp = (int *)&m_buf[m_index+1];

		fprintf(txtFile, "%x %d\n", N_JW, *tmp);
		fprintf(asmFile, "jw %d\n", *tmp);

		m_index += 1 + sizeof(int);
	},
	{
		int *pTmp = (int *)&(m_code[m_index+1]);
		int numb = *pTmp;
		if(1)
			m_index = numb;
		else
			m_index += 1 + sizeof(int);


		char dumpStr[20] = "";
		sprintf(dumpStr, "Proc jw : %d", numb);
		dumpProc(dumpStr);
	})


CMD_DEF(LAB, 38,
	if(m_buf[0] == ':')
	{
		int checkErr = OVERFLOW_ERR;
		
		for(int i = 0; i < ASM_LABELS_SIZE; i++)
		{
			if(!strlen(m_labels[i].m_name))
			{
				m_labels[i].m_numb = m_index;
				strcpy(m_labels[i].m_name, &m_buf[1]);

				char *tmp = (char *)&m_index;
				fprintf(txtFile, "%x %d\n", N_LAB, m_index);
				fprintf(binFile, "%c", N_LAB);
				for(int j = 0; j < (int)sizeof(int); j++)
					fprintf(binFile, "%c", tmp[j]);

				checkErr = SUCCESS;
				break;
			}
		}
		
		m_index += 1 + sizeof(int);
		if(checkErr != SUCCESS)
			m_errno = checkErr;
	},
	{
		int *tmp = (int *)&m_buf[m_index+1];

		fprintf(txtFile, "%x %d\n", N_LAB, *tmp);
		fprintf(asmFile, ":%d\n", *tmp);

		m_index += 1 + sizeof(int);
	},
	{
		dumpProc("Proc label");
		m_index += 1 + sizeof(int);
	})


CMD_DEF(CALL, 43,
	if(strncmp("call ", m_buf, 5) == 0)
	{
		char label[MAX_LABEL_LEN] = "";
		strcpy(label, &m_buf[5]);
		
		findLabel(txtFile, binFile, label, N_CALL);
		
		m_index += 1 + sizeof(int);
	},
	{
		int *tmp = (int *)&m_buf[m_index+1];

		fprintf(txtFile, "%x %d\n", N_CALL, *tmp);
		fprintf(asmFile, "call %d\n", *tmp);

		m_index += 1 + sizeof(int);
	},
	{
		int numb = m_index + 1 + sizeof(int);
		data_t tmp = (data_t)numb;
		int checkErr = m_retStack.push(tmp);

		if(checkErr != SUCCESS)
			m_errno = checkErr;

		int *pTmp = (int *)&(m_code[m_index+1]);
		m_index = *pTmp;

		char dumpStr[20] = "";
		sprintf(dumpStr, "Proc call : %d", numb);
		dumpProc(dumpStr);
	})


CMD_DEF(RET, 44,
	if(strncmp("ret", m_buf, 3) == 0)
	{
		if(m_buf[3] != '\n')
		{
			assert(0);
			m_errno = PARSE_ERR;
		}

		fprintf(txtFile, "%x\n", N_RET);
		fprintf(binFile, "%c", N_RET);		

		m_index++;
	},
	{
		fprintf(txtFile, "%x\n", N_RET);
		fprintf(asmFile, "ret\n");

		m_index++;
	},
	{
		if(m_retStack.getSize() == 0)
		{
			assert(0);
			return EMPTY_ERR;
		}

		data_t data;
		m_retStack.getTop(&data);
		m_retStack.pop();

		int numb = (int)data;
		if(numb < 0)
		{
			assert(0);
			return OVERFLOW_ERR;
		}

		m_index = numb;

		char dumpStr[20] = "";
		sprintf(dumpStr, "Proc ret : %d", numb);
		dumpProc(dumpStr);
	})

