#include "fonctions.h"
#include <stdio.h>
#include <stdlib.h>
/*On réserve une zone mémoire pour les grilles. On a fait deux grilles
    pour effectuer le mise à jour l'état des cases de la grille_1 sur la grille_2 */

char **init_grille(  unsigned int taille){
    char **grille;
    grille = calloc( taille , sizeof(*grille) );
    for( int i=0 ; i<taille ; i++){
        grille[i] = calloc( taille , sizeof(char) );
    }
    return grille;
}

/*On demande  à l'utilisateur combien des cases vivantes (active) au depart.
Ici si il a entrer  une valeur plus grand que la taille maximal de la grille;
on demande  de rentrer une autre valeur.*/
void init_manuel(char **grille_1, unsigned int taille){
    unsigned int nb_cases_activés;
    printf("Combien des cases voulez-vous activés au départ ? ");
    scanf( "%d" , &nb_cases_activés );

    while ( nb_cases_activés > ( taille * taille )){
        printf("La valeur qui vouz avez entré est plus grand que la taille de la grill; s'il vous plait entrez une autre : ");
        scanf( "%d" , &nb_cases_activés );
    }
    /*On demande de l'utilisateur d'entrer les coordonnées des case qui vont etre coloré (activé).
    Ici si il a entré des coordonnéesde hors de la grille;
    on demande  de rentrer une autre valeur . */
    for ( int i=0 ; i < nb_cases_activés ; i++ ){
        unsigned int x , y ;
        printf("Entrez les coordonnées de la case de la form x y : ");
        scanf( "%d %d" , &x , &y );
        while (( x >= taille ) || ( y >= taille )) {
            printf("Les coordonnées qui vous avez entré sont hors de la grill; s'il vous plait entrez une autre : ");
            scanf( "%d %d" , &x , &y);
        }
        grille_1[x][y] = 1;
    }
}


//fonctionne lire une grille a partir d'un fichier
char** LireGrille(char* nomfichier, unsigned int* taille , unsigned int* nb_repet){
    char** grille_1;
	FILE* source;
	source = fopen(nomfichier , "r");
	if (source == NULL ){
		perror(nomfichier);
		exit(1);
	}
    
	char buffer[1024];
	while (fgets(buffer , 1024 , source) != NULL){
        
		if(buffer[0] == 't'){
			if ( sscanf( buffer,"taille=%d",taille) == 1){
				grille_1 = init_grille(*taille);
			}
		}
        
        else if(buffer[0] =='r'){
            
            sscanf( buffer,"repet=%d",nb_repet) ;
        }
		else{
			//lire des coordonnées des case
			unsigned int x,y;
			if ( sscanf(buffer , "%d %d",&x,&y) ==2) {
                grille_1[x][y] = 1;
			}
		}
	}
	fclose(source);
    return grille_1;
}

/*La fonction voisines permet de voir l'état des cases par apport aux cases voisine :
si la case est vivante et elle a plus de 2 ou 3 voisines elle reste vivante si
elle a plus que troix ou une seul le case va disparaitre , si une case est vide(n'est pas vivante)
et elle a 2 ou 3 voisine dans ce cas la case sera vivante*/
char voisines( char **grille_1 ,char **grille_2, int ligne , int colonne , unsigned int taille){
    int i , j , nb = 0 ;
    for ( i = ligne - 1 ; i <= ligne + 1 ; i++ ){
        if ( i >= 0 && i < taille ){
            for ( j = colonne - 1 ; j <= colonne + 1 ; j++ ){
                if ( j >= 0 && j < taille ){
                    if ( i != ligne || j != colonne ){
                        if ( grille_1[i][j] == 1 ){
                            nb++;
                        }
                    }
                }
            }
        }
    }
    if ( grille_1[ligne][colonne]== 1 ){
        if ( nb == 2 || nb == 3 )
            { grille_2[ligne][colonne] =1;}
        else 
            { grille_2[ligne][colonne] =0;}
    }
    else {
        if ( nb == 3 ) 
            { grille_2[ligne][colonne] =1;}
        else 
            { grille_2[ligne][colonne] =0; }

        
    }
}

/*La fonction mise_jour permet de parcourir par la grille_1 et mise à jour l'état de ces case*/
void mise_jour(char **grille_1 , char **grille_2 , unsigned int taille){
    for ( int i=0 ; i < taille ; i++){
        for ( int j=0 ; j < taille ; j++){
            voisines( grille_1 , grille_2 , i , j , taille );
        }
    }
    
}



