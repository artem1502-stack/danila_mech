#include "h.h"

/*

Текстовый файл содержит строки длиной не более 512 символов,
состоящие из слов, разделенных пробелами, точками и запятыми. 
Написать функцию, которая изо всех слов файла, состоящих только 
из заглавных букв английского алфавита и начинающихся на букву A, 
находит самое короткое слово.
Имя файла и полученное слово должны передаваться через параметры
функции. Функция должна возвращать 0, если файл удалось открыть,
и -1, если файл не удалось открыть. Функция должна иметь описание:
int search(const char *SInputFile, char *word);

*/


/*
	FILE *f = fopen(SInputFile, "r");
	int i, minlen = 0, curlen = 0;
	char buff[512];
	char c;

	buff[0] = '\0';

	while (fscanf(f, "%c", &c) == 1)
	{
		if (c == 'A')
		{
			buff[0] = c;
			curlen++;
			while (fscanf(f, "%c", &c) == 1)
			{
				if ((c < 'A') || (c > 'Z'))
					break ;
				buff[curlen] = c;
				curlen++;
			}
			buff[curlen] = '\0';
			if ()
		}
	}
*/

int check_word(char *s)
{
	int i;

	if (!s)
		return 0;
	if (s[0] != 'A')
		return 0;
	for (i = 0; s[i] != '\0'; i++)
	{
		if ((s[i] < 'A') || (s[i] > 'Z'))
			return 0;
	}
	return 1;
}

int search(const char *SInputFile, char *word)
{
	FILE *f = fopen(SInputFile, "r");
	char *buff;
	char *new_word;
	size_t len, minlen = 99999999;

	if (!f)
		return -1;

	while (getline(&buff, &len, f) != -1)
	{
		new_word = strtok(buff, " .,\n");

		while (new_word)
		{
			if (check_word(new_word) && (strlen(new_word) < minlen))
			{
				strcpy(word, new_word);
				minlen = strlen(word);
			}
			new_word = strtok(NULL, " .,\n");
		}
		free(buff);
	}
	fclose(f);
	return 0;
}


void fun()
{
	static int x;
	printf("%d\n", x);
	x++;
}

int main(void)
{

	//char res[520];
	//search("txt", res);

	//printf("%s\n", res);

	fun();
	fun();
	fun();
	fun();
	fun();
	fun();
	fun();
	return 0;
}
