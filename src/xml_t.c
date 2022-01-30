#include <xml_t.h>
#include <attr_t.h>

RSXML_API xml_t *
XML_xml_add_child(xml_t *xml, xml_t child)
{
    assert(xml != NULL);
    assert(xml->children != NULL);
    assert(xml->children_count > -1);

    if (xml->children_count)
        xml->children = realloc(xml->children, (xml->children_count + 1) * sizeof(xml_t));

    xml->children[xml->children_count] = child;

    return &(xml->children[xml->children_count++]);
}

RSXML_API void
XML_print_markup(xml_t xml)
{
    char *res = malloc((strlen(xml.name != NULL ? xml.name : "null") + 2) * sizeof(char));

    if (xml.name != NULL)
        sprintf(res, "<%s", xml.name);
    else
        sprintf(res, "<null");

    for (size_t i = 0; i < xml.attr_count; i++)
    {
        res = realloc(
            res,
            (
                strlen(res) +
                strlen(
                    xml.attr_list[i].name != NULL ? xml.attr_list[i].name : "null") +
                3 +
                strlen(
                    xml.attr_list[i].value != NULL ? xml.attr_list[i].value : "null")) *
                sizeof(char)); // Big brain time

        sprintf(res, "%s %s=%s", res, xml.attr_list[i].name, xml.attr_list[i].value);
    }

    res = realloc(res, (strlen(res) + 2) * sizeof(char));
    strcat(res, ">");

    printf("%s", res);

    for (size_t i = 0; i < xml.children_count; i++)
        XML_print_markup(xml.children[i]);

    char *rc = res;
    res++;
    if (strstr(res, (char *)(char[]){' ', '\0'}) != NULL)
        res[strstr(res, (char *)(char[]){' ', '\0'}) - res] = '\0';
    printf("</%s", res);
    if (res[strlen(res) - 1] != '>')
        printf(">");
    res--;
    free(rc);
}

RSXML_API void XML_print_markup_f(xml_t xml)
{
    __xml_print_markup_f(xml, "");
}

RSXML_API void __xml_print_markup_f(xml_t xml, char *pref)
{
    char *res = malloc((strlen(xml.name != NULL ? xml.name : "") + 2) * sizeof(char));

    if (xml.name != NULL && !strcmp(xml.name, "val"))
    {
        printf("%s%s\n", pref, XML_attr_get(&xml, "val")->value);
        return;
    }

    if (xml.name != NULL)
        sprintf(res, "<%s", xml.name);
    else
        sprintf(res, "<");

    for (size_t i = 0; i < xml.attr_count; i++)
    {   
        res = realloc(
            res,
            (
                strlen(res) +
                strlen(
                    xml.attr_list[i].name != NULL ? xml.attr_list[i].name : "null") +
                3 +
                strlen(
                    xml.attr_list[i].value != NULL ? xml.attr_list[i].value : "null")) *
                sizeof(char)); // Big brain time

        sprintf(res, "%s %s=%s", res, xml.attr_list[i].name, xml.attr_list[i].value);
    }

    res = realloc(res, (strlen(res) + 2) * sizeof(char));
    strcat(res, ">");

    printf("%s%s", pref, res);
    printf("\n");

    char *pref_ = malloc((strlen(pref) + 6) * sizeof(char));
    sprintf(pref_, "%s    ", pref);

    for (size_t i = 0; i < xml.children_count; i++)
        __xml_print_markup_f(xml.children[i], pref_);

    char *rc = res;
    res++;

    if (strstr(res, (char *)(char[]){' ', '\0'}) != NULL)
        res[strstr(res, (char *)(char[]){' ', '\0'}) - res] = '\0';
    
    printf("%s</%s", pref, res);

    if (res[strlen(res) - 1] != '>')
        printf(">");
    printf("\n");

    res--;
    free(rc);

    free(pref_);
}