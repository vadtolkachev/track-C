#include "MyStack.hpp"
#include "MyProcessor.hpp"
#include "MyTranslator.hpp"


#define UNITTEST(what,op,ref)						\
{									\
	auto result = (what);						\
	auto comp = (ref);						\
									\
	std::cout << WHITE << __FILE__":" << __LINE__ << ": " 		\
		<< __PRETTY_FUNCTION__ << ": " << NORM;			\
	if(result op comp)						\
		std::cout << #what << GREEN << " [passed]\n" << NORM;	\
	else								\
		std::cout << #what << RED << " is "			\
			<< result << " but should be "			\
			<< #op" " << comp << NORM << std::endl;		\
}


void exitErr(const char *str)
{
	puts(str);
	exit(EXIT_FAILURE);
}


int main()
{	
	MyTranslator translator;
	FILE *asmFile = fopen("asm_code.txt", "r");
	if(!asmFile)
		exitErr("fopen file");

	FILE *txtFile = fopen("mach_code.txt", "w");
	if(!txtFile)
		exitErr("fopen txtFile");

	FILE *binFile = fopen("mach_code.bin", "w");
	if(!binFile)
		exitErr("fopen binFile");

	int checkErr = translator.translate(asmFile, txtFile, binFile, INT_F);
	if(checkErr == 1)
		puts("Success");
	else	
		printf("Err = %d\n", checkErr);

	fclose(asmFile);
	fclose(txtFile);
	fclose(binFile);
	if(errno)
		perror("closing files");

	return 0;
}