/* 
 * Nome: Gustavo Curado Ribeiro 
 * NUSP: 14576732
 * SCC0210 - Laboratório de Algoritmos Avançados I
 * Exercício 08: Misturando Fandom’s
*/

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cmath>

int valid_combinations(int n, std::vector<std::vector<int>> restrictions);

int main()
{
	int n; //Número de fãs
	int m; //Número de restrições sociais

	while (std::cin >> n >> m)
	{
		//Se esses valores forem lidos como zero, é porque os casos de teste acabaram
		if (m == 0 && n == 0)
			break;

		std::vector<std::vector<int>> restrictions;

		for (int i = 0; i < m; i++)
		{
			int fan_1;
			int fan_2;
			int distance;

			std::cin >> fan_1 >> fan_2 >> distance;

			//Armazena a restrição de distância dada no input
			restrictions.push_back({fan_1, fan_2, distance});
		}

		//Retorna o número de combinações de fãs sentados possíveis
		int n_combinations = valid_combinations(n, restrictions);

		std::cout << n_combinations << std::endl;
	}

	return 0;
}


int valid_combinations(int n, std::vector<std::vector<int>> restrictions)
{
	//Armazena a ordem com que os fãs estão sentados
	std::vector<int> seated_fans;

	//Inicia o vetor com uma sequência crescente para o funcionamento da função std::next_permutation()
	for (int i = 0; i < n; i++)
	{
		seated_fans.push_back(i);
	}

	int n_combinations = 0;

	do
	{
		//Inicialização de variável
		bool restrictions_met = true;

		for (auto restriction : restrictions)
		{
			int fan_1 = restriction.at(0);
			int fan_2 = restriction.at(1);
			int distance = restriction.at(2);

			//Iteradores dos dois fãs indicados pela restrição
			auto it_1 = std::find(seated_fans.begin(), seated_fans.end(), fan_1);
			auto it_2 = std::find(seated_fans.begin(), seated_fans.end(), fan_2);

			int distance_between_fans = std::abs(std::distance(it_1, it_2));

			//Se a distância ultrapassar o máximo ou for menor que o
			//mínimo estabelecido, a permutação atual fere a restrição
			if (distance > 0)
			{
				if (distance_between_fans > distance)
					restrictions_met = false;
			}
			else
			{
				if (distance_between_fans < -distance)
					restrictions_met = false;
			}
		}

		//Se a restriçào foi obedecida, essa combinação é uma solução do problema
		if (restrictions_met)
			n_combinations++;

	} while (std::next_permutation(seated_fans.begin(), seated_fans.end()));

	return n_combinations;
}
