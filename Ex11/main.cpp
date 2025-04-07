/*
 * Nome: Gustavo Curado Ribeiro 
 * NUSP: 14576732
 * SCC0210 - Laboratório de Algoritmos Avançados I
 * Exercício 11: Sem Roupas para a Formatura
*/

#include <iostream>
#include <vector>

int lowest_remaining_value(int money, std::vector<std::vector<int>> dp_matrix, std::vector<std::vector<int>> price_matrix);

int main(void)
{
	int N;
	std::cin >> N;

	for (int w = 0; w < N; w++)
	{
		int M; //Dinheiro disponível
		int C; //Número de categorias de roupa
		std::cin >> M >> C;

		//Matriz cujas colunas representam o dinheiro que resta e as linhas representam a categoria de roupa.
		//Se, dado o dinheiro "m" que sobrou em uma possibilidade de compra de roupa em uma categoria "c", seja
		//possível comprar um roupa de preço "p" na categoria "c+1", então será armazenado 1 na posição (c+1, m-p)
		//da matriz, ou 0 caso contrário
		std::vector<std::vector<int>> dp_matrix(C, std::vector<int>(M, 0));

		//Matriz que guarda o preço de cada roupa de cada categoria
		std::vector<std::vector<int>> price_matrix;

		for (int i = 0; i < C; i++)
		{
			int K; //Número de roupas em cada categoria
			std::cin >> K;
			price_matrix.push_back({});

			for (int j = 0; j < K; j++)
			{
				int num;
				std::cin >> num;
				price_matrix[i].push_back(num);
			}
		}

		//Obtém o menor valor monetário possível que pode restar após se comprar uma roupa de cada
		//categoria e subtrai com o valor inicial, o que resulta no total de dinheiro utilizado
		int lrm =  lowest_remaining_value(M, dp_matrix, price_matrix);

		if (lrm >= 0)
		{
			int solution = M - lrm;
			std::cout << solution << std::endl;
		}
		else
		{
			std::cout << "no solution" << std::endl;
		}
	}

	return 0;
}


int lowest_remaining_value(int money, std::vector<std::vector<int>> dp_matrix, std::vector<std::vector<int>> price_matrix)
{
	//Inicia marcando todas posições possíveis na categoria 0 da matriz dp_matrix, isso é, as
	//posições que indicam quanto dinheiro pode sobrar caso se compre uma roupa da categoria 0
	for (int i = 0; i < price_matrix[0].size(); i++)
	{
		int clothes_price = price_matrix[0][i];

		if (clothes_price <= money)
		{
			int remaining_value = money - clothes_price;
			dp_matrix[0][remaining_value] = 1;
		}
	}

	//Itera por cada categoria, avaliando se, baseado nas quantias válidas de dinheiro que podem sobrar da compra da roupa
	//da categoria passada, é possível comprar roupas nessa; e, se sim, marca na posição [cat][money_left] o valor "1"
	for (int cat = 1; cat < dp_matrix.size(); cat++)
	{
		int former_cat = cat - 1;

		for (int money_left = 0; money_left < dp_matrix[former_cat].size(); money_left++)
		{
			if (dp_matrix[former_cat][money_left] != 1)
				continue;

			for (int j = 0; j < price_matrix[cat].size(); j++)
			{
				int clothes_price = price_matrix[cat][j];

				if (clothes_price <= money_left)
				{
					int remaining_value = money_left - clothes_price;
					dp_matrix[cat][remaining_value] = 1;
				}
			}
		}
	}

	//Índice da última categoria de roupas disponível
	int last_cat = dp_matrix.size() -1;

	//Inicialização de variáveis
	int money_left;
	bool solution_exists = false;

	//Itera pela fileira da última categoria de roupas, procurando uma posição nela em que o
	//valor armazenado é "1", o que significa que existe uma solução do problema em que pode-se
	//comprar todas as categorias de roupa sobrando, de dinheiro, o valor "money_left"
	for (money_left = 0; money_left < dp_matrix[last_cat].size(); money_left++)
	{
		solution_exists = dp_matrix[last_cat][money_left];

		if (solution_exists)
			break;
	}

	return (solution_exists) ? money_left : -1;
}
