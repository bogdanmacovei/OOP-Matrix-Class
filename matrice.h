#include <iostream>
#include <cstdarg>

using namespace std;

class Matrice
{
    private:
        int **mat;
        int nrLinii, nrColoane;

        // metoda det(int, int**) clasica, e privata pentru ca, din exterior,
        //      ofer acces la metoda determinant()

        int det(int, int**);

    public:
        /// Constructorii

        Matrice ();

        // constructor cu parametri: nrLinii, nrColoane si element,
        //      astfel ca toata matricea va fi umpluta cu elementele egale cu element

        Matrice (int, int, int);

        // constructor cu numar variabil de parametri, avand semnificatia:
        //      primul este numarul de coloane
        //      al doilea este numarul de Instante := 1) numarul de linii
        //                                            2) arata cate numere se vor scrie in apel
        //                                            3) astfel incat linia[0] va avea primul element,
        //                                                  pana la linia[n-1] care va avea al n-lea element
        //
        // Exemplu: Matrice(4, 3, 2, 1, 5): creeaza o matrice cu 4 coloane, 3 linii, astfel incat
        //                                      pe prima   linie avem doar elemente cu valoarea 2,
        //                                      pe a doua  linie avem doar elemente cu valoarea 1
        //                                      pe a treia linie avem doar elemente cu valoarea 5

        Matrice (int, int, ...);

        /// Destructorul obisnuit

        ~Matrice ();

        /// Interogari in clasa

        int getNrLinii();
        int getNrColoane();
        int **getMatrice();

        /// Supraincarcarea operatorilor de scriere/citire

        friend istream& operator >> (istream&, Matrice&);
        friend ostream& operator << (ostream&, Matrice);

        /// Operatii cu obiecte

        friend Matrice operator + (Matrice, Matrice);
        friend Matrice operator * (Matrice, Matrice);
        friend Matrice operator - (Matrice, Matrice);
        int* &operator [] (int);

        /// Metoda determinant
        int determinant();
};
