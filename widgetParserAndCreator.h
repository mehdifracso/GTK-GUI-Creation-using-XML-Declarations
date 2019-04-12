#ifndef WIDGETPARSERANDCREATOR_H_INCLUDED
#define WIDGETPARSERANDCREATOR_H_INCLUDED
#include "macros.h"


void createAndLinkChild(GtkWidget *parentWidget, int parentNature, xmlNode *childNode, char *parentName);
GtkWidget *parseStructureAndCreateGUI(char cheminFichier[200]);
GtkWidget *createWidget(GtkWidget* parentWidget,xmlNode *node);


#endif // WIDGETPARSERANDCREATOR_H_INCLUDED
