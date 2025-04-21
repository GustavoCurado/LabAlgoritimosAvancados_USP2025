/*
 * Nome: Gustavo Curado Ribeiro 
 * NUSP: 14576732
 * SCC0210 - Laboratório de Algoritmos Avançados I
 * Exercício 14: Fazendo Somas na Ilha de Yock
*/

#include <iostream>
#include <vector>

int numero_de_somas(int N, int K);

int main()
{
	while (true)
	{
		int N;
		int K;

		std::cin >> N >> K;

		if (N == 0 && K == 0)
			break;

		int solucao = numero_de_somas(N,K);

		std::cout << solucao << std::endl;
	}

	return 0;
}


int numero_de_somas(int N, int K)
{
	
	std::vector<std::vector<int>> numero_combinacoes(N+1, std::vector(K+1, 0));

	for (int i = 0; i <= N; i++)
	{
		numero_combinacoes[i][0] = 0;
		numero_combinacoes[i][1] = 1;
	}

	//O número de combinações (N,K) é calculado pela somatória do número de combinações (N-i,K-1), com i de 0 a N
	for (int k = 2; k <= K; k++)
	{
		for (int n = 0; n <= N; n++)
		{
			for (int i = 0; i <= n; i++)	
			{
				numero_combinacoes[n][k] = (numero_combinacoes[n][k] + numero_combinacoes[n-i][k-1]) % 1000000;
			}
		}
	}

	return numero_combinacoes[N][K];
}
