//Marc LaRocco
//Pset2
//Caesar.c

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
	//declare variables
	//key
	int k = 0;
	//string input from user
	string input = "";
	//length of string
	int length = 0;

	//check the number of arguments
	if (argc != 2)
	{
		//display how many or how little arguments were entered
		if (argc < 2)
			printf("You entered less than two arguments.\n");
		else
			printf("You entered more than two arguments.\n");

		return 1;
	}
	else
	{
		//convert argv[1] to an int
		k = atoi(argv[1]);
		//obtain string from user
		input = GetString();
		//determine size of the string
		length = strlen(input);

		for (int i = 0; i < length; i++)
		{
			if (isalpha(input[i]))
			{
				//check if the character is lowercase then print the converted letters
				if (islower(input[i]))
					printf("%c", ((input[i] - 97 + k) % 26 + 97));
				//check if character is uppercase then print the converted letters
				else
					printf("%c", ((input[i] - 65 + k) % 26 + 65));
			}
			else
				//if no alpha character is detected, print
				printf("%c", input[i]);

		}


	}

	printf("\n");

	return 0;

}