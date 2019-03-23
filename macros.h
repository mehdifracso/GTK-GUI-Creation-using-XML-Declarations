#ifndef MACROS_H_INCLUDED
#define MACROS_H_INCLUDED
#include "xmlParser.h"
#include <gtk/gtk.h>

GtkWidget* creerFenetre(xmlNode* windowNode);

GtkWidget* creerBox(xmlNode* boxNode);

GtkWidget* creerBarreMenu();

GtkWidget* creerMenu(xmlNode* menuNode);

GtkWidget* creerElementMenu(xmlNode* menuItemNode);

GtkWidget* creerBarreOutils(xmlNode* toolbarNode);

GtkWidget* creerOutil(xmlNode* toolItemNode);

GtkWidget* creerBouton(xmlNode* buttonNode);

GtkWidget* creerEchelle(xmlNode* scaleNode);

GtkWidget* creerTableau(xmlNode* gridNode);


#endif // MACROS_H_INCLUDED
