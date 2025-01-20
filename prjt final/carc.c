#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carh.h"

void inscrireUtilisateur(char* nom, char* motDePasse) {
    FILE *file1 = fopen("utilisateurs.csv", "w");
    if (!file1) {
        printf("Erreur lors de l'ouverture du fichier utilisateurs.csv pour écriture.\n");
        return;
    }

    printf("Entrez un nom d'utilisateur: ");
    scanf("%s", nom);
    printf("Entrez un mot de passe: ");
    scanf("%s", motDePasse);
    fprintf(file1, "%s,%s\n", nom, motDePasse);
    fclose(file1);

    printf("Inscription réussie, vous pouvez maintenant vous connecter.\n");
}

int utilisateurExiste(char nom[50], char motDePasse[50]) {
    char fileNom[50], fileMotDePasse[50];
    FILE *file = fopen("utilisateurs.csv", "r");
    if (!file) {
        printf("Erreur lors de l'ouverture du fichier utilisateurs.csv.\n");
        return 0;
    }

    printf("Entrez votre nom d'utilisateur: ");
    scanf("%49s", nom);
    printf("Entrez votre mot de passe: ");
    scanf("%49s", motDePasse);
    printf("Vérification de l'utilisateur.\n");

    char ligne[100];
    while (fgets(ligne, sizeof(ligne), file)) {
        // Remplacer le '\n' de la fin de la ligne par '\0' si présent
        for (int i = 0; ligne[i] != '\0'; i++) {
            if (ligne[i] == '\n') {
                ligne[i] = '\0';
                break;
            }
        }

        // Diviser la ligne pour obtenir le nom d'utilisateur et le mot de passe
        int j = 0;
        while (ligne[j] != ',' && ligne[j] != '\0') {
            fileNom[j] = ligne[j];
            j++;
        }
        fileNom[j] = '\0';

        int k = 0;
        j++;
        while (ligne[j] != ',' && ligne[j] != '\0') {
            fileMotDePasse[k] = ligne[j];
            j++;
            k++;
        }
        fileMotDePasse[k] = '\0';

        // Comparer avec les entrées utilisateur
        if (strcmp(nom, fileNom) == 0 && strcmp(motDePasse, fileMotDePasse) == 0) {
            fclose(file);
            return 1; // Utilisateur trouvé
        }
    }

    fclose(file);
    return 0; // Utilisateur non trouvé
}

void ajouterVoiture(Voiture voitures[], int* nbVoitures) {
    if (*nbVoitures >= MAX_USERS) {
        printf("Capacité maximale de voitures atteinte.\n");
        return;
    }

    Voiture newVoiture;
    newVoiture.id = *nbVoitures + 1;
    printf("Entrez la marque de la voiture: ");
    fgets(newVoiture.marque, MAX_LEN, stdin);

    printf("Entrez le modèle de la voiture: ");
    fgets(newVoiture.modele, MAX_LEN, stdin);

    printf("Entrez le type de carburant de la voiture: ");
    fgets(newVoiture.typeCarburant, MAX_LEN, stdin);

    printf("Entrez le nombre de places de la voiture: ");
    scanf("%d", &newVoiture.places);
    getchar(); // Consommer le caractère de nouvelle ligne laissé par scanf

    printf("Entrez la transmission de la voiture: ");
    fgets(newVoiture.transmission, MAX_LEN, stdin);

    printf("Entrez le prix par jour de la voiture: ");
    scanf("%f", &newVoiture.prixParJour);
    getchar(); // Consommer le caractère de nouvelle ligne laissé par scanf

    printf("Entrez la disponibilité de la voiture (1: disponible, 0: non disponible): ");
    scanf("%d", &newVoiture.disponible);
    getchar(); // Consommer le caractère de nouvelle ligne laissé par scanf

    voitures[*nbVoitures] = newVoiture;
    (*nbVoitures)++;
    printf("Voiture ajoutée avec succès!\n");
}

void modifierVoiture(Voiture voitures[], int nbVoitures) {
    int id;
    printf("Entrez l'ID de la voiture à modifier: ");
    scanf("%d", &id);
    getchar(); // Consommer le caractère de nouvelle ligne laissé par scanf

    int voitureTrouvee = 0; // Indicateur pour vérifier si la voiture est trouvée

    for (int i = 0; i < nbVoitures; i++) {
        if (voitures[i].id == id) {
            voitureTrouvee = 1;
            printf("Modifiez les informations de la voiture :\n");
            printf("Marque actuelle: %s. Nouvelle marque: ", voitures[i].marque);
            fgets(voitures[i].marque, sizeof(voitures[i].marque), stdin);

            printf("Modèle actuel: %s. Nouveau modèle: ", voitures[i].modele);
            fgets(voitures[i].modele, sizeof(voitures[i].modele), stdin);

            printf("Type de carburant actuel: %s. Nouveau type de carburant: ", voitures[i].typeCarburant);
            fgets(voitures[i].typeCarburant, sizeof(voitures[i].typeCarburant), stdin);

            printf("Nombre de places actuel: %d. Nouveau nombre de places: ", voitures[i].places);
            scanf("%d", &voitures[i].places);
            getchar(); // Consommer le caractère de nouvelle ligne laissé par scanf

            printf("Transmission actuelle: %s. Nouvelle transmission: ", voitures[i].transmission);
            fgets(voitures[i].transmission, sizeof(voitures[i].transmission), stdin);

            printf("Prix actuel: %.2f. Nouveau prix par jour: ", voitures[i].prixParJour);
            scanf("%f", &voitures[i].prixParJour);
            getchar(); // Consommer le caractère de nouvelle ligne laissé par scanf

            printf("Disponibilité actuelle: %s. Nouvelle disponibilité (1: disponible, 0: non disponible): ", voitures[i].disponible ? "Disponible" : "Non disponible");
            scanf("%d", &voitures[i].disponible);
            getchar(); // Consommer le caractère de nouvelle ligne laissé par scanf

            printf("Voiture modifiée avec succès!\n");
            return;
        }
    }

    if (!voitureTrouvee) {
        printf("Voiture avec l'ID %d non trouvée.\n", id);
    }
}

void supprimerVoiture(Voiture voitures[], int* nbVoitures) {
    int id;
    printf("Entrez l'ID de la voiture à supprimer: ");
    scanf("%d", &id);
    getchar(); // Consommer le caractère de nouvelle ligne laissé par scanf

    int voitureTrouvee = 0; // Indicateur pour vérifier si la voiture est trouvée

    for (int i = 0; i < *nbVoitures; i++) {
        if (voitures[i].id == id) {
            voitureTrouvee = 1;
            for (int j = i; j < *nbVoitures - 1; j++) {
                voitures[j] = voitures[j + 1];
            }
            (*nbVoitures)--;
            printf("Voiture supprimée avec succès!\n");
            return;
        }
    }

    if (!voitureTrouvee) {
        printf("Voiture avec l'ID %d non trouvée.\n", id);
    }
}

void afficherVoitures(Voiture voitures[], int nbVoitures) {
    if (nbVoitures == 0) {
        printf("Aucune voiture disponible.\n");
        return;
    }

    for (int i = 0; i < nbVoitures; i++) {
        printf("ID: %d\n", voitures[i].id);
        printf("Marque: %s\n", voitures[i].marque);
        printf("Modèle: %s\n", voitures[i].modele);
        printf("Type de carburant: %s\n", voitures[i].typeCarburant);
        printf("Nombre de places: %d\n", voitures[i].places);
        printf("Transmission: %s\n", voitures[i].transmission);
        printf("Prix par jour: %.2f\n", voitures[i].prixParJour);
        printf("Disponibilité: %s\n", voitures[i].disponible ? "Disponible" : "Non disponible");
    }
}

void rechercherVoiture(Voiture voitures[], int nbVoitures) {
    char marque[MAX_LEN];
    printf("Entrez la marque de la voiture à rechercher: ");
    fgets(marque, MAX_LEN, stdin);

    int found = 0;
    for (int i = 0; i < nbVoitures; i++) {
        if (strcmp(voitures[i].marque, marque) == 0) {
            printf("ID: %d\n", voitures[i].id);
            printf("Marque: %s\n", voitures[i].marque);
            printf("Modèle: %s\n", voitures[i].modele);
            printf("Type de carburant: %s\n", voitures[i].typeCarburant);
            printf("Nombre de places: %d\n", voitures[i].places);
            printf("Transmission: %s\n", voitures[i].transmission);
            printf("Prix par jour: %.2f\n", voitures[i].prixParJour);
            printf("Disponibilité: %s\n", voitures[i].disponible ? "Disponible" : "Non disponible");
            found = 1;
        }
    }
    if (!found) {
        printf("Aucune voiture trouvée pour la marque %s.\n", marque);
    }
}

void trierVoitures(Voiture voitures[], int nbVoitures) {
    for (int i = 0; i < nbVoitures - 1; i++) {
        for (int j = 0; j < nbVoitures - i - 1; j++) {
            if (voitures[j].prixParJour > voitures[j + 1].prixParJour) {
                Voiture temp = voitures[j];
                voitures[j] = voitures[j + 1];
                voitures[j + 1] = temp;
            }
        }
    }
    printf("Voitures triées par prix. \n");
}

int chargerVoitures(Voiture voitures[], int maxVoitures) {
    FILE *file = fopen("cars.csv", "r");
    if (!file) {
        printf("Erreur lors de l'ouverture du fichier cars.csv.\n");
        return 0;
    }

    int nbVoitures = 0;
    while (nbVoitures < maxVoitures && fscanf(file, "%d,%49[^,],%49[^,],%49[^,],%d,%49[^,],%f,%d\n",
            &voitures[nbVoitures].id,
            voitures[nbVoitures].marque,
            voitures[nbVoitures].modele,
            voitures[nbVoitures].typeCarburant,
            &voitures[nbVoitures].places,
            voitures[nbVoitures].transmission,
            &voitures[nbVoitures].prixParJour,
            &voitures[nbVoitures].disponible) == 8) {
        nbVoitures++;
    }

    fclose(file);
    printf("Chargement des voitures terminé. %d voitures chargées.\n", nbVoitures);
    return nbVoitures;
}

void sauvegarderVoitures(Voiture voitures[], int nbVoitures) {
    FILE *file = fopen("cars.csv", "w");
    if (!file) {
        printf("Erreur lors de l'ouverture du fichier cars.csv pour écriture.\n");
        return;
    }

    for (int i = 0; i < nbVoitures; i++) {
        fprintf(file, "%d,%s,%s,%s,%d,%s,%.2f,%d\n",
                voitures[i].id,
                voitures[i].marque,
                voitures[i].modele,
                voitures[i].typeCarburant,
                voitures[i].places,
                voitures[i].transmission,
                voitures[i].prixParJour,
                voitures[i].disponible);
    }

    fclose(file);
    printf("Sauvegarde des voitures terminée.\n");
}