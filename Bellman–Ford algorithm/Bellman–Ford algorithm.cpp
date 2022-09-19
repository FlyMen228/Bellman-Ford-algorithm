#include <iostream>
#include <vector>
#include <fstream>

int const inf = INT_MAX - 100;

std::vector <std::vector <int> > inputAdjacencyMatrixFromFile()
{
	std::ifstream reader("input.txt");
	if (!reader.is_open())
		std::cout << "Input file alert!\n";
	else
	{
		int demensionOfMatrix;
		reader >> demensionOfMatrix;
		std::vector <std::vector <int> > adjacencyMatrix(demensionOfMatrix, std::vector <int>(demensionOfMatrix));
		for (int i = 0; i < demensionOfMatrix; ++i)
			for (int j = 0; j < demensionOfMatrix; ++j)
			{
				reader >> adjacencyMatrix[i][j];
				if (adjacencyMatrix[i][j] == 0 && i != j)
					adjacencyMatrix[i][j] = inf;
			}
		return adjacencyMatrix;
	}
}

std::vector <int> bellmanFordAlgorithm(std::vector <std::vector <int> > adjacencyMatrix)
{
	std::cout << "Enter start point: ";
	int startVertex, demensionOfMatrix;
	demensionOfMatrix = adjacencyMatrix.size();
	std::cin >> startVertex;
	std::vector <int> resultArray(demensionOfMatrix, inf);
	resultArray[--startVertex] = 0;
	for (int i = 0; i < demensionOfMatrix - 1; ++i)
		for (int j = 0; j < demensionOfMatrix; ++j)
			if (resultArray[i] < inf && resultArray[j] > resultArray[i] + adjacencyMatrix[i][j])
				resultArray[j] = resultArray[i] + adjacencyMatrix[i][j];
	std::vector <int> buffer(resultArray);
	for (int j = 0; j < demensionOfMatrix; ++j)
		if (resultArray[demensionOfMatrix - 1] < inf && resultArray[j] > resultArray[demensionOfMatrix - 1] + adjacencyMatrix[demensionOfMatrix - 1][j])
			resultArray[j] = resultArray[demensionOfMatrix - 1] + adjacencyMatrix[demensionOfMatrix - 1][j];
	if (resultArray == buffer)
		return resultArray;
	else
	{
		std::cout << "Attention! There's negative cycle!" << std::endl;
		std::exit(1);
	}
}

void saveResultToFile(std::vector <int> resultArray)
{
	std::ofstream writer;
	writer.open("output.txt", std::ios_base::out);
	for (int i = 0; i < resultArray.size(); ++i)
		if (resultArray[i] < inf - 100)
			writer << resultArray[i] << " ";
		else
			writer << "INF ";
	std::cout << "Programm finished successfully!\n";
}

int main()
{
	std::vector <std::vector <int> > adjacencyMatrix = inputAdjacencyMatrixFromFile();
	std::vector <int> resultArray = bellmanFordAlgorithm(adjacencyMatrix);
	saveResultToFile(resultArray);
	return 0;
}