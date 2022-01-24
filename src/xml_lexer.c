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

            while (*str != '>')
            {
                tag_name = realloc(tag_name, (ti + 1) * sizeof(char));
                tag_name[ti++] = *str;
                str++;
            }
            str++; // Eat '>'

            tag_name = realloc(tag_name, (ti + 1) * sizeof(char));
            tag_name[ti++] = '\0';

            char *tag_name_f = strdup(tag_name);
            free(tag_name);
            tag_name = NULL;
            char *tn = __xml_get_name_from_tag_line(strdup(tag_name_f));

            if (*tn != '/')
            {
                xml_t tagc = XML_xml_new(tn, NULL, 0, NULL, 0);
                if (strstr(tag_name_f, (char *)(char []){' ', '\0'}) != NULL)
                    __xml_make_attrs_from_line(&tagc, strdup(tag_name_f));

                char *xml_body_data = __xml_get_tag_body_from_line(tn, strdup(str));
                XML_lexer_fromString(&tagc, xml_body_data);
                XML_xml_add_child(xml, tagc);

                char *xbd = xml_body_data;
                while (*xbd != '\0')
                {
                    str++;
                    xbd++;
                }

                for (size_t _i = 0; _i < strlen(tn) + 2; _i++)
                    str++;

                free(xml_body_data);
            }
            else
                str += strlen(tn);
        }
        else
        {
            char *tvd = malloc(sizeof(char));
            int tvc = 0;

            while (*str != '\0')
            {
                if (*str == '<')
                    break;
                
                if ((*str == ' ' || *str == '\t' || *str == '\n') &&
                    !tvc)
                {
                    str++;
                    continue;
                }

                if (tvc)
                    tvd = realloc(tvd, (tvc + 1) * sizeof(char));

                tvd[tvc++] = *str;
                str++;
            }
            str--;

            if (tvc)
                tvd = realloc(tvd, (tvc + 1) * sizeof(char));

            tvd[tvc++] = '\0';

            if (strlen(tvd))
            {
                xml_t av = XML_xml_new(NULL, NULL, 0, NULL, 0);
                attr_t av_ = XML_attr_new(NULL, tvd);

                XML_attr_add(&av, av_);
                XML_xml_add_child(xml, av);
            }
        }

        if (*str)
            str++;
    } while (*str != '\0');

    return 0;
}

RSXML_API char *__xml_get_name_from_tag_line(char *s)
{
    char *res = malloc(sizeof(char));
    int v = 1;

    while (*s != ' ')
    {
        res = realloc(res, (++v) * sizeof(char));
        res[v - 2] = *s;
        s++;
    }

    res = realloc(res, (++v) * sizeof(char));
    res[v - 2] = '\0';

    return res;
}

RSXML_API void
__xml_make_attrs_from_line(xml_t *xml, char *line)
{
    while (*line != ' ' || *line != '\0')
        line++;
    
    if (*line == '\0')
        return;
    line++; // Eat ' '

    char *curr_attr_line = malloc(sizeof(char));

    for (size_t i = 0; i < strlen(line); i++)
    {
        char *catr = malloc(sizeof(char));
        int cat_c = 0, clfg = 0;

        for (size_t j = i; j < strlen(line); j++)
        {
            char c = line[j];

            if (c == ' ' && !clfg)
                break;

            if (c == '\'' ||
                c == '\"')
                clfg = !clfg;

            if (cat_c)
                catr = realloc(catr, (cat_c + 1) * sizeof(char));

            catr[cat_c++] = c;
        }

        if (cat_c)
            catr = realloc(catr, (cat_c + 1) * sizeof(char));

        catr[cat_c++] = '\0';
        i += strlen(catr);

        __xml_make_attr_single_from_line(xml, catr);
        free(catr);
    }
}

RSXML_API void
__xml_make_attr_single_from_line(xml_t *xml, char *line)
{
    char *key = malloc(sizeof(char)), *value = malloc(sizeof(char));
    int key_c = 0, val_c = 0;

    while (*line != '=')
    {
        if (key_c)
            key = realloc(key, (key_c + 1) * sizeof(char));

        key[key_c++] = *line;
        line++;
    }
    line++;

    if (key_c)
        key = realloc(key, (key_c + 1) * sizeof(char));

    key[key_c++] = '\0';

    while (*line != '\0')
    {
        if (val_c)
            value = realloc(value, (val_c + 1) * sizeof(char));

        value[val_c++] = *line;
        line++;
    }
    line++;

    if (val_c)
        value = realloc(value, (val_c + 1) * sizeof(char));

    value[val_c++] = '\0';

    attr_t _nt = XML_attr_new(key, value);

    XML_attr_add(xml, _nt);
}

RSXML_API char *
__xml_get_tag_body_from_line(char *key, char *data)
{
    char *end_tag = malloc((4 + strlen(key)) * sizeof(char));
    sprintf(end_tag, "/%s", key);

    char *res = malloc(sizeof(char));
    int rc = 0, tagcl = 0;

    for (size_t i = 0; i < strlen(data); i++)
    {
        char c = data[i];

        if (c == '<')
        {
            char *tn = malloc(sizeof(char));
            int tnn = 0;

            for (size_t j = i + 1; j < strlen(data); j++)
            {
                if (data[j] == ' ' || data[j] == '>')
                    break;

                if (tnn)
                    tn = realloc(tn, (tnn + 1) * sizeof(char));

                tn[tnn++] = data[j];
            }

            if (tnn)
                tn = realloc(tn, (tnn + 1) * sizeof(char));

            tn[tnn++] = '\0';

            if (!strcmp(end_tag, tn))
            {
                if (!tagcl)
                    break;
            }

            if (*tn == '/')
                tagcl--;
            else
                tagcl++;

            free(tn);
        }

        if (rc)
            res = realloc(res, (rc + 1) * sizeof(char));

        res[rc++] = c;
    }

    if (rc)
        res = realloc(res, (rc + 1) * sizeof(char));

    res[rc++] = '\0';

    free(end_tag);
    return strdup(res);
}