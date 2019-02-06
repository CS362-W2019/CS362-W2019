#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*
 * @params: pass in message, expected and actual values of variables as well as the reference of test_result
 * @print: "Test: " + "Message || " + "PASSED" / "FAILED" + " || expected = XX actual = XX" 
 * @return: False if the test failed / True when the test passed
 */

void testEqual(char *message, int expected, int actual, bool *test_result) {
  int len = strlen(message);
  char outputMessage[len + 50];
  memset(&outputMessage, 0, sizeof(outputMessage));
  strcat(outputMessage, "Test: ");
  strcat(outputMessage, message);
  if(expected == actual)
  {
    strcat(outputMessage, " || PASSED ||");
    printf("%s expected = %d, actual = %d\n", outputMessage, expected, actual);
  }
  else
  {
    strcat(outputMessage, " || FAILED ||");
    printf("%s expected = %d, actual = %d\n", outputMessage, expected, actual);
    *test_result = false;
  }
}

void testResult(bool test_result)
{
  if(test_result)
  {
    printf("All tests passed!\n");
  }
  else
  {
    printf("You got some bugs, please read the error message.\n");
  }
}