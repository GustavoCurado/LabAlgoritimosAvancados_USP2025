/*
 * Nome: Gustavo Curado Ribeiro 
 * NUSP: 14576732
 * SCC0210 - Laboratório de Algoritmos Avançados I
 * Exercício 12: Ajuda para Separar LEGOs
*/

#include <iostream>
#include <vector>
#include <climits>

int minimal_block_cost(int start, int end, std::vector<int> cut_positions, std::vector<std::vector<int>>& minimal_costs);

int main()
{
	while (true)
	{
		int l; //Comprimento do bloco
		std::cin >> l;

		if (l == 0)
			break;

		int n; //Número de cortes
		std::cin >> n;

		std::vector<int> cut_positions; //Lista que contém a posição de cada corte
		for (int i = 0; i < n; i++)
		{
			int c;
			std::cin >> c;
			cut_positions.push_back(c);
		}

		//Matriz que guarda o custo mínimo de um sub-bloco, dada a sua posição inicial e final
		std::vector<std::vector<int>> minimal_costs(l+1, std::vector<int>(l+1, -1));

		//Obtém o menor custo de para realizar todos os cortes
		int solution = minimal_block_cost(0, l, cut_positions, minimal_costs);

		std::cout << "O custo mínimo de separação é " << solution << "." << std::endl;
	}

	return 0;
}


int minimal_block_cost(int start, int end, std::vector<int> cut_positions, std::vector<std::vector<int>>& minimal_costs)
{
	//Se o custo mínimo dos cortes nessa barra não estiverem já armazenados...
	if (minimal_costs[start][end] == -1)
	{
		//Inicialização de variáveis
		int number_cuts = 0;
		int min_cost = INT_MAX;

		//Itera por todas as possibilidades de corte na barra, decidindo recursivamente qual corte é a opção menos custosa
		for (auto c : cut_positions)
		{
			//Um corte só é possível na barra se houver uma posição de corte na lista dentro do intervalo (start, end)
			if (c <= start)
				continue;
			else if (c >= end)
				break;

			number_cuts++;

			//Se o custo mínimo para essa barra não estiver já armazenada, o custo será calculado como o
			//custo do corte a ser feito somado com o custo total dos cortes das duas barras que vão se formar.
			int cost = (end - start) + minimal_block_cost(start, c, cut_positions, minimal_costs) + minimal_block_cost(c, end, cut_positions, minimal_costs);

			if (cost < min_cost)
				min_cost = cost;
		}

		//Armazena o valor de custo dos cortes na barra para possível uso futuro na recursão
		minimal_costs[start][end] = (number_cuts > 0) ? min_cost : 0;
	}

	return minimal_costs[start][end];
}
