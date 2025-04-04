/* 
 * Nome: Gustavo Curado Ribeiro 
 * NUSP: 14576732
 * SCC0210 - Laboratório de Algoritmos Avançados I
 * Exercício 08: Misturando Fandom’s
*/

#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <cmath>

void valid_combinations(int* n_combinations, int n, std::vector<int> seated_fans, std::vector<std::vector<int>> restrictions);

int main()
{
	int n, m;

	while (std::cin >> n >> m)
	{
		if (m == 0 && n == 0)
			break;

		std::vector<std::vector<int>> restrictions;

		for (int i = 0; i < m; i++)
		{
			int fan_1;
			int fan_2;
			int distance;

			std::cin >> fan_1 >> fan_2 >> distance;

			restrictions.push_back({fan_1, fan_2, distance});
		}

		std::vector<int> empty_vector;

		int n_combinations = 0;
		valid_combinations(&n_combinations, n, empty_vector, restrictions);

		std::cout << n_combinations << std::endl;
	}


	return 0;
}


void valid_combinations(int* n_combinations, int n, std::vector<int> seated_fans, std::vector<std::vector<int>> restrictions)
{
	if (n != seated_fans.size())
	{
		for (int i = 0; i < n; i++)
		{
			if (std::find(seated_fans.begin(), seated_fans.end(), i) != seated_fans.end())
				continue;

			std::vector<int> new_seated_fans = seated_fans;
			new_seated_fans.push_back(i);

			valid_combinations(n_combinations, n, new_seated_fans, restrictions);
		}
	}
	else
	{
		bool restrictions_met = true;

		for (auto restriction : restrictions)
		{
			int fan_1 = restriction.at(0);
			int fan_2 = restriction.at(1);
			int distance = restriction.at(2);

			auto it_1 = std::find(seated_fans.begin(), seated_fans.end(), fan_1);
			auto it_2 = std::find(seated_fans.begin(), seated_fans.end(), fan_2);

			int distance_between_fans = std::abs(std::distance(it_1, it_2));

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

		if (restrictions_met)
			(*n_combinations)++;
	}
}
