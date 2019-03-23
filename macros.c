#include "macros.h"

GtkWidget* creerFenetre(xmlNode* windowNode)
{
    //  Variable pour stocker les valeurs de chaque propriété
    int type, width, height, position, resizable;
    const xmlChar *title;
    gboolean resizeBool;

    //  Créer le pointeur sur fenêtre
    GtkWidget *window;

    //  Recuperer la valeur de chaque propriete
    type = atoi(xmlGetProp(windowNode,"type"));
    width = atoi(xmlGetProp(windowNode,"width"));
    height = atoi(xmlGetProp(windowNode,"height"));
    position = atoi(xmlGetProp(windowNode,"position"));
    resizable = atoi(xmlGetProp(windowNode,"resizable"));
    title = xmlGetProp(windowNode,"title");

    /*
    *   Verification si les valeurs sont correctes ou bien saisies,
    *   si elles sont correctes ne rien faire
    *   sinon affecter des valeurs par défaut
    */

    if((type < 0) || (type > 1))
        type = 0;

    if((width < 0) || (width > 1000))
        width = 100;

    if((height < 0) || (height > 1000))
        height = 100;

    if((position < 0) || (position > 4))
        position = 0;

    if(resizable != 0)
        resizeBool = TRUE;
    else
        resizeBool = FALSE;


    //  Affecter les valeurs
    window = gtk_window_new(type);
    gtk_window_set_default_size(window,width,height);
    gtk_window_set_position(window,position);
    gtk_window_set_title(window,(const char*)title);
    gtk_window_set_resizable(window,resizeBool);

    return window;
}

//  Creation d'un box
GtkWidget* creerBox(xmlNode* boxNode)
{
//    //  Variable pour stocker les valeurs de chaque propriété
//    int type, width, height, position, resizable;
//    const xmlChar *title;
//    gboolean resizeBool;
//
//    //  Créer le pointeur sur fenêtre
//    GtkWidget *box;
//
//    //  Recuperer la valeur de chaque propriete
//    type = atoi(xmlGetProp(windowNode,"type"));
//    width = atoi(xmlGetProp(windowNode,"width"));
//    height = atoi(xmlGetProp(windowNode,"height"));
//    position = atoi(xmlGetProp(windowNode,"position"));
//    resizable = atoi(xmlGetProp(windowNode,"resizable"));
//    title = xmlGetProp(windowNode,"title");
//
//    /*
//    *   Verification si les valeurs sont correctes ou bien saisies,
//    *   si elles sont correctes ne rien faire
//    *   sinon affecter des valeurs par défaut
//    */
//
//    if((type < 0) || (type > 1))
//        type = 0;
//
//    if((width < 0) || (width > 1000))
//        width = 100;
//
//
//    if(resizable != 0)
//        resizeBool = TRUE;
//    else
//        resizeBool = FALSE;
//
//
//    //  Affecter les valeurs
//    window = gtk_window_new(type);
//    gtk_window_set_default_size(window,width,height);
//    gtk_window_set_position(window,position);
//    gtk_window_set_title(window,(const char*)title);
//    gtk_window_set_resizable(window,resizeBool);
//
//    return window;
}
