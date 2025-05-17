#include "h.h"

int main(void)
{
	char *word = (char *)malloc(MAX_LINE_SIZE + 1);
	search("data", word);
	printf("%s\n", word);
	free(word);

	return 0;
}
