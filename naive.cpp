/*
Exercício de Programação de Desafios de Programação 1
Professor Doutor Alexandre

Autores:
Lucas Pipa Cervera                  8094403
Paulo Henrique Freitas Guimarães    9390361

Implementação do algoritmo de busca Naive
*/


// Baseado em implementação no GeeksforGeeks:
// https://www.geeksforgeeks.org/naive-algorithm-for-pattern-searching/



// Importando módulos necessários
#include <iostream>

using namespace std;

bool busca(string padrao, string texto) {
    int tamanho_padrao = padrao.length();
    int tamanho_texto = texto.length();

    int j;
    for(int i=0; i<=tamanho_texto - tamanho_padrao; i++) {
        for(j=0; j<tamanho_padrao; j++)
            if(texto[i+j] != padrao[j])
                break;
        
        if(j == tamanho_padrao)
            return true;
    }

    return false;
}

int main() {
    string texto = "GEEKS FOR GEEKS";
    string padrao = "GEEK";

    bool achou = busca(padrao, texto);
    if(achou)
        cout << "Achou" << endl;
    else
        cout << "Não achou" << endl;
}