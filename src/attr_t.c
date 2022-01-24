#include <attr_t.h>

RSXML_API attr_t *
XML_attr_add(xml_t *xml, attr_t attr)
{
    assert(xml != NULL);
    assert(xml->attr_list != NULL);
    assert(xml->attr_count > -1);

    if (xml->attr_count)
        xml->attr_list = realloc(xml->attr_list, (xml->attr_count + 1) * sizeof(attr_t));

    xml->attr_list[xml->attr_count] = attr;

    return &(xml->attr_list[xml->attr_count++]);
}

RSXML_API attr_t *
XML_attr_get(xml_t *xml, char *name)
{
    assert(xml != NULL);
    assert(xml->attr_list != NULL);
    assert(xml->attr_count > -1);

    if (!xml->attr_count)
        return NULL;

    int i = 0,
        j = xml->attr_count - 1;

    do
    {
        if (name == NULL)
        {
            if (
                xml->attr_list[i].name == NULL)
                return &(xml->attr_list[i]);
            else if (
                xml->attr_list[j].name == NULL)
                return &(xml->attr_list[j]);
        }
        else
        {
            if (
                !strcmp(xml->attr_list[i].name, name))
                return &(xml->attr_list[i]);
            else if (
                !strcmp(xml->attr_list[j].name, name))
                return &(xml->attr_list[j]);
        }

        i++;
        j--;
    } while (i < j);

    return NULL;
}