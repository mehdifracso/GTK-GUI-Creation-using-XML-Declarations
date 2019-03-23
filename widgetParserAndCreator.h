#ifndef WIDGETPARSERANDCREATOR_H_INCLUDED
#define WIDGETPARSERANDCREATOR_H_INCLUDED
#include "macros.h"


void createAndLinkChild(GtkWidget *parentWidget, int parentNature, xmlNode *childNode);
GtkWidget *parseStructureAndCreateGUI(char cheminFichier[200]);
GtkWidget *createWidget(xmlNode *node);


#endif // WIDGETPARSERANDCREATOR_H_INCLUDED
