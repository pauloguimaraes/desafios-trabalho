/*
Exercício de Programação de Desafios de Programação 1
Professor Doutor Alexandre da Silva Feire

Autores:
Lucas Pipa Cervera                  8094403
Paulo Henrique Freitas Guimarães    9390361

Implementação do algoritmo de busca com automatos finitos
*/


// Baseado em implementação no GeeksforGeeks:
// https://www.geeksforgeeks.org/finite-automata-algorithm-for-pattern-searching/



// Importando módulos necessários
#include <iostream> 

using namespace std;

#define N_CARACTERES 256



/**
 ** Recupera o próximo estado do automato
 **
 ** @param padrao: Padrão que temos como base
 ** @param tamanho_padrao: Tamanho do padrão que temos como base
 ** @param estado: Último estado conhecido
 ** @param x: posição do estado que estamos buscando
 **/
int get_proximo_estado(string padrao, int tamanho_padrao, int estado, int x) {
    // Se for o mesmo caratere, apenas incrementados o estado
    if(estado < tamanho_padrao && x == padrao[estado]) 
        return estado+1;
    
    int proximo_estado, i;

    // proximo_estado guarda o maior prefixo que é sufixo no texto restante
    // Inicia do maior valor possível e para quando encontra um prefixo que também seja sufixo
    for(proximo_estado = estado; proximo_estado > 0; proximo_estado--) {
        if(padrao[proximo_estado-1] == x) {
            for(i = 0; i < proximo_estado-1; i++)
                if(padrao[i] != padrao[estado-proximo_estado+1+i])
                    break;

            if(i == proximo_estado-1)
                return proximo_estado;
        }
    }

    return 0;
}

/**
 ** Monta a tabela do automato finito para o padrão estipulado
 **
 ** @param padrao: Padrão que será usado para montar o automato
 ** @param tamanho_padrao: Tamanho do padrão que está sendo usado
 ** @param automato: Matriz que está armazenando o automato
 **/
void computa_automato(string padrao, int tamanho_padrao, int automato[][N_CARACTERES]) {
    int estado, x;

    for(estado = 0; estado <= tamanho_padrao; ++estado)
        for(x = 0; x < N_CARACTERES; ++x)
            automato[estado][x] = get_proximo_estado(padrao, tamanho_padrao, estado, x);
}

/**
 ** Método de busca
 **
 ** @param padrao: Texto padrão que estamos buscando
 ** @param texto: Texto onde o padrão será buscado
 **/
bool busca(string padrao, string texto) {
    int tamanho_padrao = padrao.length();
    int tamanho_texto = padrao.length();

    int automato[tamanho_padrao+1][N_CARACTERES];

    computa_automato(padrao, tamanho_padrao, automato);

    int i, estado = 0;
    // Processa o texto sobre o automato formado
    for(i = 0; i < tamanho_texto; i++) {
        estado = automato[estado][texto[i]];
        
        if(estado == tamanho_padrao)
            return true;
    }

    return false;
}



/**
 ** Método principal da aplicação
 **/
int main() {
    string texto = "GEEKS FOR GEEKS";
    string padrao= "GOK";
    int q = 101;

    bool achou = busca(padrao, texto);
    if(achou)
        cout << "Achou" << endl;
    else
        cout << "Não achou" << endl;
}