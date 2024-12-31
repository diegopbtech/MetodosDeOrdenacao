#include <stdio.h>
#include <iostream>
#include <ctime>
#include <chrono>
#include <fstream>
#include <vector>

using namespace std;
using namespace chrono;

int main() {

    // LENDO O ARQUIVO DE TESTE (ENTRADA)
    ifstream teste("teste.in");

    cout << "Lendo arquivo 'teste.in'...\n\n";

    if (!teste) {
        cerr << "Erro ao abrir o arquivo de entrada!" << endl;
    }

    vector<int> numerosDoArray;

    int num;
    
    while (teste >> num) {
        numerosDoArray.push_back(num);
    }

    teste.close();

    cout << "Ordenando pelo método Seletion Sort... \n\n";

    auto iniciarSelectionSort = high_resolution_clock::now(); // INICIANDO O TEMPO DE EXECUÇÃO

    // PROCESSOS DE ORDENAÇÃO

    // SELECTION SORT
    int pos = 1; // O MÉTODO SELECTION SORT IRÁ COMEÇAR A PARTIR DA SEGUNDA POSIÇÃO DO VECTOR
    int aux; // SERÁ USADA UMA VARIÁVEL AUXILIAR PARA ARMAZENAR A POSIÇÃO DO VETOR E FAZER A TROCA

    vector<int> OrdenacaoSelectionSort = numerosDoArray;

    while(pos!=OrdenacaoSelectionSort.size()){
        for(int i = pos; i > 0; i--){
            if(OrdenacaoSelectionSort[i]<OrdenacaoSelectionSort[i-1]){
                aux = OrdenacaoSelectionSort[i]; // ARMAZENA NA 
                OrdenacaoSelectionSort[i] = OrdenacaoSelectionSort[i-1];
                OrdenacaoSelectionSort[i-1] = aux;
            }
        }
        pos++;
    }

    auto pararSeletionSort = high_resolution_clock::now();  // FINALIZANDO O TEMPO DE EXECUÇÃO
    auto duracaoSelectionSort = duration_cast<microseconds>(pararSeletionSort - iniciarSelectionSort);

    cout << "Ordenando pelo método Insertion Sort... \n\n";

    auto iniciarInsertionSort = high_resolution_clock::now(); // INICIANDO O TEMPO DE EXECUÇÃO

    // INSERTION SORT
    vector<int> OrdenacaoInsertionSort;
    OrdenacaoInsertionSort.push_back(numerosDoArray[0]);

    for (int p = 1; p < numerosDoArray.size(); p++) {
        int a = numerosDoArray[p]; // PEGA O VALOR DO PRÓXIMO ELEMENTO DO VECTOR A SER INSERIDO
        int m = p - 1; // POSIÇÃO DO ÚLTIMO ELEMENTO INSERIDO NO VECTOR

        // INSERINDO UM VALOR NA ÚLTIMA POSIÇÃO PARA RESOLVER PROBLEMA DO BUG
        OrdenacaoInsertionSort.push_back(a);

        // PERCORRENDO O VECTOR E VERIFICANDO SE O VALOR A SER INSERIDO É MENOR QUE O LIDO
        // CASO VERDADEIRO, O VALOR LIDO É MOVIDO PARA A POSIÇÃO SEGUINTE
        while (m >= 0 && OrdenacaoInsertionSort[m] > a){
            OrdenacaoInsertionSort[m + 1] = OrdenacaoInsertionSort[m];
            m--;
        }
        // POR FIM, PERCORRENDO OU NÃO O LOOP, O VALOR É FINALMENTE INSERIDO NO VECTOR E NA POSIÇÃO CORRETA
        OrdenacaoInsertionSort[m + 1] = a;
    }

    auto pararInsertionSort = high_resolution_clock::now();  // FINALIZANDO O TEMPO DE EXECUÇÃO
    auto duracaoInsertionSort = duration_cast<microseconds>(pararInsertionSort - iniciarInsertionSort);

    cout << "Tempo de execução do Selection Sort: " << duracaoSelectionSort.count() << " microsegundos." << endl;
    cout << "Tempo de execução do Insertion Sort: " << duracaoInsertionSort.count() << " microsegundos." << endl;

    // SALVANDO OS VALORES JÁ ORDENADAS POR CADA UM DOS MÉTODOS EM ARQUVIOS DIFERENTES

    // SALVANDO OS ORDENADOS NO SELETION SORT
    ofstream sSort("SelectionSort.txt");

    if (!sSort) {
        cerr << "Erro ao abrir o arquivo de saída!" << endl;
        return 1;
    }

    for (int num : OrdenacaoSelectionSort) {
        sSort << num << endl;
    }

    sSort.close();

    // SALVANDO OS ORDENADOS NO INSERTION SORT
    ofstream iSort("InsertionSort.txt");

    if (!iSort) {
        cerr << "Erro ao abrir o arquivo de saída!" << endl;
        return 1;
    }

    for (int num : OrdenacaoInsertionSort) {
        iSort << num << endl;
    }

    iSort.close();

    return 0;
}