#include "vertex.h"



void vertex::calculateReliableLevel()
{
	int counter = 0;
	for (int i = 0; i < sequence.size(); i++) {
		if (isReliableTable[i] == true) counter++;
	}
	float tmp = counter / (float)sequence.size();
	tmp *= 100;
	int var = (int)tmp;
	this->setReliableLevel(var);
}

void vertex::setReliableTable()
{
	for (int i = 0; i < sequence.size(); i++) {
		if (reliabilityTable[i] < deadLine) {
			isReliableTable[i] = false;
		}
		else {
			isReliableTable[i] = true;
		}
	}
}

vertex::vertex(int rng, int thresh, std::string tmpSeq, int seq, int pos, int reliable[])
{
	this->setRange(rng);
	this->setDeadLine(thresh);
	this->setSequence(tmpSeq);
	this->setOrigin(seq);
	this->setPostition(pos);
	reliabilityTable = new int[this->getRange()];
	isReliableTable = new bool[this->getRange()];
	this->setReliabilityTable(reliable);
	this->setReliableTable();
	this->calculateReliableLevel();
}


vertex::~vertex()
{
}

void vertex::setRange(int tmp)
{
	range = tmp;
}

void vertex::setOrigin(int tmp)
{
	sequenceOrigin = tmp;
}

void vertex::setPostition(int tmp)
{
	sequencePosition = tmp;
}

void vertex::setReliabilityTable(int tmp[])
{
	reliabilityTable = tmp;
}

void vertex::setReliableLevel(int tmp)
{
	reliableLevel = tmp;
}

void vertex::setSequence(std::string tmp)
{
	sequence = tmp;
}

void vertex::setDeadLine(int tmp)
{
	deadLine = tmp;
}

int vertex::getPosition()
{
	return sequencePosition;
}

int vertex::getOrigin()
{
	return sequenceOrigin;
}

bool * vertex::getReliable()
{
	return isReliableTable;
}

int vertex::getReliableLevel()
{
	return reliableLevel;
}

int vertex::getRange()
{
	return range;
}

int vertex::getDeadLine()
{
	return deadLine;
}

int vertex::getNeiAmount()
{
	return successorsList.size();
}

std::string vertex::getSequence()
{
	return sequence;
}

bool vertex::isAtList(vertex * tmp)
{
	for (std::list<vertex*>::iterator it = successorsList.begin(); it != successorsList.end(); ++it) {
		if (*it == tmp) return true;
	}
	return false;
}

void vertex::addSuccessor(vertex * tmp)
{
	if (this->isAtList(tmp) == false) {
		successorsList.push_back(tmp);
	}
}

std::list<vertex*> vertex::getSuccessorList()
{
	return successorsList;;
}

bool vertex::isAtListOfSuccessors(vertex * x)
{
	std::list<vertex*>::iterator it;
	for (it = successorsList.begin(); it != successorsList.end(); ++it) {
		if ((*it) == x) {
			return true;
		}
	}
	return false;
}
