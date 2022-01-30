#pragma once

#include <rsconfig.h>

struct xml_attr
{
    char *name;
    char *value;
};

/**
 * @brief All text which does not belong to tags is stored in tags named val (which has an attribute val),
 * till a tag is reached.
 */
struct xml_node
{
    char *name;
    struct xml_attr *attr_list;
    int attr_count;
    struct xml_node *children;
    int children_count;
};

typedef struct xml_attr attr_t;
typedef struct xml_node xml_t;

#ifdef __cplusplus
extern "C" {
#endif

RSXML_API attr_t    XML_attr_new    (char *, char *);
RSXML_API attr_t*   XML_attr_new_ptr(char *, char *);
RSXML_API xml_t     XML_xml_new     (char *, attr_t *, int, xml_t *, int);
RSXML_API xml_t*    XML_xml_new_ptr (char *, attr_t *, int, xml_t *, int);

#ifdef __cplusplus
}
#endif