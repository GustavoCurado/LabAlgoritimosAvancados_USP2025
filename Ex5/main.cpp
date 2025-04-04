/* 
 * Nome: Gustavo Curado Ribeiro 
 * NUSP: 14576732
 * SCC0210 - Laboratório de Algoritmos Avançados I
 * Exercício 05: Colocando os Robôs Para Trabalhar
*/

#include <iostream>
#include <sstream>
#include <utility>
#include <algorithm>
#include <vector>
#include <tuple>

int main()
{
	int N, M;
	std::string numbers;

	std::cin >> N;
	std::cin >> M;
	std::cin.ignore();
	getline(std::cin, numbers); //Passa para uma string os números que correspondem às deadlines de cada tarefa

	std::stringstream ss(numbers);

	std::vector<std::tuple<int, int, int, int>> tasks; //Armazena a ordem, a deadline, o dia em que a tarefa é feita e o robô que a realiza

	//Passa as informações das tarefas para o vector declarado anteriormente
	for (int i = 0; i < M; i++)
	{
		int deadline;
		ss >> deadline;

		tasks.push_back(std::make_tuple(i, deadline, 0, 0));
	}

	//Ordena o vetor de forma ascendente com base no valor da deadline
	std::sort(tasks.begin(), tasks.end(), [](const auto& a, const auto& b) {
		return std::get<1>(a) < std::get<1>(b);
	});

	//Inicialização de variáveis utilizadas no for-loop
	int day = 1;                  //O dia em que a tarefa será feita
	int n_robots = 1;             //O total de robôs
	int current_robot = 1;        //O robô sendo usado para a tarefa específica

	//Itera por todas as tarefas, inicialmente tentando realizar todas elas com um só robô.
	//Porém, quando um robô se mostra insuficiente, aumenta-se o total de robôs e reinicia-se
	//o for-loop, passando a usar dois robôs por dia e assim em diante.
	for (auto it = tasks.begin(); it != tasks.end(); it++)
	{
		auto& tuple = *it;
		int deadline = std::get<1>(tuple);

		//Se já tiver passado do prazo da deadline, isso significa que o número de robôs
		//é insuficiente. Portanto, reinicia-se o processo e aumenta-se o total de robôs
		if (deadline < day)
		{
			day = 1;              //Volta para o primeiro dia
			n_robots++;           //Aumenta o total de robôs
			current_robot = 1;    //Garante que o primeiro robô a ser usado no primeiro dia é o robô 1
			it = tasks.begin()-1; //Força o for-loop a voltar para o primeiro elemento do vector (a primeira tarefa)
			continue;
		}

		//Atribui as informações de dia e qual robô está fazendo a tarefa 
		std::get<2>(tuple) = day; 
		std::get<3>(tuple) = current_robot;

		if (current_robot < n_robots)
		{
			//Se ainda tiverem robôs que não executaram tarefas no dia atual, permanece-se
			//no mesmo dia e atribui ao próximo robô a próxima tarefa no vector
			current_robot++;
		}
		else
		{
			//Se todosos robôs já executaram uma tarefa no dia atual, passa para o próximo
			//dia e põe o robô 1 para executar a próxima tarefa no dia seguinte
			day++;
			current_robot = 1;
		}
	}

	//Ordena o vetor de forma ascendente com base no valor da ordem
	std::sort(tasks.begin(), tasks.end(), [](const auto& a, const auto& b) {
		return std::get<0>(a) < std::get<0>(b);
	});

	//Printa o total de robôs necessários
	std::cout << n_robots << std::endl;

	//Printa robô utilizado e o dia em que foi realizada cada tarefa
	for (auto tuple : tasks)
	{
		int day = std::get<2>(tuple);
		int robot = std::get<3>(tuple);

		std::cout << day << " " << robot << std::endl;
	}

	return 0;
}
