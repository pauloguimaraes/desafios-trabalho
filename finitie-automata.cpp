/*
Exercício de Programação de Desafios de Programação 1
Professor Doutor Alexandre

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

int get_proximo_estado(string padrao, int tamanho_padrao, int estado, int x) {
    if(estado < tamanho_padrao && x == padrao[estado]) 
        return estado+1;
    
    int ns, i;

    for(ns = estado; ns > 0; ns--) {
        if(padrao[ns-1] == x) {
            for(i = 0; i < ns-1; i++)
                if(padrao[i] != padrao[estado-ns+1+i])
                    break;

            if(i == ns-1)
                return ns;
        }
    }

    return 0;
}

void computa_automato(string padrao, int tamanho_padrao, int automato[][N_CARACTERES]) {
    int estado, x;

    for(estado = 0; estado <= tamanho_padrao; ++estado)
        for(x = 0; x < N_CARACTERES; ++x)
            automato[estado][x] = get_proximo_estado(padrao, tamanho_padrao, estado, x);
}

bool busca(string padrao, string texto) {
    int tamanho_padrao = padrao.length();
    int tamanho_texto = padrao.length();

    int automato[tamanho_padrao+1][N_CARACTERES];

    computa_automato(padrao, tamanho_padrao, automato);

    int i, estado = 0;
    for(i = 0; i < tamanho_texto; i++) {
        estado = automato[estado][texto[i]];
        
        if(estado == tamanho_padrao)
            return true;
    }

    return false;
}

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