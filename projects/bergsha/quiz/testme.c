#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

int randRange(int lower, int upper)
{
    return (rand() % (upper - lower + 1) + lower);
}

char inputChar()
{
	// use random generator to generate a char
	// within the ascii range that includes brackets
	// and spaces
    char input = randRange(32, 125);
    return input;
}

char *inputString()
{
    int strLen = 6;
	// use random generator to generate a string using
	// all lower case ascii characters between e and t in the alphabet
    char* inString = malloc(strLen + 1);

    for (int i=0; i<strLen-1; i++)
    {
        inString[i] = randRange(101, 116);
    }
    inString[5] = '\0';

    return inString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
