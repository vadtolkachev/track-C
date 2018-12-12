#pragma once


#define ADD_DER_CODE								\
{										\
	if(!oldNode->getRight())						\
		return NULLPTR_ERR;						\
										\
	newNode->setFunc(F_ADD);						\
										\
	checkErr = newNode->createLeft();					\
	CHECKERR();								\
	checkErr = newNode->createRight();					\
	CHECKERR();								\
										\
	checkErr = derivateNode(oldNode->getLeft(), newNode->getLeft());	\
	CHECKERR();								\
	checkErr = derivateNode(oldNode->getRight(), newNode->getRight());	\
	CHECKERR();								\
}


#define SUB_DER_CODE								\
{										\
	if(!oldNode->getRight())						\
		return NULLPTR_ERR;						\
										\
	newNode->setFunc(F_SUB);						\
										\
	checkErr = newNode->createLeft();					\
	CHECKERR();								\
	checkErr = newNode->createRight();					\
	CHECKERR();								\
										\
	checkErr = derivateNode(oldNode->getLeft(), newNode->getLeft());	\
	CHECKERR();								\
	checkErr = derivateNode(oldNode->getRight(), newNode->getRight());	\
	CHECKERR();								\
}


#define MUL_DER_CODE 								\
{										\
	if(!oldNode->getRight())						\
		return NULLPTR_ERR;						\
										\
	checkErr = newNode->createLeft();					\
	CHECKERR();								\
	checkErr = newNode->createRight();					\
	CHECKERR();								\
	checkErr = newNode->getLeft()->createLeft();				\
	CHECKERR();								\
	checkErr = newNode->getLeft()->createRight();				\
	CHECKERR();								\
	checkErr = newNode->getRight()->createLeft();				\
	CHECKERR();								\
	checkErr = newNode->getRight()->createRight();				\
	CHECKERR();								\
										\
	newNode->setFunc(F_ADD);						\
	newNode->getLeft()->setFunc(F_MUL);					\
	newNode->getRight()->setFunc(F_MUL);					\
										\
	checkErr = derivateNode(oldNode->getLeft(), 				\
		newNode->getLeft()->getLeft());					\
	CHECKERR();								\
	checkErr = newNode->getLeft()->getRight()->copy(oldNode->getRight());	\
	CHECKERR();								\
										\
	checkErr = derivateNode(oldNode->getRight(), 				\
		newNode->getRight()->getRight());				\
	CHECKERR();								\
	checkErr = newNode->getRight()->getLeft()->copy(oldNode->getLeft());	\
	CHECKERR();								\
}										\


#define DIV_DER_CODE								\
{										\
	if(!oldNode->getRight())						\
		return NULLPTR_ERR;						\
										\
	checkErr = newNode->createLeft();					\
	CHECKERR();								\
	checkErr = newNode->getLeft()->createLeft();				\
	CHECKERR();								\
	checkErr = newNode->getLeft()->getLeft()->createLeft();			\
	CHECKERR();								\
	checkErr = newNode->getLeft()->getLeft()->createRight();		\
	CHECKERR();								\
	checkErr = newNode->getLeft()->createRight();				\
	CHECKERR();								\
	checkErr = newNode->getLeft()->getRight()->createLeft();		\
	CHECKERR();								\
	checkErr = newNode->getLeft()->getRight()->createRight();		\
	CHECKERR();								\
										\
	checkErr = newNode->createRight();					\
	CHECKERR();								\
	checkErr = newNode->getRight()->createLeft();				\
	CHECKERR();								\
	checkErr = newNode->getRight()->createRight();				\
	CHECKERR();								\
										\
	newNode->setFunc(F_DIV);						\
	newNode->getLeft()->setFunc(F_SUB);					\
	newNode->getLeft()->getLeft()->setFunc(F_MUL);				\
	newNode->getLeft()->getRight()->setFunc(F_MUL);				\
	newNode->getRight()->setFunc(F_POW);					\
										\
	checkErr = derivateNode(oldNode->getLeft(), 				\
		newNode->getLeft()->getLeft()->getLeft());			\
	CHECKERR();								\
	checkErr = newNode->getLeft()->getLeft()->				\
		getRight()->copy(oldNode->getRight());				\
	CHECKERR();								\
										\
	checkErr = derivateNode(oldNode->getRight(), 				\
		newNode->getLeft()->getRight()->getRight());			\
	CHECKERR();								\
	checkErr = newNode->getLeft()->getRight()->				\
		getLeft()->copy(oldNode->getLeft());				\
	CHECKERR();								\
										\
	checkErr = newNode->getRight()->getLeft()->copy(oldNode->getRight());	\
	CHECKERR();								\
	newNode->getRight()->getRight()->setDouble(2);				\
}		

#define SIN_DER_CODE								\
{										\
	if(oldNode->getRight())							\
		return NOTNULLPTR_ERR;						\
										\
	checkErr = newNode->createLeft();					\
	CHECKERR();								\
	checkErr = newNode->getLeft()->createLeft();				\
	CHECKERR();								\
	checkErr = newNode->createRight();					\
	CHECKERR();								\
										\
	newNode->setFunc(F_MUL);						\
	newNode->getLeft()->setFunc(F_COS);					\
	newNode->getLeft()->getLeft()->copy(oldNode->getLeft());		\
	checkErr = derivateNode(oldNode->getLeft(), newNode->getRight());	\
	CHECKERR();								\
}

#define COS_DER_CODE								\
{										\
	if(oldNode->getRight())							\
		return NOTNULLPTR_ERR;						\
										\
	checkErr = newNode->createLeft();					\
	CHECKERR();								\
	checkErr = newNode->createRight();					\
	CHECKERR();								\
	checkErr = newNode->getRight()->createLeft();				\
	CHECKERR();								\
	checkErr = newNode->getRight()->getLeft()->createLeft();		\
	CHECKERR();								\
	checkErr = newNode->getRight()->createRight();				\
	CHECKERR();								\
										\
	newNode->setFunc(F_MUL);						\
	newNode->getLeft()->setDouble(-1);					\
	newNode->getRight()->setFunc(F_MUL);					\
	newNode->getRight()->getLeft()->setFunc(F_SIN);				\
	newNode->getRight()->getLeft()->getLeft()->copy(oldNode->getLeft());	\
	checkErr = derivateNode(oldNode->getLeft(),				\
		newNode->getRight()->getRight());				\
	CHECKERR();								\
}

#define TG_DER_CODE								\
{										\
	if(oldNode->getRight())							\
		return NOTNULLPTR_ERR;						\
										\
	checkErr = newNode->createRight();					\
	CHECKERR();								\
	checkErr = newNode->createLeft();					\
	CHECKERR();								\
	checkErr = newNode->getLeft()->createLeft();				\
	CHECKERR();								\
	checkErr = newNode->getLeft()->createRight();				\
	CHECKERR();								\
	checkErr = newNode->getLeft()->getRight()->createLeft();		\
	CHECKERR();								\
	checkErr = newNode->getLeft()->getRight()->				\
		getLeft()->createLeft();					\
	CHECKERR();								\
	checkErr = newNode->getLeft()->getRight()->createRight();		\
	CHECKERR();								\
										\
	newNode->setFunc(F_MUL);						\
	newNode->getLeft()->setFunc(F_DIV);					\
	newNode->getLeft()->getLeft()->setDouble(1);				\
	newNode->getLeft()->getRight()->setFunc(F_POW);				\
	newNode->getLeft()->getRight()->getLeft()->setFunc(F_COS);		\
	checkErr = newNode->getLeft()->getRight()->getLeft()->			\
		getLeft()->copy(oldNode->getLeft());				\
	CHECKERR();								\
	newNode->getLeft()->getRight()->getRight()->setDouble(2);		\
	checkErr = derivateNode(oldNode->getLeft(), newNode->getRight());	\
	CHECKERR();								\
}


#define CTG_DER_CODE								\
{										\
	if(oldNode->getRight())							\
		return NOTNULLPTR_ERR;						\
										\
	checkErr = newNode->createLeft();					\
	CHECKERR();								\
	checkErr = newNode->createRight();					\
	CHECKERR();								\
	checkErr = newNode->getRight()->createLeft();				\
	CHECKERR();								\
	checkErr = newNode->getRight()->getLeft()->createLeft();		\
	CHECKERR();								\
	checkErr = newNode->getRight()->getLeft()->createRight();		\
	CHECKERR();								\
	checkErr = newNode->getRight()->getLeft()->getRight()->createLeft();	\
	CHECKERR();								\
	checkErr = newNode->getRight()->getLeft()->getRight()->			\
		getLeft()->createLeft();					\
	CHECKERR();								\
	checkErr = newNode->getRight()->getLeft()->getRight()->createRight();	\
	CHECKERR();								\
	checkErr = newNode->getRight()->createRight();				\
	CHECKERR();								\
										\
	newNode->setFunc(F_MUL);						\
	newNode->getLeft()->setDouble(-1);					\
	newNode->getRight()->setFunc(F_MUL);					\
	newNode->getRight()->getLeft()->setFunc(F_DIV);				\
	newNode->getRight()->getLeft()->getLeft()->setDouble(1);		\
	newNode->getRight()->getLeft()->getRight()->setFunc(F_POW);		\
	newNode->getRight()->getLeft()->getRight()->getLeft()->setFunc(F_SIN);	\
	checkErr = newNode->getRight()->getLeft()->getRight()->getLeft()->	\
		getLeft()->copy(oldNode->getLeft());				\
	CHECKERR();								\
	newNode->getRight()->getLeft()->getRight()->getRight()->setDouble(2);	\
	checkErr = derivateNode(oldNode->getLeft(), 				\
		newNode->getRight()->getRight());				\
	CHECKERR();								\
}


#define SQRT_DER_CODE								\
{										\
	if(oldNode->getRight())							\
		return NOTNULLPTR_ERR;						\
										\
	checkErr = newNode->createLeft();					\
	CHECKERR();								\
	checkErr = newNode->createRight();					\
	CHECKERR();								\
	checkErr = newNode->getLeft()->createLeft();				\
	CHECKERR();								\
	checkErr = newNode->getLeft()->createRight();				\
	CHECKERR();								\
	checkErr = newNode->getLeft()->getRight()->createLeft();		\
	CHECKERR();								\
	checkErr = newNode->getLeft()->getRight()->createRight();		\
	CHECKERR();								\
	checkErr = newNode->getLeft()->getRight()->getRight()->createLeft();	\
	CHECKERR();								\
										\
	newNode->setFunc(F_MUL);						\
	newNode->getLeft()->setFunc(F_DIV);					\
	newNode->getLeft()->getLeft()->setDouble(1);				\
	newNode->getLeft()->getRight()->setFunc(F_MUL);				\
	newNode->getLeft()->getRight()->getLeft()->setDouble(2);		\
	newNode->getLeft()->getRight()->getRight()->setFunc(F_SQRT);		\
	checkErr = newNode->getLeft()->getRight()->getRight()->			\
		getLeft()->copy(oldNode->getLeft());				\
	CHECKERR();								\
	checkErr = derivateNode(oldNode->getLeft(), 				\
		newNode->getRight());						\
	CHECKERR();								\
}


#define POW_DER_CODE								\
{										\
	if(!oldNode->getRight())						\
		return NULLPTR_ERR;						\
										\
	if(oldNode->getRight()->getType() == VNumbType)				\
		CONST_POW_DER_CODE						\
	else if(oldNode->getLeft()->getType() == VNumbType)			\
		EXP_POW_DER_CODE						\
	else									\
	{									\
		printf("POW_DER_CODE: exit with error\n");			\
		exit(EXIT_FAILURE);						\
	}									\
}


#define CONST_POW_DER_CODE							\
{										\
	checkErr = newNode->createLeft();					\
	CHECKERR();								\
	checkErr = newNode->createRight();					\
	CHECKERR();								\
	checkErr = newNode->getRight()->createLeft();				\
	CHECKERR();								\
	checkErr = newNode->getRight()->createRight();				\
	CHECKERR();								\
	checkErr = newNode->getRight()->getLeft()->createLeft();		\
	CHECKERR();								\
	checkErr = newNode->getRight()->getLeft()->createRight();		\
	CHECKERR();								\
										\
	newNode->setFunc(F_MUL);						\
	newNode->getLeft()->setDouble(oldNode->getRight()->getDouble());	\
	newNode->getRight()->setFunc(F_MUL);					\
	newNode->getRight()->getLeft()->setFunc(F_POW);				\
	checkErr = newNode->getRight()->getLeft()->getLeft()->			\
		copy(oldNode->getLeft());					\
	CHECKERR();								\
	newNode->getRight()->getLeft()->getRight()->				\
		setDouble(oldNode->getRight()->getDouble() - 1);		\
	checkErr = derivateNode(oldNode->getLeft(), 				\
		newNode->getRight()->getRight());				\
	CHECKERR();								\
}


#define EXP_POW_DER_CODE							\
{										\
	checkErr = newNode->createLeft();					\
	CHECKERR();								\
	checkErr = newNode->createRight();					\
	CHECKERR();								\
	checkErr = newNode->getLeft()->createLeft();				\
	CHECKERR();								\
	checkErr = newNode->getRight()->createLeft();				\
	CHECKERR();								\
	checkErr = newNode->getRight()->createRight();				\
	CHECKERR();								\
										\
	newNode->setFunc(F_MUL);						\
	newNode->getLeft()->setFunc(F_LN);					\
	newNode->getLeft()->getLeft()->setDouble(oldNode->			\
		getLeft()->getDouble());					\
	newNode->getRight()->setFunc(F_MUL);					\
	checkErr = newNode->getRight()->getLeft()->copy(oldNode);		\
	CHECKERR();								\
	checkErr = derivateNode(oldNode->getRight(), 				\
		newNode->getRight()->getRight());				\
	CHECKERR();								\
}


#define EXP_DER_CODE								\
{										\
	if(oldNode->getRight())							\
		return NOTNULLPTR_ERR;						\
										\
	checkErr = newNode->createLeft();					\
	CHECKERR();								\
	checkErr = newNode->createRight();					\
	CHECKERR();								\
	checkErr = newNode->getLeft()->createLeft();				\
	CHECKERR();								\
										\
	newNode->setFunc(F_MUL);						\
	newNode->getLeft()->setFunc(F_EXP);					\
	checkErr = newNode->getLeft()->getLeft()->copy(oldNode->getLeft());	\
	CHECKERR();								\
	checkErr = derivateNode(oldNode->getLeft(), 				\
		newNode->getRight());						\
	CHECKERR();								\
}


#define LOG_DER_CODE								\
{										\
	if(oldNode->getRight())							\
		return NOTNULLPTR_ERR;						\
										\
	printf("LOG_DER_CODE: ещё не сделан\n");				\
	exit(EXIT_FAILURE);							\
}


#define LN_DER_CODE								\
{										\
	if(oldNode->getRight())							\
		return NOTNULLPTR_ERR;						\
										\
	checkErr = newNode->createLeft();					\
	CHECKERR();								\
	checkErr = newNode->createRight();					\
	CHECKERR();								\
										\
	newNode->setFunc(F_DIV);						\
	checkErr = newNode->getRight()->copy(oldNode->getLeft());		\
	CHECKERR();								\
	checkErr = derivateNode(oldNode->getLeft(), 				\
		newNode->getLeft());						\
	CHECKERR();								\
}



#define D_FUNC_DEF(name, str, num) FUNC_DEF(name, str, num, name##_DER_CODE)


#define FUNCS_DEF			\
	D_FUNC_DEF(ADD, +, 1)		\
	D_FUNC_DEF(SUB, -, 2)		\
	D_FUNC_DEF(MUL, *, 3)		\
	D_FUNC_DEF(DIV, /, 4)		\
	D_FUNC_DEF(SIN, sin, 5)		\
	D_FUNC_DEF(COS, cos, 6)		\
	D_FUNC_DEF(TG, tg, 7)		\
	D_FUNC_DEF(CTG, ctg, 8)		\
	D_FUNC_DEF(SQRT, sqrt, 9)	\
	D_FUNC_DEF(POW, ^, 10)		\
	D_FUNC_DEF(EXP, e^, 11) 	\
	D_FUNC_DEF(LOG, log, 12) 	\
	D_FUNC_DEF(LN, ln, 13)

