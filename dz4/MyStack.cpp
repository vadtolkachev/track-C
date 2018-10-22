#include "MyStack.hpp"


#define PRINT_ERR(err, file, line, func, what, format)			\
{									\
	std::cout << WHITE << file <<":" << line 			\
		<< ": " << func << ": " << RED << err << " = ";		\
									\
	if(format == HEX_F)						\
		std::cout << std::hex << "0x" << what << std::dec 	\
			<< NORM <<"\n";					\
									\
	if(format == SUM1_F)	 					\
		std::cout << m_sum1 << ", but should be = "		\
			<< what << NORM << "\n";			\
									\
	if(format == SUM2_F)	 					\
		std::cout << m_sum2 << ", but should be = "		\
			<< what << NORM << "\n";			\
									\
	if(format == NORM_F)	 					\
		std::cout << what << NORM << "\n";			\
}


#define ASSERT_ERROR()				\
{						\
	int res = checkStack_print(__FILE__, 	\
		__LINE__, __PRETTY_FUNCTION__);	\
	if(res)					\
	{					\
		dumpStack();			\
		abort();			\
	}					\
}



MyStack::MyStack()
{
	m_size = 0;
	m_capacity = BUF;
	m_canary1 = (long) &m_canary1;
	m_canary2 = (long) &m_canary2;
	m_stack = (data_t *)calloc(2 + BUF, sizeof(data_t));
	m_stack[0] = CANARY3;

	for(int i = 1; i < BUF + 1; i++)
		m_stack[i] = (data_t)POISON1;

	m_stack[BUF + 1] = CANARY4;
	calcSum1();
	calcSum2();
}


MyStack::~MyStack()
{
	ASSERT_ERROR();
	free(m_stack);
}


int MyStack::checkFirstCanary() const
{
	if(m_canary1 != (long) &m_canary1)
		return CANARY1_ERR;

	return STACK_OK;
}


int MyStack::checkSecondCanary() const
{
	if(m_canary2 != (long) &m_canary2)
		return CANARY2_ERR;

	return STACK_OK;
}


int MyStack::checkThirdCanary() const
{
	if(m_stack[0] != CANARY3)
		return CANARY3_ERR;

	return STACK_OK;
}


int MyStack::checkFourthCanary() const
{
	if(m_stack[m_capacity+1] != CANARY4)
		return CANARY4_ERR;

	return STACK_OK;
}


int MyStack::checkSize() const
{
	if((m_size < 0) || (m_size > m_capacity))
		return SIZE_ERR;

	return STACK_OK;
}


int MyStack::checkCapacity() const
{
	if((m_capacity < 0) || (m_capacity % BUF != 0))
		return CAPACITY_ERR;

	return STACK_OK;
}


int MyStack::checkPoison(data_t *data) const
{
	for(int i = m_size + 1; i < m_capacity + 1; i++)
	{
		if(data)
			*data = m_stack[i];

		if((m_stack[i] != POISON1) && (m_stack[i] != POISON2))
			return POISON_ERR;
	}

	return STACK_OK;
}


int MyStack::checkSum1(long *ref) const
{
	char *pByte = (char*) this;
	long sum1 = 0;

	for(unsigned i = 0; i < sizeof(*this); i++)
	{
		if((i >= 24) && (i < 40))
			sum1 += pByte[i];
	}

	if(ref)
		*ref = sum1;
	
	if(m_sum1 != sum1)
		return SUM1_ERR;

	return STACK_OK;
}


int MyStack::checkSum2(long *ref) const
{
	char *pByte = (char*) m_stack;
	long sum2 = 0;

	for(unsigned i = 0; i < sizeof(data_t) * (m_capacity + 2); i++)
	{
		if((i >= 4) && (i < 4*(m_size+1)))
			sum2 += pByte[i];
	}

	if(ref)
		*ref = sum2;

	if(m_sum2 != sum2)
		return SUM2_ERR;

	return STACK_OK;
}


int MyStack::checkNullptr() const
{
	if(!this)
		return  NULLPTR_ERR;

	return STACK_OK;
}


int MyStack::checkStack(data_t *data, long *ref) const
{
	int err = checkNullptr();
	if(err)
		return err; 

	err = checkFirstCanary();
	if(err)
		return err; 

	err = checkSecondCanary();
	if(err)
		return err; 

	err = checkSize();
	if(err)
		return err; 

	err = checkCapacity();
	if(err)
		return err; 

	err = checkThirdCanary();
	if(err)
		return err; 

	err = checkFourthCanary();
	if(err)
		return err; 

	err = checkPoison(data);
	if(err)
		return err; 

	err = checkSum1(ref);
	if(err)
		return err; 

	err = checkSum2(ref);
	if(err)
		return err; 

	return err;
}


int MyStack::checkStack_print(const char *file, int line, const char *func) const
{
	data_t data;
	long ref;
	int nErr = checkStack(&data, &ref);

	switch(nErr)
	{
		case NULLPTR_ERR : PRINT_ERR("this = nullptr", file, line, func, 0, NORM_F);
			break;

		case CANARY1_ERR : PRINT_ERR("canary1", file, line, func, m_canary1, HEX_F);
			break;

		case CANARY2_ERR : PRINT_ERR("canary2", file, line, func, m_canary2, HEX_F);
			break;

		case SIZE_ERR : PRINT_ERR("size", file, line, func, m_size, NORM_F);
			break;

		case CAPACITY_ERR : PRINT_ERR("capacity", file, line, func, m_capacity, NORM_F);
			break;

		case CANARY3_ERR : PRINT_ERR("canary3", file, line, func, m_stack[0], HEX_F);
			break;

		case CANARY4_ERR :PRINT_ERR("canary4", file, line, func, m_stack[m_capacity+1], HEX_F);
			break;

		case POISON_ERR : PRINT_ERR("not a posion", file, line, func, data, NORM_F);
			break;

		case SUM1_ERR : PRINT_ERR("sum1", file, line, func, ref, SUM1_F);
			break;

		case SUM2_ERR : PRINT_ERR("sum2", file, line, func, ref, SUM2_F);
			break;

		case STACK_OK : break;
	
		default : PRINT_ERR("wrong error", file, line, func, nErr, NORM_F);
			break;	
	}
	
	return nErr;
}


int MyStack::getTop(data_t *res) const
{
	ASSERT_ERROR();
	if(res == nullptr)
		return NULLPTR_ERR;
	
	if(!m_size)
		return EMPTY_ERR;

	*res = m_stack[m_size];
	return SUCCESS;
}


int MyStack::getSize() const
{
	ASSERT_ERROR();
	return m_size;
}


int MyStack::getCapacity() const
{
	ASSERT_ERROR();
	return m_capacity;
}


int MyStack::push(data_t data)
{
	ASSERT_ERROR();

	if(m_capacity == m_size)
	{
		data_t *tmp;
		tmp = (data_t *) reallocarray(m_stack, m_capacity + BUF + 2, sizeof(data_t));
		if(!tmp)
		{
			ASSERT_ERROR();
			return ALLOC_ERR;
		}

		m_stack = tmp;		
		m_capacity += BUF;
		for(int i = m_size + 1; i < m_capacity + 1; i++)
			m_stack[i] = (data_t)POISON1;
		m_stack[m_capacity + 1] = CANARY4;
	}
	
	m_stack[++m_size] = data;
	
	calcSum1();
	calcSum2();

	ASSERT_ERROR();
	return SUCCESS;
}


int MyStack::pop()
{
	ASSERT_ERROR();

	if(m_size == 0)
		return EMPTY_ERR;

	m_stack[m_size--] = POISON2;
	
	if(m_capacity == m_size + BUF)
	{
		data_t *tmp;
		tmp = (data_t *) reallocarray(m_stack, m_capacity - BUF + 2, sizeof(data_t));
		if(!tmp)
		{	
			ASSERT_ERROR();
			return ALLOC_ERR;
		}

		m_stack = tmp;		
		m_capacity -= BUF;
		m_stack[m_capacity + 1] = CANARY4;
	}

	calcSum1();
	calcSum2();

	ASSERT_ERROR();
	return SUCCESS;
}


bool MyStack::isEmpty() const
{
	ASSERT_ERROR();

	if(m_size)
		return true;

	return false;
}


void MyStack::printStack() const
{
	ASSERT_ERROR();
	
	std::cout << "Stack [" << this << "]\n{"
		<< "\n\tcanary1 = 0x" << std::hex << m_canary1 << std::dec
		<< "\n\tsum1 = " << m_sum1 
		<< "\n\tsum2 = " << m_sum2
		<< "\n\tsize = " << m_size 
		<< "\n\tcapacity = " << m_capacity
		<< "\n\tdata[" << m_capacity + 2 << "] [" << m_stack << "]\n\t{";
		
	for(int i = 0; i < m_capacity + 2; i++)
	{
		std::cout << "\n\t\t";
		if((i > 0) && (i <= m_size))
			std::cout << "*";
		else
		{
			if((i == 0) || (i == m_capacity + 1))
				std::cout << ">";
			else
				std::cout << " ";
		}

		std::cout << "[" << i << "] : ";

		if((i == 0) || (i == m_capacity + 1))
			std::cout << std::hex << "0x" << m_stack[i] << std::dec;
		else
			std::cout << m_stack[i];

		if(i == 0)
			std::cout << " (canary3)";

		if(i == m_capacity + 1)
			std::cout << " (canary4)";

		if((i > m_size) && (i != m_capacity + 1))
			std::cout << " (poison)";
	}
		
	std::cout << "\n\t}\n\tcanary2 = 0x" << std::hex << m_canary2 << std::dec
		<< "\n}\n";
}


void MyStack::dumpStack() const
{
	data_t data;
	//long ref;
	int nErr = checkStack(&data, nullptr);

	std::cout << "Stack [" << this << "]";
	if(nErr)
		std::cout << " (ERROR!!!)\n";

	if(nErr == NULLPTR_ERR)
	{
		std::cout << "{nullptr!!!}\n";
		return;
	}
	
	std::cout << "{\n\tcanary1 = 0x" << std::hex << m_canary1 << std::dec;

	if(nErr == CANARY1_ERR)
	{
		std::cout << "\n}\n";
		return;
	}

	std::cout << "\n\tcanary2 = 0x" << std::hex << m_canary2 << std::dec;

	if(nErr == CANARY2_ERR)
	{
		std::cout << "\n}\n";
		return;
	}
	
	std::cout << "\n\tsize = " << m_size;
	
	if(nErr == SIZE_ERR)
	{
		std::cout << "\n}\n";
		return;
	}
	
	std::cout << "\n\tcapacity = " << m_capacity;

	if(nErr == CAPACITY_ERR)
	{
		std::cout << "\n}\n";
		return;
	}
	
	if(nErr == CANARY3_ERR)
	{
		std::cout << "\n\tcanary3 = 0x" << std::hex << m_stack[0] << std::dec << "\n}\n";
		return;
	}

	if(nErr == CANARY4_ERR)
	{
		std::cout << "\n\tcanary4 = 0x" << std::hex << m_stack[m_capacity + 1]<< std::dec << "\n}\n";
		return;
	}
	
	std::cout << "\n\tsum1 = " << m_sum1 
		<< "\n\tsum2 = " << m_sum2;

	std::cout << "\n\tdata[" << m_capacity + 2 << "] [" << m_stack << "]\n\t{";
		
	for(int i = 0; i < m_capacity + 2; i++)
	{
		std::cout << "\n\t\t";
		if((i > 0) && (i <= m_size))
			std::cout << "*";
		else
		{
			if((i == 0) || (i == m_capacity + 1))
				std::cout << ">";
			else
				std::cout << " ";
		}
	
		std::cout << "[" << i << "] : ";

		if((i == 0) || (i == m_capacity + 1))
			std::cout << std::hex << "0x" << m_stack[i] << std::dec;
		else
			std::cout << m_stack[i];

		if(i == 0)
			std::cout << " (canary3)";

		if(i == m_capacity + 1)
			std::cout << " (canary4)";

		if((i > m_size) && (i != m_capacity + 1))
			std::cout << " (poison)";
	}

	std::cout << "\n\t}\n}\n";
}


void MyStack::calcSum1()
{
	char *pByte = (char*) this;
	assert(sizeof(*this) == 48);

	m_sum1 = 0;
	for(unsigned i = 0; i < sizeof(*this); i++)
	{
		if((i >= 24) && (i < 40))
			m_sum1 += pByte[i];
	}
}


void MyStack::calcSum2()
{
	char *pByte = (char*) m_stack;
	m_sum2 = 0;
	for(unsigned i = 0; i < sizeof(data_t) * (m_capacity + 2); i++)
	{
		if((i >= 4) && (i < 4*(m_size+1)))
			m_sum2 += pByte[i];
	}
}