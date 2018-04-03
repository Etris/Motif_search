#pragma once
#include <iostream>
#include <string>
#include <list>
#include "vertex.h"
#include "timer.h"
#include <vector>
class graphContainer
{
private:
	//frame size
	int range;
	//threshold of quality, above that value quality is sufficient to use that nucleotyde
	int deadLine;
	//percentage points, above which nucleotyde is sufficient to use
	int tresh;
	timer * TimeMaster = new timer();
	std::list<vertex *>graphList;
	std::list<std::list<vertex*>> cliques;
	std::list<std::list<std::list<vertex*>>> tmpCliques;
	std::list<std::list<vertex*>> maxMotif;
	void saveMaxMotif(std::list<std::list<vertex*>>);
public:
	std::vector<std::string> sequenceID;
	graphContainer();
	~graphContainer();
	//setter for frame size
	void setRange(int);
	//setter for threshold of quality
	void setDeadLine(int);
	//setter for threshold, in percentage, above which whole nucleotyde can be used
	void setThresh(int);
	//save clique to list
	void saveClique(std::list<vertex *>);
	//This function generate a copy of graph
	std::list<vertex*> makeCopyOfGraph();
	//print graph
	void printGraph();
	//int position, int seqOrigin, std::string seq, int tab[]
	void addVertex(int, int, std::string, int[]);
	//method which generete connections in graph
	void genereteSuccesors();
	//find motif/theme
	void findSequence();
	//print max theme/motif/sequence
	void printMaxSequence();
	//exact algo
	void exactAlgorithm();
	//print amount of cliques
	void printCliquesSize();
	//tmp printMax
	void printMaxSeqTemp();
};

