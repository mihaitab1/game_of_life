#include "gameoflife.h"
#include <stdlib.h>
#include <string.h>
int main(int argc, const char *argv[])
{
    FILE *fisier1 = fopen(argv[1], "r");
    if (fisier1 == NULL)
    {
        printf("eroare la deschiderea fisierului in");
        exit(1);
    }
    FILE *fisier2 = fopen(argv[2], "w");
    if (fisier2 == NULL)
    {
        printf("eroare la deschiderea fisierului out");
        exit(1);
    }
    int n, m, k, i, t;
    Nod *cap_lista = NULL;
    Stiva *varf = NULL;
    char mat[300][300], mat2[300][300];
    citire(&t, &n, &m, &k, mat, fisier1);
    if (t == 1)
    {
        afisare(n, m, mat, fisier2);
        for (i = 1; i <= k; i++)
        {
            vie_moarta(n, m, mat);
            afisare(n, m, mat, fisier2);
        }
    }
    else if (t == 2)
    {
        for (i = 1; i <= k; i++)
        {
            for (int lin = 0; lin < n; lin++)
                for (int col = 0; col < m; col++)
                    mat2[lin][col] = mat[lin][col];
            vie_moarta(n, m, mat);
            cap_lista = NULL;
            for (int lin = 0; lin < n; lin++)
                for (int col = 0; col < m; col++)
                    if (mat[lin][col] != mat2[lin][col])
                        cap_lista = push(cap_lista, lin, col);
            cap_lista = inversare_lista(cap_lista);
            varf = push_stiva(varf, cap_lista, i);
        }
        varf = inversare_stiva(varf);
        afisare_stiva(varf, fisier2);
    }
    else if (t == 3)
    {
        arbore *root = creare_nod();
        for (int lin = 0; lin < n; lin++)
            for (int col = 0; col < m; col++)
                if (mat[lin][col] == 'X')
                    root->lista = push(root->lista, lin, col);
        root->lista = inversare_lista(root->lista);
        construire_arbore(root, mat, n, m, k, 0);
        preorder(root, fisier2, n, m, mat);
    }
    else if (t == 4)
    {
        /*arbore *root = creare_nod();
        for (int lin = 0; lin < n; lin++)
            for (int col = 0; col < m; col++)
                if (mat[lin][col] == 'X')
                    root->lista = push(root->lista, lin, col);
        root->lista = inversare_lista(root->lista);
        construire_arbore(root, mat, n, m, k, 0);
        preorder(root, fisier2, n, m, mat);*/
    }
    else if (t == 5) // pentru bonus
    {
        char linie[9000];
        fgets(linie, sizeof(linie), fisier1);
        for (int gen = 1; gen <= k; gen++)
        {
            cap_lista = NULL;
            fgets(linie, sizeof(linie), fisier1);
            const char *p;
            strtok(linie, " ");
            p = strtok(NULL, " ");
            while (p != NULL)
            {
                i = atoi(p);
                p = strtok(NULL, " ");
                int j = atoi(p);
                p = strtok(NULL, " ");
                cap_lista = push(cap_lista, i, j);
            }
            cap_lista = inversare_lista(cap_lista);
            varf = push_stiva(varf, cap_lista, gen);
        }
        varf = inversare_stiva(varf);
        Stiva *aux = varf;
        while (aux)
        {
            Nod *nou = aux->lista;
            while (nou)
            {
                int l = nou->coord.l;
                int c = nou->coord.c;
                if (mat[l][c] == 'X')
                    mat[l][c] = '+';
                else
                    mat[l][c] = 'X';
                nou = nou->urm;
            }
            aux = aux->urm;
        }
        afisare(n, m, mat, fisier2);
    }
    fclose(fisier1);
    fclose(fisier2);
    return 0;
}