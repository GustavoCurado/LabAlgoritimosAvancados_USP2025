/* 
 * Nome: Gustavo Curado Ribeiro	
 * NUSP: 14576732
 * SCC0210 - Laboratório de Algoritmos Avançados I
 * Exercício 01: Automatizando Comentários em Configuração Nginx 
*/

#include <stdio.h>
#include <stdlib.h>

#define STRING_MAX 20

/* Essa struct armazena o nome e o IP de um dado servidor */
struct Server
{
	int ip[4];  //Esse vetor armazena os 4 números que formam um IP
	char* name;
};

/* Essa struct armazena um comando passado no input e o IP ao qual ele referencia */
struct Command
{
	int ip[4];
	char* command;
};

int compare_ip(struct Server* server, struct Command* command);


int main(void)
{
	int n, m;
	struct Server** servers;
	struct Command** commands;

	scanf("%d %d", &n, &m); //Obtém os valores de "n" e "m"

	servers  = malloc(n*sizeof(*servers));
	commands = malloc(m*sizeof(*commands));

	//Armazena cada servidor passado no input em um vetor de ponteiros de struct Server "servers"
	for (int i = 0; i < n; i++)
	{
		servers[i] = malloc(1*sizeof(*servers[i]));
		servers[i]->name = malloc(STRING_MAX*sizeof(*(servers[i]->name)));

		scanf("%s %d.%d.%d.%d;", servers[i]->name, &servers[i]->ip[0], &servers[i]->ip[1], &servers[i]->ip[2], &servers[i]->ip[3]);
	}

        //Armazena cada comando passado no input em um vetor de ponteiros de struct Command "commands"
	for (int i = 0; i < m; i++)
	{
		commands[i] = malloc(1*sizeof(*commands[i]));
		commands[i]->command = malloc(STRING_MAX*sizeof(*(commands[i]->command)));

		scanf("%s %d.%d.%d.%d;", commands[i]->command, &commands[i]->ip[0], &commands[i]->ip[1], &commands[i]->ip[2], &commands[i]->ip[3]);
	}

	//Para cada comando passado, procura o servidor cujo IP é igual ao referenciado pelo
        //comando e printa na tela o comando conforme a especificação: "comando ip; #nome"
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (compare_ip(servers[j], commands[i]))
			{
				printf("%s %d.%d.%d.%d; #%s\n", commands[i]->command, commands[i]->ip[0], commands[i]->ip[1], commands[i]->ip[2], commands[i]->ip[3], servers[j]->name);
				break;
			}
		}
	}

	//Libera os ponteiros alocados
	for (int i = 0; i < n; i++)
	{
		free(servers[i]->name);
		free(servers[i]);
	}
	free(servers);
	for (int i = 0; i < m; i++)
	{
		free(commands[i]->command);
		free(commands[i]);
	}
	free(commands);

	return 0;
}


/* Compara os IPs passados para um servidor e para um comando e retorna se são iguais ou não*/
int compare_ip(struct Server* server, struct Command* command)
{
	int first_equal;
	int second_equal;
	int third_equal;
	int forth_equal;
	int are_the_same_ip;

	first_equal  = server->ip[0] == command->ip[0];
	second_equal = server->ip[1] == command->ip[1];
	third_equal  = server->ip[2] == command->ip[2];
	forth_equal  = server->ip[3] == command->ip[3];

	are_the_same_ip = first_equal && second_equal && third_equal && forth_equal;

	return are_the_same_ip;
}
