/* 
 * Nome: Gustavo Curado Ribeiro 
 * NUSP: 14576732
 * SCC0210 - Laboratório de Algoritmos Avançados I
 * Mini-Maratona E2: Vendendo Loot para Armadura Lendária
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Função de backtracking para encontrar o menor número de peças de loot para atingir exatamente Gils
void Calculate_optimal_solution(int& minimum_ammount, int current, int Gils, int loot_types, const vector<int>& loot_values, bool& solution) {

    // Caso base: valor exato foi alcançado
    if (Gils == 0) {
        if (current < minimum_ammount) {
            minimum_ammount = current; // Atualiza a menor quantidade de peças usada
        }
        solution = true; // Indica que foi encontrada uma solução válida
        return;
    }

    // Poda: se já usamos mais peças do que a melhor solução encontrada até agora, aborta este caminho
    if (current > minimum_ammount) {
        return;
    }

    // Tenta todas as peças possíveis que ainda cabem no valor restante de Gils
    for (int i = 0; i < loot_types; i++) {
        if (loot_values[i] <= Gils) { // Se a peça cabe no valor restante
            Gils -= loot_values[i];   // Usa a peça (reduz Gils)
            current++;                // Conta a peça

            Calculate_optimal_solution(minimum_ammount, current, Gils, loot_types, loot_values, solution); // Chamada recursiva

            current--;                // Desfaz escolha (backtracking)
            Gils += loot_values[i];   // Devolve Gils
        }
    }
}

int main () {

    int Gils, loot_types;

    // Loop de múltiplos casos de teste até encontrar entrada de parada (0 0)
    while (true) {
        cin >> Gils >> loot_types;

        if (Gils == 0 and loot_types == 0) {
            break; // Condição de parada
        }

        vector loot_values (loot_types, 0); // Vetor para armazenar os valores das peças

        for (int i = 0; i < loot_types; i++) {
            cin >> loot_values[i]; // Lê os valores de cada tipo de loot
        }

        // Ordena os valores em ordem decrescente para priorizar peças maiores primeiro
        sort(loot_values.begin(), loot_values.end(), greater());

        int minimum_ammount = static_cast<int>(1e10); // Inicializa o valor mínimo com um número alto
        bool solution = false; // Indica se foi possível encontrar uma solução
        int current = 0; // Contador de peças usadas até o momento

        // Chamada da função de backtracking
        Calculate_optimal_solution(minimum_ammount, current, Gils, loot_types, loot_values, solution);

        // Imprime o resultado conforme foi ou não possível alcançar exatamente Gils
        if (solution) {
            cout << minimum_ammount << endl;
        }
        else {
            cout << "-1" << endl;
        }
    }

    return 0;
}
