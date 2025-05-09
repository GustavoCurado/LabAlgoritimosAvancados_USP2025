/*    
 * Nome: Gustavo Curado Ribeiro     
 * NUSP: 14576732    
 * SCC0210 - Laboratório de Algoritmos Avançados I    
 * Exercício 16: Brain Age – Divisibilidade Fatorial
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <map>

std::vector<int> crivo(int N);
std::map<int, int> decomp_fatorial(int N, std::vector<int> primos);

int main()
{
	unsigned long long int n, m;

	while (std::cin >> n >> m)
        {
		std::vector<int> primos = crivo(n);
                std::map<int,int> decomp_n = decomp_fatorial(n, primos);

                std::map<int,int> decomp_m;
		unsigned long long int num_fatorado = m;

		for (auto it = primos.begin(); it != primos.end();)
		{
			int primo = *it;
			int resto = num_fatorado % primo;

			if (resto == 0)
			{
				decomp_m[primo] += 1;
				num_fatorado /= primo;
			}
			else
			{
				it++;
			}
		}

		if (num_fatorado == 1)
		{
			bool nao_divide = false;

			for (auto it = decomp_m.begin(); it != decomp_m.end(); it++)
			{
				if (decomp_n[it->first] < it->second)
				{
					nao_divide = true;
					break;
				}
			}

			if (nao_divide)
				std::cout << m << " does not divide " << n << "!" << std::endl;
			else
				std::cout << m << " divides " << n << "!" << std::endl;
		}
		else
		{
			std::cout << m << " does not divide " << n << "!" << std::endl;
		}
        }

	return 0;
}


/* Utiliza o crivo de Erastótenes para achar todos os primos no intervalo de 2 a N */
std::vector<int> crivo(int N)
{
	if (N == 0 || N == 1)
	{
		return std::vector<int>({});
	}

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


std::map<int, int> decomp_fatorial(int N, std::vector<int> primos)
{
	if (N == 0 || N == 1)
	{
		std::map<int,int> tabela_superflua;
		tabela_superflua[2] = 0;
		return tabela_superflua;
	}
	
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
