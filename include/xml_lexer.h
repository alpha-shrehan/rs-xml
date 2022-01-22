#pragma once

#include <rsconfig.h>
#include <rsutils.h>
#include <attr_t.h>
#include <xml_t.h>

RSXML_API int XML_lexer_fromString(xml_t *, char *);
RSXML_API int __xml_atomic_lexer_from_string(xml_t *, char *);