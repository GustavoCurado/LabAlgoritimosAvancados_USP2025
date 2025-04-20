/*
 * Nome: Gustavo Curado Ribeiro 
 * NUSP: 14576732
 * SCC0210 - Laboratório de Algoritmos Avançados I
 * Exercício 13: O Caminho Ótimo na República Suja
*/

#include <iostream>
#include <vector>

int main()
{
	int N;
	std::cin >> N;

	for (int z = 0; z < N; z++)
	{
		int w; //Largura do ambiente
		int h; //Altura do ambiente
		std::cin >> l >> h;

		int xo; //Posição horizontal inicial do robô
		int yo; //Posição vertical inicial do robô
		std::cin >> xo >> yo;

		int n_sujeiras; //Número de montes de sujeira no chão
		std::cin >> n_sujeiras;

		std::vector<std::pair<int>> coord_sujeiras; //Coordenadas para cada monte de sujeira
		for (int i = 0; i < n_sujeiras; i++)
		{
			int x_sujeira;
			int y_sujeira;
			std::cin >> x_sujeira >> y_sujeira;

			coord_sujeiras.push_back(std::make_pair(x_sujeira, y_sujeira));
		}


	}

	return 0;
}
