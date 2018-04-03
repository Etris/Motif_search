#pragma once
#include <string>
#include "graphContainer.h"
#include <fstream>
#include <vector>
#include <sstream>

class fileService
{
private:
	int actualSequence;
	std::vector<std::vector<char>> readedSequence;
	std::vector<std::vector<int>> readedSequenceValues;
	std::string inputQualName;
	std::string inputFastaName;
	int size;
	//vector operators
	void resetVectors();
	//debug printing method, for internal use
	void printDebug(std::string, std::string);
	//debug print for vectors
	void printVectors();
public:
	fileService();
	~fileService();
	//setters section
	//Qual name setter
	void setInputQual(std::string);
	//Fasta name setter
	void setInputFasta(std::string);
	//Frame size setter
	void setSize(int);
	//getters section 
	//option: qual name getter
	std::string getInputQualName();
	//optional: fasta name getter
	std::string getInputFastaName();
	//general functions
	//reader(graph) - to read data from files
	void reader(graphContainer *);
	//saveData(graph) - to save data from vectors to graph
	void saveData(graphContainer *);
};

