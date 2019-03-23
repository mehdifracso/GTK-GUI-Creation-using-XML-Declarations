#include "widgetParserAndCreator.h"


GtkWidget *createWidget(xmlNode *node)
{
    GtkWidget *widget = NULL;

    if(xmlStrcmp(node->name, "window"))
    {
        widget = creerFenetre(node);
    }
    else if(xmlStrcmp(node->name, "box"))
    {
        widget = creerBox(node);
    }
    //  Une petite verification avant de retourner le widget
    if(widget)
        return widget;
    else
    {
        printf("Un widget n'a pas pu etre cree, le programme s'arretera");
        exit(0);
    }
}

GtkWidget *parseStructureAndCreateGUI(char cheminFichier[200])
{
    //  Charger le document dans la memoire
    xmlDoc *doc = chargerFichierXML(cheminFichier);

    //  Retrouver le noeud racine
    xmlNode *mainWindowNode = xmlDocGetRootElement(doc);

    //  Verifier si le noeud racine est une fenetre
    if(xmlStrcmp(mainWindowNode->name,"window") != 0)
    {
        printf("Le noeud racine n'est pas une fenetre, le programme sera arrete !");
        exit(0);
    }

    //  Creer le widget fenetre
    GtkWidget* mainWindow = creerFenetre(mainWindowNode);

    //  Trouver le noeud fils de la fenetre, le creer et le lier � son parent
    if(mainWindowNode->children)
        createAndLinkChild(mainWindow,1,mainWindowNode->children);
}

//  Child node is the current node
void createAndLinkChild(GtkWidget *parentWidget, int parentNature, xmlNode *childNode)
{
    //  Verifier si on est arriv� � un noeud feuille (pas de noeud(s) enfant(s))
    if(!childNode)
    {
        int top, left, height, width;
        //  Creer le widget et le retourner
        GtkWidget *childWidget = createWidget(childNode);

        //  Le lier � son widget pere
        switch(parentNature)
        {
        case 1:
            gtk_container_add(GTK_CONTAINER(parentWidget),childWidget);
            break;
        case 2:
            gtk_menu_shell_append(GTK_MENU_SHELL(parentWidget), childWidget);
            break;
        case 3:
            gtk_toolbar_insert(GTK_TOOLBAR(parentWidget),GTK_TOOL_ITEM(childWidget),0);
            break;
        case 4:
            top = atoi(xmlGetProp(childNode,"startCol"));      //  La colonne d'o� la cellule va d�buter
            left = atoi(xmlGetProp(childNode,"startRow"));     //  La ligne d'o� la cellule va d�buter
            height = atoi(xmlGetProp(childNode,"finishRow"));  //  La ligne o� la cellule va se terminer
            width = atoi(xmlGetProp(childNode,"finishCol"));   //  La colonne o� la cellule va se terminer
            gtk_grid_attach(GTK_GRID(parentWidget),childWidget,left,top,width,height);
            break;
        case 5:
            gtk_box_pack_start(GTK_BOX(parentWidget), childWidget, FALSE, FALSE, 0);
            break;
        }

        //  Si le widget parent a plusieurs widgets fils, il faudra les creer aussi
        if(childNode->next)
            createAndLinkChild(parentWidget,parentNature,childNode->next);

        //  Si le widget courant a un fils, on le cree
        if(childNode->children)
            createAndLinkChild(childWidget,atoi(xmlGetProp(childNode,"nature")),childNode->children);
    }
}