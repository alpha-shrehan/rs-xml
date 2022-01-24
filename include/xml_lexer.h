#pragma once

#include <rsconfig.h>
#include <rsutils.h>
#include <attr_t.h>
#include <xml_t.h>

RSXML_API int XML_lexer_fromString(xml_t *, char *);
RSXML_API int __xml_atomic_lexer_from_string(xml_t *, char *);
RSXML_API char *__xml_get_name_from_tag_line(char *);
RSXML_API void __xml_make_attrs_from_line(xml_t *, char *);
RSXML_API void __xml_make_attr_single_from_line(xml_t *, char *);
RSXML_API char *__xml_get_tag_body_from_line(char *, char *);