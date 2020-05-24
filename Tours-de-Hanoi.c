


#include <time.h>                                       // bibliothèque pour chronomètre
#include <stdlib.h>
#include <string.h>




char    plateau[3][3];                                  // 3 piquets de 3 disques chacun
int     Vide;                                           // Vide correspond au grand plateau + 1 qui est le "vide"
int     ColD, ColA;                                     // Colonne de départ et celle d'arrivée
int     Gagne;                                          // Variable pour savoir si gagne... 0 = non    1 = gagne
int     Nbr_Coup;
int ColD, ColA;
int Erreur_Retour;
clock_t temps;


void Vide_Piliers();
void Affiche_Piliers();
int Bouge_Disque(int ColD,int ColA);                   // fonctions déclarées
int Saisie_Valeur();
void Teste_Gagne();




int main()
{


    Gagne = 0;                                          // Variable pour savoir si gagne=1 sinon = 0

    int Bouge_Disque(int ColD,int ColA);

    Vide_Plateau();                                     // on va a fonction vide plateau
    Erreur_Retour = 0;
    do {
        if (Erreur_Retour == 0) {
            Affiche_Plateau();                          // on va a fonction affiche plateau
        }
        Erreur_Retour = Saisie_Valeur();                // on va a fonction saisie valeur
        if (Erreur_Retour == 0) {
            Erreur_Retour = Bouge_Disque(ColD,ColA);

        }
        Teste_Gagne();
    } while (Gagne == 0);
    Affiche_Plateau();
    printf("\t\t+=======+\n");
    printf("\t\t! GAGNE !\n");                          // on a gagné
    printf("\t\t+=======+\n");
    temps=clock();
            printf("Bravo !\nVous avez mis %f secondes pour gagner en %d coups\n", (double) temps/CLOCKS_PER_SEC,Nbr_Coup);
	//printf("\nVous avez gagne en %d coups (le minimum etant de 7)\n\n",Nbr_Coup);

    system("Pause");


    return 0;
}


void Vide_Plateau()
{
    int i,j;

    for(i=0;i<3;i++) {                                  // Remplir la table a vide (incrémentation pour colones et disques
        for(j=0;j<3;j++) {
            plateau[i][j] = Vide;                       //   1 = petit plateau  2 = plateau moyen  3 = plateau grand ....

        }
    }

    plateau[0][0]= 3;                                   // petit disque en haut...
    plateau[0][1]= 2;                                   // Disque moyen au milieu...
    plateau[0][2]= 1;
                                                        // grand disque en bas...
}


void Affiche_Plateau()
{
    int i,j;

    system("cls");

    printf("\t\t            TOURS DE HANOI            \n");
    printf("\n");
    printf("A vous de jouer !\n");



    printf("\n");
    for(j=2;j>-1;j--) {                                 // boucle sur les colonnes puis les lignes
        for(i=0;i<3;i++) {
            switch(plateau[i][j]) {
                case 1:                                 // 1 = petit plateau
                 
                    printf("     =!=     ");
              
                    break;
                case 2:                                 // 2 = plateau moyen
               
                    printf("    ==!==    ");
                 ;
                    break;
                case 3:                                 // 3 = plateau grand ....
                 
                    printf("   ===!===   ");
                
                    break;

                default:
                
                    printf("      !      ");
                    break;
            }
        }
        printf("\n");                                   // Saute une ligne pour l'étage du dessous
    }
    printf("  ----!----    ----!----    ----!----  ");
    printf("\n\n");
    printf("      1            2            3      ");
    printf("\n\n");                                     // Saute trois lignes en fin d'affichage

}


int Bouge_Disque(int ColD, int ColA)
{
    int Val_Retour;
    int i,j,k,l;

    Val_Retour = 0;                                     // Par défault on met à "pas d'erreur"
    i=ColD;                                             // On cherche la case de celule de depart par le haut
    if (plateau[i][2]!=Vide)
        j=2;
    else {
        if (plateau[i][1]!=Vide)
            j=1;
        else
            j=0;
    }
    k=ColA;                                             // On cherche la case de celule d'arrivee par le bas
    if (plateau[k][0]==Vide)
        l=0;
    else {
        if (plateau[k][1]==Vide)
            l=1;
        else
            l=2;
    }
    if ((plateau[i][j]>plateau[k][l-1])&&(l!=0)) {
        printf("Le disque de depart dois etre plus petit que celui d'arrivee.\n");
        Val_Retour = 1;
    }
    else {
        plateau[k][l] = plateau[i][j];                  // Transfere le disque de depart
        plateau[i][j] = Vide;                           // sur celui d'arrivée
        ++Nbr_Coup;                                     // Augmente de 1 le nombre de coup jouer
        Val_Retour = 0;
    }

    return Val_Retour;
}


int Saisie_Valeur()
{
    int Val_Retour;

    Val_Retour = 0;                                     // Par défault on met à "pas d'erreur"

    printf("Saisir la colonne de depart : ");
    ColD = getchar();;                                    // Saisie de la colonne de départ
    while (getchar() != '\n')
    printf("%c\n",ColD);                                // et affiche le carractere saisie a l'ecran

    printf("Saisir la colonne d'arrivee : ");
    ColA = getchar();                                  // Saisie de celle d'arrivée
    while (getchar() != '\n')
    printf("%c\n",ColA);                               // et affiche le carractere saisie a l'ecran

    ColD = ColD - 48 - 1;                               // 48 = "0" donc on diminue de 48 pour avoir notre colonne (48 est en ASCII et 0 son symbol)
    ColA = ColA - 48 - 1;                             // et de -1 pour correspondre au tableau

    if (ColD == ColA) {
        printf("La colonne de depart doit etre differente de celle d'arrivee.\n");
        Val_Retour = 1;                                 // erreur
    }
    if (plateau[ColD][0]==Vide) {
        printf("La colonne de depart ne doit pas etre vide.\n");
        Val_Retour = 1;
    }
    if ((ColD < 0) || (ColD > 2)) {
        printf("La colonne de depart dois etre comprise entre 1 et 3.\n");
        Val_Retour = 1;
    }
    if ((ColA < 0) || (ColA > 2)) {
        printf("La colonne d'arrivee dois etre comprise entre 1 et 3.\n");
        Val_Retour = 1;
    }

    return Val_Retour;                                  // 0 = Pas de problème    1 = probleme
}


void Teste_Gagne()
{
    Gagne = 0;                                          // par defaut on a perdu

    if ((plateau[2][0]!=Vide)&&(plateau[2][1]!=Vide)&&(plateau[2][2]!=Vide)) {
        Gagne = 1;                                      // verifie si dernier piquet est plein, alors gagne = 1
    }
}
