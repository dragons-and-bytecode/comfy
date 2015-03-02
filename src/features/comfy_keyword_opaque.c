#include "comfy_keyword_opaque.h"

#include "asprintf.h"
#include "string.h"
#include "slre.h"
#include "stdlib.h"

static const string RE_OPAQUE = "\\n(\\s*?opaque\\s+struct)\\s+([^;{}]+)\\s*{";
static const string RE_OPAQUE_DOC = "(/\\*.*?\\*/)\\s*\\n\\s*opaque\\s+struct\\s+([^;{}]+)\\s*{";


string append_str(string first, string second, int copy_length)
{
    string ret_val;
    if (!first)
    {
        asprintf(&ret_val, "%.*s", copy_length, second);
    } else {
        asprintf(&ret_val, "%s%.*s", first, copy_length, second);
    }
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
string _comfy_keyword_opaque(string name, string source, bool with_doc)
{
    const string regex = with_doc ? RE_OPAQUE_DOC : RE_OPAQUE;

    string target = NULL;

    struct slre_cap groups[2];

    bool any_match = false;
    int match = 0;
    string source_ptr = source;
    while (0 <= (match = slre_match(regex,
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
        int name_length = string_trimmed_length(groups[1].ptr, groups[1].len);
        groups[1].len = name_length;
        string structdef;
        asprintf(&structdef,
            "§ struct _%.*s;\n§ typedef struct _%.*s %.*s;\nstruct _%.*s",
            name_length, groups[1].ptr,
            name_length, groups[1].ptr,
            name_length, groups[1].ptr,
            name_length, groups[1].ptr);

        if (with_doc){
            string docstr = string_replace_all_in_sized(
                        groups[0].ptr, groups[0].len, "\n", "\n§ ");
            string replacement;
            asprintf(&replacement,
                "§ %s\n%s", docstr, structdef);

            target = append_str(target, replacement, strlen(replacement));

            free(docstr);
            docstr = NULL;

            free(replacement);
            replacement = NULL;
        } else {
            target = append_str(target, "\n", strlen("\n"));
            target = append_str(target, structdef, strlen(structdef));
        }

        free(structdef);
        structdef = NULL;

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

string comfy_keyword_opaque(string name, string source)
{
    string t1 = _comfy_keyword_opaque(name, source, true);
    string t2 = _comfy_keyword_opaque(name, t1 ? t1 : source, false);
    if (t1)
    {
        free(t1);
        t1 = NULL;
    }

    return t2;
}
