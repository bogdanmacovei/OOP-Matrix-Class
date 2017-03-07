#include <iostream>
#include <cmath>
#include "matrice.h"

using namespace std;

Matrice :: Matrice ()
{
    nrLinii = nrColoane = 0;

    cout << "Obiect initializat in constructorul 1\n";
}

Matrice :: Matrice(int linii, int coloane, int element)
{
    nrLinii = linii;
    nrColoane = coloane;

    mat = new int* [nrLinii + 1];

    for(int i = 0; i < nrLinii; ++i)
        mat[i] = new int [nrColoane + 1];

    for(int i = 0; i < nrLinii; ++i)
        for(int j = 0; j < nrColoane; ++j)
            mat[i][j] = element;

    cout << "Obiect initializat in constructorul 2\n";
}

Matrice :: Matrice(int coloane, int numarInstante, ...)
{
    nrColoane = coloane;
    nrLinii = numarInstante;

    mat = new int* [nrLinii + 1];

    for(int i = 0; i < nrLinii; ++i)
        mat[i] = new int [nrColoane + 1];

    va_list lp;
    va_start(lp, numarInstante);

    for (int it = 0; it < numarInstante; ++it)
    {
        int elementIt = va_arg(lp, int);

        for(int i = 0; i < coloane; ++i)
            mat[it][i] = elementIt;
    }

    va_end(lp);

    cout << "Obiect initializat in constructorul 3\n";
}

Matrice :: ~Matrice()
{
    cout << "Obiect distrus\n";
}

int Matrice :: getNrLinii()
{
    return nrLinii;
}

int Matrice :: getNrColoane()
{
    return nrColoane;
}

istream& operator >> (istream &f, Matrice &matLocal)
{
    f >> matLocal.nrLinii >> matLocal.nrColoane;

    matLocal.mat = new int* [matLocal.nrLinii + 1];

    for(int i = 0; i < matLocal.nrLinii; ++i)
        matLocal.mat[i] = new int [matLocal.nrColoane + 1];

    for(int i = 0; i < matLocal.nrLinii; ++i)
        for(int j = 0; j < matLocal.nrColoane; ++j)
            f >> matLocal.mat[i][j];

    return f;
}

ostream& operator << (ostream &f, Matrice matLocal)
{
    for(int i = 0; i < matLocal.nrLinii; ++i)
    {
        for(int j = 0; j < matLocal.nrColoane; ++j)
            f << matLocal.mat[i][j] << " ";

        f << "\n";
    }

    return f;
}

Matrice operator + (Matrice matLocal1, Matrice matLocal2)
{
    Matrice matRezultat;

    /// daca nu au acelasi numar de linii si de coloane opresc functia

    if ((matLocal1.nrLinii != matLocal2.nrLinii) || (matLocal1.nrColoane != matLocal2.nrColoane))
    {
        matRezultat.nrLinii = matRezultat.nrColoane = 0;
        return matRezultat;
    }

    /// altfel, stiu pentru rezultat numarul de linii si numarul de coloane

    matRezultat.nrLinii = matLocal1.nrLinii;
    matRezultat.nrColoane = matLocal1.nrColoane;

    /// aloc memoria pentru rezultat

    matRezultat.mat = new int* [matRezultat.nrLinii + 1];

    for(int i = 0; i < matRezultat.nrLinii; ++i)
        matRezultat.mat[i] = new int [matRezultat.nrColoane + 1];

    /// rezultatul este matricea insumata pe componente

    for(int i = 0; i < matRezultat.nrLinii; ++i)
        for(int j = 0; j < matRezultat.nrColoane; ++j)
            matRezultat.mat[i][j] = matLocal1.mat[i][j] + matLocal2.mat[i][j];

    return matRezultat;
}

Matrice operator - (Matrice matLocal1, Matrice matLocal2)
{
    Matrice matRezultat;

    /// daca nu au acelasi numar de linii si de coloane opresc functia

    if ((matLocal1.nrLinii != matLocal2.nrLinii) || (matLocal1.nrColoane != matLocal2.nrColoane))
    {
        matRezultat.nrLinii = matRezultat.nrColoane = 0;
        return matRezultat;
    }

    /// altfel, stiu pentru rezultat numarul de linii si numarul de coloane

    matRezultat.nrLinii = matLocal1.nrLinii;
    matRezultat.nrColoane = matLocal1.nrColoane;

    /// aloc memoria pentru rezultat

    matRezultat.mat = new int* [matRezultat.nrLinii + 1];

    for(int i = 0; i < matRezultat.nrLinii; ++i)
        matRezultat.mat[i] = new int [matRezultat.nrColoane + 1];

    /// rezultatul este matricea cu diferenta pe componente

    for(int i = 0; i < matRezultat.nrLinii; ++i)
        for(int j = 0; j < matRezultat.nrColoane; ++j)
            matRezultat.mat[i][j] = matLocal1.mat[i][j] - matLocal2.mat[i][j];

    return matRezultat;
}

int*& Matrice :: operator [] (int linie)
{
    if (linie > nrLinii)
    {
        cout << "Eroare!";
        return mat[0];
    }

    return (mat[linie]);
}

int ** Matrice :: getMatrice()
{
    return mat;
}

int Matrice :: det(int nrLinii, int **matrice)
{
    static int detMat = 0;
    int **submat;

    /// Alocare de memorie

    submat = new int* [nrLinii + 1];
    for(int i = 0; i < nrLinii; ++i)
        submat[i] = new int [nrLinii + 1];

    if (nrLinii == 2)
    {
        return matrice[0][0] * matrice[1][1] - matrice[1][0] * matrice[0][1];
    }

    else
    {
        for(int it = 0; it < nrLinii; it++)
        {
            int subi = 0;

            for(int i = 1; i < nrLinii; i++)
            {
                int subj = 0;

                for(int j = 0; j < nrLinii; j++)
                {
                    if (j == it)
                        continue;

                    submat[subi][subj] = matrice[i][j];
                    subj++;
                }
                subi++;
            }
            detMat = detMat + (pow(-1, it) * matrice[0][it] * det(nrLinii - 1, submat));
        }
    }
    return detMat;
}

int Matrice :: determinant()
{
    return det(nrLinii, mat);
}
