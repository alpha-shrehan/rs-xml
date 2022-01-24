#pragma once

#include <rsconfig.h>
#include <rsutils.h>

RSXML_API xml_t* XML_xml_add_child(xml_t *, xml_t);
RSXML_API void   XML_print_markup(xml_t *);