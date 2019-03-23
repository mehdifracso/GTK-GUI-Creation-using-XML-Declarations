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
GtkWidget* creerMenu(xmlNode* menuNode)
{
    //  Variable pour stocker le titre
    const xmlChar *label;

    //  Recuperer le titre du menu
    label = xmlGetProp(menuNode,"title");

    //  Donner un titre par defaut si on ne l'a pas saisi dans le fichier XML
    strcpy((char *)label,"menu sans nom");

    GtkWidget *menu, *labeledMenuItem;

    menu = gtk_menu_new();
    labeledMenuItem = gtk_menu_item_new_with_label(label);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(labeledMenuItem),menu);

    return menu;
}

//  Creation d'un element de menu
GtkWidget* creerElementMenu(xmlNode* menuItemNode)
{
    //  Variable pour stocker le titre
    const xmlChar *label;

    //  Recuperer le titre de l'element de menu
    label = xmlGetProp(menuItemNode,"name");

    //  Donner un titre par defaut si on ne l'a pas saisi dans le fichier XML
    strcpy((char *)label,"menu sans nom");

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

    const xmlChar *tooltipText = NULL, *markupText = NULL;


    //  Recuperer les valeurs des proprietes
    homogeneous = atoi(xmlGetProp(toolItemNode,"homogeneous"));
    expandable = atoi(xmlGetProp(toolItemNode,"expandable"));
    dragWindow = atoi(xmlGetProp(toolItemNode,"dragWindow"));
    important = atoi(xmlGetProp(toolItemNode,"important"));
    visibleVertical = atoi(xmlGetProp(toolItemNode,"visibleVertical"));
    visibleHorizontal = atoi(xmlGetProp(toolItemNode,"visibleHorizontal"));
    tooltipText = xmlGetProp(toolItemNode,"tooltipText");
    markupText = xmlGetProp(toolItemNode,"markupText");

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
    if(visibleHorizontal)
        visibleHorizontal = 1;
    if(!tooltipText)
        strcpy((char *)tooltipText,"Pas de texte saisi");
    if(!markupText)
        strcpy((char *)markupText,"Pas de texte saisi");

    //  Creation du widget et affectation des valeurs recuperees
    GtkWidget *toolitem;
    toolitem = gtk_tool_item_new();

    gtk_tool_item_set_homogeneous(toolitem,homogeneous);
    gtk_tool_item_set_expand(toolitem,expandable);
    gtk_tool_item_set_use_drag_window(toolitem,dragWindow);
    gtk_tool_item_set_is_important(toolitem,important);
    gtk_tool_item_set_visible_vertical(toolitem,visibleVertical);
    gtk_tool_item_set_visible_horizontal(toolitem,visibleHorizontal);
    gtk_tool_item_set_tooltip_markup(toolitem,markupText);
    gtk_tool_item_set_tooltip_text(toolitem,tooltipText);

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

//  Creation d'un tableau
GtkWidget* creerTableau(xmlNode* gridNode)
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
