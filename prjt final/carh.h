#ifndef CAR_H
#define CAR_H

#define MAX_USERS 100
#define MAX_LEN 50

typedef struct {
    int id;
    char marque[MAX_LEN];
    char modele[MAX_LEN];
    char typeCarburant[MAX_LEN];
    int places;
    char transmission[MAX_LEN];
    float prixParJour;
    int disponible;
} Voiture;

// Déclarations des fonctions
void inscrireUtilisateur(char* nom, char* motDePasse);
int utilisateurExiste(char nom[50], char motDePasse[50]);
void afficherMenu_editeur();
void afficherMenu_utilisateur();
void ajouterVoiture(Voiture voitures[], int* nbVoitures);
void modifierVoiture(Voiture voitures[], int nbVoitures);
void supprimerVoiture(Voiture voitures[], int* nbVoitures);
void afficherVoitures(Voiture voitures[], int nbVoitures);
void rechercherVoiture(Voiture voitures[], int nbVoitures);
void trierVoitures(Voiture voitures[], int nbVoitures);
int chargerVoitures(Voiture voitures[], int maxVoitures);
void sauvegarderVoitures(Voiture voitures[], int nbVoitures);

#endif // CAR_H