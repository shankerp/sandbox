#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

FILE *desc;

static int
readPacket(char *mem, int size) {
    int res;

    res = fread(mem, 1, size, desc);
    return(res);
}

static void
example4Func(const char *filename) {
    xmlParserCtxtPtr ctxt;
    char chars[1];
    xmlDocPtr doc;
    int res;

    ctxt = xmlCreatePushParserCtxt(0, 0, 0, 0, 0);
    ctxt->replaceEntities = 1;
    const unsigned BOM = 0xFEFF;
    const unsigned char BOMHighByte = *(const unsigned char *)&BOM;
xmlSwitchEncoding(ctxt, BOMHighByte == 0xFF ? XML_CHAR_ENCODING_UTF16LE : XML_CHAR_ENCODING_UTF16BE);

    while ((res = readPacket(chars, 1)) > 0) {
        short unicode = chars[0];
xmlParseChunk(ctxt, (const char *)&unicode, sizeof (unsigned), 0);
    }
    xmlParseChunk(ctxt, chars, 0, 1);

    doc = ctxt->myDoc;
    res = ctxt->wellFormed;
    xmlFreeParserCtxt(ctxt);

    if (res)
        fprintf(stderr, "Success!\n");
    else
        fprintf(stderr, "Failed to parse %s\n", filename);

    xmlFreeDoc(doc);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Incorrect number of args\n");
        return(1);
    }
    LIBXML_TEST_VERSION

    desc = fopen(argv[1], "rb");
    if (desc != NULL) {
        example4Func(argv[1]);
        fclose(desc);
    } else
        fprintf(stderr, "Failed to open %s\n", argv[1]);

    xmlCleanupParser();
    xmlMemoryDump();
    return 0;
}
