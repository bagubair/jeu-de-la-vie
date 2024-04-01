#ifndef FONCTIONS
#define FONCTIONS

char **init_grille( unsigned int taille);
void init_manuel(char **grille_1, unsigned int taille);
char **LireGrille(char* nomfichier,  unsigned int* taille , unsigned int* nb_repet);


char voisines( char **grille_1 , char **grille_2 , int ligne , int colonne , unsigned int taille);
void mise_jour(char **grille_1 , char **grille_2 , unsigned int taille);

#endif