/* 
 * Nome: Gustavo Curado Ribeiro 
 * NUSP: 14576732
 * SCC0210 - Laboratório de Algoritmos Avançados I
 * Exercício 07: Jogando Todos os Dias
*/

#include <iostream>
#include <algorithm>
#include <sstream>
#include <utility>
#include <vector>

std::pair<int,int> choose_games(std::vector<int> game_prices, int M);

int main()
{
	int N; //Número de jogos disponíveis
	int M; //Dinheiro disponível

	while (std::cin >> N) 
	{
		std::string texto;

		std::cin.ignore();
		getline(std::cin, texto);
		std::cin >> M;

		std::vector<int> game_prices;
		std::stringstream ss(texto);

		for (int i = 0; i < N; i++)
		{
			int price;
			ss >> price;

			game_prices.push_back(price);
		}

		std::pair<int,int> solution = choose_games(game_prices, M);

		std::cout << "Joaquina deve comprar os jogos de preços " << solution.first << " e " << solution.second << ".\n\n";
	}

	return 0;
}


std::pair<int,int> choose_games(std::vector<int> game_prices, int M)
{
	//Ordena o vetor de preços em ordem crescente
	std::sort(game_prices.begin(), game_prices.end(), [](auto a, auto b)
	{
		return a < b;
	});

	std::vector<std::pair<int,int>> possible_solutions;

	//Esse for loop vai encontrar, no vetor de preços, as combinações de dois preços que se igualam a M 
	for (int i = 0, j = game_prices.size()-1; i < j; )
	{
		int price_1 = game_prices.at(i);
		int price_2 = game_prices.at(j);

		if (price_1 + price_2 == M)
		{
			possible_solutions.push_back(std::make_pair(price_1, price_2));
			i++;
			j--;
		}
		else if (price_1 + price_2 < M)
		{
			i++;
		}
		else
		{
			j--;
		}
	}

	std::pair<int,int> solution = possible_solutions.at(0);

	//Se houver mais de uma solução, seleciona a que tem a menor diferença de preço entre os dois jogos
	if (possible_solutions.size() > 1)
	{
		for (auto poss_solution : possible_solutions)
		{
			int price_diff_1 = solution.second - solution.first;
			int price_diff_2 = poss_solution.second - poss_solution.first;

			if (price_diff_1 > price_diff_2)
				solution = poss_solution;
		}
	}

	return solution;
}
