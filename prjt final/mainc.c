#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carh.h"

void afficherMenu_editeur() {
    printf("Gestion de la location de voitures:\n");
    printf("1. Ajouter une voiture\n");
    printf("2. Modifier une voiture\n");
    printf("3. Supprimer une voiture\n");
    printf("4. Quitter\n");
}

void afficherMenu_utilisateur() {
    printf("1. Afficher toutes les voitures\n");
    printf("2. Rechercher une voiture\n");
    printf("3. Trier les voitures\n");
    printf("4. Quitter\n");
}

int main() {
    Voiture voitures[MAX_USERS];
    int nbVoitures = chargerVoitures(voitures, MAX_USERS);
    int choix, choice;
    char nom[MAX_LEN], motDePasse[MAX_LEN];
    char codeEditeur[MAX_LEN] = "editeur1234";
    char codeEntree[MAX_LEN];

    while (1) {
        printf("===== Bienvenue dans l'application de location de voitures =====\n");
        printf("1. S'inscrire\n");
        printf("2. Se connecter\n");
        printf("3. Quitter\n");
        printf("Votre choix: ");
        scanf("%d", &choix);
        getchar(); // Consommer le caractère de nouvelle ligne laissé par scanf

        if (choix == 1) {
            inscrireUtilisateur(nom, motDePasse);
        } else if (choix == 2) {
            if (utilisateurExiste(nom, motDePasse)) {
                printf("Connexion réussie !\n");

                printf("Souhaitez-vous continuer en tant qu'éditeur ou client?\n");
                printf("1. Éditeur\n");
                printf("2. Client\n");
                printf("Votre choix: ");
                int roleChoix;
                scanf("%d", &roleChoix);
                getchar(); // Consommer le caractère de nouvelle ligne laissé par scanf

                if (roleChoix == 1) {
                    printf("Entrez le code éditeur: ");
                    fgets(codeEntree, sizeof(codeEntree), stdin);

                    // Enlever le caractère de nouvelle ligne à la fin de codeEntree
                    for (int i = 0; codeEntree[i] != '\0'; i++) {
                        if (codeEntree[i] == '\n') {
                            codeEntree[i] = '\0';
                            break;
                        }
                    }

                    if (strcmp(codeEntree, codeEditeur) == 0) {
                        while (1) {
                            afficherMenu_editeur();
                            scanf("%d", &choice);
                            getchar(); // Consommer le caractère de nouvelle ligne laissé par scanf
                            switch (choice) {
                                case 1:
                                    ajouterVoiture(voitures, &nbVoitures);
                                    break;
                                case 2:
                                    modifierVoiture(voitures, nbVoitures);
                                    break;
                                case 3:
                                    supprimerVoiture(voitures, &nbVoitures);
                                    break;
                                case 4:
                                    printf("Au revoir!\n");
                                    sauvegarderVoitures(voitures, nbVoitures);
                                    exit(0); // Quitter le programme
                                default:
                                    printf("Option non valide. Veuillez réessayer.\n");
                            }
                        }
                    } else {
                        printf("Code éditeur incorrect.\n");
                    }
                } else if (roleChoix == 2) {
                    while (1) {
                        afficherMenu_utilisateur();
                        scanf("%d", &choice);
                        getchar(); // Consommer le caractère de nouvelle ligne laissé par scanf
                        switch (choice) {
                            case 1:
                                afficherVoitures(voitures, nbVoitures);
                                break;
                            case 2:
                                rechercherVoiture(voitures, nbVoitures);
                                break;
                            case 3:
                                trierVoitures(voitures, nbVoitures);
                                break;
                            case 4:
                                printf("Au revoir!\n");
                                exit(0); // Quitter le programme
                            default:
                                printf("Option non valide. Veuillez réessayer.\n");
                        }
                    }
                } else {
                    printf("Option non valide. Veuillez réessayer.\n");
                }
            } else {
                printf("Nom d'utilisateur ou mot de passe incorrect.\n");
            }
        } else if (choix == 3) {
            printf("Au revoir!\n");
            sauvegarderVoitures(voitures, nbVoitures);
            break; // Quitter la boucle et terminer le programme
        } else {
            printf("Option non valide. Veuillez réessayer.\n");
        }
    }

    return 0;
}