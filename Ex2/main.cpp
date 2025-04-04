/* 
 * Nome: Gustavo Curado Ribeiro 
 * NUSP: 14576732
 * SCC0210 - Laboratório de Algoritmos Avançados I
 * Exercício 02: Analisador de Textos
*/

#include <iostream>
#include <sstream>
#include <bits/stdc++.h>
#include <set>
#include <vector>
#include <cctype>

int main()
{
	//Colhe a frase dada no input e a armazena em "text"
	std::string text;            
	std::getline(std::cin, text);

	//Troca todas os sinais de pontuação da string "text" por espaços brancos
	std::transform(text.begin(), text.end(), text.begin(), [](char c) {
		return std::ispunct(c) ? ' ' : c;
	});

	std::stringstream ss(text);

	std::set<std::string> words_set; //O set organiza as palavras em ordem alfabética
	std::vector<std::string> words_vector; //O vector possibilita múltiplos elementos de valor equivalente, o que será usado na contagem de repetição de palavras

	while(!ss.eof())
	{
		//Recolhe individualmente cada palavra da stringstream ss
		std::string word;
		ss >> word;
		
		//Muda qualquer caractere maíusculo da palavra para seu equivalente em minúsculo
		std::transform(word.begin(), word.end(), word.begin(), ::tolower);

		//Se a palavra nao for uma string vazia, adiciona ela ao vector e ao set
		if (word != std::string(""))
		{
			words_set.insert(word);
			words_vector.push_back(word);
		}
	}

	//Printa o número de palavras no texto
	std::cout << words_vector.size() << std::endl;

	//Printa todas as palavras, separando-as por vírgula
	for (auto it = words_set.begin(); it != words_set.end(); it++)
	{
		if (it != std::prev(words_set.end()))
			std::cout << *it << ", ";
		else
			std::cout << *it << std::endl;
	}

	//Printa todas as palavras e, em sua frente, o número de vezes que ela se repete no texto
	for (auto it = words_set.begin(); it != words_set.end(); it++)
	{
		//Obtém a contagem do número de vezes que a palavra se repetiu
		int count = std::count(words_vector.begin(), words_vector.end(), *it);

		std::cout << *it << " " << count << std::endl;
	}

	return 0;
}
