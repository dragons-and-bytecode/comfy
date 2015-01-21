
/**
 * `asprintf.c' - asprintf
 *
 * copyright (c) 2014 joseph werle <joseph.werle@gmail.com>
 */

#ifndef HAVE_ASPRINTF

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "asprintf.h"

int
asprintf (char **str, const char *fmt, ...) {
printf("++++ asprintf(%s) ++++\n", fmt);
  int size = 0;
  va_list args;

  // init variadic argumens
  va_start(args, fmt);

  // format and get size
  size = vasprintf(str, fmt, args);

  // toss args
  va_end(args);

printf("---- asprintf(%s) ----\n", fmt);
  return size;
}

int
vasprintf (char **str, const char *fmt, va_list args) {
    printf("++++ vasprintf(%s) ++++\n", fmt);
  int size = 0;
  va_list tmpa;

  // copy
  va_copy(tmpa, args);

  // apply variadic arguments to
  // sprintf with format to get size
  printf("  Guessing size....\n");
  size = vsnprintf(NULL, size, fmt, tmpa);
  printf("    Buest guess is %i\n", size);

  // toss args
  va_end(tmpa);

  // return -1 to be compliant if
  // size is less than 0
  if (size < 0) { return -1; }

  // alloc with size plus 1 for `\0'
  printf("  Allocating space\n");
  *str = (char *) malloc(size + 1);
  printf("    ... found some.\n");

  // return -1 to be compliant
  // if pointer is `NULL'
  if (NULL == *str) { return -1; }

  // format string with original
  // variadic arguments and set new size
  printf("  Filling string with stuff...\n");
  size = vsprintf(*str, fmt, args);
  printf("    ...ok.\n");
  printf("---- vasprintf(%s) ----\n", fmt);
  return size;
}

#endif
