#include <rsxml.h>

char *read_file(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
        return NULL;
    
    char *str = malloc(sizeof(char));
    int i = 0;
    char c;

    while ((c = fgetc(fp)) != EOF)
    {
        if (i)
            str = realloc(str, (i + 1) * sizeof(char));
        str[i++] = c;
    }

    str = realloc(str, (i + 1) * sizeof(char));
    str[i++] = '\0';

    fclose(fp);
    return str;
}

int main(int argc, const char *argv[])
{
    xml_t *xml = XML_xml_new_ptr((char *)"root", NULL, 0, NULL, 0);
    XML_lexer_fromString(xml, read_file("C:\\Users\\USER\\Desktop\\HProjects\\RsXML\\tests\\main.xml"));

    XML_print_markup_f(xml);
    return 0;
}