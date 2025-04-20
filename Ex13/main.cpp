/*
 * Nome: Gustavo Curado Ribeiro 
 * NUSP: 14576732
 * SCC0210 - Laboratório de Algoritmos Avançados I
 * Exercício 13: O Caminho Ótimo na República Suja
*/

#include <iostream>
#include <cstdint>
#include <climits>
#include <algorithm>
#include <vector>
#include <utility>
#include <map>

bool ainda_tem_sujeira(uint16_t sujeiras_limpadas, int n_sujeiras);
void limpa_sujeira(uint16_t& sujeiras_limpadas, int posicao_sujeira);
std::pair<int,int> muda_posicao(std::pair<int,int> dimensoes, std::pair<int,int> posicao, int direcao, bool& direcao_eh_valida);
bool sujeira_posicao_atual(std::pair<int,int> posicao, const std::vector<std::pair<int,int>>& coord_sujeiras, uint16_t sujeiras_limpadas, int& posicao_sujeira);
int achar_menor_caminho(std::pair<int,int> dimensoes, std::pair<int,int> posicao, uint16_t sujeiras_limpadas, const std::vector<std::pair<int,int>>& coord_sujeiras, std::map<std::pair<std::pair<int,int>, uint16_t>, int>& custos_caminhos);

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

		//Mapa que relaciona um cenário possível do problema, definido pelo par de coordenadas
		//da posição do robô e um uint16_t em que cada bit representa se uma sujeira já foi limpada
		//(1) ou não (0), com um custo mínimo inteiro do menor caminho que se pode atingir
		std::map<std::pair<std::pair<int,int>, uint16_t>, int> custos_caminhos;

		std::pair<int,int> dimensoes_sala(l, h);
		std::pair<int,int> posicao(xo, yo);
		uint16_t sujeiras_limpadas = 0; //Para uma sujeira na posição n do coord_sujeiras, o bit na posição n dessa variável estará 1 quando a sujeira indicada estiver limpa

		int solucao = achar_menor_caminho(dimensoes_sala, posicao, sujeiras_limpadas, coord_sujeiras, custos_caminhos);

		std::cout << "A menor rota tem tamanho " << solucao << ".\n";
	}

	return 0;
}


int achar_menor_caminho(std::pair<int,int> dimensoes, std::pair<int,int> posicao, uint16_t sujeiras_limpadas, const std::vector<std::pair<int,int>>& coord_sujeiras, std::map<std::pair<std::pair<int,int>, uint16_t>, int>& custos_caminhos)
{
	int posicao_sujeira; //Se houver uma sujeira na posição atual, indicará em qual índice de coord_sujeiras está essa sujeira;

	//Se houver um monte de sujeira na posição atual do robô, limpa-o
	if (sujeira_posicao_atual(posicao, coord_sujeiras, sujeiras_limpadas, posicao_sujeira))
		limpa_sujeira(sujeiras_limpadas, posicao_sujeira);

	std::pair<std::pair<int,int>, uint16_t> situacao_atual(posicao, sujeiras_limpadas);

	//Se um custo mínimo não estiver armazenado em custos_caminhos, calcula recursivamente esse custo
	if (custos_caminhos.find(situacao_atual) == custos_caminhos.end())
	{
		//Inicialização de variável
		int menor_custo = INT_MAX;

		if (ainda_tem_sujeira(sujeiras_limpadas, coord_sujeiras.size()))
		{
			for (int direcao = 0; direcao < 4; direcao++)
			{
				bool direcao_eh_valida; 
				std::pair<int,int> nova_posicao = muda_posicao(dimensoes, posicao, direcao, direcao_eh_valida);

				if (!direcao_eh_valida)
					continue;

				int custo = 1 + achar_menor_caminho(dimensoes, nova_posicao, sujeiras_limpadas, coord_sujeiras, custos_caminhos);

				if (custo < menor_custo)
					menor_custo = custo;
			}
		}
		else
		{
			menor_custo = 0;
		}

		custos_caminhos[situacao_atual] = menor_custo;
	}

	return custos_caminhos[situacao_atual];
}


//Checa se ainda há um monte de sujeira que não foi limpado pelo robô
bool ainda_tem_sujeira(uint16_t sujeiras_limpadas, int n_sujeiras)
{
	uint16_t mascara = (1 << n_sujeiras) - 1;

	return (sujeiras_limpadas & mascara) != mascara;
}


//Checa se, na posição atual do robô, tem alguma sujeira para ser limpada, e atribui a "indice_sujeira" o valor da posição da sujeira em coord_sujeiras, se essa sujeira existir
bool sujeira_posicao_atual(std::pair<int,int> posicao, const std::vector<std::pair<int,int>>& coord_sujeiras, uint16_t sujeiras_limpadas, int& indice_sujeira)
{
	//Inicialização de variável
	bool tem_sujeira = false;

	auto it = std::find(coord_sujeiras.begin(), coord_sujeiras.end(), posicao); 

	if (it != coord_sujeiras.end())
	{
		indice_sujeira = std::distance(coord_sujeiras.begin(), it);

		uint16_t mascara = 1 << indice_sujeira;
		tem_sujeira = (sujeiras_limpadas & mascara) != mascara;
	}

	return tem_sujeira;
}


//Modifica o "posicao_sujeira"-ésimo bit de sujeiras_limpadas para indicar que o monte de sujeira nessa posição foi limpo
void limpa_sujeira(uint16_t& sujeiras_limpadas, int posicao_sujeira)
{
	sujeiras_limpadas |= (1 << posicao_sujeira);
}


//Muda o valor da posição do robô dada a direção passada se, dada as dimensões da sala, isso for possível 
std::pair<int,int> muda_posicao(std::pair<int,int> dimensoes, std::pair<int,int> posicao, int direcao, bool& direcao_eh_valida)
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
}
