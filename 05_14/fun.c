#include "h.h"

int is_word(char *s)
{
	int i;

	if ((s[0] < 'A') || (s[0] > 'Z'))
		return 0;

	for (i = 1; s[i] != '\0'; i++)
	{
		if ((s[i] < 'A') || (s[i] > 'z')
			|| ((s[i] > 'Z') && (s[i] < 'a')))
			return 0;
	}
	return 1;
}

/*
line

char buff[512];

int flag = 0;

for (i = 0; i < len; i++)
{
	if ((s[i] >= 'A') && (s[i] <= 'Z') && (!flag))
	{
		buff[0] = s[i];
		flag = 1;
		for (j = 1; j < len - i; j++)
		{
			if (!((s[i + j] < 'A') || (s[i + j] > 'z')
				|| ((s[i + j] > 'Z') && (s[i + j] < 'a'))))
			buff[j] = s[i + j];
			else if ((s[i + j] != ' ') && (s[i + j] != '\t') && (s[i + j] != '\n'))
			{
				break ;
			}
			else
			{
				buff[j] = '\0';
				if (j < minlen)
				{
					minlen = j;
					// Копируем cur_line в word
					strcpy(word, buff);
				}
				flag = 0;
				break ;
			}
		}
		i += j;
	}
	else if ((s[i] == ' ') || (s[i] == '\t') || (s[i] == '\n'))
		flag = 0;
	else
		flag = 1;
}
		 012 3456 78
line  = "AAA\0BBB\0CCC\0DDD\0\0"

cur_line = line ||| "AAA"
cur_line = line + 4 ||| "BBB"
cur_line = line + 8 ||| "CCC"

*/
int search(const char *SInputFile, char *word)
{
	FILE *f;
	char *line, *cur_line;
	size_t len = 0, minlen = MAX_LINE_SIZE + 1, cur_len;

	f = fopen(SInputFile, "r");

	if (!f)
		return -1;

	while (1)
	{	
		// Считываем строчку до \n в line, а в len кладём длину считанного
		// если len = максимальному значению size_t - считать не удалось
		len = getline(&line, &len, f);
		if (len == ((size_t)0 - 1))
		{
			free(line);
			break ;
		}
	//	Откусывает от строки куски слева до разделителя
		cur_line = strtok(line, " \t\n");
		while (cur_line)
		{
			// Проверка, что cur_line является словом
			if (is_word(cur_line))
			{
				// Подсчитываем длину строки
				cur_len = strlen(cur_line);
				if (cur_len < minlen)
				{
					minlen = cur_len;
					// Копируем cur_line в word
					strcpy(word, cur_line);
				}
			}
			cur_line = strtok(NULL, " \t\n");
		}
		//free(line);
	}
	fclose(f);
	return 0;
}
