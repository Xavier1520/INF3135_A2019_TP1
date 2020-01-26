#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NAME_MAX_LENGTH 20
#define NUM_MIN_PLAYERS 2
#define NUM_MAX_PLAYERS 20

enum Style {
    STYLE_COMPACT,
    STYLE_TABLE
};

enum Format {
    FORMAT_ID,
    FORMAT_NAME
};

struct PlayerList {
    unsigned int num_players;
    char name[NUM_MAX_PLAYERS][NAME_MAX_LENGTH + 1];
};

struct Grid {
    unsigned int num_players;
    unsigned int day[NUM_MAX_PLAYERS][NUM_MAX_PLAYERS];
};

/*Vérifier le nombre d'arguments dans la commande.*/
int verifierNbArg(int argc);

/*Vérifier le nombre de joueurs dans le fichier d'entrée.*/
int verifierNbJoueurs(int nbJoueurs);

/*Créer une liste de joueur à partir de l'entrée standard.*/
struct PlayerList creerListe(struct PlayerList CetteListe);

/*Créer un grille des matchs à partir de la liste de joueurs.*/
struct Grid creerGrille(struct PlayerList CetteListe, struct Grid CetteGrille);

/*Afficher la grille en fonction du style et du format*/
void afficherIdCompact(struct PlayerList CetteListe, struct Grid CetteGrille);
void afficherNameCompact(struct PlayerList CetteListe, struct Grid CetteGrille);
void afficherIdTable(struct PlayerList CetteListe, struct Grid CetteGrille);
void afficherNameTable(struct PlayerList CetteListe, struct Grid CetteGrille);

int main(int argc, char* argv[]) {

	/*Déclaration et initialisation des variables*/
	int codeRetour = 0;
	enum Style CeStyle = STYLE_COMPACT;
	enum Format CeFormat = FORMAT_ID;
	struct PlayerList CetteListe;
	CetteListe.num_players = 0;
	struct Grid CetteGrille;
	char* bye = "Bye";
	int index = 1;	

	codeRetour = verifierNbArg(argc);

	while(index < argc && codeRetour == 0) { 
		if(strcmp(argv[index], "-f") == 0 || strcmp(argv[index], "--format") == 0) {
			if(strcmp(argv[index+1], "id") == 0) {
				CeFormat = FORMAT_ID;
			} else if(strcmp(argv[index+1], "name") == 0) {
				CeFormat = FORMAT_NAME;
            		} else {
				fprintf(stderr, "Error: unknown format (%s)\n", argv[index+1]);
				codeRetour = 1;
			}
			index++;
		} else if(strcmp(argv[index], "-s") == 0 || strcmp(argv[index], "--style") == 0) {
			if(strcmp(argv[index+1], "compact") == 0) {
				CeStyle = STYLE_COMPACT;
			} else if(strcmp(argv[index+1], "table") == 0) {
				CeStyle = STYLE_TABLE;
			} else {
				fprintf(stderr, "Error: unknown style (%s)\n", argv[index+1]);
				codeRetour = 1;
			}
			index++;
		} else {
			fprintf(stderr, "Error: unknown option (%s)\n", argv[index]);
			codeRetour = 1;
		}
		index++;
	}

	if(codeRetour == 0) {
		CetteListe = creerListe(CetteListe);
		codeRetour = verifierNbJoueurs(CetteListe.num_players);
	}
	
	if(codeRetour == 0) {
		if (CetteListe.num_players % 2 == 1) {
			strncpy(CetteListe.name[CetteListe.num_players], bye, NAME_MAX_LENGTH);
			CetteListe.num_players++;
		}

		CetteGrille.num_players = CetteListe.num_players;
		CetteGrille = creerGrille(CetteListe, CetteGrille);

		if(CeStyle == STYLE_COMPACT && CeFormat == FORMAT_ID) {
			afficherIdCompact(CetteListe, CetteGrille);
		} else if(CeStyle == STYLE_COMPACT && CeFormat == FORMAT_NAME) {
			afficherNameCompact(CetteListe, CetteGrille);
		} else if(CeStyle == STYLE_TABLE && CeFormat == FORMAT_ID) {
			afficherIdTable(CetteListe, CetteGrille);
		} else if(CeStyle == STYLE_TABLE && CeFormat == FORMAT_NAME) {
			afficherNameTable(CetteListe, CetteGrille);
		}
	}
	
	return codeRetour;
}

int verifierNbArg(int argc) {
	int codeRetour = 0;
	if(argc != 1 && argc != 3 && argc != 5) {
		fprintf(stderr, "Error: wrong number of arguments\n");
		codeRetour = 1;
	}
	return codeRetour;
}

int verifierNbJoueurs(int nbJoueurs) {
	int codeRetour = 0;
	if(nbJoueurs < NUM_MIN_PLAYERS) {
		fprintf(stderr, "Error: not enough players (minimum is %d)", NUM_MIN_PLAYERS);
		codeRetour = 1;
	} else if (nbJoueurs > NUM_MAX_PLAYERS) {
		fprintf(stderr, "Error: too many players (maximum is %d)", NUM_MAX_PLAYERS);
		codeRetour = 1;
	}
	return codeRetour;
}

struct PlayerList creerListe(struct PlayerList CetteListe) {
	char ligne[NAME_MAX_LENGTH + 1];
	char nom[NAME_MAX_LENGTH];
	const char* delim = "\n";

	while(fgets(ligne, NAME_MAX_LENGTH, stdin) != NULL) {
		strncpy(nom, strtok(ligne, delim), NAME_MAX_LENGTH);
		strncpy(CetteListe.name[CetteListe.num_players], nom, NAME_MAX_LENGTH);
		CetteListe.num_players++;
	}
	return CetteListe;
}

struct Grid creerGrille(struct PlayerList CetteListe, struct Grid CetteGrille) {
	int jour;
	int i;
	int j;
	for(i = 0; i < CetteGrille.num_players; i++) {
		for(j = 0; j < CetteGrille.num_players; j++) {
			if(i != j && i + 1 != CetteGrille.num_players && j + 1 != CetteGrille.num_players) {
				if(i + j + 1 < CetteGrille.num_players) {
					jour = i + j + 1;
				} else {
					jour = i + j + 2 - CetteGrille.num_players;
				}
				CetteGrille.day[i][jour - 1] = j + 1;
			} else if (i != j && j + 1 == CetteGrille.num_players) {
				if((i * 2) + 2 <= CetteGrille.num_players) {
					jour = (i * 2) + 1;
				} else {
					jour = (i * 2) + 2 - CetteGrille.num_players;
				}
				CetteGrille.day[i][jour - 1] = j + 1;
			} else if (i != j && i + 1 == CetteGrille.num_players) {
				if((j * 2) + 2 <= CetteGrille.num_players) {
					jour = (j * 2) + 1;
				} else {
					jour = (j * 2) + 2 - CetteGrille.num_players;
				}
				CetteGrille.day[i][jour - 1] = j + 1;
			}
		}
	}
	return CetteGrille;
}

void afficherIdCompact(struct PlayerList CetteListe, struct Grid CetteGrille) {
	int i;
	int j;
	for(i = 0; i < CetteGrille.num_players; i++) {
		printf("%d:%s\n", i + 1, CetteListe.name[i]);
	}
	for(i = 0; i < CetteGrille.num_players; i++) {
		printf("%d:", i + 1);
		for(j = 0; j < CetteGrille.num_players - 1; j++) {
			if(j == CetteGrille.num_players -2) {
				printf("%d\n", CetteGrille.day[i][j]);
			} else {
				printf("%d,", CetteGrille.day[i][j]);
			}
		}
	}
}

void afficherNameCompact(struct PlayerList CetteListe, struct Grid CetteGrille) {
	int i;
	int j;
	for(i = 0; i < CetteGrille.num_players; i++) {
		printf("%s:", CetteListe.name[i]);
		for(j = 0; j < CetteGrille.num_players - 1; j++) {
			if(j == CetteGrille.num_players -2) {
				printf("%s\n", CetteListe.name[CetteGrille.day[i][j] - 1]);
			} else {
				printf("%s,", CetteListe.name[CetteGrille.day[i][j] - 1]);
			}
		}
	}
}

void afficherIdTable(struct PlayerList CetteListe, struct Grid CetteGrille) {
	int i;
	int j;
	printf("ID  Player  ");
	for(i = 1; i < CetteGrille.num_players; i++) {
		printf("  Day %-2d", i);
	}
	printf("\n--  --------");
	for(i = 1; i < CetteGrille.num_players; i++) {
		printf("  ------");
	}
	for(i = 0; i < CetteGrille.num_players; i++) {
		printf("\n%2d  %-8.8s", i + 1, CetteListe.name[i]);
		for (j = 0; j < CetteGrille.num_players - 1; j++) {
			printf("  %-6d", CetteGrille.day[i][j]);
		}
	}
}

void afficherNameTable(struct PlayerList CetteListe, struct Grid CetteGrille) {
	int i;
	int j;
	printf("ID  Player  ");
	for(i = 1; i < CetteGrille.num_players; i++) {
		printf("  Day %-4d", i);
	}
	printf("\n--  --------");
	for(i = 1; i < CetteGrille.num_players; i++) {
		printf("  --------");
	}
	for(i = 0; i < CetteGrille.num_players; i++) {
		printf("\n%2d  %-8.8s", i + 1, CetteListe.name[i]);
		for(j = 0; j < CetteGrille.num_players - 1; j++) {
			printf("  %-8.8s", CetteListe.name[CetteGrille.day[i][j] - 1]);
		}
	}
}
