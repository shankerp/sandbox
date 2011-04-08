#include <stdio.h>
#include <stdlib.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

int main(int argc, char **argv)
{

  xmlNode *cur_node, *child_node;
  xmlChar *fieldLength, *alternateName;
  char *DisplayXName, *DisplayXType, *altProp, *textFont;

  // --------------------------------------------------------------------------
  // Open XML document
  // --------------------------------------------------------------------------

  xmlDocPtr doc;
  doc = xmlParseFile("testLibXml2.xml");

  if (doc == NULL)
        printf("error: could not parse file file.xml\n");

  // --------------------------------------------------------------------------
  // XML root.
  // --------------------------------------------------------------------------

  /*Get the root element node */
  xmlNode *root = NULL;
  root = xmlDocGetRootElement(doc);

  // --------------------------------------------------------------------------
  // Must have root element, a name and the name must be "AppConfigData"
  // --------------------------------------------------------------------------

  if( !root ||
      !root->name ||
      xmlStrcmp(root->name,"AppConfigData") )
  {
     xmlFreeDoc(doc);
     return FALSE;
  }

  // --------------------------------------------------------------------------
  // AppConfigData children: For each DisplayX
  // --------------------------------------------------------------------------

  for(cur_node = root->children; cur_node != NULL; cur_node = cur_node->next)
  {
     if ( cur_node->type == XML_ELEMENT_NODE  &&
          !xmlStrcmp(cur_node->name, (const xmlChar *) "DisplayX" ) )
     {
        printf("Element: %s \n", cur_node->name);
        DisplayXName = xmlGetProp(cur_node,"name");
        if(DisplayXName) printf("         name=%s\n", DisplayXName);
        DisplayXType = xmlGetProp(cur_node,"type");
        if(DisplayXType) printf("         type=%s\n", DisplayXType);

        // For each child of DisplayX: i.e. AlternateName, FieldLength
        for(child_node = cur_node->children; child_node != NULL; child_node = child_node->next)
        {
           if ( cur_node->type == XML_ELEMENT_NODE  &&
                !xmlStrcmp(child_node->name, (const xmlChar *)"FieldLength") )
           {
              printf("   Child=%s\n", child_node->name);
              fieldLength = xmlNodeGetContent(child_node);
              if(fieldLength) printf("         Length: %s\n", fieldLength);
              xmlFree(fieldLength);
           }
           if ( cur_node->type == XML_ELEMENT_NODE  &&
                !xmlStrcmp(child_node->name, (const xmlChar *)"AlternateName") )
           {
              printf("   Child=%s\n", child_node->name);
              alternateName = xmlNodeGetContent(child_node);
              if(alternateName) printf("         Name: %s\n", alternateName);
              altProp = xmlGetProp(child_node,"type");
              if(altProp) printf("               type=%s\n", altProp);
              xmlFree(altProp);
              xmlFree(alternateName);
           }
           if ( cur_node->type == XML_ELEMENT_NODE  &&
                !xmlStrcmp(child_node->name, (const xmlChar *)"TextFont") )
           {
              printf("   Child=%s\n", child_node->name);
              textFont = xmlGetProp(child_node,"type");
              if(textFont) printf("         type=%s\n", textFont);
              xmlFree(textFont);
           }
        }
        xmlFree(DisplayXType);
        xmlFree(DisplayXName);
     }
  }

  // --------------------------------------------------------------------------

  /*free the document */
  xmlFreeDoc(doc);

  /*
   *Free the global variables that may
   *have been allocated by the parser.
   */
  xmlCleanupParser();

  return 0;
}
