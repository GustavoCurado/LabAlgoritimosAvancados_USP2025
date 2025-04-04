/* 
 * Nome: Gustavo Curado Ribeiro 
 * NUSP: 14576732
 * SCC0210 - Laboratório de Algoritmos Avançados I
 * Exercício 09: Harmonia em Algoritmolândia
*/

#include <iostream>
#include <algorithm>
#include <vector>

void find_numbers(int N, std::vector<int> chosen_numbers, std::vector<int>& numerators, std::vector<int>& denominators);
int vector_to_int(std::vector<int> vec);
std::vector<int> int_to_vector(int number);
bool has_duplicates(std::vector<int> vec);

int main()
{
	int N;

	while (std::cin >> N)
	{
		if (N == 0)
			break;

		std::vector<int> numerators;
		std::vector<int> denominators;
		std::vector<int> empty_vector;

		find_numbers(N, empty_vector, numerators, denominators);

		//Se houver soluções, printa-as
		if (denominators.size() != 0)
		{
			for (auto it_1 = numerators.begin(), it_2 = denominators.begin(); it_1 != numerators.end(); it_1++, it_2++)
			{
				int numerator = *it_1;
				int denominator = *it_2;

				std::cout << numerator << " / " << denominator << " = " << N << std::endl;
			}

			std::cout << std::endl;
		}
		else
		{
			std::cout << "Não há soluções para " << N << ".\n\n";
		}
	}

	return 0;
}


/* Em essência, essa função encontra recursivamente todas as combinaçoes de 10 dígitos tomados 5 a 5 (os possíveis denominadores), *
 * multiplica-os por N para obter 5 outros dígitos (o numerador) e checa se não há repetição de dígitos nesse número               */
void find_numbers(int N, std::vector<int> chosen_numbers, std::vector<int>& numerators, std::vector<int>& denominators)
{
	if (chosen_numbers.size() != 5)
	{
		for (int i = 0; i < 10; i++)
		{
			//Para que os números no denominador não se repitam, pula o loop se o número já estiver no vetor
			if (std::find(chosen_numbers.begin(), chosen_numbers.end(), i) != chosen_numbers.end())
				continue;

			//Insere o novo dígito ao vetor
			std::vector<int> new_chosen_numbers = chosen_numbers;
			new_chosen_numbers.push_back(i);

			//Chama recursivamente a função find_numbers() para selecionar os dígitos ainda não escolhidos
			find_numbers(N, new_chosen_numbers, numerators, denominators);
		}
	}
	else
	{
		int denominator = vector_to_int(chosen_numbers);

		//Calcula o numerador baseado no denominador formado na recursão
		int numerator = N * denominator;
		std::vector<int> numerator_vec = int_to_vector(numerator);

		bool has_more_than_5_digits = (numerator_vec.size() > 5) ? true : false;

		//Checa se o numerador tem mais de 5 dígitos porque, se tiver, não é soluçao do problema
		if (!has_more_than_5_digits)
		{
			//Inicialização de variável
			bool has_repeated_digit = false;

			//Checa se um dígito do numerador coincide com um do denominador
			for (auto digit : numerator_vec)
			{
				if (std::find(chosen_numbers.begin(), chosen_numbers.end(), digit) != chosen_numbers.end())
					has_repeated_digit = true;
			}

			//Checa se nao há dígitos repetidos no numerador
			if (has_duplicates(numerator_vec))
				has_repeated_digit = true;
			
			//Se os 10 dígitos do numerador e do denominador forem diferentes entre si, elessão solução do problema
			if (!has_repeated_digit)
			{
				numerators.push_back(numerator);
				denominators.push_back(denominator);
			}
		}
	}
}


/* Tranforma os dígitos armazenados no vetor em um só número, estando o último da *
 * lista na casa das unidades, o penúltimo na casa das dezenas e assim por diante */
int vector_to_int(std::vector<int> vec)
{
	int number = 0;

	for (auto num : vec)
	{
		number = 10 * number + num;
	}

	return number;
}


/* Transfere cada dígito de um inteiro para um vector */
std::vector<int> int_to_vector(int number)
{
	int num = number;
	std::vector<int> vec;

	while (num != 0)
	{
		vec.push_back(num % 10);
		num /= 10;
	}

	std::reverse(vec.begin(), vec.end());

	//Para atender a necessidade da função find_numbers(), o vector de dígitos deve ter
	//5 dígitos, então se adiciona zeros à esquerda caso seja necessário completar o vector
	while (vec.size() < 5)
	{
		vec.insert(vec.begin(), 0);
	}

	return vec;
}


/* Checa se existem dois ou mais números iguais em um vector */
bool has_duplicates(std::vector<int> vec)
{
	bool answer = false;

	for (auto it_i = vec.begin(); it_i != vec.end(); it_i++)
	{
		for (auto it_j = vec.begin(); it_j != vec.end(); it_j++)
		{
			if (it_i == it_j)
				continue;

			if (*it_i == *it_j)
			{
				answer = true;
				break;
			}
		}
	}

	return answer;
}
