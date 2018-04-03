#include "fileService.h"
#include <iostream>

void fileService::resetVectors()
{
	readedSequence.clear();
	readedSequenceValues.clear();
}

void fileService::printDebug(std::string debug, std::string msg)
{
	std::cout << std::endl;
	std::cout << debug << msg << std::endl;
}

void fileService::printVectors()
{
	std::cout << std::endl;
	for (int i = 0; i < readedSequence.size(); i++) {
		std::cout << "SEQUENCE: " << i << std::endl;
		for (int x = 0; x < readedSequence[i].size(); x++) {
			std::cout << readedSequence[i][x] << ": " << readedSequenceValues[i][x] << std::endl;
		}
	}
}

fileService::fileService()
{
}


fileService::~fileService()
{
}

void fileService::setInputQual(std::string tmp)
{
	this->inputQualName = tmp;
}

void fileService::setInputFasta(std::string tmp)
{
	this->inputFastaName = tmp;
}

void fileService::setSize(int tmp)
{
	size = tmp;
}

std::string fileService::getInputQualName()
{
	return this->inputQualName;
}

std::string fileService::getInputFastaName()
{
	return this->inputFastaName;
}

void fileService::reader(graphContainer * tmpG)
{
	int act = 0;
	std::string standardMsg = "DEBUG: READER SECTION: ";
	std::fstream sequenceReaderHandler, sequenceValueReaderHandler;
	sequenceReaderHandler.open(inputFastaName.c_str(), std::ios::in);
	sequenceValueReaderHandler.open(inputQualName.c_str(), std::ios::in);
	this->printDebug(standardMsg, "Staring with first file");
	std::string line;
	if (sequenceReaderHandler.good()) {
		std::vector<char> * tmp = new std::vector<char>;
		while (getline(sequenceReaderHandler, line)) {
			if (line.find(">") == std::string::npos) {
				for (int i = 0; i < line.length(); i++) {
					std::cout << line[i] << " ";
					tmp->push_back(line[i]);
				}
			}
			else {
				this->printDebug(standardMsg, line);
				tmpG->sequenceID.push_back(line.substr(1, std::string::npos));
				if (act == 0) {
					act++;
					continue;
				}
				readedSequence.push_back(*tmp);
				tmp = new std::vector<char>;
			}
		}
		readedSequence.push_back(*tmp);
	}
	else {
		std::cout << "FASTA error!" << std::endl;
	}
	act = 0;
	line = "";
	this->printDebug(standardMsg, "Staring with second file");
	if (sequenceValueReaderHandler.good()) {
		std::vector<int> * tmpc = new std::vector<int>;
		while (getline(sequenceValueReaderHandler, line)) {
			if (line.find(">") == std::string::npos) {
				std::istringstream iss(line);
				while (true) {
					int var;
					var = -1;
					iss >> var;
					if (var == -1) break;
					std::cout << var << " ";
					tmpc->push_back(var);
				}
			}
			else {
				this->printDebug(standardMsg, line);
				if (act == 0) {
					act++;
					continue;
				}
				act++;
				readedSequenceValues.push_back(*tmpc);
				tmpc = new std::vector<int>;
			}
		}
		readedSequenceValues.push_back(*tmpc);
	}
	else {
		std::cout << "Qual error!" << std::endl;
	}
	//printVectors();
}

void fileService::saveData(graphContainer * tmp)
{
	std::string standardMsg = "DEBUG: TRANSCRIBE SECTION ";
	std::cout << std::endl;
	this->printDebug(standardMsg, "");
	for (int z = 0; z < readedSequence.size(); z++) {
		std::cout << readedSequence[z].size() << std::endl;
		for (int y = 0; y < readedSequence[z].size() - size + 1; y++) {
			//std::cout << "NUCLEO: " << y << std::endl;
			int c;
			std::string tmpSequence = "";
			int * tab = new int[size];
			for (c = 0; c < size; c++) {
				int tmprc = y + c;
				tmpSequence = tmpSequence + readedSequence[z][tmprc];
			}
			for (c = 0; c < size; c++) {
				int tmprc = y + c;
				tab[c] = readedSequenceValues[z][tmprc];
			}
			tmp->addVertex(y, z, tmpSequence, tab);
			//std::cout << tmpSequence << ": " << tab[0] <<" "<< tab[1] <<" "<< tab[2] <<" "<< tab[3] << std::endl;
		}
	}
}
	