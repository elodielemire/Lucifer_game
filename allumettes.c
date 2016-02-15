/* <<<<<<<<<<<<<<<<<<<<<<< JEU   DES   ALLUMETTES >>>>>>>>>>>>>>>>>>>> */

#include <stdio.h>
#include <stdlib.h>
#include "esdl/esdl.h"


typedef struct UserData UserData;

struct UserData {
    EsdlImage* image;
    int numberOfClicks;
    int numberOfSprite;
};

void initUserData();
void spaceCallback(EsdlEvent* event);
void clickCallback(EsdlEvent* event);
void deleteUserData();

// Fonction principale
#define SIZE 13
int main(int argc, char* argv[]) {

    EsdlSprite * sprites[SIZE];
    int i;
    int size = SIZE;
       
    EsdlImage* image;

    // Création de la fenêtre
    esdlCreateWindow("Projet_Jeu", 1300, 600);


    // Chargement de la ressource image
    image = esdlLoadImage("allumette.jpg");
    if (image == NULL) {
        printf("Unable to loadlkjhg resources...\n");
        exit(1);
    }
        
    printf("voici le jeu des allumettes : selectionnez 1, 2 ou 3 allumettes \n et appuyez sur espace pour changer de joueur \n celui qui a perdu est celui qui prend la derniere allumette \n");
    
    // Création des sprites qui utilisent la ressource image
    for (i = 0; i < size; i++) {
        sprites[i] = esdlLoadSpriteFromImage(image);
    }


    // Positionnement des sprites
    for (i = 0; i < size; i++) {
        esdlSetSpritePosition(sprites[i], 100 * i, 100);
    }


    // deplacement des sprites si clickCallback   
    for (i = 0; i < size; i++) {
        esdlAddListenerOnFocus(sprites[i], clickCallback);
    }
    esdlAddListenerOnKeyUp(esdlGetScreen(), spaceCallback);

    // Appel de la structure de données
    struct UserData myData;
    
    // Sauvegarde des données utilisateurs
    esdlSetUserData(&myData); // sert à aller stocker facilement myData

 
    // initialise les données
    initUserData();

    // Boucle d'évènement
    esdlEventLoop(NULL);


    // Libération de la mémoire
    for (i = 0; i < size; i++) {
        esdlDeleteSprite(sprites[i]);
    }
    esdlDeleteImage(image);


    deleteUserData();

    // Fermeture du programme
    esdlCloseWindow();

    return 0;

}

// Initialise les données utilisateurs

void initUserData() {
    // Récupération des données utilisateurs
    UserData* myData = (UserData*) esdlGetUserData();

    // Initialisation des données utilisateurs
    myData->numberOfClicks = 0;
    myData->numberOfSprite = SIZE;
    
    //if (myData->image == NULL) {
       // printf("Unable to loadeeeeeee resources...\n");
        //exit(1);
   // }
}

//// Callback exécuté lorsque l'on clique sur une allumette

void clickCallback(EsdlEvent* event) {

    struct UserData * data = (UserData*) esdlGetUserData();
    EsdlSprite* sprite = esdlGetSpriteEvent(event);
    EsdlImage* image;
    
    if (sprite->y != 300) { // si on n'a pas encore appuyé sur l'allumette        
        data->numberOfClicks = data->numberOfClicks + 1;
        esdlSetSpritePosition(sprite, sprite->x, sprite->y + 200); // alors on la déplace UNE fois car la seconde fois, sprite.y=300 donc on ne la déplace plus

        switch (data->numberOfClicks) {
            case 1:
            case 2:

                printf("Vous avez pris %d allumettes !\n", data->numberOfClicks);
                data->numberOfSprite = data->numberOfSprite - 1;

                break;
        }

        if (data->numberOfClicks == 3) {
            printf("vous avez pris 3 allumettes ! \n joueur suivant \n");
            data->numberOfClicks = 0;
            data->numberOfSprite = data->numberOfSprite - 1;
        }

        if (data->numberOfSprite == 0) { // si toutes les allumettes ont ete prises <=> fin du jeu
            printf("perdu ! \n");    
            image = esdlLoadImage("lose.jpg");
           esdlLoadSpriteFromImage(image);

        
         }
    }

}

// callback executé lorsqu'on appuie sur la touche espace

void spaceCallback(EsdlEvent* event) {
    struct UserData * data = (UserData*) esdlGetUserData();
    if (esdlGetKey(event) == KEY_SPACE) {
        data->numberOfClicks = 0;
        printf("joueur suivant \n");
    }
}

// Libère la mémoire

void deleteUserData() {
    // Récupération des données utilisateurs
    UserData* mesDonnees = (UserData*) esdlGetUserData();

    // Libération de la mémoire
    esdlDeleteSprite(mesDonnees->image);
}
