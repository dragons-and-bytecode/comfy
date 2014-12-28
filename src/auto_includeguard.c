#include "comfy.h"

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
