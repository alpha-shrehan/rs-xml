#include <rsxml.h>

int main(int argc, const char *argv[])
{
    xml_t *xml = XML_xml_new_ptr((char *)"root", NULL, 0, NULL, 0);
    XML_lexer_fromString(xml, "<name val='10'>Shrehan</name>");
    return 0;
}