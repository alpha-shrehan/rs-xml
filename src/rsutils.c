#include <rsutils.h>

RSXML_API attr_t
XML_attr_new(char *name, char *val)
{
    attr_t v = (attr_t){
        .name = name,
        .value = val};

    return v;
}

RSXML_API attr_t *
XML_attr_new_ptr(char *name, char *val)
{
    attr_t *v = malloc(sizeof(attr_t));
    *v = XML_attr_new(name, val);

    return v;
}

RSXML_API xml_t
XML_xml_new(
    char *name,
    attr_t *attr_list,
    int attr_count,
    xml_t *children,
    int children_count)
{
    xml_t v = (xml_t){
        .name = name,
        .attr_count = attr_count,
        .children_count = children_count,
        .attr_list = attr_list,
        .children = children};

    if (attr_list == NULL)
        v.attr_list = malloc(sizeof(attr_t));

    if (children == NULL)
        v.children = malloc(sizeof(xml_t));

    return v;
}

RSXML_API xml_t * 
XML_xml_new_ptr(
    char *name, 
    attr_t *attr_list, 
    int attr_count, 
    xml_t *children, 
    int children_count)
{
    xml_t *v = malloc(sizeof(xml_t));
    *v = XML_xml_new(name, attr_list, attr_count, children, children_count);

    return v;
}