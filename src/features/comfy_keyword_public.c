#include "comfy_keyword_public.h"

#include <slre.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <asprintf.h>
#include <stdlib.h>

#define RE_PUBLIC     "(\\n\\s*public)\\s+([^;{}]+){"
#define RE_PUBLIC_DOC "(/\\*.*?\\*/)\\s*\\n\\s*public\\s+([^;{}]+){"

/**
 * removes whitespaces from the end of the string, and returns the new length.
 * @param  str [description]
 * @param  len [description]
 * @return     [description]
 */
static int remove_whitespace(string str, int len){
    while (isspace(str[len-1]) && 0 <= len)
    {
        len--;
    }

    return len;
}

static string make_public_string(string str, int len){
    len = remove_whitespace(str, len);

    string masked = string_replace_all_in_sized(str, len, "\n", "\n§");
    string result;
    asprintf(&result, "§%s", masked);
    free(masked);
    return result;
}

static string append_to(string target, string str, int len){
    string next;
    asprintf(&next, "%s%.*s", target, len, str);
    free(target);
    return next;
}

static string append_str_to(string target, string str){
    return append_to(target, str, strlen(str));
}

static int match_re(string source, int start, struct slre_cap* groups, string* match_start){
    int len = strlen(source) - start;
    int bytes_read;

    bytes_read = slre_match(RE_PUBLIC_DOC, source + start, len, groups, 2, 0);

    //if no match, try without documentation
    if (0 > bytes_read)
    {
        bytes_read = slre_match(RE_PUBLIC, source + start, len, groups, 2, 0);
        if (0 <= bytes_read){
            *match_start = (string) groups[0].ptr;
            groups[0].ptr = NULL;
            groups[0].len = 0;
        }
    } else {
        *match_start = (string) groups[0].ptr;
    }

    return bytes_read;
}

string comfy_keyword_public(string name, string source)
{
    struct slre_cap groups[2];
    string match_start;
    int start = 0;
    int bytes_read = 0;
    int source_len = strlen(source);

    string target;
    asprintf(&target, "");
    bool found = false;
    string end_of_match;

    while (0 < (bytes_read = match_re(source, start, groups, &match_start)))
    {
        found = true;
        const string docstr  = (const string) groups[0].ptr;
        int docstr_len = groups[0].len;
        const string mhead   = (const string) groups[1].ptr;
        int mhead_len  = groups[1].len;

        //string match_start = docstr ? docstr : mhead;
        string source_start = source + start;
        target = append_to(target, source_start, match_start - source_start);

        if (docstr)
        {
            string pubdoc = make_public_string(docstr, docstr_len);
            target = append_str_to(target, pubdoc);
        }

        string pub_mhead = make_public_string(mhead, mhead_len);
        target = append_str_to(target, "\n");

        target = append_str_to(target, pub_mhead);
        target = append_str_to(target, ";\n");
        target = append_to(target, mhead, mhead_len);

        end_of_match = mhead + mhead_len;
        start = end_of_match - source;

        /*
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

        end_of_match = source + start + bytes_read - 1;
*/
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
