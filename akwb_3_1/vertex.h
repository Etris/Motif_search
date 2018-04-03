#pragma once
#include <iostream>
#include <string>
#include <list>

class vertex
{
private:
	//frame size
	int range;
	//threshold of quality, above that value quality is sufficient to use that nucleotyde
	int deadLine;
	std::string sequence;
	std::list<vertex*> successorsList;
	int * reliabilityTable;
	bool * isReliableTable;
	int reliableLevel;
	int sequenceOrigin;
	int sequencePosition;
	void calculateReliableLevel();
	void setReliableTable();
public:
	vertex(int, int, std::string, int, int, int[]);
	~vertex();
	//setters section
	void setRange(int);
	void setOrigin(int);
	void setPostition(int);
	void setReliabilityTable(int[]);
	void setReliableLevel(int);
	void setSequence(std::string);
	void setDeadLine(int);
	//getters section
	int getPosition();
	int getOrigin();
	bool * getReliable();
	int getReliableLevel();
	int getRange();
	int getDeadLine();
	int getNeiAmount();
	std::string getSequence();
	//general methods
	bool isAtList(vertex *);
	void addSuccessor(vertex *);
	std::list<vertex*> getSuccessorList();
	bool isAtListOfSuccessors(vertex*);
};

