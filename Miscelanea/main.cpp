#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>

int main()
{
	while (true)
	{
		int n, l, w;
		std::cin >> n >> l >> w;

		if (n == 0 && w == 0 && l == 0)
			break;

		std::vector<std::pair<int,int>> roteadores;

		for (int i = 0; i < n; i++)
		{
			int p, r;
			std::cin >> p >> r;

			if ((float)r < ((float)w)/2.0)
				continue;

			for (auto it = roteadores.begin(); it != roteadores.end();)
			{
				auto rot = *it;
				float d = fabs((float)rot.first - (float)p);

				if (d <= (float)r - (float)rot.second)
				{
					continue;
				}
				else if (d <= (float)rot.second - (float)r)
				{
					it = roteadores.erase(it);
				}
				else
				{
					it++;
				}
			}

			roteadores.push_back(std::make_pair(p, r));
		}

		std::sort(roteadores.begin(), roteadores.end(), [](const auto& a, const auto& b)
		{
			return a.first < b.first;
		});

		auto it_primeiro = roteadores.end();

		for (auto it = roteadores.begin(); it != roteadores.end(); it++)
		{
			auto rot = *it;

			float seg_reta = 2.0 * sqrt(powf((float)rot.second, 2) - powf((float)rot.first, 2));
			
			if (seg_reta < w)
				continue;
			else
				it_primeiro = it;
		}

		if (it_primeiro != roteadores.end())
		{
			for (auto it = roteadores.begin(); it != it_primeiro;)
			{
				it = roteadores.erase(it);
			}

			bool deu_ruim = false;

			for (auto it = it_primeiro; it != roteadores.end();)
			{
				auto rot = *it;
				auto it_vizinho = roteadores.end();

				for (auto it_v = it+1; it_v != roteadores.end(); it_v++)
				{
					auto rot_vizinho = *it_v;

					float R = (float)rot.second;
					float r = (float)rot_vizinho.second;
					float d = fabs((float)rot.first - (float)rot_vizinho.first);
					float a = (powf(R, 2) - powf(r, 2) + powf(d, 2))/(2 * d);
					float tamanho_ogiva = sqrt(powf(R, 2) - powf(a, 2));

					if (std::isnan(tamanho_ogiva) || tamanho_ogiva < w)
						continue;
					else
						it_vizinho = it_v;
				}

				if (it_vizinho != roteadores.end())
				{
					for (auto it_v = it+1; it_v != it_vizinho;)
					{
						it_v = roteadores.erase(it_v);
					}

					it = it_vizinho;
				}
				else
				{
					deu_ruim = true;
					break;
				}
			}

			auto rot_final = *(roteadores.end()-1);
			float d = fabs((float)rot_final.first - (float)l);
			float seg_reta = 2.0 * sqrt(powf((float)rot_final.second, 2) - powf(d, 2));
			
			if (seg_reta < w)
				deu_ruim = true;


			if (!deu_ruim)
			{
				std::cout << roteadores.size() << std::endl;
			}
			else
			{
				std::cout << "-1" << std::endl;
			}
		}
		else
		{
			std::cout << "-1" << std::endl;
		}
	}

	return 0;
}
