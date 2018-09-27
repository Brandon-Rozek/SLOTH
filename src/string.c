#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "string.h"

char* substring(char* str, int start, int end) {
// Add conditions that substring is valid, probably using strlen
  int stringLength = strlen(str);
  if (start >= stringLength || end > stringLength) { fprintf(stderr, "Requesting substring outside of valid range.\n"); return NULL; }

  char* substr;
  int c;
  int length = end - start;
  substr = (char*) malloc(length + 1);
 
  if (substr == nullptr) {
    fprintf(stderr, "Unable to allocate memory for substring.\n");
    exit(1);
  }
 
  for (c = 0; c < length; c++) {
    substr[c] = str[start + c];         
  }
 
  substr[c] = '\0';
 
  return substr;
}
