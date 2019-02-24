#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char inputChar()
{
  int randNum = rand(); //get a pseudorandom number
  int triggers[9] = {40, 41, 91, 93, 123, 125, 120, 97, 32} ; //chars that can trigger state change

  //increase likelihood of trigger char selection
  if (randNum % 103 == 0) { //pick a trigger char
    int x = rand() % 9; //limit choice to array
    randNum = triggers[x];
  } else { //just pick any reasonable char
    randNum = randNum % 94 + 33;
  }

  return randNum;
}

char *inputString()
{
  int i;
  int len = strlen("reset"); // improve likelihood of target string
  int idx;

  char *testString = NULL;
  // go heavy on chars in target string to improve likelihood of it occuring
  char *heavyAlpha = "abcdeeefghijklmnopqrrrssstttuvwxyz";

  testString = malloc(sizeof(char) * (len+1));

  for (i = 0; i < len; i++) {
    idx = rand() % strlen(heavyAlpha);
    testString[i] = heavyAlpha[idx];
  }

  testString[len] = '\0'; // terminate the string

  return testString;
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

    if (c == '[' && state == 0)
      state = 1;
    if (c == '(' && state == 1)
      state = 2;
    if (c == '{' && state == 2)
      state = 3;
    if (c == ' ' && state == 3)
      state = 4;
    if (c == 'a' && state == 4)
      state = 5;
    if (c == 'x' && state == 5)
      state = 6;
    if (c == '}' && state == 6)
      state = 7;
    if (c == ')' && state == 7)
      state = 8;
    if (c == ']' && state == 8)
      state = 9;
    if (s[0] == 'r' && s[1] == 'e' && s[2] == 's' && s[3] == 'e' && s[4] == 't' && s[5] == '\0' && state == 9)
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
