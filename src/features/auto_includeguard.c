#include "auto_includeguard.h"
#include "../regex.h"

static const string PATTERN_PRAGMA_ONCE = "^\\s*#pragma\\s+once\\s*\\n";
static const string PATTERN_GUARD_START = "^\\s*#ifndef\\s+([a-zA-Z_]+)\\s*\\n"
                                          "\\s*#define\\s+([a-zA-Z_]+)\\s*\\n";
static const string PATTERN_GUARD_END =   "#endif\\s*$";

bool _would_modify(ComfyFileBundle* bundle){
    if (!regex_match(".*\\.h$", bundle->source.name)){
        return false;
    }
    

    if (regex_match(PATTERN_PRAGMA_ONCE, bundle->source.content)){
        printf("%s has #pragma once\n", bundle->source.name);
        return false;
    }
    
    RegexMatcher match_start = regex_matcher(PATTERN_GUARD_START, 
                                             bundle->source.content);
    
    if (regex_did_match(match_start)){
        if (0 == strcmp(regex_group(match_start, 0), 
                        regex_group(match_start, 1))
                && regex_match(PATTERN_GUARD_END, bundle->source.content)){
            
            regex_free_matcher(match_start);
            return false;
        }
    }
    
    regex_free_matcher(match_start);
    return true;
}

void replace_char_in_string(char find, char replace, char* string){
  char* found = string;

  while (NULL != found){
    found = strchr(found, find);
    if (NULL != found){
      found[0] = replace;
      found++;
    }
  }
}

char* create_headername(const char* filename){
  char* headername = malloc((strlen(filename) + 4) * sizeof(char));
  sprintf(headername, "__%s__", filename);
  replace_char_in_string('.', '_', headername);
  return headername;
}

char* create_pure_filename(const char* filename){
  char* my_filename = malloc(strlen(filename) * sizeof(char));
  strcpy(my_filename, filename);

  replace_char_in_string('\\', '/', my_filename);
  char* last_slash = strrchr(my_filename, '/');

  if (NULL == last_slash){
    return my_filename;
  } else {
    char* simple_name = malloc((strlen(last_slash)-1) * sizeof(char));
    strcpy(simple_name, (last_slash + sizeof(char)));
    free(my_filename);
    return simple_name;
  }
}

void create_guard(const char* filename, FILE* input, FILE* output){

  char* simplename = create_pure_filename(filename);
  char* headername = create_headername(simplename);

  fprintf(output, "#ifndef %s\n#define %s\n\n", headername, headername);

  while (!feof(input)){
    char c = fgetc(input);
    if (EOF != c)
      fputc(c, output);
  }


  fprintf(output, "\n\n#endif\n");

  free(headername);
  free(simplename);
}

void _process(ComfyFileBundle* bundle){
    char* simplename = create_pure_filename(bundle->source.name);
    char* headername = create_headername(simplename);
    
    
    
    free(headername);
    free(simplename);
}

Feature* create_auto_incudeguard(){
    Feature* f = malloc(sizeof(Feature));
    f->would_modify = _would_modify;
    f->process = _process;
    return f;
}
