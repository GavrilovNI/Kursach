#pragma once
#include "./NeuralNet/Net.h"
#include "./NeuralNet/NetLoader.h"
#include "./NeuralNet/Matrix.h"
#include "./Visual/Menu.h"
#include "./NeuralNet/Visual/NeuralNetMenu.h"
#include <vector>
#include <conio.h>
#include <iostream>
#include "./NeuralNet/ActivationFunc.h"
#include <iosfwd>
#include <sstream>
#include <cassert>

using namespace NeuralNet;
using namespace NeuralNet::Utils;
using namespace std;
using namespace Visual;
using namespace NeuralNet::NetMenu;

template<typename T>
vector<T> fromArr(T* arr, uint32_t size)
{
	vector<T> result(size);
	for (size_t i = 0; i < size; i++)
	{
		result[i] = arr[i];
	}
	return result;
}



vector<double> study(Net& net, double* inputs, double* answers)
{
	return net.Study(fromArr(inputs, 9),
		fromArr(answers, 2),
		NeuralNet::Sigmoid(),
		0.2);
}

void printNet(vector<double> results, vector<double> inputs)
{
	for (size_t y = 0; y < 3; y++)
	{
		for (size_t x = 0; x < 3; x++)
		{
			printf("%lf ", inputs[y * 3 + x]);
		}
		printf("\n");
	}
	printf("%lf %lf\n\n", results[0], results[1]);
}

void printNet(vector<double>& results, double* inputs)
{
	printNet(results, fromArr(inputs, 9));
}

void printNet(vector<double> results, double* inputs, double* answers)
{
	printNet(results, inputs);
	printf("%lf %lf\n\n", answers[0], answers[1]);
}

void check(Net& net)
{
	vector<double> inputs;
	for (size_t i = 0; i < 9; i++)
	{
		int in;
		cout << "input[" << to_string(i) << "] = ";
		cin >> in;
		inputs.push_back(in%10);
	}

	vector<double> results = net.GetResult(inputs, NeuralNet::Sigmoid());

	cout << "\n";
	printNet(results, inputs);
}

template <typename T>
std::vector<char> Var2Bytes(T value)
{
	std::vector<char> arrayOfByte(sizeof(value));
	char* val = reinterpret_cast<char*>(&value);
	for (int i = 0; i < sizeof(value); i++)
		arrayOfByte[i] = *(val + i);
	return arrayOfByte;
}

template <typename T>
void AddVector2Another(std::vector<T>& dest, std::vector<T> from)
{
	dest.insert(dest.end(), from.begin(), from.end());
}



/*int main()
{

	/*Net net(vector<uint32_t>{ 5, 4, 4, 2 });

	std::ostringstream buf;

	//buf << "a";
	Loader::Save(&net, buf);

	string str = buf.str();
	for (size_t i = 0; i < str.size(); i++)
	{
		cout << (int)str[i] << ',';
	}
	cout << endl << endl;
	auto vec = Var2Bytes((size_t)3);
	AddVector2Another(vec, Var2Bytes((size_t)5));
	AddVector2Another(vec, Var2Bytes((size_t)4));
	AddVector2Another(vec, Var2Bytes((double)4.15));

	for (size_t i = 0; i < vec.size(); i++)
	{
		cout << (int)vec[i] << ',';
	}
	cout << endl;

	int a = 1;*/


	/*std::stringstream buf;

	auto layerSizes = vector<uint32_t>{ 5, 4, 4, 2 };

	Net net(layerSizes);
	Loader::Save(&net, buf);

	Net net2 = Loader::Load(buf);

	int x = net.GetLayersCount();
	int x2 = net2.GetLayersCount();
	for (size_t i = 0; i < net.GetLayersCount(); i++)
	{
		Layer layer = net.GetLayer(i);
		Layer layer2 = net2.GetLayer(i);

		x = layer.GetInputsCount();
		x2 = layer2.GetInputsCount();

		x = layer.GetNeuronsCount();
		x2 = layer2.GetNeuronsCount();

		for (size_t i = 0; i < layer.GetInputsCount() + 1; i++)
		{
			for (size_t n = 0; n < layer.GetNeuronsCount(); n++)
			{
				double d = layer.GetWeight(i, n);
				double d2 = layer2.GetWeight(i, n);
				d = d;
			}
		}
	}

	int a = 2;*/
	

	/*TConsole::GetInstance()->SetBackgroundColor(Color::BROWN);
	//TConsole::GetInstance()->GetBackgroundColor();

	for (size_t i = 0; i < 100; i++)
	{
		cout << to_string(i) << "\n";
	}

	//cout << "qwe\nasd\nzxc";

	TConsole::GetInstance()->GotoXY({ 1, 1 });

	//TConsole::GetInstance()->DelLine();
	//TConsole::GetInstance()->DelLine();
	TConsole::GetInstance()->ClrScr();

	cout << "\t";

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	char buf;
	COORD coord = { 1,0 };

	DWORD num_read;

	if (ReadConsoleOutputCharacter(hConsole, (LPTSTR)&buf, 1, coord, (LPDWORD)&num_read) == 0)
	{
		cout << "Error reading console." << endl;
	}
	else
		cout << buf;

		*/

	//cout << "asd";

	/*TConsole::GetInstance()->GetSettings();

	Menu menu({ 0,0 });

	menu.AddButton(new Button("button1", { 7,1 }));
	menu.AddButton(new Button("button2", { 7,2 }));
	menu.AddButton(new Button("button3", { 7,1 }));


	Menu menu2({ 0,0 });

	menu2.AddButton(new Button("ITISBUTTONN1", { 10,1 }));
	menu2.AddButton(new Button("btn2", { 10,1 }));
	menu2.AddButton(new QuitButton(QuitButton::defaultName, { 10,1 }));
	Button* quitInactive = new QuitButton("quitInactive", { 10,1 });
	quitInactive->SetActive(false);
	menu2.AddButton(quitInactive);
	menu2.settings.loopScrolling = true;

	menu.AddButton(new MenuButton(&menu2, "menu2", { 7,1 }));

	NeuralNetMenu netMenu({ 0,0 });
	Menu* netMenuAsMenu = (Menu*)(&netMenu);
	netMenuAsMenu->settings.loopScrolling = true;

	menu.AddButton(new MenuButton(netMenuAsMenu, "netMenu", { 7,1 }));


	menu.AddButton(new QuitButton(QuitButton::defaultName, { 7,1 }));
	menu.settings.loopScrolling = true;

	TConsole::GetInstance()->GetSettings();

	menu.Run();
	

	//cout << "qwe";
}*/


int main()
{
	Net net(vector<uint32_t>(4) = { 9,4,3,2 });

	double inputs[16][9]{
		{ 1, 1, 1,
		  0, 0, 0,
		  0, 0, 0 },

		{ 0, 0, 0,
		  1, 1, 1,
		  0, 0, 0 },

		{ 0, 0, 0,
		  0, 0, 0,
		  1, 1, 1 },

		{ 1, 0, 0,
		  1, 0, 0,
		  1, 0, 0 },

		{ 0, 1, 0,
		  0, 1, 0,
		  0, 1, 0 },

		{ 0, 0, 1,
		  0, 0, 1,
		  0, 0, 1 },

		{ 1, 1, 1,
		  1, 0, 0,
		  1, 0, 0 },

		{ 1, 1, 1,
		  0, 1, 0,
		  0, 1, 0 },

		{ 1, 1, 1,
		  0, 0, 1,
		  0, 0, 1 },

		{ 1, 0, 0,
		  1, 1, 1,
		  1, 0, 0 },

		{ 0, 1, 0,
		  1, 1, 1,
		  0, 1, 0 },

		{ 0, 0, 1,
		  1, 1, 1,
		  0, 0, 1 },

		{ 1, 0, 0,
		  1, 0, 0,
		  1, 1, 1 },

		{ 0, 1, 0,
		  0, 1, 0,
		  1, 1, 1 },

		{ 0, 0, 1,
		  0, 0, 1,
		  1, 1, 1 },

		{ 0, 0, 0,
		  0, 0, 0,
		  0, 0, 0 }
	};

	double answers[16][2]{
		{ 1, 0 },
		{ 1, 0 },
		{ 1, 0 },
		{ 0, 1 },
		{ 0, 1 },
		{ 0, 1 },
		{ 1, 1 },
		{ 1, 1 },
		{ 1, 1 },
		{ 1, 1 },
		{ 1, 1 },
		{ 1, 1 },
		{ 1, 1 },
		{ 1, 1 },
		{ 1, 1 },
		{ 0, 0 }
	};

	double error = 0;

	while (true)
	{
		int n = 100000;

		for (size_t j = 0; j < n; j++)
		{
			error = 0;
			
			for (size_t i = 0; i < 16; i++)
			{
				vector<double> results = study(net, inputs[i], answers[i]);

				error += (answers[i][0] - results[0]) * (answers[i][0] - results[0]);
				error += (answers[i][1] - results[1]) * (answers[i][1] - results[1]);

				if (j == 0)
				{
					printNet(results, inputs[i], answers[i]);
					int in;
					do
					{
						in = _getch();
						//printf("%d\n",in);

						if (in == 32)
						{
							check(net);
						}
					} while (in==32);
				}
			}

			if (j == n-1)
				printf("error: %lf\n\n\n", error);
			
			if(j%(n/100)==0)
				printf("%d %%\n", j/ (n / 100));
		}
	}

}


