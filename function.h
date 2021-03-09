#include <iostream>
#include <string.h>
#include <iomanip>
#include <windows.h>

//#define DEBUG true

namespace matrix{


    //Struct Matrix
    //Contiene tutte le informazioni di una matrice
    struct Matrix{

        unsigned int m_row;         //Numbers of rows
        unsigned int n_col;         //Numbers of Columns
        float** matrix;          //Matrix pointer
    };

    /*
    **  Crea una matrice inizializzandola con i valori contenuti in valueArray[]
    **  la dimensione dell'array deve essere uguale al numero di valori nella matrice a cui si riferisce (es matrice 2x2 dim(valueArray)=4)
    **  i valori di valueArray devono per forza essere tutti inizializzati per non incorrere in errori
    */
    void newMatrix(Matrix* matrix, float valueArray[]);

    /*
    **  Riempe le matrici in modo automatico con i valori dell'esercitazione (senza inserire i valori da stdin)
    */
    void initMatrix(Matrix* A1, Matrix* A2, Matrix* P, Matrix* T, Matrix* x_A1A2, Matrix* x_pascal, Matrix* x_tridiagonale);

    /*
    **  Stampa una matrice su standard output
    */
    void printMatrix(Matrix* matrix);

    /*
    **  Restituisce la norma infinito di una matrice
    */
    float normInf(Matrix* matrix);

    /*
    **  Modulo
    */
    float fabs(float elem);

    /*
    **  fattoriale
    */
    float fact(float elem);

    /*
    **  Prodotto tra matrici
    **  viene ritornato un puntatore che punta ad una matrice con il prodotto delle due matrici
    **  error: Viene ritornato NULL quando la moltiplicazione non è possibile cioe' quando il numero delle colonne della matrice A
    **         e' diverso dal numero delle righe della matrice B
    */
    Matrix* multiplication(Matrix* A, Matrix* B);

    /*
    **  Eliminazione gaussiana
    **  return -> matrice con la soluzione dell'equazione Ax = b  (x1, x2, ... , xn)
    */
    Matrix* GaussElimination(Matrix* A, Matrix* b);

    /*
    *   Esegue una deep copy della matrice passata come parametro
    *   ritorna la copia della matrice
    */
    Matrix* deepCopy(Matrix* A); 
    
    /*
    *   Dealloca una matrice precedentemente allocata da newMatrix
    */
    void deallocMatrix(Matrix* matrix);
}