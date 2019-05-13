/*
Exercício de Programação de Desafios de Programação 1
Professor Doutor Alexandre da Silva Freire

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

// Tamanho do alfabeto usado
#define TAMANHO_DO_ALFABETO 256
#define NUMERO_PRIMO 101



/**
 ** Método de busca
 **
 ** @param padrao: Texto padrão que estamos buscando
 ** @param texto: Texto onde o padrão será buscado
 ** @param q: Número primo que será usado para o cálculo do hash
 **/
bool busca(string padrao, string texto, int q) {
    bool achou = false;
    int tamanho_padrao = padrao.length();
    int tamanho_texto = texto.length();

    int i, j;
    int hash_padrao = 0, hash_texto = 0, h = 1;

    for(i=0; i<tamanho_padrao-1; i++)
        h = (h * TAMANHO_DO_ALFABETO) % q;

    // Calcula o hash do padrão e da primeira janela no texto
    for(i=0; i<tamanho_padrao; i++) {
        hash_padrao = (TAMANHO_DO_ALFABETO * hash_padrao + padrao[i]) % q;
        hash_texto = (TAMANHO_DO_ALFABETO * hash_texto + texto[i]) % q;
    }

    // Avança no texto
    for(i=0; i<=tamanho_texto-tamanho_padrao; i++) {
        if(hash_padrao == hash_texto) {
            // Checa os caracteres individualmente
            for(j=0; j<tamanho_padrao; j++)
                if(texto[i+j] != padrao[j])
                    break;
            
            // Se tudo bateu, achamos um padrão
            if(j == tamanho_padrao)
                achou = true;
        }

        // Calcula o hash para a próxima janela
        if(i < tamanho_texto-tamanho_padrao) {
            hash_texto = (TAMANHO_DO_ALFABETO * (hash_texto - texto[i] * h) + texto[i+tamanho_padrao]) % q;

            // Converte o hash para positivo caso seja negativo
            if(hash_texto < 0)
                hash_texto = (hash_texto + q);
        }
    }

    return achou;
}



/**
 ** Método principal da aplicação
 **/
int main() {
    string texto = "GEEKS FOR GEEKS";
    string padrao= "GOK";

    bool achou = busca(padrao, texto, NUMERO_PRIMO);
    if(achou)
        cout << "Achou" << endl;
    else
        cout << "Não achou" << endl;
}