#include "function.h"

//Crea una matrice inizializzandola con i valori contenuti in valueArray[]
//la dimensione dell'array deve essere uguale al numero di valori nella matrice a cui si riferisce (es matrice 2x2 dim(valueArray)=4)
//i valori di valueArray devono per forza essere tutti inizializzati per non incorrere in errori
void matrix::newMatrix(Matrix* matrix, float valueArray[]){


    //Allocazione dinamica della memoria di una matrice
    matrix->matrix = (float**)(malloc(matrix->m_row * sizeof(float*)));
    if(matrix->matrix == NULL){
        std::cerr << "error allocating memory for new matrix!" << std::endl;
        std::fflush(stderr);
    }
    
    for(unsigned int i=0; i<matrix->m_row; i++){
        matrix->matrix[i] = (float*)malloc(matrix->n_col * sizeof(float));
        
        if(matrix->matrix == NULL){
            std::cerr << "error allocating memory for new matrix!" << std::endl;
            std::fflush(stderr);
        }
    }

    unsigned int arrayCount = 0;
    for (unsigned int i=0; i<matrix->m_row; i++){
        for(unsigned int j=0; j<matrix->n_col; j++){
            matrix->matrix[i][j] = valueArray[arrayCount];
            arrayCount += 1;
        }
    }
}

//Riempe le matrici in modo automatico con i valori dell'esercitazione (senza inserire i valori da stdin)
void matrix::initMatrix(Matrix* A1, Matrix* A2, Matrix* P, Matrix* T, Matrix* x_A1A2, Matrix* x_pascal, Matrix* x_tridiagonale){

    //Valori matrice A1
    float ElemOfA1[A1->m_row * A1->n_col] =    {    3,  1, -1,  0,
                                                    0,  7, -3,  0,
                                                    0, -3,  9, -2,
                                                    0,  0,  4, -10
                                                };

    //Valori matrice A2
    float ElemOfA2[A2->m_row * A2->n_col] =    {    2,  4, -2,  0,
                                                    1,  3,  0,  1,
                                                    3, -1,  1,  2,
                                                    0, -1,  2,  1
                                                };
    float ElemOfx_A1A2[x_A1A2->m_row * x_A1A2->n_col] = {1, 1, 1, 1};

    //Valori matrice di Pascal
    float ElemOfP[P->m_row * P->n_col];
    float ElemOfx_pascal[P->m_row * P->n_col];
    unsigned int arrayIndex = 0;

    for (unsigned int i=1; i<=P->m_row; i++){
        for(unsigned int j=1; j<=P->n_col; j++){

            ElemOfP[arrayIndex] = matrix::fact(i + j -2) / (matrix::fact(i - 1) * matrix::fact(j - 1));
            ElemOfx_pascal[arrayIndex] = 1;
            arrayIndex++;
        }
    }

    //Valori matrice Tridiagonale
    float ElemOfT[T->m_row * T->n_col];
    float ElemOfx_tridiagonale[T->m_row * T->n_col];
    arrayIndex = 0;
    for (int i=1; i<=T->m_row; i++){
        for(int j=1; j<=T->n_col; j++){
            if (i == j)
                ElemOfT[arrayIndex] = 2;
            else if (matrix::fabs(i - j) == 1)
                ElemOfT[arrayIndex] = -1;
            else
                ElemOfT[arrayIndex] = 0;
            
            ElemOfx_tridiagonale[arrayIndex] = 1;
            arrayIndex++;
        }
    }

    newMatrix(A1, ElemOfA1);
    newMatrix(A2, ElemOfA2);
    newMatrix(P, ElemOfP);
    newMatrix(T, ElemOfT);
    newMatrix(x_A1A2, ElemOfx_A1A2);
    newMatrix(x_pascal, ElemOfx_pascal);
    newMatrix(x_tridiagonale, ElemOfx_tridiagonale);
}

//Stampa una matrice su standard output
void matrix::printMatrix(Matrix* matrix){   

    if(matrix->n_col == 1){         //se la matrice passata ha una colonna (vettore) stampa il vettore trasposto
        std::cout << "[";
        for(unsigned int i=0; i<matrix->m_row; i++){
            std::cout << "" << matrix->matrix[i][0] << "";
            if(matrix->m_row-1 != i)
                std::cout << "  ";
        }
        std::cout << "]t" << std::endl;
    }   
    else{         //Altrimenti stampa "normalmente" la matrice
        for (unsigned int i=0; i<matrix->m_row; i++){
            for(unsigned int j=0; j<matrix->n_col; j++){
                std::cout << std::setprecision(2) << matrix->matrix[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }
    std::fflush(stdout);
}

//Restituisce la norma infinito di una matrice
float matrix::normInf(Matrix* matrix){

    float normRow = 0;
    float return_normInf;

    for(unsigned int i=0; i<matrix->m_row; i++){
        
        //calcolo delle righe
        for(unsigned int j=0; j<matrix->n_col; j++){
            normRow += matrix::fabs(matrix->matrix[i][j]);
        }

        //assegnazione
        if(i == 0)
            return_normInf = normRow;
        else
            if (normRow > return_normInf)
                return_normInf = normRow;
        
        normRow = 0;
    }

    return return_normInf;
}

//Modulo 
float matrix::fabs(float elem){

    if(elem >= 0)
        return elem;
    return elem * (-1);
}

//Fattoriale
float matrix::fact(float elem){
    
    //Fattoriale di un numero negativo non definito
    if(elem < 0)
        return 0;
 
    if(elem == 0)
        return 1;

    return elem * matrix::fact(elem - 1);
}

//Prodotto tra matrici
//viene ritornato un puntatore che punta ad una matrice con il risultato del prodotto tra le due matrici passate come argomento
//error: Viene ritornato NULL quando la moltiplicazione non è possibile cioe' quando il numero delle colonne della matrice A
//       e' diverso dal numero delle righe della matrice B
matrix::Matrix* matrix::multiplication(Matrix* A, Matrix* B){

    if(A->n_col != B->m_row)
        return NULL;
    
    Matrix* returnMatrix = new Matrix;
    returnMatrix->m_row = A->m_row;
    returnMatrix->n_col = B->n_col;

    float ElemOfreturnMatrix[returnMatrix->m_row * returnMatrix->n_col];
    float value = 0;
    unsigned int arrayIndex = 0;
    for (unsigned int i=0; i<A->m_row; i++){        //Fissa la riga della matrice A
        for (unsigned int j=0; j<B->n_col; j++){    //Fissa la colonna della matrice B
            for(unsigned int k=0; k<B->m_row; k++){     //Indice per elemento da moltiplicare
                value += A->matrix[i][k] * B->matrix[k][j];         //Valore "parziale" dell'elemento
            }
            ElemOfreturnMatrix[arrayIndex] = value;     //Assegnazione dell'elemento nella corretta posizione
            arrayIndex++;
            value = 0;
        }
    }

    newMatrix(returnMatrix, ElemOfreturnMatrix);     //crea la nuova matrice di ritorno con il risultato della moltiplicazione
    return returnMatrix;
}


/*
**  Eliminazione gaussiana
**  return -> matrice con la soluzione dell'equazione Ax = b  (x1, x2, ... , xn)
*/
matrix::Matrix* matrix::GaussElimination(Matrix* A, Matrix* b){

    matrix::Matrix* A_copy = matrix::deepCopy(A);
    matrix::Matrix* b_copy = matrix::deepCopy(b);

    for(unsigned int i=0; i<A_copy->n_col-1; i++){
        float pivot = A_copy->matrix[i][i];

        for(unsigned int j=i+1; j<A_copy->m_row; j++){
            if(A_copy->matrix[j][i] != 0){
                float coff = A_copy->matrix[j][i] / pivot;
                
                for(unsigned int k=i; k<A_copy->n_col; k++){
                    A_copy->matrix[j][k] -= coff * A_copy->matrix[i][k];
                }
                b_copy->matrix[j][0] -= coff * b_copy->matrix[i][0];
            }
        }
    }

    for(int i=A_copy->n_col-1; i>0; i--){
        float pivot = A_copy->matrix[i][i];
        
        for(int j=i-1; j>=0; j--){
            if(A_copy->matrix[j][i] != 0){
                float coff = A_copy->matrix[j][i] / pivot;
                
                for(unsigned int k=0; k<A_copy->n_col; k++){
                    A_copy->matrix[j][k] -= coff * A_copy->matrix[i][k];
                }
                b_copy->matrix[j][0] -= coff * b_copy->matrix[i][0];
            }
        }
    }
    
    for(unsigned int i=0; i<A_copy->m_row; i++){
        float pivot = A_copy->matrix[i][i];

        for(unsigned int j=i; j<A_copy->n_col; j++){
            if(A_copy->matrix[i][j] != 0){
                A_copy->matrix[i][j] /= pivot;
            }
        }
        b_copy->matrix[i][0] /= pivot;
    }

    return b_copy;
}

/*
*   Esegue una deep copy della matrice passata come parametro
*   ritorna la copia della matrice
*/
matrix::Matrix* matrix::deepCopy(Matrix* A){

    struct matrix::Matrix* A_copy;
    A_copy = new matrix::Matrix;
    
    A_copy->m_row = A->m_row;
    A_copy->n_col = A->n_col;
    float ElementOfA_copy[A_copy->m_row * A_copy->n_col];

    unsigned int arrayElement_index = 0;
    for(unsigned int i=0; i<A->m_row; i++){
        for(unsigned int j=0; j<A->n_col; j++){
            ElementOfA_copy[arrayElement_index] = A->matrix[i][j];
            arrayElement_index += 1;
        }
    }

    matrix::newMatrix(A_copy, ElementOfA_copy);
    return A_copy;
}


/*
*   Dealloca una matrice precedentemente allocata da newMatrix
*/
void matrix::deallocMatrix(Matrix* matrix){
    for(unsigned int i=0; i<matrix->m_row; i++)
        free(matrix->matrix[i]);
    free(matrix->matrix);
    free(matrix);
}