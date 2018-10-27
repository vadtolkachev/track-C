#include "textSort.hpp"


int main()
{
	FILE *file = fopen("text/hamlet.txt", "r");
	if(errno != 0)
		exitErr("failed to open file");
	
	FILE *res = fopen("res.txt", "w");
	if(errno != 0)
		exitErr("failed to open res");
	
	int nStrings;
	char **text = getText(file, &nStrings);
	char *bigString = text[0]; 
	writeText(text, res, nStrings, WITH_SLASHN);

	const char *str = "--------------------------------------------------------------------------------------------------\n";
	fprintf(res, "%s%s%s%s",str,str,str,str);
	leftSort(text, nStrings);
	writeText(text, res, nStrings, NO_GARBAGE);

	fprintf(res, "%s%s%s%s",str,str,str,str);
	rightSort(text, nStrings);
	writeText(text, res, nStrings, NO_GARBAGE);	

	fclose(file);
	if(errno != 0)
		exitErr("file fclose() failed");

	fclose(res);
	if(errno != 0)
		exitErr("res fclose() failed");

	memfree(text, bigString);

	return 0;
}