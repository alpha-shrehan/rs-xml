#pragma once

#include <rsutils.h>

/**
 * @brief XML_new_fromString(char *).
 * Parses XML from raw data.
 * @param str Raw data (char *)
 * @return xml_t
 */
RSXML_API xml_t XML_new_fromString(char *);