#ifndef __auto_includeguard_h__
#define __auto_includeguard_h__

#include "../base.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "feature.h"
#include "../processor.h"

Feature* create_auto_incudeguard();

void replace_char_in_string(char find, char replace, char* string);
char* create_headername(const char* filename);
char* create_pure_filename(const char* filename);
void create_guard(const char* filename, FILE* input, FILE* output);

#endif
