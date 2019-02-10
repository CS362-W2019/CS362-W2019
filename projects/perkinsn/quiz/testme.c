#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
// returns a random char from ' ' to '}'

{
    return rand() % ('}' - ' ' + 1) + ' ';
}

char *inputString()
// starts with a string "reset" and randomly overwrites the letters
// with around a 90% chance per letter

// returns a pointer to the string
{
    static char s[6];
    strcpy(s, "reset");
    for (int i = 0; i < 5; ++i) {
        if (rand() % 10 < 9) {
          s[i] = rand() % ('z' - 'a' + 1) + 'a';
        }
    } 

    return s;
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
      printf("error\n");
      break;
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));

    for (int i = 0; i < 100; ++i) {
      testme();
    }

    return 0;
}
