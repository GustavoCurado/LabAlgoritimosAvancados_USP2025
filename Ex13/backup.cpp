/*
 * Nome: Gustavo Curado Ribeiro 
 * NUSP: 14576732
 * SCC0210 - Laboratório de Algoritmos Avançados I
 * Exercício 13: O Castd::minho Ótimo na República Suja
*/

#include <iostream>
#include <climits>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <queue>
#include <map>


void distancia_ate_ponto(std::pair<int,int> dimensoes, std::pair<int,int> pos_inicial, std::map<std::pair<int, int>, std::map<std::pair<int, int>, int>>& matriz_distancias);
//void bfs(std::pair<int,int> dimensoes, std::pair<int,int> pos_inicial, std::map<std::pair<int, int>, std::map<std::pair<int, int>, int>>& matriz_distancias);
//std::pair<int,int> muda_posicao(std::pair<int,int> dimensoes, std::pair<int,int> posicao, int direcao, bool& direcao_eh_valida);
int tsp(std::pair<int,int> pos_inicial, std::vector<std::pair<int, int>> coord_sujeiras, std::map<std::pair<int, int>, std::map<std::pair<int, int>, int>> matriz_distancias);

int main()
{
	int N;
	std::cin >> N;

	for (int z = 0; z < N; z++)
	{
		int l; //Largura do ambiente
		int h; //Altura do ambiente
		std::cin >> l >> h;

		int xo; //Posição horizontal inicial do robô
		int yo; //Posição vertical inicial do robô
		std::cin >> xo >> yo;

		int n_sujeiras; //Número de montes de sujeira no chão
		std::cin >> n_sujeiras;

		std::vector<std::pair<int, int>> coord_sujeiras; //Coordenadas para cada monte de sujeira
		for (int i = 0; i < n_sujeiras; i++)
		{
			int x_sujeira;
			int y_sujeira;
			std::cin >> x_sujeira >> y_sujeira;

			coord_sujeiras.push_back(std::make_pair(x_sujeira, y_sujeira));
		}

		//Dado dois pontos determinados por seus pares de coordenadas, armazena a distância mínima entre eles
		std::map<std::pair<int, int>, std::map<std::pair<int, int>, int>> matriz_distancias;

		//std::cout << "z="<<z<<": "<<l<<" "<<h<<std::endl;

		for (int i = 1; i <= h; i++)
		{
			for (int j = 1; j <= l; j++)
			{
				//Esse último for garante que meu código não falhe caso tenha um ponto out-of-bounds no input
				//(Na verdade, ele falha mesmo assim, mas melhor que nada)
				int max_x = l;
				int max_y = h;
				for (int it = 0; it < coord_sujeiras.size(); it++)
				{
					max_x = std::max(max_x, coord_sujeiras[it].first);
					max_y = std::max(max_y, coord_sujeiras[it].second);
					//if (z==5 && it==6) std::cout << "max_x=" << max_x << ", max_y==" << max_y << std::endl;
				}

				distancia_ate_ponto(std::make_pair(max_x,max_y), std::make_pair(j,i), matriz_distancias);
			}
		}

		std::pair<int,int> pos_inicial(xo,yo);

		int solucao = tsp(pos_inicial, coord_sujeiras, matriz_distancias);

		std::cout << "A menor rota tem tamanho " << solucao << ".\n";
	}

	return 0;
}


void distancia_ate_ponto(std::pair<int,int> dimensoes, std::pair<int,int> pos_inicial, std::map<std::pair<int, int>, std::map<std::pair<int, int>, int>>& matriz_distancias)
{
	int l = dimensoes.first;
	int h = dimensoes.second;

	auto teste1 = std::make_pair(12, 12);
	auto teste2 = std::make_pair(14, 15);

	for (int i = 1; i <= h; i++)
	{
		for (int j = 1; j <= l; j++)
		{
			matriz_distancias[pos_inicial][std::make_pair(j,i)] = abs(pos_inicial.first - j) + abs(pos_inicial.second - i);
		}
	}
}

/*void bfs(std::pair<int,int> dimensoes, std::pair<int,int> pos_inicial, std::map<std::pair<int, int>, std::map<std::pair<int, int>, int>>& matriz_distancias)
{
	std::queue<std::pair<int, int>> fila;
	std::map<std::pair<int, int>, int> distancias;

	fila.push(pos_inicial);
	distancias[pos_inicial] = 0;
	
	while (!fila.empty())
	{
		std::pair<int,int> pos_atual = fila.front();
		fila.pop();

		for (int direcao = 0; direcao < 4; direcao++)
		{
			bool direcao_eh_valida;
			std::pair<int,int> pos_vizinha = muda_posicao(dimensoes, pos_atual, direcao, direcao_eh_valida);

			if (!direcao_eh_valida)
				continue;

			if (distancias.find(pos_vizinha) == distancias.end())
			{
				distancias[pos_vizinha] = distancias[pos_atual] + 1;
				fila.push(pos_vizinha);
			}
		}
	}

	matriz_distancias[pos_inicial] = distancias;
}*/


/*std::pair<int,int> muda_posicao(std::pair<int,int> dimensoes, std::pair<int,int> posicao, int direcao, bool& direcao_eh_valida)
{
	std::pair<int,int> nova_posicao = posicao;
	direcao_eh_valida = true;

	switch(direcao)
	{
	case 0:
		if (posicao.first < dimensoes.first)
			++nova_posicao.first;
		else
			direcao_eh_valida = false;
		break;
	case 1:
		if (posicao.second < dimensoes.second)
			++nova_posicao.second;
		else
			direcao_eh_valida = false;
		break;
	case 2:
		if (posicao.first > 1)
			--nova_posicao.first;
		else
			direcao_eh_valida = false;
		break;
	case 3:
		if (posicao.second > 1)
			--nova_posicao.second;
		else
			direcao_eh_valida = false;
		break;
	default:
		break;
	}

	return nova_posicao;
}*/


int tsp(std::pair<int,int> pos_inicial, std::vector<std::pair<int, int>> coord_sujeiras, std::map<std::pair<int, int>, std::map<std::pair<int, int>, int>> matriz_distancias)
{
	//Adiciona a posiçao inicial do robô a lista de montes de sujeira, como uma "sujeira fictícia" para possibilitar a execução do algoritmo 
	coord_sujeiras.insert(coord_sujeiras.begin(), pos_inicial);

	int n_sujeiras = coord_sujeiras.size();

	int visitados = 0; //Máscara que indica quais sujeiras foram limpas (bit 0 se não, bit 1 se sim)
	std::vector<std::vector<int>> dp(1 << n_sujeiras, std::vector(n_sujeiras, INT_MAX)); //dp[mascara][i_sujeira] = custo mínimo para percorrer todas as sujeiras marcadas pela máscara e parar em i_sujeira

	for (int i = 0; i < n_sujeiras; i++)
	{
		dp[1 << i][i] = matriz_distancias[pos_inicial][coord_sujeiras[i]];
	}

	for (int mascara = 0; mascara < (1 << n_sujeiras); mascara++)
	{
		for (int i1 = 0; i1 < n_sujeiras; i1++)
		{
			if (!(mascara & (1 << i1)))
				continue;

			for (int i2 = 0; i2 < n_sujeiras; i2++)
			{
				if (mascara & (1 << i2))
					continue;

				int nova_mascara = mascara | (1 << i2); //Marca a sujeira i2 como limpa
				int nova_distancia = dp[mascara][i1] + matriz_distancias[coord_sujeiras[i1]][coord_sujeiras[i2]]; //Soma da distância percorrida até i1 com a distância entre i1 e i2

				//std::cout << i1 << " -> " << i2 << " (máscara=" << nova_mascara << "); op1=" << dp[nova_mascara][i2] << " op2=" << nova_distancia << std::endl;
				//std::cout << "dp[mascara][i1] = " << dp[mascara][i1] << "; matriz_ditancias[coord_sujeiras[i1]][coord_sujeiras[i2]] = " << matriz_distancias[coord_sujeiras[i1]][coord_sujeiras[i2]] << std::endl;

				dp[nova_mascara][i2] = std::min(dp[nova_mascara][i2], nova_distancia);
			}
		}
	}

	int solucao = INT_MAX;
	for (int i = 1; i < n_sujeiras; i++) 
	{
        	solucao = std::min(solucao, dp[(1 << n_sujeiras) - 1][i] + matriz_distancias[coord_sujeiras[i]][coord_sujeiras[0]]);
    	}

	return solucao;
}
