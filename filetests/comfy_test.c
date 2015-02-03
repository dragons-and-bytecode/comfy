/**
 * 1. create 'target' dir (WON'T DO -> is done externally)
 * 2. run comfy --source 'source' --target 'target' (WON'T DO -> is done externally)
 * 3. for every file in target:
 * 4.1.  found NO matching file in  'expected'? --> FAIL
 * 4.2.  string content doesn't equal string content in expected file? --> FAIL
 * 4.3.  if no failure occoured: delete file
 * 5. for every file in expected:
 * 5.1.  found NO matching file in  'target'? --> FAIL
 * 5.2.  if no failure occoured: delete file
 * 6. if no file failed: delete 'target' (WON'T DO -> is done externally)
 */

#include "sys/stat.h"
#include "stdio.h"
#include "stdlib.h"
#include "dirent.h"
#include "unistd.h"
#include "string.h"
#include "limits.h"
#include "asprintf.h"

#ifndef LINE_MAX
#define LINE_MAX 2048
#endif

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define bool int
#define true 1
#define false 0

typedef struct {
    int size;
    char** items;
} string_array;

char* test_target_file(char* target_file, char* expected_file){
    struct stat buffer;
    if (stat(expected_file, &buffer) != 0){
        char* fail;
        asprintf(&fail, "Found unexpected '%s'", target_file);
        return fail;
    }
    
    char target_line[LINE_MAX];
    char expected_line[LINE_MAX];
    
    FILE* target = fopen(target_file, "r");
    FILE* expected = fopen(expected_file, "r");
    
    for(int line = 1; true; line++){
        char* target_test = fgets(target_line, LINE_MAX, target);
        char* expected_test = fgets(expected_line, LINE_MAX, expected);
        //printf("%i: %s | %s\n", line, target_line, expected_line);
        if (NULL == target_line && NULL != expected_line){
            char* fail;
            asprintf(&fail, "%s ends at line %i, while %s is longer.", 
                        target_file, line - 1, expected_file);
            
            fclose(expected);
            fclose(target);
            return fail;
        } else if (NULL != target_test && NULL == expected_test) {
            char* fail;
            asprintf(&fail, "%s is logner than %i lines, while %s has already ended.", 
                        target_file, line, expected_file);
            
            fclose(expected);
            fclose(target);
            return fail;
        } else if (NULL == target_test && NULL == expected_test){
            break;
        } else {
            if (strcmp(target_line, expected_line)){
                char* fail;
                asprintf(&fail, "%s differs in line %i from %s", 
                            target_file, line, expected_file);
            
                fclose(expected);
                fclose(target);
                return fail;
            }
        }
    }
    
    fclose(expected);
    fclose(target);
    
    return NULL;
}

char* test_expected_file(char* expected_file, char* target_file){
    struct stat buffer;
    if (stat(target_file, &buffer) != 0){
        char* fail;
        asprintf(&fail, "'%s' expected, but not found", target_file);
        return fail;
    }
    return NULL;
}

string_array test_with_directory(char* dir_name, char* reference_dir,
                        char* (*test_func)(char*, char*)){
    
    string_array failures;
    failures.size = 0;
    failures.items = NULL;
    
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir (dir_name)) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            if (0 == strcmp(".", ent->d_name) || 0 == strcmp("..", ent->d_name))
                continue;
            
            char* ref_file;
            asprintf(&ref_file, "%s/%s", reference_dir, ent->d_name);
            char* file;
            asprintf(&file, "%s/%s", dir_name, ent->d_name);
            
            char* failure = test_func(file, ref_file);
            if (failure){
                printf(ANSI_COLOR_RED ".");
                failures.size++;
                failures.items = realloc(failures.items, 
                                         failures.size * sizeof(char*));
                failures.items[failures.size -1] = failure;
            } else {
                printf(ANSI_COLOR_GREEN ".");
            }
        }
    }
    
    return failures;
}

int main(int argc, char* argv[]){
    char* source_dir   = argv[1];
    char* target_dir   = argv[2];
    char* expected_dir = argv[3];
    
    
    printf("Testing Comfy outputs ");
    printf("...\n  [");
    
    string_array tFailures = test_with_directory(
        target_dir, expected_dir,
        test_target_file);
    
    printf(ANSI_COLOR_RESET "] [");    
    
    string_array eFailures = test_with_directory(
        expected_dir, target_dir,
        test_expected_file);

    
    printf(ANSI_COLOR_RESET "]\n");
    
    if (tFailures.size > 0 || eFailures.size > 0) {
        for (int i = 0; i < tFailures.size; i++){
            printf(ANSI_COLOR_RED "  !! %s\n", tFailures.items[i]);
        }
        printf("\n");
        for (int i = 0; i < eFailures.size; i++){
            printf(ANSI_COLOR_RED "  !! %s\n", eFailures.items[i]);
        }
        printf(ANSI_COLOR_RESET "\n");
        return -1;
    } else {
        //rmdir(target_dir);
        return 0;
    }
}
