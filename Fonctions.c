#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "Fonctions.h"



void wconfig() //fonction qui nous permet d'editer la configuration du shell
{
   FILE *config=NULL;


	Profile Profile1; //creation d'une structure profile

	printf("Quelle Langue voulez vous?\n");
	printf("Langues disponibles: 1-Francais 2-Anglais 3-Espagnol\n");
	printf("Votre choix (1-3):");
	scanf("%d",&Profile1.lang);

    switch (Profile1.lang)
    {
    case 1:
    {
	printf("Quelle Mode voulez vous?\n");
	printf("Modes disponibles: 1-Mode Expert 2-Mode Pas à Pas 3-Mode Langage Naturel\n");
	printf("Votre choix (1-3):");
	}
	break;
    case 2:
    {
	printf("Wich Mode do you want?\n");
	printf("Available Modes: 1-Expert Mode 2-Step by Step Mode 3-Fluent langage mode\n");
	printf("Your choice (1-3):");
	}break;
	 case 3:
    {
	printf("Que modo es lo que quieres?\n");
	printf("Modos disponibles: 1-modo experto 2-modo de menu 3-modo de lenguaje natural\n");
	printf("su eleccion (1-3):");
	}break;
    }
    scanf("%d",&Profile1.mode);


    switch (Profile1.lang)
    {
    case 1:
    {
	printf("Que sera votre prompt?");
	}
	break;
    case 2:
    {
	printf("What will be your prompt?");;
	}break;
	 case 3:
    {
	printf("Cual sera su pronta?");;
	}break;
    }
	scanf("%s",Profile1.prompt);




    //aprés avoir recuperer les données entrées par l'utilisateur on stock le tout dans un fichier


	config= fopen("config.cfg", "w");


    fprintf(config, "%d\n", Profile1.lang);
    fprintf(config, "%d\n", Profile1.mode);
    fprintf(config, "%s\n", Profile1.prompt);
    fclose(config);


}


int rconfigp()//fonction qui configure le prompt et qui verifie que la configuration a était faite
{
     FILE *config=NULL;



	Profile Profile1;
    //on lit le fichier
	config= fopen("config.cfg", "r");

    fscanf(config, "%d\n", &Profile1.lang);
    fscanf(config, "%d\n", &Profile1.mode);
    fscanf(config, "%s\n", Profile1.prompt);
    fclose(config);



    //on verifier que le mode et la langue sont bien configuré
   if ((Profile1.lang==1||Profile1.lang==2||Profile1.lang==3)||(Profile1.mode==1||Profile1.mode==2||Profile1.mode==3))
      {
         if (Profile1.mode==2)
          { return 1;}
          else
          {
         printf("Shell2.0@%s>",Profile1.prompt);//si oui on printf notre shell et on return 1
       return 1;
       }
      }
    else
     {
      return 0; //sinon return 0 pour appeler la fonction de configuration
     }


}







