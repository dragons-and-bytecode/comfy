#include "comfy_keyword_public.h"

#include <slre.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <asprintf.h>
#include <stdlib.h>

#define RE_PUBLIC "(/\\*.*?\\*/)\\s*\\n\\s*public\\s+([^;{}]+){"

static void remove_whitespace(struct slre_cap* group){
    while (isspace(group->ptr[group->len-1])
                && 0 <= group->len)
    {
        group->len--;
    }
}

string comfy_keyword_public(string name, string source)
{
    struct slre_cap groups[2];
    int start = 0;
    int bytes_read = 0;
    int source_len = strlen(source);

    string target;
    asprintf(&target, "");
    bool found = false;
    string end_of_match;

    while (0 < (bytes_read = slre_match(RE_PUBLIC,
                                    source + start,
                                    source_len - start,
                                    groups, 3, 0)))
    {

        int size_matched =  groups[1].ptr - source + groups[1].len;

        remove_whitespace(&groups[0]);
        remove_whitespace(&groups[1]);
        if (0 >= groups[0].len || 0 >= groups[1].len){
            return NULL;
        }

        string start_str = source + start;

        string append_target;
        asprintf(&append_target, "%s%.*s", target,
                (int)(groups[0].ptr - start_str),  start_str);

        string to_header;
        string to_source;

        asprintf(&to_header, "§%.*s\n%.*s;",
                groups[0].len, groups[0].ptr,
                groups[1].len, groups[1].ptr);
        string masked = string_replace_all_in(to_header, "\n", "\n§");

        asprintf(&to_source, "%s%s\n%.*s",
                append_target,
                masked, groups[1].len, groups[1].ptr);



        free(masked);
        free(append_target);
        free(to_header);

        free(target);
        target = to_source;

        string end_of_last_group = (string)(groups[1].ptr + groups[1].len);
        end_of_match = source + start + bytes_read - 1;

        start = end_of_last_group - source;
        found = true;
    }

    if (found){
        string append_tail;
        asprintf(&append_tail, "%s%s", target, end_of_match);
        free(target);
        return append_tail;
    } else {
        return NULL;
    }
}
