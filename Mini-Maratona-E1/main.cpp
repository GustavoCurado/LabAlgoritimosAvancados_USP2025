/* 
 * Nome: Gustavo Curado Ribeiro 
 * NUSP: 14576732
 * SCC0210 - Laboratório de Algoritmos Avançados I
 * Mini-Maratona E1: Wi-Fi para Pokémon GO Fests
*/


#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int routers;
    float length, width;

    while (true) {
        cin >> routers >> length >> width;

        // Se entrada for "0 0 0", termina o programa
        if (routers == 0 and length == 0 and width == 0) {
            break;
        }

        vector<pair<float, float>> router; // Armazena os roteadores válidos (posição, raio)

        for (int i = 0; i < routers; i++) {
            float radius, position;
            cin >> position >> radius;

            // Descarta roteadores cujo raio não cobre metade da largura do corredor
            if (radius < width / 2) {
                continue;
            }

            bool add_or_not = true;

            // Remove roteadores redundantes (totalmente contidos em outro) ou ignora se for contido
            for (auto it = router.begin(); it != router.end(); ) {
                const float distance = fabs(it->first - position);

                // Novo roteador está contido em um já adicionado
                if (distance + radius <= it->second) {
                    add_or_not = false;
                    break;
                }

                // Um roteador já adicionado está contido no novo → remove o antigo
                if (distance + it->second <= radius) {
                    it = router.erase(it);
                    continue;
                }

                ++it;
            }

            // Adiciona o roteador se for útil
            if (add_or_not) {
                router.emplace_back(position, radius);
            }
        }

        // Ordena os roteadores pela posição (menor x primeiro)
        sort(router.begin(), router.end());

        pair<float, float> first; // Melhor roteador inicial
        pair<float, float> last;  // Melhor roteador final
        bool found_first = false;
        bool found_last = false;

        // Escolhe o melhor roteador à direita que cobre o início do corredor
        for (const auto & it : router) {
            if (powf(it.second, 2) >= powf(it.first, 2) + powf(width / 2, 2)) {
                first = it;
                found_first = true;
            }
        }

        // Escolhe o melhor roteador à esquerda que cobre o final do corredor
        for (const auto& it : router) {
            if (powf(it.second, 2) >= powf(length - it.first, 2) + powf(width / 2, 2)) {
                last = it;
                found_last = true;
                break;
            }
        }

        // Verifica se o primeiro roteador cobre também o final — caso especial
        if (powf(first.second, 2) >= powf(length - first.first, 2) + powf(width / 2, 2)) {
            last = first;
        }

        // Se não encontrou roteadores viáveis para início ou fim, imprime -1
        if (!found_first or !found_last) {
            cout << -1 << endl;
            continue;
        }

        // Se início e fim forem o mesmo roteador
        if (first == last) {
            cout << "1" << endl;
            continue;
        }

        int nrouters = 1; // Contador de roteadores usados (começa com o primeiro)
        auto last_selected_router = first;

        // Loop para escolher os roteadores intermediários
        while (true) {
            auto it = find(router.begin(), router.end(), last_selected_router);
            ++it; // Começa a busca no próximo roteador

            pair<float, float> best_choice = make_pair(0, 0);
            bool found_router = false;

            for (; it != router.end(); ++it) {
                float distance = fabs(it->first - last_selected_router.first);

                // Se as circunferências não se tocam ou não se sobrepõem, pare
                if (distance >= it->second + last_selected_router.second) {
                    break;
                }

                // Calcula a altura da interseção entre as duas circunferências
                float aux = (powf(last_selected_router.second, 2) - powf(it->second, 2) + powf(distance, 2)) / (2 * distance);
                float height = sqrtf(powf(last_selected_router.second, 2) - powf(aux, 2));

                // Se a interseção não cobre a largura do corredor, pare
                if (height < width / 2) {
                    break;
                }

                // Não considerar roteadores além do último necessário
                if (it->first > last.first) {
                    break;
                }

                best_choice = *it;
                found_router = true;
            }

            last_selected_router = best_choice;

            // Se chegou ao roteador final, termina
            if (best_choice == last) {
                nrouters++;
                break;
            }

            // Se não achou nenhum roteador viável, falha
            if (!found_router) {
                nrouters = -1;
                break;
            }

            nrouters++;
        }

        cout << nrouters << endl;
    }

    return 0;
}
