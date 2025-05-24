#include "gameoflife.h"
#include <stdlib.h>
#include <string.h>
void citire(int *t, int *n, int *m, int *k, char mat[300][300], FILE *fisier1)
{
    int i, j;
    fscanf(fisier1, "%d", t);
    fscanf(fisier1, "%d %d", n, m);
    fscanf(fisier1, "%d", k);
    for (i = 0; i < *n; i++)
        for (j = 0; j < *m; j++)
            fscanf(fisier1, " %c", &mat[i][j]);
}
void afisare(int n, int m, const char mat[300][300], FILE *fisier2)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
            fprintf(fisier2, "%c", mat[i][j]);
        fprintf(fisier2, "\n");
    }
    fprintf(fisier2, "\n");
}
int nr_vecini(int n, int m, const char mat[300][300], int lin, int col)
{
    const int vlinie[] = {-1, -1, -1, 0, 0, 1, 1, 1}, vcoloana[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int nr = 0, i;
    for (i = 0; i < 8; i++)
    {
        int indice_linie = vlinie[i] + lin;
        int indice_coloana = vcoloana[i] + col;
        if (indice_linie >= 0 && indice_coloana >= 0 && indice_linie < n && indice_coloana < m)
            if (mat[indice_linie][indice_coloana] == 'X')
                nr++;
    }
    return nr;
}
void vie_moarta(int n, int m, char mat[300][300])
{
    int i, j, nr;
    char aux[300][300];
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
        {
            nr = nr_vecini(n, m, mat, i, j);
            if (mat[i][j] == 'X')
            {
                if (nr < 2 || nr > 3)
                    aux[i][j] = '+';
                else /*if (nr == 2 || nr == 3)*/
                    aux[i][j] = 'X';
            }
            else
            {
                if (nr == 3)
                    aux[i][j] = 'X';
                else
                    aux[i][j] = '+';
            }
        }
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            mat[i][j] = aux[i][j];
}
void vie_moartaB(int n, int m, char mat[300][300])
{
    int i, j, nr;
    char aux[300][300];
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
        {
            nr = nr_vecini(n, m, mat, i, j);
            if (mat[i][j] == 'X')
                aux[i][j] = 'X';
            else
            {
                if (nr == 2)
                    aux[i][j] = 'X';
                else
                    aux[i][j] = '+';
            }
        }
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            mat[i][j] = aux[i][j];
}
Nod *push(Nod *varf, int linie, int coloana)
{
    Nod *nou = (Nod *)malloc(sizeof(Nod));
    nou->coord.l = linie;
    nou->coord.c = coloana;
    nou->urm = varf;
    return nou;
}
Stiva *push_stiva(Stiva *varf, Nod *lista, int generatie)
{
    Stiva *nou = (Stiva *)malloc(sizeof(Stiva));
    if (nou == 0)
    {
        printf("Eroare la alocarea memoriei!");
        exit(1);
    }
    nou->lista = lista;
    nou->generatie = generatie;
    nou->urm = varf;
    return nou;
}
Nod *inversare_lista(Nod *cap_lista)
{
    Nod *aux = NULL, *curent = cap_lista, *urmator;
    while (curent != NULL)
    {
        urmator = curent->urm;
        curent->urm = aux;
        aux = curent;
        curent = urmator;
    }
    return aux;
}
Stiva *inversare_stiva(Stiva *varf)
{
    Stiva *aux = NULL, *curent = varf, *urmator;
    while (curent != NULL)
    {
        urmator = curent->urm;
        curent->urm = aux;
        aux = curent;
        curent = urmator;
    }
    return aux;
}
void afisare_stiva(Stiva *varf, FILE *fisier2)
{
    Stiva *aux = varf;
    while (aux != NULL)
    {
        fprintf(fisier2, "%d", aux->generatie);
        Nod *aux2 = aux->lista;
        while (aux2 != NULL)
        {
            fprintf(fisier2, " %d %d", aux2->coord.l, aux2->coord.c);
            aux2 = aux2->urm;
        }
        fprintf(fisier2, "\n");
        aux = aux->urm;
    }
}
arbore *creare_nod()
{
    arbore *nou = (arbore *)malloc(sizeof(arbore));
    nou->lista = NULL;
    nou->left = NULL;
    nou->right = NULL;
    return nou;
}
void construire_arbore(arbore *nod, char mat[300][300], int n, int m, int k, int h)
{
    if (k == h)
        return;
    char aux[300][300];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            aux[i][j] = mat[i][j];
    vie_moartaB(n, m, aux);
    arbore *left = creare_nod();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (mat[i][j] != aux[i][j])
                left->lista = push(left->lista, i, j);
    left->lista = inversare_lista(left->lista);
    nod->left = left;
    construire_arbore(left, aux, n, m, k, h + 1);
    char aux2[300][300];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            aux2[i][j] = mat[i][j];
    vie_moarta(n, m, aux2);
    arbore *right = creare_nod();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (mat[i][j] != aux2[i][j])
                right->lista = push(right->lista, i, j);
    right->lista = inversare_lista(right->lista);
    nod->right = right;
    construire_arbore(right, aux2, n, m, k, h + 1);
}
void preorder(arbore *root, FILE *fisier2, int n, int m, char mat[300][300])
{
    if (!root)
        return;
    afisare(n, m, mat, fisier2);
    if (root->left)
    {
        char aux_stanga[300][300];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                aux_stanga[i][j] = mat[i][j];
        Nod *curent = root->left->lista;
        while (curent)
        {
            int linie, col;
            linie = curent->coord.l;
            col = curent->coord.c;
            if (aux_stanga[linie][col] == 'X')
                aux_stanga[linie][col] = '+';
            else
                aux_stanga[linie][col] = 'X';
            curent = curent->urm;
        }
        preorder(root->left, fisier2, n, m, aux_stanga);
    }
    if (root->right)
    {
        char aux_dreapta[300][300];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                aux_dreapta[i][j] = mat[i][j];
        Nod *curent = root->right->lista;
        while (curent)
        {
            int linie, col;
            linie = curent->coord.l;
            col = curent->coord.c;
            if (aux_dreapta[linie][col] == 'X')
                aux_dreapta[linie][col] = '+';
            else
                aux_dreapta[linie][col] = 'X';
            curent = curent->urm;
        }
        preorder(root->right, fisier2, n, m, aux_dreapta);
    }
}