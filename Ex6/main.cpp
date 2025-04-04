/* 
 * Nome: Gustavo Curado Ribeiro 
 * NUSP: 14576732
 * SCC0210 - Laboratório de Algoritmos Avançados I
 * Exercício 06: Descida da Serra
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <cctype>
#include <cmath>

#define MAX_FUEL 300

float binary_search(std::vector<std::string> commands);
bool fuel_is_enough(float liters, std::vector<std::string> commands);

int main(void)
{
	std::vector<std::vector<std::string>> inputs; //Vetor que guarda o vetor da sequência de eventos de cada caso de teste
	std::string command;

	int i = 0;
	inputs.push_back({});

	while (true)
	{
		//Armazena o evento
		std::getline(std::cin, command);
		inputs[i].push_back(command);

		bool is_destino;

		//Esse if basicamente checa se tem um '\r' no final da string command, o que acontece no RunCodes, mas não no meu computador
		if (std::isspace(command.back()))
			is_destino = (command.substr(command.size() - 8, 7) == "Destino");
		else
			is_destino = (command.substr(command.size() - 7) == "Destino");

		//Se acabou um dos casos de teste, incrementa "i" e inicializa mais
		//um vetor de eventos para passar para o próximo caso de testes 
		if (is_destino)
		{
			i++;
			inputs.push_back({});
		}

		//Se o evento for "0 Consumo de combustível 0", para a leitura
		if (command.substr(command.size() - 2) == " 0")
			break;
	}

	std::cout << std::fixed << std::setprecision(3);

	//Printa o combustível mínimo necessário para realizar
	//cada viagem dado os eventos ocorridos no caminho
	for (auto it = inputs.begin(); it != inputs.end() - 1; it++)
	{
		auto commands = *it;
		float necessary_fuel = binary_search(commands);

		std::cout << necessary_fuel << std::endl;
	}
	
	return 0;
}


/* Realiza uma busca binária na função fuel_is_enough(). Essa função                                  *
 * se comporta de forma similar a uma função degrau, dado que, até o valor "fuel"                     *
 * ser igual ao combustível necessário, o valor de retorno é false, e, no caso contrário,             *
 * seu valor é true. A busca binária procurará o ponto em que essa mudança no valor de retorno ocorre */
float binary_search(std::vector<std::string> commands)
{
	float fuel;
	float min_fuel = 0;
	float max_fuel = MAX_FUEL;

	while (std::abs(min_fuel - max_fuel) >= 0.0005)
	{
		fuel = (min_fuel + max_fuel) / 2.0;
		bool is_enough = fuel_is_enough(fuel, commands);

		if (is_enough)
			max_fuel = fuel;
		else
			min_fuel = fuel;
	}

	return fuel;
}


bool fuel_is_enough(float liters, std::vector<std::string> commands)
{
	float distance;
	float last_distance;
	float current_consumption;

	int leakages = 0;
	float fuel_left = liters;

	//Itera por toda a sequência de eventos que ocorre no caminho
	for (auto command : commands)
	{
		std::string command_type;
		std::stringstream ss(command);

		last_distance = distance;

		ss >> distance;
		ss >> command_type;

		//Diminui o combustível disponível dada a distância percorrida e o número de vazamentos
		if (distance != 0.0)
			fuel_left -= (distance - last_distance) * ((current_consumption / 100.0) + (float)leakages);

		//Se acabou o combustível, termina o loop
		if (fuel_left < 0.0)
			break;

		//Esses ifs lidam com os eventos que ocorrem na estrada
		if (command_type == "Consumo")
		{
			std::string useless_string;

			ss >> useless_string >> useless_string;
			ss >> current_consumption;
		}
		else if (command_type == "Vazamento")
		{
			leakages++;
		}
		else if (command_type == "Posto")
		{
			fuel_left = liters;
		}
		else if (command_type == "Mecânico")
		{
			leakages = 0;
		}
	}

	return (fuel_left >= 0.0);
}
