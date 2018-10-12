#include "textSort.hpp"


int main()
{
	FILE *file = fopen("text/2.txt", "r");
	if(errno != 0)
		exitErr("failed to open file");
	
	FILE *res = fopen("res.txt", "w");
	if(errno != 0)
		exitErr("failed to open res");
	
	int nStrings;
	char **text = getText(file, &nStrings);
	char *bigString = text[0]; 
	writeText(text, res, nStrings, WITH_SLASHN);

	fprintf(res, "\n\n");
	leftSort(text, nStrings);
	writeText(text, res, nStrings, NO_SLASHN);

	fprintf(res, "\n\n");
	rightSort(text, nStrings);
	writeText(text, res, nStrings, NO_SLASHN);	

	fclose(file);
	if(errno != 0)
		exitErr("file fclose() failed");

	fclose(res);
	if(errno != 0)
		exitErr("res fclose() failed");

	memfree(text, bigString);

	return 0;
}