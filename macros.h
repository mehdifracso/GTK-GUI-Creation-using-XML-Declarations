#ifndef MACROS_H_INCLUDED
#define MACROS_H_INCLUDED
#include "xmlParser.h"
#include <gtk/gtk.h>

GtkWidget* creerFenetre(xmlNode* windowNode);

GtkWidget* creerBox(xmlNode* boxNode);

GtkWidget* creerBarreMenu();

GtkWidget* creerMenu(GtkWidget* parentWidget,xmlNode* menuNode);

GtkWidget* creerElementMenu(xmlNode* menuItemNode);

GtkWidget* creerBarreOutils(xmlNode* toolbarNode);

GtkWidget* creerOutil(xmlNode* toolItemNode);

GtkWidget* creerBouton(xmlNode* buttonNode);

GtkWidget* creerEchelle(xmlNode* scaleNode);

GtkWidget* creerTableau(xmlNode* tableNode);

GtkWidget* creerGrille(xmlNode* gridNode);

GtkWidget *creerBarreDefilement(xmlNode* scrollNode);

GtkWidget* creerBoutonDeRotation(xmlNode *spinNode);

GtkWidget* creerCaseACocher(const xmlNode* checkbuttonNode);

GtkWidget* creerEtiquette(xmlNode* labelNode);

GtkWidget* creerImage(xmlNode* imageNode);

GtkWidget* creerComboBox(xmlNode* ComboBoxNode);

GtkWidget* creerComboBoxElement(GtkWidget *ComboBox,xmlNode* ComboBoxNode);

GtkWidget *creerSearchEntry(xmlNode* SearchEntryNode);

GtkWidget *creerSeparateur(xmlNode* separateurNode);

GtkWidget *creerFrame(xmlNode* frameNode);

//GtkWidget *creerEntreeTexte(xmlNode* textEntryNode);
#endif // MACROS_H_INCLUDED
