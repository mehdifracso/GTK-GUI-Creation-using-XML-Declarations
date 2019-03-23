#include <stdlib.h>
#include <gtk/gtk.h>
#include "widgetParserAndCreator.h"




int main (int argc, char *argv[])
{
    gtk_init(&argc,&argv);

    GtkWidget *mainWindow = parseStructureAndCreateGUI("mainWidgetsStructure.xml");

    gtk_widget_show_all(mainWindow);
    gtk_main();
    return 0;
}

