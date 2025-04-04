/*
 * Nome: Gustavo Curado Ribeiro 
 * NUSP: 14576732
 * SCC0210 - Laboratório de Algoritmos Avançados I
 * Exercício 10: Política sem Conversa
*/

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cmath>

void find_campaign_positions(std::vector<std::vector<int>>& solutions, std::vector<int>chosen_positions);

int main()
{
	int N;
	std::cin >> N;

	//Loops for every N, which representes the number of inputted (i,j) sets
	for (int w = 0; w < N; w++)
	{
		int input_i, input_j;
		std::cin >> input_i >> input_j;

		//When I programmed this, I didn't realize that, in the test cases, the first position of the matrix was deemed to be (1,1), and not
		//(0,0), so, in order to fix this without remaking the entire code, I'll just decrement the variable and increment teh values on the output
		input_i--;
		input_j--;

		//Stores the matrix vertical position (that is, the row) of all party campaigns. The first element
		//will be the value of "i" when j == 0, the second one will be the value of "i" when j == 1, and so on.
		std::vector<int> i_position;

		for (int i = 0; i < 8; i++)
		{
			//Stores -1 in all "i" positions, indicating they are uninitialized, that is,
			//that a valid row position for these columns based on the input is yet unknown
			i_position.push_back(-1);
		}

		//Stores the inputted coordinate 
		i_position[input_j] = input_i;

		std::vector<std::vector<int>> solutions;

		//Find all solutions and stores them in the "solutions" vector
		find_campaign_positions(solutions, i_position);

		//Print all solutions
		for (int j = 0; j < solutions.size(); j++)
		{
			std::cout << j + 1;
			std::vector<int> solution = solutions.at(j);

			for (int i = 0; i < solution.size(); i++)
			{
				//Incrementing the value of the position because, as explained earlier, for
				//the test cases, the first position of the matrix is (1,1), and not (0,0)
				int real_solution = solution.at(i) + 1;

				std::cout << " " << real_solution;
			}

			std::cout << std::endl;
		}
		

		std::cout << std::endl;
	}

	return 0;
}


void find_campaign_positions(std::vector<std::vector<int>>& solutions, std::vector<int>chosen_positions)
{
	//Finds and stores an iterator that points to the first uninitialized
	//column of the matrix, that is the first one whose "i" value is -1
	auto first_uninitialized_column_it = std::find(chosen_positions.begin(), chosen_positions.end(), -1);

	//If not all campaign positions have been determined...
	if (first_uninitialized_column_it != chosen_positions.end()) 
	{
		//The following two for loops will check if a certain row of the uninitialized column
		//is a valid position for the party campaign based on whether this position is in the
		//same diagonal or row as any other initialized campaign position in the matrix
		for (int i = 0; i < 8; i++)
		{
			//Variable initialization
			bool in_same_diagonal = false;
			bool in_same_row     = false;

			int i1 = i;
			int j1 = std::distance(chosen_positions.begin(), first_uninitialized_column_it);

			//Checks if row "i" of this column is in the same row or diagonal
			//as any of the other initialized party campaign positions
			for (auto it = chosen_positions.begin(); it != chosen_positions.end(); it++)
			{
				//if column is uninitialized, ignore it
				if (*it == -1)
					continue;

				int i2 = *it;
				int j2 = std::distance(chosen_positions.begin(), it);

				if (fabs((float)(i2 - i1)/(float)(j2 - j1)) == 1.0)
					in_same_diagonal = true;

				if (i1 == i2)
					in_same_row = true;
			}

			//If the position is valid, inserts it into the row positions vector and
			//recursively calls find_campaign_positions() to find valid positions for
			//the rest of the other uninitialized columns
			if (in_same_diagonal == false && in_same_row == false)
			{
				std::vector<int> new_chosen_positions = chosen_positions;
				new_chosen_positions.at(j1) = i1;

				find_campaign_positions(solutions, new_chosen_positions);
			}
		}
	}
	else
	{
		//Since a valid arrangement of positions in the matrix has been found,
		//insert the position vector into the solutions vector
		solutions.push_back(chosen_positions);
	}
}
