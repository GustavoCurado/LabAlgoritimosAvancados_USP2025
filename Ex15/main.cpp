/*
 * Nome: Gustavo Curado Ribeiro 
 * NUSP: 14576732
 * SCC0210 - Laboratório de Algoritmos Avançados I
 * Exercício 15: Brain Age – Fatoração em Primos
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <map>

std::vector<int> crivo(int N);
std::map<int, int> decomp_fatorial(int N);

int main()
{
	while (true)
	{
		int N;
		std::cin >> N;

		if (N == 0)
			break;

		std::map<int,int> tabela_decomp = decomp_fatorial(N);


		std::cout << N << "! = ";

		for (auto it = tabela_decomp.begin(); it != tabela_decomp.end(); it++)
		{
			std::cout << it->second << " ";
		}

		std::cout << std::endl;
	}

	return 0;
}

/* Utiliza o crivo de Erastótenes para achar todos os primos no intervalo de 2 a N */
std::vector<int> crivo(int N)
{
	//Preenche um vector com numeros de 2 a N
	std::vector<int> numeros(N-1);
	std::iota(numeros.begin(), numeros.end(), 2);

	//Percorre todos os numeros da lista, deletando todos os múltiplos
	//de cada número que colher na iteração. Dessa forma, só sobram os
	//números primos na lista
	for (auto it = numeros.begin(); it != numeros.end(); it++)
	{
		int n = *it;

		for (int i = 2; i <= N/n; i++)
		{
			int multiplo = n*i;

			auto it_multiplo = std::find(numeros.begin(), numeros.end(), multiplo);
			if (it_multiplo == numeros.end())
				continue;

			numeros.erase(it_multiplo);
		}
	}

	return numeros;
}


std::map<int, int> decomp_fatorial(int N)
{
	if (N == 0 || N == 1)
	{
		std::map<int,int> tabela_superflua;
		tabela_superflua[2] = 0;
		return tabela_superflua;
	}
	
	//Obtém todos os primos entre 2 e N, pois é uma combinação
	//desses que forma a decomposição de N fatorial
	std::vector<int> primos = crivo(N);

	//Registra o número de vezes que um primo aparece na decomposição de N!
	std::map<int,int> tabela_decomp;

	for (int n = 2; n <= N; n++)
	{
		int num_fatorado = n;

		for (auto it = primos.begin(); it != primos.end();)
		{
			int primo = *it;
			int resto = num_fatorado % primo;

			if (resto == 0)
			{
				tabela_decomp[primo] += 1;
				num_fatorado /= primo;
			}
			else
			{
				it++;
			}
		}
	}

	return tabela_decomp;
}
