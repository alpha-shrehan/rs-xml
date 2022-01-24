#include <xml_t.h>

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
XML_print_markup(xml_t *xml)
{
    char *res = malloc((strlen(xml->name != NULL ? xml->name : "null") + 2) * sizeof(char));

    if (xml->name != NULL)
        sprintf(res, "<%s", xml->name);
    else
        sprintf(res, "<null");

    for (size_t i = 0; i < xml->attr_count; i++)
    {
        res = realloc(
            res,
            (
                strlen(res) +
                strlen(
                    xml->attr_list[i].name != NULL ? xml->attr_list[i].name : "null") +
                3 +
                strlen(
                    xml->attr_list[i].value != NULL ? xml->attr_list[i].value : "null")) *
                sizeof(char)); // Big brain time

        sprintf(res, "%s %s=%s", res, xml->attr_list[i].name, xml->attr_list[i].value);
    }

    res = realloc(res, (strlen(res) + 2) * sizeof(char));
    strcat(res, ">");

    printf("%s\n", res);
}