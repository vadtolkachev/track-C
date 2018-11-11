#define S_DEBUG
//#define S_DOUBLE
#include "MyProcessor.hpp"
#include "MyAssembler.hpp"
#include "MyDisassembler.hpp"


void exitErr(const char *str)
{
	printf("Exit with error: %s\n", str);
	exit(EXIT_FAILURE);
}


void makeAsm(const char *asmStr, const char *txtStr, const char *binStr)
{
	MyAssembler theAsm;
	FILE *asmFile = fopen(asmStr, "r");
	if(!asmFile)
		exitErr("fopen file");

	FILE *txtFile = fopen(txtStr, "w");
	if(!txtFile)
		exitErr("fopen txtFile");

	FILE *binFile = fopen(binStr, "wb");
	if(!binFile)
		exitErr("fopen binFile");

	int checkErr = theAsm.assemble(asmFile, txtFile, binFile);
	if(checkErr == SUCCESS)
		puts("1.Success");
	else	
		printf("1.Err = %d\n", checkErr);

	fclose(asmFile);
	fclose(txtFile);
	fclose(binFile);

	if(errno)
	{
		perror("1.closing files");
		exitErr("makeAsm");
	}
}


void makeDAsm(const char *binStr, const char *txtStr, const char *asmResStr)
{
	FILE *binFile = fopen(binStr, "r");
	if(!binFile)
		exitErr("fopen binFile");
	
	FILE *txtFile2 = fopen(txtStr, "w");
	if(!txtFile2)
		exitErr("fopen txtFile2");

	FILE *asmFileRes = fopen(asmResStr, "w");
	if(!asmFileRes)
		exitErr("fopen asmFileRes");

	MyDisassembler theDasm;

	int checkErr = theDasm.disassemble(binFile, txtFile2, asmFileRes);
	if(checkErr == SUCCESS)
		puts("2.Success");
	else	
		printf("2.Err = %d\n", checkErr);

	fclose(binFile);
	fclose(txtFile2);
	fclose(asmFileRes);

	if(errno)
	{
		perror("2.closing files");
		exitErr("makeDAsm");
	}
}


void makeProcExec(const char *binStr)
{
	FILE *binFile = fopen(binStr, "r");
	if(!binFile)
		exitErr("fopen binFile");

	MyProcessor proc;
	int checkErr = proc.proc_exec(binFile);
	if(checkErr == SUCCESS)
		puts("3.Success");
	else	
		printf("3.Err = %d\n", checkErr);

	fclose(binFile);
	if(errno)
	{
		perror("3.closing files");
		exitErr("makeProcExec");
	}
}


int main()
{	
	char asmStr[25] = "code/asm_code7.txt";
	char txtStr[25] = "code/mach_code.txt";
	char binStr[25] = "code/mach_code.bin";
	char txtStr2[25] = "code/mach_code2.txt";
	char asmResStr[25] = "code/asm_code_res.txt";

	makeAsm(asmStr, txtStr, binStr);
	makeDAsm(binStr, txtStr2, asmResStr);
	makeProcExec(binStr);

	return 0;
}