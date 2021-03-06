#include "widgetParserAndCreator.h"


GtkWidget *createWidget(GtkWidget* parentWidget,xmlNode *node)
{
    GtkWidget *widget = NULL;

    if(xmlStrcmp(node->name, "window") == 0)
    {
        widget = creerFenetre(node);
    }
    else if(xmlStrcmp(node->name, "box") == 0)
    {
        widget = creerBox(node);
    }
    else if(xmlStrcmp(node->name, "menubar") == 0)
    {
        widget = creerBarreMenu(node);
    }
    else if(xmlStrcmp(node->name, "menu") == 0)
    {
        widget = creerMenu(parentWidget,node);
    }
    else if(xmlStrcmp(node->name, "menuItem") == 0)
    {
        widget = creerElementMenu(node);
    }
    else if(xmlStrcmp(node->name, "toolbar") == 0 )
    {
        widget = creerBarreOutils(node);
    }
    else if(xmlStrcmp(node->name, "toolItem") == 0)
    {
        widget = creerOutil(node);
    }
    else if(xmlStrcmp(node->name, "button") == 0)
    {
        widget = creerBouton(node);
    }
    else if(xmlStrcmp(node->name, "scale") == 0)
    {
        widget = creerEchelle(node);
    }
    else if(xmlStrcmp(node->name, "grid") == 0 )
    {
        widget = creerGrille(node);
    }
    else if(xmlStrcmp(node->name, "table") == 0 )
    {
        widget = creerTableau(node);
    }
    else if(xmlStrcmp(node->name, "textEntry") == 0)
    {
//        widget = creerEntreeTexte(node);
    }
    else if(xmlStrcmp(node->name, "scrollBar") == 0)
    {
        widget = creerBarreDefilement(node);
    }
    else if(xmlStrcmp(node->name, "spinButton") == 0)
    {
        widget = creerBoutonDeRotation(node);
    }
    else if(xmlStrcmp(node->name, "checkButton") == 0)
    {
        widget = creerCaseACocher(node);
    }
    else if(xmlStrcmp(node->name, "label") == 0)
    {
        widget = creerEtiquette(node);
    }
    else if(xmlStrcmp(node->name, "image") == 0)
    {
        widget = creerImage(node);
    }
    else if(xmlStrcmp(node->name, "searchEntry") == 0 )
    {
        widget = creerSearchEntry(node);
    }
    else if(xmlStrcmp(node->name, "textEntry") == 0)
    {
        //  widget = creerEntreeTexte(node);
    }
     else if(xmlStrcmp(node->name, "combobox") == 0 )
    {
        widget = creerComboBox(node);
    }
     else if(xmlStrcmp(node->name, "comboboxItem") == 0 )
    {
        widget = creerComboBoxElement(parentWidget,node);
    }
     else if(xmlStrcmp(node->name, "separateur") == 0 )
    {
        widget = creerSeparateur(node);
    }
    else if(xmlStrcmp(node->name, "frame") == 0 )
    {
        widget = creerFrame(node);
    }

    //  Une petite verification avant de retourner le widget
    if(widget)
        return widget;
    else
    {
        printf("widget %s n'a pas pu etre cree, le programme s'arretera",node->name);
        exit(0);
    }
}

GtkWidget *parseStructureAndCreateGUI(char cheminFichier[200])
{
    xmlKeepBlanksDefault(0);
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

    printf("Parent: %s Child: %s\n", mainWindowNode->name, mainWindowNode->children->name);
    if(xmlStrcmp(mainWindowNode->children->name,"text"))
       createAndLinkChild(mainWindow,1,mainWindowNode->children, "window");

    return mainWindow;

}



//  Child node is the current node
void createAndLinkChild(GtkWidget *parentWidget, int parentNature, xmlNode *childNode, char *parentName)
{
    xmlKeepBlanksDefault(0);
    printf("--------------------------------------------------\n\n");
    printf("Entrain de creer: %s\n", childNode->name);
    //  Verifier si on est arriv� � un noeud feuille (pas de noeud(s) enfant(s))
    if(childNode && (xmlStrcmp(childNode->name,"text"))!=0)
    {
        int top, left, height, width;

        //  Creer le widget et le retourner
        GtkWidget *childWidget = createWidget(parentWidget,childNode);

        //  Le lier � son widget pere
        switch(parentNature)
        {
            case 1:
                gtk_container_add(GTK_CONTAINER(parentWidget),childWidget);
                printf("Linked %s to %s\n", childNode->name, parentName);
                break;
            case 2:
                gtk_menu_shell_append(GTK_MENU_SHELL(parentWidget), childWidget);
                printf("Linked %s to %s\n", childNode->name, parentName);
                break;
            case 3:
                gtk_toolbar_insert(GTK_TOOLBAR(parentWidget),GTK_TOOL_ITEM(childWidget),0);
                printf("Linked %s to %s\n", childNode->name, parentName);
                break;
            case 4:
                top = atoi(xmlGetProp(childNode,"startCol"));      //  La colonne d'o� la cellule va d�buter
                left = atoi(xmlGetProp(childNode,"startRow"));     //  La ligne d'o� la cellule va d�buter
                height = atoi(xmlGetProp(childNode,"finishRow"));  //  La ligne o� la cellule va se terminer
                width = atoi(xmlGetProp(childNode,"finishCol"));   //  La colonne o� la cellule va se terminer
                gtk_grid_attach(GTK_GRID(parentWidget),childWidget,left,top,width,height);
                printf("Linked %s to %s\n", childNode->name, parentName);
                break;
            case 5:
                gtk_box_pack_start(GTK_BOX(parentWidget), childWidget, FALSE, FALSE, 0);
                printf("Linked %s to %s\n", childNode->name, parentName);
                break;
            case 6:
                gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(parentWidget),childWidget);
                break;
            case 7:
                top = atoi(xmlGetProp(childNode,"startCol"));      //  La colonne d'o� la cellule va d�buter
                left = atoi(xmlGetProp(childNode,"startRow"));     //  La ligne d'o� la cellule va d�buter
                height = atoi(xmlGetProp(childNode,"finishRow"));  //  La ligne o� la cellule va se terminer
                width = atoi(xmlGetProp(childNode,"finishCol"));   //  La colonne o� la cellule va se terminer
                gtk_table_attach_defaults(GTK_TABLE(parentWidget),childWidget,top,width,left,height);
                printf("Linked %s to %s\n", childNode->name, parentName);
                break;
        }

        printf("J'ai fini de creer: %s\n", childNode->name);
        printf("--------------------------------------------------\n\n");
        //  Si le widget parent a plusieurs widgets fils, il faudra les creer aussi
        if((childNode->next != NULL) && (xmlStrcmp(childNode->next->name,"text") != 0))
            createAndLinkChild(parentWidget,parentNature,childNode->next, parentName);

        //  Si le widget courant a un fils, on le cree
        if((childNode->children != NULL) && (xmlStrcmp(childNode->children->name,"text")!=0))
            createAndLinkChild(childWidget,atoi(xmlGetProp(childNode,"nature")),childNode->children,(char *)childNode->name);
    }
}
