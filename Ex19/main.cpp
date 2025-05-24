#include <iostream>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <utility>
#include <tuple>
#include <bits/stdc++.h>

#define INF INT_MAX

struct Retorno
{
	int custo_caminho;
	std::vector<int> caminho_minimo;
};


struct Retorno dijkstra(int origem, int destino, std::vector<std::vector<int>> arestas);


int main()
{
	int n, m, L, s, t;
	std::cin >> n >> m >> L >> s >> t;

	std::vector<std::tuple<int,int,int>> ordem_input;
	std::vector<std::vector<int>> arestas(n, std::vector<int>(n, -1));

	for (int i = 0; i < m; i++)
	{
		int u, v, w;
		std::cin >> u >> v >> w;

		arestas[u][v] = w;
		arestas[v][u] = w;

		ordem_input.push_back(std::make_tuple(u, v, w));
	}

	struct Retorno retorno = dijkstra(s, t, arestas);

	std::vector<std::tuple<int,int,int>> arestas_caminho;
	std::vector<std::tuple<int,int,int>> arestas_apagadas;

	for (auto it = retorno.caminho_minimo.begin(); std::next(it,1) != retorno.caminho_minimo.end(); it++)
	{
		int custo = arestas[*it][*(it+1)];

		arestas_caminho.push_back(std::make_tuple(*it, *(it+1), custo));

		if (custo == 0)
			arestas_apagadas.push_back(std::make_tuple(*it, *(it+1), 0));
	}

	int dist_restante = L - retorno.custo_caminho;
	int custo_apagadas = 0;

	if (arestas_apagadas.size() != 0)
	{
		custo_apagadas = dist_restante/arestas_apagadas.size();
	}
	else if (arestas_apagadas.size() == 0 && dist_restante > 0)
	{
		std::cerr << "DEU RUIM" << std::endl;
		exit(-1);
	}

	std::vector<std::tuple<int,int,int>> output;

	for (auto it = arestas_apagadas.begin(); it != arestas_apagadas.end(); it++)
	{
		std::tuple<int,int,int> aresta1 = *it;
		std::tuple<int,int,int> aresta2 = std::make_tuple(std::get<1>(aresta1), std::get<0>(aresta1), std::get<2>(aresta1));

		auto it_input1 = std::find(ordem_input.begin(), ordem_input.end(), aresta1);
		auto it_input2 = std::find(ordem_input.begin(), ordem_input.end(), aresta2);

		if (it_input1 != ordem_input.end())
			std::get<2>(*it_input1) = custo_apagadas;
		if (it_input2 != ordem_input.end())
			std::get<2>(*it_input2) = custo_apagadas;
	}


	if (dist_restante > 0)
	{
		std::cout << "YES" << std::endl;

		for (auto it = ordem_input.begin(); it != ordem_input.end(); it++)
		{
			std::tuple<int,int,int> aresta = *it;

			std::cout << std::get<0>(aresta) << " " << std::get<1>(aresta) << " " << std::get<2>(aresta) << std::endl;
		}
	}
	else
	{
		std::cout << "NO" << std::endl;
	}

	return 0;
}


struct Retorno dijkstra(int origem, int destino, std::vector<std::vector<int>> arestas)
{
	int n = arestas.size();
	std::vector<int> dist_minimas(n, INF);

	std::priority_queue <
        std::pair<int, int>, 
        std::vector<std::pair<int, int>>, 
        std::greater<std::pair<int, int>>
	> fila_prioridade; 
	fila_prioridade.push(std::make_pair(0, origem));

	std::vector<int> caminho_minimo;

	int no_anterior = -1;

	while (dist_minimas[destino] == INF)
	{
		std::pair<int,int> topo_fila = fila_prioridade.top();
		fila_prioridade.pop();

		int custo_atual = topo_fila.first;
		int no_atual = topo_fila.second;

		if (dist_minimas[no_atual] != INF)
			continue;

		dist_minimas[no_atual] = custo_atual;
		caminho_minimo.push_back(no_atual);

		int i = 0;
		for (auto it = arestas[no_atual].begin(); it != arestas[no_atual].end(); it++)
		{
			int no_conectado = i++;
			int custo_aresta = *it;

			if (custo_aresta == -1)
				continue;

			fila_prioridade.push(std::make_pair(custo_atual+custo_aresta, no_conectado));
		}
	}

	struct Retorno retorno;
	retorno.caminho_minimo = caminho_minimo;
	retorno.custo_caminho = dist_minimas[destino];
	
	return retorno;
}
