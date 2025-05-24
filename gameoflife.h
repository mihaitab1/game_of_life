#include <stdio.h>
typedef struct coord
{
    int l, c;
} coord;
typedef struct Nod
{
    struct Nod *urm;
    coord coord;
} Nod;
typedef struct Stiva
{
    Nod *lista;
    int generatie;
    struct Stiva *urm;
} Stiva;
typedef struct arbore
{
    Nod *lista;
    struct arbore *left, *right;
} arbore;

/*functii citire /afisare*/
void citire(int *t, int *n, int *m, int *k, char mat[300][300], FILE *fisier1);
void afisare(int n, int m, const char mat[300][300], FILE *fisier2);
/*Regulile jocului*/
int nr_vecini(int n, int m, const char mat[300][300], int lin, int col);
void vie_moarta(int n, int m, char mat[300][300]);
void vie_moartaB(int n, int m, char mat[300][300]);
/* Liste si stive */
Nod *push(Nod *varf, int linie, int coloana);
Stiva *push_stiva(Stiva *varf, Nod *lista, int generatie);
Nod *inversare_lista(Nod *cap_lista);
Stiva *inversare_stiva(Stiva *varf);
void afisare_stiva(Stiva *varf, FILE *fisier2);
/*Arbori*/
arbore *creare_nod();
void construire_arbore(arbore *nod, char mat[300][300], int n, int m, int k, int h);
void preorder(arbore *root, FILE *fisier2, int n, int m, char mat[300][300]);
