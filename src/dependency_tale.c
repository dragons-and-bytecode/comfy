#include "dependency_tale.h"

#include <stdio.h>
#include <stdlib.h>
#include <slre.h>
#include <string.h>

bool is_known_comfy_file(const string base_name, int len, Files* known_files)
{
    for (size_t i = 0; i < files_count(known_files); i++) {
        string file_name = files_filepath(known_files, i);
        string file_type = files_get_filetype(file_name);
        if (string_equals("comfy", file_type))
        {
            string comfy_path = files_filepath(known_files, i);
            string comfy_name = strrchr(comfy_path, '/');
            if (comfy_name) comfy_name++;
            else comfy_name = comfy_path;

            string tail = strrchr(comfy_name, '.');
            int name_len = tail ? tail - comfy_name : strlen(comfy_name);

            //DEBUG(":: %.*s", name_len, comfy_name);
            if (len == name_len and 0 == strncmp(base_name, comfy_name, len))
                return true;
        }
    }
    return false;
}

static bool is_known(String str, TokenList array)
{
    for (size_t i = 0; i < array.size; i++) {
        String compare = array.tokens[i];
        if (str.length == compare.length
                and 0 == strncmp(str.text, compare.text, str.length))
            return true;
    }

    return false;
}

void print_dependency_headers(string source_dir, Files* source_files)
{
    Files* all_comfy_files = files_list_dir(source_dir);

    TokenList already_known = {
        .tokens = NULL,
        .size = 0
    };

    for (size_t i = 0; i < files_count(source_files); i++)
    {
        if (!files_type_is_regular_file(source_files, i)){
            continue;
        }
        string file_name = files_filepath(source_files, i);
        string content = files_read_file(file_name);

        TokenList lines = string_as_lines(content);
        for (size_t j = 0; j < lines.size; j++) {
            String line = lines.tokens[j];

            struct slre_cap cap[1];
            if (0 <= slre_match("#include\\s+\"(.+).h\"",
                                line.text, line.length, cap, 1, 0))
            {
                if (is_known_comfy_file((const string)cap[0].ptr, cap[0].len,
                        all_comfy_files))
                {
                    //DEBUG("??%.*s--", cap[0].len, cap[0].ptr);
                    String found_header = {
                        .text=(string) cap[0].ptr,
                        .length=cap[0].len
                    };

                    unless (is_known(found_header, already_known))
                    {
                        printf("%.*s.h ", found_header.length, found_header.text);

                        already_known.size++;
                        already_known.tokens = realloc(already_known.tokens,
                                already_known.size * sizeof(String));
                        already_known.tokens[already_known.size - 1] =
                                found_header;
                    }
                }
            }
        }
    }

    printf("\n");
    files_free_files(all_comfy_files);
}
