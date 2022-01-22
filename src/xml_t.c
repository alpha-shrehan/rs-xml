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