#include <api/xml_api.h>
#include <xml_lexer.h>

RSXML_API xml_t XML_new_fromString(char *str)
{
    xml_t *nx = XML_xml_new_ptr(NULL, NULL, 0, NULL, 0);
    XML_lexer_fromString(nx, str);

    return *(nx->children);
}