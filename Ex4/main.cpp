/* 
 * Nome: Gustavo Curado Ribeiro 
 * NUSP: 14576732
 * SCC0210 - Laboratório de Algoritmos Avançados I
 * Exercício 04: Máximo de Doces
*/

#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>

int main()
{
	int N, K;
	std::string numbers;

	std::cin >> N; //Diferente tipos de doce
	std::cin >> K; //Máximo de doces grátis que se pode receber na compra de um doce
	std::cin.ignore();
	std::getline(std::cin, numbers);

	std::stringstream ss(numbers);

	std::vector<int> prices; //Armazena o preço de cada doce

	for (int i = 0; i < N; i++)
	{
		int price;
		ss >> price;

		prices.push_back(price);
	}

	//Ordena o vetor de preços em ordem crescente
        std::sort(prices.begin(), prices.end(), [](const auto& a, const auto& b) {
                return a < b;
        });

	//Inicialização de variáveis
	int lowest_price = 0;
	int j = prices.size() - 1;

	//Encontra o menor valor possível em que uma pessoa pode comprar todos os tipos de doce
	for (int i = 0; i < N; i++)
	{
		lowest_price += prices.at(i);

		int free_candies = (j-i >= K) ? K : j-i;

		j -= free_candies;

		if (i >= j)
			break;
	}

	//Inicialização de variáveis
	int highest_price = 0;
	j = 0;

	//Encontra o maior valor possível em que uma pessoa pode comprar todos os tipos de doce
	for (int i = prices.size() - 1; i >= 0; i--)
	{
		highest_price += prices.at(i);

		int free_candies = (i-j >= K) ? K : i-j;

		j += free_candies;

		if (i <= j)
			break;
	}

	std::cout << lowest_price << " " << highest_price << std::endl;

	return 0;
}
