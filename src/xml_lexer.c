#include <xml_lexer.h>

RSXML_API int
XML_lexer_fromString(xml_t *xml, char *str)
{
    return __xml_atomic_lexer_from_string(xml, str);
}

RSXML_API int
__xml_atomic_lexer_from_string(xml_t *xml, char *str)
{
    for (size_t i = 0; i < strlen(str); i++)
    {
        char c = str[i];

        if (c == '<')
        {
            char *rt = malloc(sizeof(char));
            int ri = 0, sfg = 0;

            for (size_t j = i + 1; j < strlen(str); j++)
            {
                if (str[j] == '>' && !sfg)
                {
                    i = j;
                    break;
                }

                if (str[j] == '\'' ||
                    str[j] == '\"')
                    sfg = !sfg;

                if (ri)
                    rt = realloc(rt, (ri + 1) * sizeof(char));

                rt[ri++] = str[j];
            }

            if (ri)
                rt = realloc(rt, (ri + 1) * sizeof(char));

            rt[ri++] = '\0';

            char *tag_name = strdup(__xml_get_name_from_tag_line(strdup(rt)));

            xml_t xt = XML_xml_new(strdup(tag_name), NULL, 0, NULL, 0);
            __xml_make_attrs_from_line(&xt, strdup(rt));

            char *tag_body = strdup(__xml_get_tag_body_from_line(tag_name, str + i + 1));

            XML_lexer_fromString(&xt, strdup(tag_body));
            XML_xml_add_child(xml, xt);

            i += strlen(tag_body) + strlen(tag_name) + 3;

            free(tag_body);
            free(tag_name);
            free(rt);
        }
        else
        {
            char *r = malloc(sizeof(char));
            char ri = 0;
            int ej = -1;

            for (size_t j = i; j < strlen(str); j++)
            {
                if (str[j] == '<')
                {
                    ej = j - 1;
                    break;
                }

                if ((
                        str[j] == ' ' ||
                        str[j] == '\t' ||
                        str[j] == '\n') &&
                    !ri)
                    continue;

                if (ri)
                    r = realloc(r, (ri + 1) * sizeof(char));

                r[ri++] = str[j];
            }

            if (ri)
                r = realloc(r, (ri + 1) * sizeof(char));

            r[ri++] = '\0';

            if (strlen(r))
            {
                xml_t tagc = XML_xml_new("val", NULL, 0, NULL, 0);
                attr_t att = XML_attr_new("val", strdup(r));

                XML_attr_add(&tagc, att);
                XML_xml_add_child(xml, tagc);
            }

            free(r);
            
            if (ej != -1)
                i = ej;
            else
                break; // EOF
        }
    }

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
    if (strstr(line, (char *)(char[]){' ', '\0'}) == NULL)
        return;

    while (*line != '\0')
    {
        line++;

        if (*line == ' ')
            break;
    }

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
    sprintf(end_tag, "/%s", strdup(key));

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