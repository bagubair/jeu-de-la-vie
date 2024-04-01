/*Le projet de I31 qui est sur "LE JEU DE LA VIE".
le projet réalisé par : BOUNOUAR Lina et BA GUBAIR Emad.*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "fonctions.h"


int main(){
    
    /*On a déclaré trois variable (taille) pour la taille de la grille,
    (nb_cases_activés) pour le nombres des cases que l'utilisateur va entrer
    et (nb_répétition_jeu) pour nombre de fois que le jeu se répète.*/
    unsigned int taille , nb_cases_activés , nb_répétition_jeu , test;
    char **grille_1 ;
    char **grille_2;
    

    printf("Bienvenue dans le Jeu de la Vie. Vous voulez tester les exemples prêts ou jouer à la main ?\nPour jouer avec les exemples, tapez (1); sinon, tapez (2)\n");
    scanf( "%d" , &test );
    if (test == 1) {
        int i;
        printf("choisiez un example entre 1 et 5 \n");
        scanf("%d", &i);
        char nomfichier[20];
        sprintf(nomfichier, "../data/test_%d.dat", i);
        
        grille_1 = LireGrille(nomfichier, &taille, &nb_répétition_jeu);
        grille_2 = init_grille(taille);
    }
    else if(test == 2){

        /*On demande de l'utilisateur d'entrer la taille de la grille*/
        printf("Entrez une valeur pour la taille de la grille : ");
        scanf( "%d" , &taille );

        /*On réserve une zone mémoire pour les grilles. On a fait deux grilles
        pour effectuer le mise à jour l'état des cases de la grille_1 sur la grille_2 */
        grille_1 = init_grille(taille);
        grille_2 = init_grille(taille);
    
        init_manuel(grille_1,taille);

        /*On demande à l'utilisateur d'entrer combien de fois il veut répéter le jeu.*/
        printf("Combien des fois voulez-vous répéter le jeu ? ");
        scanf( "%d" , &nb_répétition_jeu );
    }
    //Les dimensions de la fenetre (zone d'affichage) en pixels
    unsigned int frame_width  = 800; // Largeur
    unsigned int frame_height = 800; // Hauteur

    /*La largeur d'une colonne et la hauteur d'une ligne en pixel
    ces tailles son fonction des dimensions de la fenetre et du
    nombre de colonnes et de lignes*/
    unsigned int colonnes_width = 0;
    unsigned int linges_height   = 0;

    //Calcul des largeur de colonnes et hauteur de lignes en pixe
    colonnes_width = frame_width / taille;
    linges_height = frame_height / taille;

    printf("Taille de la grille ( lignes x colonnes )        : %d x %d\n", taille, taille);
    printf("Taille d'une cellule ( largeur x hauteur )       : %dpx x %dpx\n", colonnes_width, linges_height);

    printf("\nLancement de l'interface graphique\n");
    SDL_Window *fenetre;
    SDL_Renderer *renderer;// Déclaration du renderer

    // Initialisation de la SDL
    if(SDL_VideoInit(NULL) < 0){
        printf("Erreur d'initialisation de la SDL : %s",SDL_GetError());
        return EXIT_FAILURE;
    }
    // Création de la fenêtre
    // la fonction de creation renvoie NULL si la fenetre n'a pas pu etre cree
    fenetre = SDL_CreateWindow("Jeu de la vie" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , frame_width , frame_height , 0);

    // Si la fenetre n'a pas pu etre cree, le programme ne peut continuer
    if(fenetre == NULL) {
        printf("Erreur lors de la creation d'une fenetre : %s",SDL_GetError());
        return EXIT_FAILURE;
    }
    // Création du renderer
    // Le renderer est l'objet qui permet de dessiner dans la fenetre.
    // la fonction de creation du renderer renvoie NULL si le renderer n'a pu etre cree
    renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); // Création du renderer
    
    // Si le renderer n'a pu etre creer, le programme ne peut pas continuer
    if(renderer == NULL) {
        printf("Erreur lors de la creation d'un renderer : %s",SDL_GetError());
        return EXIT_FAILURE;
    }
    // Initialisation du contenu de la fenetre en demandant au renderer de s'effacer avec la couleur noire
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    // Dessin d'une grille au bonnes dimensions

    // La structure qui permet de representer un rectangle
    // Cette structure contient les champs suivants:
    // x: abcisse du coin supérieur gauche du rectangle
    // y: ordonnee du coin superieur droit du rectangle
    // w: largeur du rectangle (taille selon l'axe x)
    // h: hauteur du rectangle (taille selon l'axe y)
    SDL_Rect cell;
    /*la boucle d'affichage */
    //printf("ezezezeze\n");
    
    for ( int i=0 ; i < nb_répétition_jeu ; i++ ){
        // Choix de la couleur utilisee pour le tracage
        SDL_SetRenderDrawColor(renderer,14,75,239,0);
        for(unsigned int colonne = 0; colonne < taille; colonne++){
            for(unsigned int ligne = 0; ligne < taille; ligne++){
            // Initialisation du rectangle a la bonne position
                //printf("eezzzzzzeze %d \n", nb_répétition_jeu);
                if( grille_1[ligne][colonne] == 1){
                    cell.x = colonne * colonnes_width;
                    cell.y = ligne * linges_height;
                    cell.w = colonnes_width;
                    cell.h = linges_height;

                    // Dessin du rectangle sur le renderer
                    SDL_RenderFillRect(renderer, &cell);
                }
                //le temps d'attente entre chaque affichage.
                SDL_Delay(.000001);
            }
        }
        // Demande au renderer de se rafraichir
        SDL_RenderPresent(renderer);
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        
        mise_jour(grille_1 ,grille_2 ,taille);

        char **g = grille_1;
        grille_1 = grille_2;
        grille_2 = g;
        
    }
    SDL_Delay(1000); // Pause de 2 secondes, pour admirer notre œuvre autant que l'on ve
    // Destruction du renderer et de la fenêtre :
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    SDL_Quit(); // On quitte la SDL

    free(grille_1);
    free(grille_2);

return 0;
}