#include <xml_lexer.h>

RSXML_API int
XML_lexer_fromString(xml_t *xml, char *str)
{
    return __xml_atomic_lexer_from_string(xml, str);
}

RSXML_API int
__xml_atomic_lexer_from_string(xml_t *xml, char *str)
{
    assert(str != NULL);
    char *_str_beg = str;

    do
    {
        char c = *str;

        if (c == '<')
        {
            char *tag_name = malloc(sizeof(char));
            int ti = 0;
            str++;
            // *tag_name = *str;

            while (*str != '>')
            {
                tag_name = realloc(tag_name, (ti + 1) * sizeof(char));
                tag_name[ti++] = *str;
                str++;
            }

            tag_name = realloc(tag_name, (ti + 1) * sizeof(char));
            tag_name[ti++] = '\0';

            char *tag_name_f = strdup(tag_name);
            free(tag_name);
            tag_name = NULL;

            printf("%s\n", tag_name_f);
        }

        str++;
    } while (*str != '\0');

    return 0;
}