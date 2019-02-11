#ifndef TEST_HELPERS_H
#define TEST_HELPERS_H

#include <stdio.h>

// used for INT_MIN and INT_MAX
// from https://www.tutorialspoint.com/c_standard_library/limits_h.htm
#include <limits.h>

// macro for quickly testing a bool value
// from https://piazza.com/class/jpu18p346423vs?cid=159
#define asserttrue(bool) if(bool) printf("TEST SUCCESSFULLY COMPLETED.\n"); else printf("TEST FAILED: '" #bool  "' on line %d.\n", __LINE__);

#endif