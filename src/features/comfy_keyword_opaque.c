#include "comfy_keyword_opaque.h"

#include "asprintf.h"
#include "string.h"
#include "slre.h"
#include "stdlib.h"

static const string RE_OPAQUE = "(\\n\\s*opaque\\s+struct)\\s+([^;{}]+)\\s*{";
static const string RE_OPAQUE_DOC = "(/\\*.*?\\*/)\\s*\\n\\s*opaque\\s+struct\\s+([^;{}]+)\\s*{";


string append_str(string first, string second, int copy_length)
{
    string ret_val;
    asprintf(&ret_val, "%s%.*s", first, copy_length, second);
    return ret_val;
}

/*
 * transform comfy source:
 *
 *     (docstr)
 *     opaque struct Foobar { ... };
 *
 * into
 *
 *     §(docstr)
 *     §struct _Foobar;
 *     §typedef struct _Foobar Foobar;
 *     struct _Foobar { ... };
 */
string comfy_keyword_opaque(string name, string source)
{
    string target;

    struct slre_cap groups[2];

    bool any_match = false;
    int match = 0;
    string source_ptr = source;
    while (0 <= (match = slre_match(RE_OPAQUE_DOC,
                                    source_ptr,
                                    strlen(source_ptr),
                                    groups, 2, 0)))
    {
        any_match = true;

        /*
         * append in betweeny bits.
         */
        int match_start = groups[0].ptr - source_ptr;
        target = append_str(target, source_ptr, match_start);

        /*
         * append replacement here.
         */
        string docstr = string_replace_all_in_sized(
                    groups[0].ptr, groups[0].len, "\n", "\n§ ");
        string replacement;
        int name_length = string_trimmed_length(groups[1].ptr, groups[1].len);
        asprintf(&replacement,
            "§ %s\n§ struct _%.*s;\n§ typedef struct _%.*s %.*s;\nstruct _%.*s",
            docstr,
            name_length, groups[1].ptr,
            name_length, groups[1].ptr,
            name_length, groups[1].ptr,
            name_length, groups[1].ptr);

        target = append_str(target, replacement, strlen(replacement));

        source_ptr = groups[1].ptr + groups[1].len;
    }

    if (any_match)
    {
        /*
         * append tail.
         */
        target = append_str(target, source_ptr, strlen(source_ptr));
    } else {
        return NULL;
    }

    return target;
}
