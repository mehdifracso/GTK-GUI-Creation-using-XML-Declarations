#include "xmlParser.h"

xmlDoc* chargerFichierXML(char cheminFichier[200])
{
    //	Charge le contenu du fichier XML dans la memoire
	xmlDoc *doc = xmlReadFile(cheminFichier,NULL,0);

	//	Verifier si le fichier a bien été chargé
	if(doc == NULL)
	{
		printf("Le fichier contenant les propriétés n'a pu être chargé");
		exit(1);
	}

	return doc;
}

