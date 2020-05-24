#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "Fonctions.h"


void tabarg(char *args[], int MAXARGS, char * ligne);//Fonction creation tableau de pointeurs vers arguments
int nettoie(char * ligne);//fonction qui nettoie la chaine de caractéres rentrés
void fonclog();//fonction qui crée et remplie le journal log
void del_char(char* str, char c);//fonctions pour supprimer un caractére
int rconfigm();//fonction qui renvoie les données de configuration de mode
int rconfigl();//fonction qui renvoie les données de configuration de langue
void modeLang();//fonctions du mode langage naturel
void Modemenu();

char ligne[256];//tableau de caractéres qui contient la ligne tapée
int main()
{


    char *args[64];//tableau de pointeurs vers les arguments


switch (rconfigl()) //Acceuil de bienvenue en fonction de la langue choisie
{
case 1:{printf("\t\t\tBienvenue dans le Shell 2.0\n\n\n");}break;
case 2:{printf("\t\t\tWelcome to the Shell 2.0\n\n\n");}break;
case 3:{printf("\t\t\tBienvenido a la Shell 2.0\n\n\n");}break;
}



switch (rconfigl())
{
 case 1:
 {
  switch (rconfigm())
    {
   case 1:{printf("Vous etes en mode Expert\n\n");}break;
   case 2:{printf("Vous etes en mode Menu\n\n");}break;
   case 3:{printf("Vous etes en mode Langage Naturel\n\n");}break;

  }
 }break;
 case 2:
 {
 switch (rconfigm())
 {
  case 1:{printf("You are in Expert Mode\n\n");}break;
  case 2:{printf("You are in step by step Mode\n\n");}break;
  case 3:{printf("You are in fluent langage Mode\n\n");}break;

 }
 }break;
 case 3:
 {
 switch (rconfigm())
 {
  case 1:{printf("Usted esta en el modo experto\n\n");}break;
  case 2:{printf("Usted esta en modo de menu\n\n");}break;
  case 3:{printf("Usted esta en el modo de lenguaje natural\n\n");}break;
 }
 }break;
  default:{
   printf("Nous vous invitons a configurer votre shell \n");
   printf("We invite you to configure your shell \n");
   printf("Te invitamos a configurar su cascara \n\n");
   }break;
}





//Code du Shell
while(1)
{
// le programme verifie que la fonction de lecture du prompt ne renvoie pas 0
if (rconfigp()==0)
   {
    wconfig(); //si elle renvoie 0,on fait appele a la fonction qui permet de configurer notre shell
    }


    switch (rconfigm())//le return de rconfigm nous dit dans quel fonction nous nous trouvons
    {
    case 1:
    {
     fgets(ligne,sizeof(ligne),stdin);
    }break;
    case 2:
    {
    Modemenu();


     }break;
     case 3:
    {
     modeLang();
    }break;
    }



    nettoie(ligne); //on retire les espaces en plus dans notre chaine de caractéres

    tabarg(args,sizeof(args),ligne); // on tokenize notre commande et ses paramétres

   if(strstr(ligne,"config")) //si l'utilisateur tape config dans le shell il aura a nouveau accés à la fonction de configuration
   {
     wconfig();
   }




    fonclog(); //on fait appel à la fonction qui crée notre journal


    int pid; //declare variable pid

    switch (pid = fork()) //on crée notre fils
    {
    case -1: //si ca création echoue PID = -1
    {
     printf("erreur\n");
     }
     case 0: //notre fils est crée et il renvoie 0 (PID du pére)
     {

     execvp(args[0],args); //on execute notre commande et ses paramétres dans le fils
     }
     default:
     {

     waitpid( pid, 0, WUNTRACED ); //le processus pére attend que le fils se termine
     }
     }

     if (rconfigm()==2)
     {
      getchar();
     }
}

return 0;

}



void tabarg(char *args[], int nbArg, char * ligne) //fonction de découpage de la commande et des paramétres en token
{
  static char espace[] = " \t";
  int i = 0;
  args[i++] = strtok(ligne, espace);//strtok va crée un tableau de pointeurs qui pointe chacun vers une chaine de caractéres(qui sont notre commande et les paramétres)
  while ((args[i++] = strtok(0, espace)))
    if (i > nbArg) {
      fprintf(stderr, "plus de %d arguments, le reste n'est pas pris en compte\n", nbArg);
      return;
    }
}




int nettoie(char * ligne)//la fonction parcours notre chaine de la fin vers le début et continue tant qu'il y'a des espaces grace a isspace
 {
  int lg = strlen(ligne);
  while (isspace(ligne[lg -1]))
    lg--;
  ligne[lg] = '\0'; //lorsque elle arrive a un caractére qui n'est pas un espace,elle remplace le caractéres d'aprés par un \0 (qui represente la fin de la chaine)
  return(lg);
}


void fonclog() //la fonction crée un fichier sur lequel elle va ecrire notre variable ligne (commande+paramétres) et la date de saisie de cette ligne
{
   FILE *log=NULL;

     time_t temps;
     struct tm date;
     time(&temps);
    date=*localtime(&temps);

   log = fopen("journal.txt", "a+");
   fprintf(log,"Action:%s Date: %s\n",ligne,asctime(&date));
   fclose(log);
}


void modeLang()//fonction Mode Naturel (Feriel Ouzaghla)
{


	char motsc[20][20];
    char tampon[32];

    FILE *dict=NULL;
    int i=0;

   fgets(ligne,sizeof(ligne),stdin);

    switch (rconfigl())
    {
    case 1:
    {
         dict=fopen("dicoFR.txt","r");

         for (i=0;i<sizeof(motsc);i++)
        {
        fgets(motsc[i] ,sizeof(motsc),dict); //lit tout les mots situés sur toutes les lignes et les charge dans un tableau de chaines de caractéres
        del_char(motsc[i],'\n');


        }

        if((strstr(ligne,motsc[0]))&&(strstr(ligne,motsc[1])))//afficher repertoire voulu
        {
         sprintf(ligne,"ls --color=auto");
        }
        else if((strstr(ligne,motsc[0]))&&(strstr(ligne,motsc[2])))//afficher processus en cours
        {
         sprintf(ligne,"ps");
        }
         else if((strstr(ligne,motsc[0]))&&(strstr(ligne,motsc[3])))//afficher  chemin (le path)
        {
         sprintf(ligne,"pwd");
        }
        else if(strstr(ligne,motsc[4]))//affiche l'utilisateur
        {
         sprintf(ligne,"whoami");
        }
        else if((strstr(ligne,motsc[5]))&&(strstr(ligne,motsc[1])))//creation d'un repertoire
        {

         printf("Nom du repertoire:");
         scanf("%s",tampon);
         sprintf(ligne,"mkdir %s",tampon);
        }
        else if((strstr(ligne,motsc[5]))&&(strstr(ligne,motsc[7])))//creation d'un fichier
        {

         printf("Nom du fichier:");
         scanf("%s",tampon);
         sprintf(ligne,"touch %s",tampon);
        }
        else if((strstr(ligne,motsc[8]))&&(strstr(ligne,motsc[1])))//supprimer repertoire voulu
        {

         printf("Nom du repertoire:");
         scanf("%s",tampon);
         sprintf(ligne,"rmdir %s",tampon);
        }
        else if((strstr(ligne,motsc[8]))&&(strstr(ligne,motsc[7])))//supprimer un fichier
        {

         printf("Nom du fichier:");
         scanf("%s",tampon);
         sprintf(ligne,"rm %s",tampon);
        }
          else if((strstr(ligne,motsc[9]))&&(strstr(ligne,motsc[7])))//editer un  fichier
        {

         printf("Nom du fichier:");
         scanf("%s",tampon);
         sprintf(ligne,"nano %s",tampon);
        }
          else if((strstr(ligne,motsc[10]))&&(strstr(ligne,motsc[11])))//ejecter le disque (ouverture du lecteur)
        {
         sprintf(ligne,"eject");
        }
         else if(strstr(ligne,motsc[6]))//jeu tour Hanoi
    {
     sprintf(ligne,"./TourH");
    }
	}
	break;

    case 2:
    {
        dict=fopen("dicoEN.txt","r");//ouverture et lecture du dictionaire anglais
        for (i=0;i<sizeof(motsc);i++)
        {
        fgets(motsc[i] ,sizeof(motsc),dict);
        del_char(motsc[i],'\n');


        }
            if((strstr(ligne,motsc[0]))&&(strstr(ligne,motsc[1])))//afficher repertoire
        {
         sprintf(ligne,"ls --color=auto");
        }
        else if((strstr(ligne,motsc[0]))&&(strstr(ligne,motsc[2])))//afficher les processus en cours

        {
         sprintf(ligne,"ps");
        }
         else if((strstr(ligne,motsc[0]))&&(strstr(ligne,motsc[3])))//afficher le chemin (path)
        {
         sprintf(ligne,"pwd");
        }
        else if(strstr(ligne,motsc[4]))//affiche l'utilisateur
         {
         sprintf(ligne,"whoami");
        }
        else if((strstr(ligne,motsc[5]))&&(strstr(ligne,motsc[1])))//creation d'un repertoire
        {

         printf("Name of the directory:");
         scanf("%s",tampon);
         sprintf(ligne,"mkdir %s",tampon);
        }
        else if((strstr(ligne,motsc[5]))&&(strstr(ligne,motsc[7])))//creation d'un fichuer
        {

         printf("Name of the file:");
         scanf("%s",tampon);
         sprintf(ligne,"touch %s",tampon);
        }
        else if((strstr(ligne,motsc[8]))&&(strstr(ligne,motsc[1])))//supprimer le repertoire
        {

         printf("Name of the directory:");
         scanf("%s",tampon);
         sprintf(ligne,"rmdir %s",tampon);
        }
        else if((strstr(ligne,motsc[8]))&&(strstr(ligne,motsc[7])))//supprimer un fichier
        {

         printf("Name of the file:");
         scanf("%s",tampon);
         sprintf(ligne,"rm %s",tampon);
        }
          else if((strstr(ligne,motsc[9]))&&(strstr(ligne,motsc[7])))//editer un fichier
        {

         printf("Name of the file:");
         scanf("%s",tampon);
         sprintf(ligne,"nano %s",tampon);
        }
          else if((strstr(ligne,motsc[10]))&&(strstr(ligne,motsc[11])))//ejecter disque ( ouvrir lecteur)
        {
         sprintf(ligne,"eject");
        }
         else if(strstr(ligne,motsc[6]))//jeu tour Hanoi
    {
     sprintf(ligne,"./TourH");
    }

	}break;
	 case 3:
    {
        dict=fopen("dicoES.txt","r");//ouverture et lecture du dictionaire Espagnol
        for (i=0;i<sizeof(motsc);i++)
        {
        fgets(motsc[i] ,sizeof(motsc),dict);
        del_char(motsc[i],'\n');
        }




            if((strstr(ligne,motsc[0]))&&(strstr(ligne,motsc[1])))//afficher un repertoire
        {
         sprintf(ligne,"ls --color=auto");
        }
        else if((strstr(ligne,motsc[0]))&&(strstr(ligne,motsc[2])))//afficher  processus en cours
        {
         sprintf(ligne,"ps");
        }
         else if((strstr(ligne,motsc[0]))&&(strstr(ligne,motsc[3])))//afficher  chemin (path)
        {
         sprintf(ligne,"pwd");
        }
        else if(strstr(ligne,motsc[4]))//afficher utilisateur
        {
         sprintf(ligne,"whoami");
        }
        else if((strstr(ligne,motsc[5]))&&(strstr(ligne,motsc[1])))//creer un repertoire
        {

         printf("Nombre de directorio:");
         scanf("%s",tampon);
         sprintf(ligne,"mkdir %s",tampon);
        }
        else if((strstr(ligne,motsc[5]))&&(strstr(ligne,motsc[7])))//creer un fichier
        {

         printf("Nombre de expediente:");
         scanf("%s",tampon);
         sprintf(ligne,"touch %s",tampon);
        }
        else if((strstr(ligne,motsc[8]))&&(strstr(ligne,motsc[1])))//supprimer le repertoire
        {

         printf("Nombre de directorio:");
         scanf("%s",tampon);
         sprintf(ligne,"rmdir %s",tampon);
        }
        else if((strstr(ligne,motsc[8]))&&(strstr(ligne,motsc[7])))//supprimer le fichier souhaité
        {

         printf("Nombre de expediente:");
         scanf("%s",tampon);
         sprintf(ligne,"rm %s",tampon);
        }
          else if((strstr(ligne,motsc[9]))&&(strstr(ligne,motsc[7])))//editer un fichier
        {

         printf("Nombre de expediente:");
         scanf("%s",tampon);
         sprintf(ligne,"nano %s",tampon);
        }
          else if((strstr(ligne,motsc[10]))&&(strstr(ligne,motsc[11])))//ejecter disque (ouvrir lecteur)
        {
         sprintf(ligne,"eject");
        }
         else if(strstr(ligne,motsc[6]))//jeu tour Hanoi
    {
     sprintf(ligne,"./TourH");
    }
	}break;
    }












}




void del_char(char* str, char c) //Fonction pour retirer un caractére choisie d'une chaine de caractéres
{
   int id_read, id_write;
   id_read = 0;
   id_write = 0;

   while (str[id_read] != '\0') //detecte fin de chaine de caractère
   {
      if (str[id_read] != c)
      {
          str[id_write] = str[id_read];
          id_write++;
      }
      id_read++;
    }

        str[id_write] = '\0';

}

int rconfigm()//fonction qui configure le mode
{
     FILE *config=NULL;
     int Mode=0;



	Profile Profile1;

	//on lit le fichier
	config= fopen("config.cfg", "r+");

    fscanf(config, "%d\n", &Profile1.lang);
    fscanf(config, "%d\n", &Profile1.mode);
    fscanf(config, "%s\n", Profile1.prompt);
    fclose(config);



    //et on regarde dans quel mode nous nous trouvons
    if (Profile1.mode==1)//Monde Expert
    {
     Mode=1;
    }
    else if (Profile1.mode==2)//Mode pas à pas
    {
     Mode=2;
    }
    else if (Profile1.mode==3)//Mode langage naturel
    {
     Mode=3;
    }

    //on renvoie le numéro du Mode
    return Mode;


}



int rconfigl()//fonction qui configure la langue,méme fonctionement que la fonction au dessus
{
     FILE *config=NULL;
     int Langue=0;



	Profile Profile1;

	config= fopen("config.cfg", "r");

    fscanf(config, "%d\n", &Profile1.lang);
    fscanf(config, "%d\n", &Profile1.mode);
    fscanf(config, "%s\n", Profile1.prompt);
    fclose(config);

    if (Profile1.lang==1)//Francais
    {
     Langue=1;
    }
    else if (Profile1.lang==2)//Anglais
    {
     Langue=2;
    }
    else if (Profile1.lang==3)//Espagnol
    {
     Langue=3;
    }
    return Langue;


}



void Modemenu()
{
   FILE *dictio=NULL;
   int etats=0;
   int choix=0;
   char dico[64][64];
   int i=0;
   char tampon[64];

   switch (rconfigl())
    {
    case 1:
    {
	 dictio=fopen("dico2FR.txt","r");
	}
	break;
    case 2:
    {
	 dictio=fopen("dico2EN.txt","r");
	}break;
	 case 3:
    {
	 dictio=fopen("dico2ES.txt","r");
	}break;
    }



    for (i=0;i<sizeof(dico);i++)
    {
    fgets(dico[i] ,sizeof(dico),dictio);
    }

   while (etats==0)
   {
     system("clear");
     printf("\t\t\t%s\n\n",dico[24]);
     printf("%s",dico[0]); //gestion des processus
     printf("%s",dico[1]); //gestion des repertoire
     printf("%s",dico[2]); //gestion des fichiers
     printf("%s",dico[3]); //gestion des periphériques
     printf("%s",dico[4]); //gestion du shell
     printf("%s",dico[20]);
     scanf("%d",&choix);
    if (choix==1){etats=1;} //gestion des processus
    else if (choix==2){etats=2;} //gestion des repertoire
    else if (choix==3){etats=3;} //gestion des fichiers
    else if (choix==4){etats=4;} //gestion des utilisateurs
    else if (choix==5){etats=5;} //gestion des periphériques



     if (etats==1)//gestion des processus
   {
     system("clear");
     printf("\t\t\t%s\n\n",dico[24]);
     printf("%s",dico[5]); //afficher processus
     printf("%s",dico[6]); //afficher processus detaillé
     printf("%s",dico[7]); //tuer processus
     printf("%s",dico[8]); //retour
     printf("%s",dico[20]);
     scanf("%d",&choix);
    if (choix==1){sprintf(ligne,"ps");} //afficher processus
    else if (choix==2){sprintf(ligne,"ps -al");} //afficher processus detaillé
    else if (choix==3){etats=6;} //tuer processus
    else if (choix==0){etats=0;} //retour

    }

       if (etats==2)//gestion des repertoire
   {
     system("clear");
     printf("\t\t\t%s\n\n",dico[24]);
     printf("%s",dico[9]); //afficher repertoire
     printf("%s",dico[10]); //afficher repertoire detaillé
     printf("%s",dico[11]); //effacer repertoire
     printf("%s",dico[12]); //montrer le chemin courant
     printf("%s",dico[8]); //retour
     printf("%s",dico[20]);
     scanf("%d",&choix);
    if (choix==1){sprintf(ligne,"ls --color=auto");} //afficher repertoire
    else if (choix==2){sprintf(ligne,"ls -l --color=auto");} //afficher repertoire detaillé
    else if (choix==3){etats=7;} //effacer repertoire
    else if (choix==4){sprintf(ligne,"pwd");} //montrer le chemin courant
    else if (choix==0){etats=0;} //retour

    }

          if (etats==3)//gestion des fichiers
   {
     system("clear");
     printf("\t\t\t%s\n\n",dico[24]);
     printf("%s",dico[13]); //creer fichier
     printf("%s",dico[14]); //effacer fichier
     printf("%s",dico[15]); //ouvrir fichier
     printf("%s",dico[16]); //editer fichier
     printf("%s",dico[8]); //retour
     printf("%s",dico[20]);
     scanf("%d",&choix);
    if (choix==1){etats=8;} //creer fichier
    else if (choix==2){etats=9;} //effacer fichier
    else if (choix==3){etats=10;} //ouvrir fichier
    else if (choix==4){etats=11;} //editer fichier
    else if (choix==0){etats=0;} //retour

    }


           if (etats==4)//gestion des periphériques
   {
     system("clear");
     printf("\t\t\t%s\n\n",dico[24]);
     printf("%s",dico[17]); //ejecter le disque
     printf("%s",dico[8]); //retour
     printf("%s",dico[20]);
     scanf("%d",&choix);
    if (choix==1)sprintf(ligne,"eject");} //ejecter le disque
    else if (choix==0){etats=0;} //retour

    }



              if (etats==5)//gestion du shell
   {
     system("clear");
     printf("\t\t\t%s\n\n",dico[24]);
     printf("%s",dico[18]); //configurer le shell
     printf("%s",dico[19]); //the cake is a lie
     printf("%s",dico[8]); //retour
     printf("%s",dico[20]);
     scanf("%d",&choix);
    if (choix==1){sprintf(ligne,"config");} //configurer le shell
    if (choix==2){sprintf(ligne,"./TourH");} //the cake is a lie
    else if (choix==0){etats=0;} //retour

    }

    if (etats==6)//tuer processus
    {
      printf("%s",dico[21]); //nom du processus
      printf("%s",dico[20]);
      scanf("%s",tampon);
      sprintf(ligne,"kill %s",tampon);


    }


    if (etats==7)//tuer processus
    {
      printf("%s",dico[22]); //nom du repertoire
      printf("%s",dico[20]);
      scanf("%s",tampon);
      sprintf(ligne,"mkdir %s",tampon);


    }

     if (etats==8)//creer fichier
    {
      printf("%s",dico[23]); //nom du fichier
      printf("%s",dico[20]);
      scanf("%s",tampon);
      sprintf(ligne,"touch %s",tampon);


    }

     if (etats==9)//effacer fichier
    {
      printf("%s",dico[23]); //nom du fichier
      printf("%s",dico[20]);
      scanf("%s",tampon);
      sprintf(ligne,"rm %s",tampon);


    }

     if (etats==10)//ouvrir fichier
    {
      printf("%s",dico[23]); //nom du fichier
      printf("%s",dico[20]);
      scanf("%s",tampon);
      sprintf(ligne,"cat %s",tampon);


    }


    if (etats==11)//editer fichier
    {
      printf("%s",dico[23]); //nom du fichier
      printf("%s",dico[20]);
      scanf("%s",tampon);
      sprintf(ligne,"nano %s",tampon);


    }

    getchar();

   }


