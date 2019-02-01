#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/*
 * @params: pass in message, expected and actual values of variables
 * @print: "Test: " + "Message || " + "PASSED" / "FAILED" + " || expected = XX actual = XX" 
 * @return: False if the test failed / True when the test passed
 */
bool testEqual(char *message, int expected, int actual) {
  int len = strlen(message);
  char outputMessage[len + 50];
  memset(&outputMessage, 0, sizeof(outputMessage));
  strcat(outputMessage, "Test: ");
  strcat(outputMessage, message);
  if(expected == actual)
  {
    strcat(outputMessage, " || PASSED ||");
    printf("%s expected = %d, actual = %d\n", outputMessage, expected, actual);
    return true;
  }
  strcat(outputMessage, " || FAILED ||");
  printf("%s expected = %d, actual = %d\n", outputMessage, expected, actual);
  return false;
}