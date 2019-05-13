/*
Exercício de Programação de Desafios de Programação 1
Professor Doutor Alexandre

Autores:
Lucas Pipa Cervera                  8094403
Paulo Henrique Freitas Guimarães    9390361

Implementação do algoritmo de busca Rabin-Karp
*/


// Baseado em implementação no GeeksforGeeks:
// https://www.geeksforgeeks.org/rabin-karp-algorithm-for-pattern-searching/



// Importando módulos necessários
#include <iostream>

using namespace std;

#define d 256

bool busca(string padrao, string texto, int q) {
    bool achou = false;
    int tamanho_padrao = padrao.length();
    int tamanho_texto = texto.length();

    int i, j;
    int hash_padrao = 0, hash_texto = 0, h = 1;

    for(i=0; i<tamanho_padrao-1; i++)
        h = (h * d) % q;

    for(i=0; i<tamanho_padrao; i++) {
        hash_padrao = (d * hash_padrao + padrao[i]) % q;
        hash_texto = (d * hash_texto + texto[i]) % q;
    }

    for(i=0; i<=tamanho_texto-tamanho_padrao; i++) {
        if(hash_padrao == hash_texto) {
            for(j=0; j<tamanho_padrao; j++)
                if(texto[i+j] != padrao[j])
                    break;
            
            if(j == tamanho_padrao)
                achou = true;
        }

        if(i < tamanho_texto-tamanho_padrao) {
            hash_texto = (d * (hash_texto - texto[i] * h) + texto[i+tamanho_padrao]) % q;

            if(hash_texto < 0)
                hash_texto = (hash_texto + q);
        }
    }

    return achou;
}

int main() {
    char texto[] = "GEEKS FOR GEEKS";
    char padrao[] = "GOK";
    int q = 101;

    bool achou = busca(padrao, texto, q);
    if(achou)
        cout << "Achou" << endl;
    else
        cout << "Não achou" << endl;
}