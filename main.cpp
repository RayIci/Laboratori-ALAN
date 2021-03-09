//**********************************************************************
//Valle Alex S4854159 
//Esercitazione 2 - Laboratorio ALAN (Esercitazione Sui Sistemi Lineari)
//**********************************************************************

#include "function.h"

int main(int argc, char** argv){

    //Inizializzazione  matrici
    struct matrix::Matrix* A1 = new matrix::Matrix;
    struct matrix::Matrix* A2 = new matrix::Matrix;
    struct matrix::Matrix* P = new matrix::Matrix;
    struct matrix::Matrix* T = new matrix::Matrix;
    struct matrix::Matrix* x_A1A2 = new matrix::Matrix;
    struct matrix::Matrix* x_pascal = new matrix::Matrix;
    struct matrix::Matrix* x_tridiagonale = new matrix::Matrix;

    A1->m_row = A1->n_col = 4;
    A2->m_row = A2->n_col = 4;
    P->m_row = P->n_col = 10;
    x_A1A2->m_row = 4;  x_A1A2->n_col = 1;
    x_pascal->m_row = 10; x_pascal->n_col = 1;
    
    //Numero matricola 4854159
    int d0 = 9;
    int d1 = 5;
    T->m_row = T->n_col = 10*(d1 + 1) + d0;
    x_tridiagonale->m_row = T->n_col; x_tridiagonale->n_col = 1;

    matrix::initMatrix(A1, A2, P, T, x_A1A2, x_pascal, x_tridiagonale);

#ifdef DEBUG 
    //stampa delle matrici per vedere la corretta inizializzazione
    std::cout << "Matrice A1:" << std::endl;
    matrix::printMatrix(A1);

    std::cout << "\n\nMatrice A2:" << std::endl;
    matrix::printMatrix(A2);

    std::cout << "\n\nMatrice di Pascal:" << std::endl;
    matrix::printMatrix(P);
    
    std::cout << "\n\nMatrice Tridiagonale:" << std::endl;
    matrix::printMatrix(T);

#endif


    //*****     Esercizio 1:    *****
    //a)
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "**************    ESERCIZIO 1    **************\n" << std::endl;
    std::cout << "Norma infinito della matrice A1: " << matrix::normInf(A1) << std::endl;
    std::fflush(stdout);

    std::cout << "Norma infinito della matrice A2: " << matrix::normInf(A2) << std::endl;
    std::fflush(stdout);
    
    //b)
    std::cout << "Norma infinito della matrice di Pascal: " << matrix::normInf(P) << std::endl;
    std::fflush(stdout);

    //c)
    std::cout << "Norma infinito della matrice Tridiagonale: " << matrix::normInf(T) << std::endl;
    std::fflush(stdout);




    //*****     Esercizio 2:    *****

    //Matrice A1
    std::cout << "\n\n\n**************    ESERCIZIO 2    **************\n" << std::endl;
    matrix::Matrix* b_A1 = matrix::multiplication(A1, x_A1A2);
    struct matrix::Matrix* ris = matrix::GaussElimination(A1, b_A1);
    std::cout << "Trovo la matrice dei termini noti x (soluzione all'equazione Ax = b) con:" << std::endl;
    std::cout << "-A= " << std::endl;
    matrix::printMatrix(A1);
    std::cout << "\n-b = ";
    matrix::printMatrix(b_A1);
    std::cout << "\nMatrice dei coefficenti x trovata con il metodo di eliminazione gaussiana: " << std::endl;
    std::cout << "-x = ";
    matrix::printMatrix(ris);
    std::fflush(stdout);

    //Matrice A2
    matrix::Matrix* b_A2 = matrix::multiplication(A2, x_A1A2);
    ris = matrix::GaussElimination(A1, b_A2);
    std::cout << "\n\nTrovo la matrice dei termini noti x (soluzione all'equazione Ax = b) con:" << std::endl;
    std::cout << "-A= " << std::endl;
    matrix::printMatrix(A1);
    std::cout << "\n-b = ";
    matrix::printMatrix(b_A2);
    std::cout << "\nMatrice dei coefficenti x trovata con il metodo di eliminazione gaussiana: " << std::endl;
    std::cout << "-x = ";
    matrix::printMatrix(ris);
    std::fflush(stdout);

    //Matrice Pascal
    matrix::Matrix* b_pascal = matrix::multiplication(P, x_pascal);
    ris = matrix::GaussElimination(P, b_pascal);
    std::cout << "\n\nTrovo la matrice dei termini noti x (soluzione all'equazione Ax = b) con:" << std::endl;
    std::cout << "-A= " << std::endl;
    matrix::printMatrix(P);
    std::cout << "\n-b = ";
    matrix::printMatrix(b_pascal);
    std::cout << "\nMatrice dei coefficenti x trovata con il metodo di eliminazione gaussiana: " << std::endl;
    std::cout << "-x = ";
    matrix::printMatrix(ris);
    std::fflush(stdout);

    //Matrice Tridiagonale
    matrix::Matrix* b_tridiagonale = matrix::multiplication(T, x_tridiagonale);
    ris = matrix::GaussElimination(T, b_tridiagonale);
    std::cout << "\n\nTrovo la matrice dei termini noti x (soluzione all'equazione Ax = b) con:" << std::endl;
    std::cout << "-A= " << std::endl;
    matrix::printMatrix(T);
    std::cout << "\n-b = ";
    matrix::printMatrix(b_tridiagonale);
    std::cout << "\nMatrice dei coefficenti x trovata con il metodo di eliminazione gaussiana: " << std::endl;
    std::cout << "-x = ";
    matrix::printMatrix(ris);
    std::fflush(stdout);


    //*****     Esercizio 3:    *****

    matrix::Matrix* bPert_A1 = new matrix::Matrix;
    matrix::Matrix* bPert_A2 = new matrix::Matrix;
    matrix::Matrix* bPert_pascal = new matrix::Matrix;
    matrix::Matrix* bPert_tridiagonale = new matrix::Matrix;


    bPert_A1->m_row = 4;      bPert_A1->n_col = 1;
    bPert_A2->m_row = 4;      bPert_A2->n_col = 1;
    bPert_pascal->m_row = 10;   bPert_pascal->n_col = 1;
    bPert_tridiagonale->m_row = 10*(d1 + 1) + d0; bPert_tridiagonale->n_col = 1;


    float ElemOf_bPert_A1[bPert_A1->m_row * bPert_A1->n_col];
    float ElemOf_bPert_A2[bPert_A2->m_row * bPert_A2->n_col];
    float ElemOf_bPert_pascal[bPert_pascal->m_row * bPert_pascal->n_col];
    float ElemOf_bPert_tridiagonale[bPert_tridiagonale->m_row * bPert_tridiagonale->n_col];
    

    float norm = matrix::normInf(b_A1);
    for(unsigned int i=0; i<bPert_A1->m_row; i++)
        ElemOf_bPert_A1[i] = (norm * (-0.01))  + b_A1->matrix[i][0];

    norm = matrix::normInf(b_A2);
    for(unsigned int i=0; i<bPert_A2->m_row; i++)
        ElemOf_bPert_A2[i] = (norm * (-0.01))  + b_A2->matrix[i][0];

    norm = matrix::normInf(b_pascal);
    for(unsigned int i=0; i<bPert_pascal->m_row; i++)
        ElemOf_bPert_pascal[i] = (norm * (-0.01))  + b_pascal->matrix[i][0];

    norm = matrix::normInf(b_tridiagonale);
    for(unsigned int i=0; i<bPert_tridiagonale->m_row; i++)
        ElemOf_bPert_tridiagonale[i] = (norm * (-0.01)) + b_tridiagonale->matrix[i][0];


    matrix::newMatrix(bPert_A1,ElemOf_bPert_A1);
    matrix::newMatrix(bPert_A2,ElemOf_bPert_A2);
    matrix::newMatrix(bPert_pascal,ElemOf_bPert_pascal);
    matrix::newMatrix(bPert_tridiagonale,ElemOf_bPert_tridiagonale);

    std::cout << "\n\n\n**************    ESERCIZIO 3    **************\n" << std::endl;
    std::cout << "Soluzione del sistema liare Ax = b + b_perturbato:\n" << std::endl;

    std::cout << "Matrice dei coefficenti A1 (con b perturbato): " << std::endl;
    ris = matrix::GaussElimination(A1, bPert_A1);
    matrix::printMatrix(ris);
    std::cout << "\n\n";
    std::fflush(stdout);

    std::cout << "Matrice dei coefficenti A2 (con b perturbato): " << std::endl;
    ris = matrix::GaussElimination(A2, bPert_A2);
    matrix::printMatrix(ris);
    std::cout << "\n\n";
    std::fflush(stdout);

    std::cout << "Matrice dei coefficenti Pascal (con b perturbato): " << std::endl;
    ris = matrix::GaussElimination(P, bPert_pascal);
    matrix::printMatrix(ris);
    std::cout << "\n\n";
    std::fflush(stdout);

    std::cout << "Matrice dei coefficenti Tridiagonale (con b perturbato): " << std::endl;
    ris = matrix::GaussElimination(T, bPert_tridiagonale);
    matrix::printMatrix(ris);
    std::cout << "\n\n";
    std::fflush(stdout);

    matrix::deallocMatrix(A1);
    matrix::deallocMatrix(A2);
    matrix::deallocMatrix(P);
    matrix::deallocMatrix(T);
    matrix::deallocMatrix(b_A1);
    matrix::deallocMatrix(b_A2);
    matrix::deallocMatrix(b_pascal);
    matrix::deallocMatrix(b_tridiagonale);
    matrix::deallocMatrix(bPert_A1);
    matrix::deallocMatrix(bPert_A2);
    matrix::deallocMatrix(bPert_pascal);
    matrix::deallocMatrix(bPert_tridiagonale);
    matrix::deallocMatrix(x_A1A2);
    matrix::deallocMatrix(x_pascal);
    matrix::deallocMatrix(x_tridiagonale);
    matrix::deallocMatrix(ris);


}