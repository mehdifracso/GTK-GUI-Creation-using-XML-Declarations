#include "macros.h"
#include <string.h>

//  Creer une fenetre
GtkWidget* creerFenetre(xmlNode* windowNode)
{
    //  Variable pour stocker les valeurs de chaque propriété
    int type, width, height, position, resizable;
    const xmlChar *title;

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
        resizable = 1;



    //  Affecter les valeurs
    window = gtk_window_new(type);
    gtk_window_set_default_size(window,width,height);
    gtk_window_set_position(window,position);
    gtk_window_set_title(window,(const char*)title);
    gtk_window_set_resizable(window,resizable);

    return window;
}

//  Creation d'un box
GtkWidget* creerBox(xmlNode* boxNode)
{
    //  Variable pour stocker les valeurs de chaque propriété
    int orientation, spacing, homogeneous;

    //  Créer le pointeur sur le box
    GtkWidget *box;

    //  Recuperer la valeur de chaque propriete
    orientation = atoi(xmlGetProp(boxNode,"orientation"));
    spacing = atoi(xmlGetProp(boxNode,"spacing"));
    homogeneous = atoi(xmlGetProp(boxNode,"homogeneous"));


    /*
    *   Verification si les valeurs sont correctes ou bien saisies,
    *   si elles sont correctes ne rien faire
    *   sinon affecter des valeurs par défaut
    */

    if((orientation < 0) || (orientation > 1))
        orientation = 1;

    if((spacing < 0) || (spacing > 10))
        spacing = 0;


    if(homogeneous != 0)
        homogeneous = 1;


    //  Affecter les valeurs
    box = gtk_box_new(orientation,spacing);
    gtk_box_set_homogeneous(box,homogeneous);

    return box;
}


//  Creation d'une barre de menus
GtkWidget* creerBarreMenu()
{
    //  Créer le pointeur sur la barre de menus
    GtkWidget *menuBar;
    menuBar = gtk_menu_bar_new();

    return menuBar;
}


//  Creation d'un menu
GtkWidget* creerMenu(GtkWidget* menuBar, xmlNode* menuNode)
{
    //  Variable pour stocker le titre
    const xmlChar *label;

    //  Recuperer le titre du menu
    label = xmlGetProp(menuNode,"title");

    //  Donner un titre par defaut si on ne l'a pas saisi dans le fichier XML
    //  strcpy((char *)label,"menu sans nom");

    GtkWidget *menu, *labeledMenuItem;

    menu = gtk_menu_new();
    labeledMenuItem = gtk_menu_item_new_with_label(label);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(labeledMenuItem),menu);
    gtk_menu_shell_append(GTK_MENU_SHELL(menuBar),labeledMenuItem);

    return menu;
}

//  Creation d'un element de menu
GtkWidget* creerElementMenu(xmlNode* menuItemNode)
{
    //  Variable pour stocker le titre
    const xmlChar *label;

    //  Recuperer le titre de l'element de menu
    label = xmlGetProp(menuItemNode,"name");

    GtkWidget *menuItem;

    menuItem = gtk_menu_item_new_with_label((const gchar*)label);

    return menuItem;
}


//  Creation d'une barre d'outils
GtkWidget* creerBarreOutils(xmlNode* toolbarNode)
{
    //  Variable d'affichage d'une fleche d'extension d'outils
    //  au cas où il n'y a pas d'espace pour afficher le tout
    int showArrow;

    //  Recuperer la valeur d'affichage d'extension
    showArrow = atoi(xmlGetProp(toolbarNode,"showArrow"));

    //  Une petite verification
      if(showArrow)
        showArrow = 1;

    //  Creation du widget
    GtkWidget *toolbar;
    toolbar = gtk_toolbar_new();

    gtk_toolbar_set_show_arrow(GTK_TOOLBAR(toolbar),showArrow);

    return toolbar;
}

//  Creation d'un outil
GtkWidget* creerOutil(xmlNode* toolItemNode)
{
    //  Variables pour stocker les proprietes de l'outil
    int homogeneous, expandable, dragWindow, important,
    visibleVertical, visibleHorizontal;


    //  Recuperer les valeurs des proprietes
    homogeneous = atoi(xmlGetProp(toolItemNode,"homogeneous"));
    expandable = atoi(xmlGetProp(toolItemNode,"expandable"));
    dragWindow = atoi(xmlGetProp(toolItemNode,"dragWindow"));
    important = atoi(xmlGetProp(toolItemNode,"important"));
    visibleVertical = atoi(xmlGetProp(toolItemNode,"visibleVertical"));
    visibleHorizontal = atoi(xmlGetProp(toolItemNode,"visibleHorizontal"));



    //  Une petite verification
    if(homogeneous)
        homogeneous = 1;
    if(expandable)
        expandable = 1;
    if(dragWindow)
        dragWindow = 1;
    if(important)
        important = 1;
    if(visibleVertical)
        visibleVertical = 1;


    //  Creation du widget et affectation des valeurs recuperees
    GtkWidget *toolitem;
    toolitem = gtk_tool_item_new();
    gtk_tool_item_set_homogeneous(toolitem,homogeneous);
    gtk_tool_item_set_expand(toolitem,expandable);
    gtk_tool_item_set_use_drag_window(toolitem,dragWindow);
    gtk_tool_item_set_is_important(toolitem,important);
    gtk_tool_item_set_visible_vertical(toolitem,visibleVertical);



    return toolitem;
}

//  Creation d'un bouton
GtkWidget* creerBouton(xmlNode* buttonNode)
{
    //  Variables pour stocker les proprietes du bouton
    int relief;

    const xmlChar *label = NULL;


    //  Recuperer les valeurs des proprietes
    relief = atoi(xmlGetProp(buttonNode,"relief"));
    label = xmlGetProp(buttonNode,"name");

    //  Une petite verification
    if((relief < 0) || (relief > 2))
        relief = 0;

    if(!label)
        strcpy(label, "pas de texte predefini");

    //  Creation du widget et affectation des valeurs recuperees
    GtkWidget *button;
    button = gtk_button_new();

    gtk_button_set_relief(button,relief);
    gtk_button_set_label(button,label);

    return button;
}


//  Creer une echelle (Scale)
GtkWidget* creerEchelle(xmlNode* scaleNode)
{
    //  Variables pour stocker les proprietes du bouton
    int orientation, min, max, step, digits, draw, origin, valuePosition;

    //  Recuperer les valeurs des proprietes
    orientation = atoi(xmlGetProp(scaleNode,"orientation"));
    min = atoi(xmlGetProp(scaleNode,"min"));
    max = atoi(xmlGetProp(scaleNode,"max"));
    step = atoi(xmlGetProp(scaleNode,"step"));
    digits = atoi(xmlGetProp(scaleNode,"digits"));
    draw = atoi(xmlGetProp(scaleNode,"draw"));
    origin = atoi(xmlGetProp(scaleNode,"origin"));
    valuePosition = atoi(xmlGetProp(scaleNode,"valuePosition"));

    //  Une petite verification
    if(max > min)
    {
        int tmp = max;
        max = min;
        min = tmp;
    }

    if(step>= max)
    {
        int tmp = max;
        max = step;
        step = tmp;
    }

    if(orientation)
        orientation = 1;

    if(!step)
        step = 1;

    if(digits < 0)
        digits = 0;

    if(draw)
        draw = 1;

    if(origin)
        origin = 1;

    if((valuePosition < 0) || (valuePosition > 3))
        valuePosition = 0;

    //  Creation du widget et affectation des valeurs recuperees
    GtkWidget *scale;
    scale = gtk_scale_new_with_range(orientation,min,max,step);
    gtk_scale_set_digits(scale,digits);
    gtk_scale_set_draw_value(scale,draw);
    gtk_scale_set_has_origin(scale,origin);
    gtk_scale_set_value_pos(scale,valuePosition);

    return scale;
}

//  Creation d'une grille
GtkWidget* creerGrille(xmlNode* gridNode)
{
    //  Variables pour stocker les proprietes du tableau
    int columns, rows;


    //  Recuperer les valeurs des proprietes
    columns = atoi(xmlGetProp(gridNode,"columns"));
    rows = atoi(xmlGetProp(gridNode,"rows"));

    //  Une petite verification
    if((columns < 0) || (columns > 50))
        columns = 25;

    if((rows < 0) || (rows > 50))
        rows = 25;

    //  Creation du widget et affectation des valeurs recuperees
    GtkWidget *grid;
    grid = gtk_grid_new();

    int i;
    for(i=0; i<columns; i++)
        gtk_grid_insert_column(grid,0);

    for(i=0; i<rows; i++)
        gtk_grid_insert_row(grid,0);

    return grid;
}

//  creation d'un tableau
GtkWidget* creerTableau(xmlNode* tableNode)
{
    GtkWidget *table;
    //  Variables pour stocker les proprietes du tableau
    int columns, rows;


    //  Recuperer les valeurs des proprietes
    columns = atoi(xmlGetProp(tableNode,"columns"));
    rows = atoi(xmlGetProp(tableNode,"rows"));

    //  Une petite verification
    if((columns < 0) || (columns > 50))
        columns = 25;

    if((rows < 0) || (rows > 50))
        rows = 25;

    //  Creation du widget et affectation des valeurs recuperees

    table = gtk_table_new(rows,columns,TRUE);

    return table;
}


GtkWidget *creerBarreDefilement(xmlNode* scrollNode)
{
    GtkWidget *scrollbar;

    int horizontalScrolling, verticalScrolling;
    horizontalScrolling = atoi(xmlGetProp(scrollNode,"hscroll_policy"));
    verticalScrolling = atoi(xmlGetProp(scrollNode,"vscroll_policy"));

    if(horizontalScrolling)
        horizontalScrolling = 1;

    if(verticalScrolling)
        verticalScrolling = 1;

    if(horizontalScrolling && verticalScrolling)
        horizontalScrolling = 0;

    /* paramètres concernant l'affichage des barres de défilement.*/
    scrollbar = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(scrollbar,verticalScrolling,horizontalScrolling);

   return scrollbar;
}


GtkWidget* creerBoutonDeRotation(xmlNode *spinNode)
{
    GtkWidget* spin;

    int min, max, step;

    min = atoi(xmlGetProp(spinNode,"min"));
    max = atoi(xmlGetProp(spinNode,"max"));
    step = atoi(xmlGetProp(spinNode,"step"));

    spin = gtk_spin_button_new_with_range(min,max,step);

    return spin;

}

GtkWidget* creerCaseACocher(const xmlNode* checkbuttonNode)
{
    GtkWidget *checkbutton;
    const xmlChar *contenucb;
    int choice;

    choice = atoi(xmlGetProp(checkbuttonNode,"type"));
    contenucb = xmlGetProp(checkbuttonNode,"contenucb");

    if(!choice)
        checkbutton = gtk_check_button_new_with_mnemonic(contenucb);
    else
        checkbutton = gtk_check_button_new_with_label(contenucb);

    return checkbutton;
}


GtkWidget* creerEtiquette(xmlNode* labelNode)
{
    GtkWidget *label;
    const xmlChar *contenu;

    contenu = xmlGetProp(labelNode,"contenu");

    label=gtk_label_new(contenu);

    return label;
}


GtkWidget* creerImage(xmlNode* imageNode)
{
    GtkWidget *image;//widget image
    const xmlChar *path;//chemin de l'image
    int  width, height;//position de l'image
   // int image_type; // CH_IMG ou Q_IMG


    path = xmlGetProp(imageNode,"path");
    width= atoi(xmlGetProp(imageNode,"width"));
    height = atoi(xmlGetProp(imageNode,"height"));

    if((width <= 0) || (width > 5000))
        width = 100;

    if((height< 0) || (height > 5000))
        height = 100;

    image = gtk_image_new_from_file(path);
    gtk_widget_set_size_request(GTK_WIDGET(image),width,height);

    return image;
}

//creer searchEntry
GtkWidget *creerSearchEntry(xmlNode* SearchEntryNode)
{
    //  Variables pour stocker les proprietes du bouton

    GtkWidget  *search;
    int width, height;

    //  Recuperer les valeurs des proprietes

    width = atoi(xmlGetProp(SearchEntryNode,"width"));
    height = atoi(xmlGetProp(SearchEntryNode,"height"));

    // Affectation des  valeurs

    search = gtk_search_entry_new ();
    gtk_widget_set_size_request(GTK_WIDGET(search),width,height);

    return search;
}

//  Creation du ComboBox
GtkWidget* creerComboBox(xmlNode* ComboBoxNode)
{
    // Declaration du widget
    GtkWidget *ComboBox;
    // Creation de la liste deroulante
   ComboBox=gtk_combo_box_text_new();
    // retourner le widget
   return ComboBox;
}


//  Ajout d'element au combo box
GtkWidget* creerComboBoxElement(GtkWidget *ComboBox,xmlNode* ComboBoxNode)
{
    //  Variables pour stocker les proprietes

   const xmlChar *label;

   //  Recuperer les valeurs des proprietes

   label = (xmlGetProp(ComboBoxNode,"label"));

   // Affectation des  valeurs et l'ajout de l'element a la liste deroulante

   gtk_combo_box_text_append_text(GTK_COMBO_BOX(ComboBox),label);

   return ComboBox;
}


//  Creation separateur
GtkWidget *creerSeparateur(xmlNode* separateurNode)
{
    //  Variables pour stocker les proprietes du separateur

    GtkWidget *separateur;
    const xmlChar *type;
    int width, height;

    //  Recuperer les valeurs des proprietes

    width = atoi(xmlGetProp(separateurNode,"width"));
    height = atoi(xmlGetProp(separateurNode,"height"));
    type = atoi(xmlGetProp(separateurNode,"type"));


    // Affectation des  valeurs
    /// si type != 0 alors on va creer un separateur horizontal sinon le separateur creer va etre vertical
    if(type)
    	separateur = gtk_hseparator_new();
    else
    	separateur = gtk_vseparator_new();

    gtk_widget_set_size_request(GTK_WIDGET(separateur),width,height);

    return separateur;
}

//  Creation cadre
GtkWidget *creerFrame(xmlNode* frameNode)
{
    //  Variables pour stocker les proprietes du bouton

    GtkWidget *frame;
    const xmlChar *label;
    ///int x, y;

    //  Recuperer les valeurs des proprietes

    ///x = atoi(xmlGetProp(frameNode,"x"));
    ///y = atoi(xmlGetProp(frameNode,"y"));
    label = (xmlGetProp(frameNode,"label"));


    // Affectation des  valeurs
    frame = gtk_frame_new (label);
    //gtk_frame_set_label(frame,label);
    //gtk_frame_set_label_align(frame,x,y);
    //gtk_frame_set_shadow_type(GTK_FRAME(frame),C_SHADOW_ETCHED_IN_OUT);

    return frame;
}


//// Creation d'une zone d'entrée de texte
//GtkWidget *creerEntreeTexte(xmlNode* textEntryNode)
//{
//    GtkWidget *textEntry;
//    int maxLength,getOrNot,visibOrNot, hasFrame, maxWidth;
//    float alignement;
//    xmlChar *contentValue = NULL, *placeholder = NULL;
//
//    maxLength = atoi(xmlGetProp(textEntryNode,"maxLength"));
//    getOrNot = atoi(xmlGetProp(textEntryNode,"method"));
//    visible = atoi(xmlGetProp(textEntryNode,"visible"));
//    hasFrame = atoi(xmlGetProp(textEntryNode,"hasFrame"));
//    hasFrame = atoi(xmlGetProp(textEntryNode,"hasFrame"));
//    alignement = atof(xmlGetProp(textEntryNode,"alignement"));
//    contentValue = xmlGetProp(textEntryNode, "contentValue");
//    placeholder = xmlGetProp(textEntryNode, "placeholder");
//
//
//    if((maxLength < 0) || (maxLength > 50))
//        maxLength = 50;
//
//    if(visible != 0)
//        visible = 1;
//
//    if(hasFrame)
//        hasFrame = 1;
//
//    if(maxWidth < 1)
//        maxWidth = 1;
//
//    if((alignement < 0) || (alignement > 1))
//        alignement = 0;
//
//    if(!contentValue)
//        strcpy((char *)contentValue, "Pas de texte prédifini");
//
//    if(!placeholder)
//        strcpy((char *)placeholder, "Pas d'indication");
//
//    textEntry = gtk_entry_new_with_max_length(length);
//    gtk_entry_set_visibility(textEntry,visible);
//    gtk_entry_set_text(textEntry, (const gchar *)contentValue);
//    gtk_entry_set_max_length(textEntry,maxLength);
//    gtk_entry_set_has_frame(textEntry,hasFrame);
//    gtk_entry_set_max_width_char(textEntry,maxWidth);
//    gtk_entry_set_placeholder_text(textEntry,placeholder);
//
//
//    return textentry;
//}
