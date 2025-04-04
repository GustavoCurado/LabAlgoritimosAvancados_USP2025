/* 
 * Nome: Gustavo Curado Ribeiro 
 * NUSP: 14576732
 * SCC0210 - Laboratório de Algoritmos Avançados I
 * Exercício 03: Stonks
*/

#include <iostream>
#include <sstream>
#include <map>

int main()
{
	int N;               //Número de dias
	std::string numbers; //String que armazena os preços passados no input

	std::cin >> N;
	std::cin.ignore(); //Retira o '\n' do input
	getline(std::cin, numbers);

	std::stringstream ss(numbers);
	std::map<int, int> prices_limits;

	//Armazena todos os preços e limites de compras, determinados pelo dia, em um std::map ordenado pelo preço
	for (int day = 1; day <= N; day++)
	{
		int price;
		int limit;

		ss >> price;
		limit = day;
		
		prices_limits.insert({price, limit});
	}

	int k;                //Quantidade inicial de dinheiro
	int budget;           //Quantidade restante de dinheiro
	int total_shares = 0; //Total de açoes compradas no período de tempo N

	std::cin >> k;
	budget = k;

	//Itera por todo std::map, indo do menor ao maior preço
	for (auto it = prices_limits.begin(); it != prices_limits.end(); it++)
	{
		int price = (*it).first;
		int limit = (*it).second;

		//Tenta-se comprar o máximo de ações possíveis dado o orçamento disponível
		//e o limite estipulado. Assim, se o orçamento for menor que o limite, com-
		//pra-se todas as ações que o orçamento consegue comprar. Senão, compra-se
		//a quantidade dada pelo limite
		int shares_amount = budget / price;
		shares_amount = (shares_amount < limit) ? shares_amount : limit;

		total_shares += shares_amount; //Adiciona as ações compradas no dia ao total
		budget -= price*shares_amount; //Remove o dinheiro gasto do orçamento
	}

	std::cout << total_shares << std::endl; //Printa o total de ações compradas

	return 0;
}
