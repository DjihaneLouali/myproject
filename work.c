#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TAILLE_DE_BLOC 1200

typedef struct {
    char bloc[TAILLE_DE_BLOC + 1];
} TBloc;

typedef struct {
    bool efface;
    int taille;
    int matricule;
    char etudiantData[1190];
} Etudiant;

typedef Etudiant Buffer;

typedef struct Enreg {
    char mattricule[6];
    char efface;
    char size[3];
    char info[1190];
} Enreg;

typedef struct Header {
    int adrLastBloc;
    int nbrEnreg;
    int nbrSuprLogiq;
} Header;

typedef struct {
    FILE* mainFile;
    Header header;
} TnOVnC;

TnOVnC* open(char* fileName, char mode);
int close(TnOVnC* tnOVnC);
int GetHeader(TnOVnC* tnOVnC, int i);
void SetHeader(TnOVnC* tnOVnC, int i, int val);
int liredir(TnOVnC* tnOVnC, int i, TBloc* buf);
int ecriredir(TnOVnC* tnOVnC, int i, TBloc buf);
int lireEtudiant(TBloc tBloc, int debutEnreg, Etudiant* etudiant);
int ecrireEtudiant(TnOVnC* tnOVnC, TBloc* tBloc, int debutEnregistrement, Etudiant etudiant, int numBloc);
int rechercheEtudiant(TnOVnC* tnOVnC, int matricule, bool* trouv, Etudiant* etudiant);
int insererEtudiant(TnOVnC* tnOVnC, Etudiant etudiant);

int main() {
    // Votre programme principal ici

    return 0;
}

// Reste du code...

int insererEtudiant(TnOVnC* tnOVnC, Etudiant etudiant) {
    TBloc bloc;
    int blocPos = 0;

    // Lecture du dernier bloc
    if (liredir(tnOVnC, tnOVnC->header.adrLastBloc, &bloc) == -1) {
        // Gestion de l'erreur de lecture
        return -1;
    }

    // Vérifier si l'étudiant peut être inséré dans le dernier bloc
    if ((blocPos + etudiant.taille + 10) <= TAILLE_DE_BLOC) {
        // Insérer l'étudiant dans le dernier bloc
        ecrireEtudiant(tnOVnC, &bloc, blocPos, etudiant, tnOVnC->header.adrLastBloc);
        return 0;
    } else {
        // Si le dernier bloc est plein, créer un nouveau bloc
        TBloc nouveauBloc;
        tnOVnC->header.adrLastBloc++;
        ecriredir(tnOVnC, tnOVnC->header.adrLastBloc, nouveauBloc);

        // Insérer l'étudiant dans le nouveau bloc
        ecrireEtudiant(tnOVnC, &nouveauBloc, 0, etudiant, tnOVnC->header.adrLastBloc);
        return 0;
    }
}
TnOVnC* open(char* fileName, char mode);

int main() {
    TnOVnC* tnOVnC = open("monfichier.dat", 'A');
    // ... autres opérations ...
    return 0;
}

TnOVnC* open(char* fileName, char mode) {
    TnOVnC* tnOVnC = (TnOVnC*)malloc(sizeof(TnOVnC));
    if (tnOVnC == NULL) {
        perror("Erreur d'allocation de mémoire lors de l'ouverture");
        return NULL;
    }

    if ((mode == 'A') || (mode == 'a')) {
        tnOVnC->mainFile = fopen(fileName, "ab+");
    } else {
        tnOVnC->mainFile = fopen(fileName, "wb+");
    }

    if (tnOVnC->mainFile == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        free(tnOVnC);
        return NULL;
    }

    if ((mode == 'A') || (mode == 'a')) {
        fread(&(tnOVnC->header), sizeof(Header), 1, tnOVnC->mainFile);
    } else {
        tnOVnC->header.adrLastBloc = 0;
        tnOVnC->header.nbrEnreg = 0;
        tnOVnC->header.nbrSuprLogiq = 0;
        fwrite(&(tnOVnC->header), sizeof(Header), 1, tnOVnC->mainFile);
    }

    return tnOVnC;
}
nt rechercheEtudiant(TnOVnC* tnOVnC, int matricule, bool* trouv, Etudiant* etudiant) {
    int blocPos = 0;
    *trouv = false;
    TBloc* bufBloc = (TBloc*)malloc(sizeof(TBloc));

    for (int i = 1; i <= tnOVnC->header.adrLastBloc; i++) {
        liredir(tnOVnC, i, bufBloc);

        while (blocPos < TAILLE_DE_BLOC) {
            lireEtudiant(*bufBloc, blocPos, etudiant);
            if (etudiant->matricule == matricule) {
                printf("Étudiant trouvé\n");
                *trouv = true;
                return 0;
            } else {
                blocPos += etudiant->taille;
            }
        }
    }

    printf("Étudiant non trouvé\n");
    return 0;
}
int ecriredir(TnOVnC* tnOVnC, int i, TBloc buf) {
    if (i <= tnOVnC->header.adrLastBloc) {
        fseek(tnOVnC->mainFile, sizeof(Header) + (i - 1) * sizeof(TBloc), SEEK_SET);
        fwrite(&buf, sizeof(TBloc), 1, tnOVnC->mainFile);
        return 0;
    } else {
        printf("Erreur, le bloc n'existe pas !\n");
        return -1;
    }
}
int liredir(TnOVnC* tnOVnC, int i, TBloc* buf) {
    if (i <= tnOVnC->header.adrLastBloc) {
        fseek(tnOVnC->mainFile, sizeof(Header) + (i - 1) * sizeof(TBloc), SEEK_SET);
        fread(buf, sizeof(TBloc), 1, tnOVnC->mainFile);
        return 0;
    } else {
        printf("Erreur, le bloc n'existe pas !\n");
        return -1;
    }
}
int close(TnOVnC* tnOVnC) {
    rewind(tnOVnC->mainFile);
    fwrite(&(tnOVnC->header), sizeof(Header), 1, tnOVnC->mainFile);
    fclose(tnOVnC->mainFile);
    free(tnOVnC);
    tnOVnC = NULL;
    return 0;
}

int GetHeader(TnOVnC* tnOVnC, int i) {
    if (i == 1) return tnOVnC->header.adrLastBloc;
    else if (i == 2) return tnOVnC->header.nbrEnreg;
    else return tnOVnC->header.nbrSuprLogiq;
}

void SetHeader(TnOVnC* tnOVnC, int i, int val) {
    if (i == 1) tnOVnC->header.adrLastBloc = val;
    else if (i == 2) tnOVnC->header.nbrEnreg = val;
    else tnOVnC->header.nbrSuprLogiq = val;
}