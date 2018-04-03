#include "graphContainer.h"
#include <iostream>
#include <math.h>
#include <windows.h>
#include <cstdlib>

void graphContainer::saveClique(std::list<vertex*> tmp)
{
	bool possible, stmt1, stmt2, stmt3, found;
	bool copy = true;
	//main list
	std::list<std::list<std::list<vertex*>>>::iterator mIT;
	//potential candidates
	std::list<std::list<vertex*>>::iterator cIT;
	//cliques
	std::list<vertex*>::iterator pIT, sIT = tmp.begin();
	std::list<vertex*> hpp;
	if (tmpCliques.size() != 0) {
		found = false;
		for (mIT = tmpCliques.begin(); mIT != tmpCliques.end(); ++mIT) {
			possible = false;
			if ((*mIT).front().front()->getOrigin() == tmp.front()->getOrigin()) {
				possible = true;
			}
			if (possible == true) {
				stmt1 = true;
				hpp = (*mIT).front();
				sIT = tmp.begin();
					for (pIT = hpp.begin(); pIT != hpp.end(); ++pIT) {
						if ((*pIT)->getOrigin() != (*sIT)->getOrigin()) {
							stmt1 = false;
						}
						++sIT;
					}
					if (stmt1 == true) {
						stmt2 = true, stmt3 = true;
						hpp = (*mIT).front();
						if (hpp.size() < 1) continue;
						pIT = hpp.begin();
						sIT = tmp.begin();
						//check if pass to front
						while (sIT != tmp.end() && pIT != hpp.end()) {
							if ((*pIT)->getPosition() - 1 != (*sIT)->getPosition()) {
								stmt2 = false;
							}
							++pIT;
							++sIT;
						}
						hpp = (*mIT).back();
						pIT = hpp.begin();
						sIT = tmp.begin();
						//check if pass to back
						while (sIT != tmp.end() && pIT != hpp.end()) {
							if ((*pIT)->getPosition() + 1 != (*sIT)->getPosition()) {
								stmt3 = false;
							}
							++pIT;
							++sIT;
						}
						if (stmt2 == true) (*mIT).push_front(tmp);
						if (stmt3 == true) (*mIT).push_back(tmp);
						if (stmt2 == true || stmt2 == true) {
							found = true;
							//break;
						}
					}
			}
		}
		if (found == false) {
			std::list<std::list<vertex*>> trs;
			trs.push_back(tmp);
			tmpCliques.push_back(trs);
		}
	}
	else {
		std::list<std::list<vertex*>> trs;
		trs.push_back(tmp);
		tmpCliques.push_back(trs);
	}
}

std::list<vertex*> graphContainer::makeCopyOfGraph()
{
	std::list <vertex*> tmp;
	for (std::list<vertex*>::iterator it = graphList.begin(); it != graphList.end(); ++it) {
		tmp.push_back(*it);
	}
	return tmp;
}

void graphContainer::printGraph()
{
	for (std::list<vertex*>::iterator iFirst = graphList.begin(); iFirst != graphList.end(); ++iFirst) {
		std::cout << (*iFirst)->getSequence() << " seq: " << (*iFirst)->getOrigin() << " pos: " << (*iFirst)->getPosition();
		std::cout << " reliability: " << (*iFirst)->getReliableLevel() << std::endl;
	}
}

void graphContainer::saveMaxMotif(std::list<std::list<vertex*>> tmp)
{
	std::list<std::list<vertex*>>::iterator it;
	maxMotif.clear();
	if (tmp.size() > maxMotif.size()) {
		for (it = tmp.begin(); it != tmp.end(); ++it) {
			maxMotif.push_back(*it);
		}
	}
	this->printMaxSequence();
}

graphContainer::graphContainer()
{
	TimeMaster->start();
}


graphContainer::~graphContainer()
{
}

void graphContainer::setRange(int tmp)
{
	range = tmp;
}

void graphContainer::setDeadLine(int tmp)
{
	deadLine = tmp;
}

void graphContainer::setThresh(int tmp)
{
	tresh = tmp;
}

void graphContainer::addVertex(int pos, int seqOrigin, std::string seq, int tab[])
{
	vertex * tmp = new vertex(range, deadLine, seq, seqOrigin, pos, tab);
	graphList.push_back(tmp);
	//std::cout << "ADDED: " << seq << " origin: " << seqOrigin << " at position: " << pos << std::endl;
}

void graphContainer::genereteSuccesors()
{
	for (std::list<vertex*>::iterator iFirst = graphList.begin(); iFirst != graphList.end(); ++iFirst) {
		std::string firstSeq = "";
		if ((*iFirst)->getReliableLevel() >= tresh){
			std::string tmpStr = (*iFirst)->getSequence();
			bool * tab = (*iFirst)->getReliable();
			for (int i = 0; i < this->range; i++) {
				if (tab[i] == true) {
					firstSeq += tmpStr[i];
				}
			}
		}
		for (std::list<vertex*>::iterator iSecond = graphList.begin(); iSecond != graphList.end(); ++iSecond) {
			if (*iSecond == *iFirst) continue;
			std::string secondSeq = "";
			if((*iSecond)->getReliableLevel() >= tresh){
				std::string tmpStr = (*iSecond)->getSequence();
				bool * tab = (*iSecond)->getReliable();
				for (int i = 0; i < this->range; i++) {
					if (tab[i] == true) {
						secondSeq += tmpStr[i];
					}
				}
			}
			if ((*iFirst)->getSequence() == (*iSecond)->getSequence() && (*iFirst)->getOrigin() != (*iSecond)->getOrigin() && *iFirst != *iSecond) {
				if ((*iFirst)->isAtList(*iSecond) == false) {
					(*iFirst)->addSuccessor(*iSecond);
					//std::cout << (*iFirst)->getSequence() << " to " << (*iSecond)->getSequence() << "\t";
					//std::cout << (*iFirst)->getOrigin() << ":" << (*iFirst)->getPosition() << " to " << (*iSecond)->getOrigin() << ":" << (*iSecond)->getPosition() << std::endl;
				}
			}
			if ((*iFirst)->getOrigin() != (*iSecond)->getOrigin() && firstSeq.size() > 0 && secondSeq.size() > 0 && (*iSecond)->getReliableLevel() >= tresh) {
				if (firstSeq == secondSeq || firstSeq.find(secondSeq) != std::string::npos) {
					//std::cout << firstSeq << " to " << secondSeq << "\t";
					//std::cout<<(*iFirst)->getOrigin() << ":" << (*iFirst)->getPosition() << " to " << (*iSecond)->getOrigin() << ":" << (*iSecond)->getPosition() << std::endl;
					if ((*iFirst)->isAtList(*iSecond) == false) {
						(*iFirst)->addSuccessor(*iSecond);
					}
				}
			}
		}
	}
	std::cout << "Actual processing time: "<<TimeMaster->end() << std::endl;
}


void graphContainer::findSequence()
{
	TimeMaster->start();
	int id = 0, idp = 0;
	int sizer = cliques.size();
	bool isValid, isFound;
	std::list<std::list<vertex*>> tmpTheme;
	std::list<std::list<vertex*>>::iterator it, it1, it2;
	std::list<vertex*> tmpElement;
	std::list<vertex*>::iterator itF, itS;
	//first loop - 1 clique
	for (it = cliques.begin(); it != cliques.end(); ++it) {
		if (id % 10 == 0) {
			//system("CLS");
			std::cout << "#" << id << ": " << ((float)id / sizer) * 100 << "%" << std::endl;
			std::cout << "Actual processing time: " << TimeMaster->end() << std::endl;
		}
		id++;
		//idp = 0;
		//then - save it on tmp list
		isFound = false;
		tmpTheme.push_back(*it);
		//second loop - take another loop - check positions with last element from tmp, if there is not that element - check if tmp is bigger than max, if it is - save it
		for (it1 = cliques.begin(); it1 != cliques.end(); ++it1) {
			//std::cout << idp++ << " ";
			if((*it).size() == (*it1).size()){
				if (*it != *it1) {
					isValid = true;
					tmpElement = tmpTheme.back();
					if (tmpElement.size() == (*it1).size()) {
						itF = tmpElement.begin();
						itS = (*it1).begin();
						while (itF != tmpElement.end() && itS != (*it1).end()) {
							if ((*itF)->getOrigin() == (*itS)->getOrigin()) {
								if (((*itF)->getPosition() + 1) == (*itS)->getPosition()) {
								}
								else {
									isValid = false;
								}
							}
							else {
								isValid = false;
							}
							++itF;
							++itS;
							}
						if (isValid == true) {
							//std::cout << "t";
							tmpTheme.push_back(*it1);
							//it1 = cliques.begin();
							if (tmpTheme.size() > maxMotif.size()) {
								//std::cout << "s";
								this->saveMaxMotif(tmpTheme);
							}
						}
					}
				}
			}
		}
		tmpTheme.clear();
	}
	std::cout << "Final processing time: " << TimeMaster->end() << std::endl;
}

void graphContainer::printMaxSequence()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::cout << "NEW ONE FOUND! Size: " <<  maxMotif.size() + range - 1 << std::endl;
	for (std::list<std::list<vertex*>>::iterator it1 = maxMotif.begin(); it1 != maxMotif.end(); ++it1){
		for (std::list<vertex*>::iterator it = (*it1).begin(); it != (*it1).end(); ++it) {
			std::cout << (*it)->getSequence() << ":" << (*it)->getOrigin() << "." << (*it)->getPosition() << " - ";
			//std::cout << (*it)->getSequence()[0];
		}
		std::cout << std::endl;
	}
	SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

}

void graphContainer::exactAlgorithm()
{
	TimeMaster->start();
	std::list<vertex*>tmp;
	std::list<vertex*>::iterator it, it1, it2, it3;
	for (it = graphList.begin(); it != graphList.end(); ++it) {
		if ((*it)->getSuccessorList().size() < 4) {
			continue;
		}
		else {
			for (it1 = graphList.begin(); it1 != graphList.end(); ++it1) {
				if ((*it1)->getSuccessorList().size() < 3 && (*it1)->getOrigin() == (*it)->getOrigin()) {
					continue;
				}
				else {
					if ((*it1)->isAtList((*it)) == true){
						for (it2 = graphList.begin(); it2 != graphList.end(); ++it2) {
							if ((*it2)->getSuccessorList().size() < 3 && (*it1)->getOrigin() == (*it2)->getOrigin() && (*it2)->getOrigin() == (*it)->getOrigin()) {
								continue;
							}
							else {
								if ((*it2)->isAtList(*it) && (*it2)->isAtList(*it1) & (*it)->isAtList(*it2) && (*it1)->isAtList(*it2)) {
									for (it3 = graphList.begin(); it3 != graphList.end(); ++it3) {
										if ((*it3)->getSuccessorList().size()  < 3) {
											continue;
										}
										else {
											if ((*it3)->isAtList(*it) && (*it3)->isAtList(*it1) && (*it3)->isAtList(*it2) && (*it)->isAtList(*it3) && (*it1)->isAtList(*it3) && (*it2)->isAtList(*it3)) {
												if ((*it3)->getOrigin() != (*it1)->getOrigin() && (*it2)->getOrigin() != (*it3)->getOrigin() && (*it3)->getOrigin() != (*it)->getOrigin()) {
													tmp.push_back(*it);
													tmp.push_back(*it1);
													tmp.push_back(*it2);
													tmp.push_back(*it3);
													tmp.sort([](vertex * lhs, vertex * rhs) {return lhs->getOrigin() < rhs->getOrigin(); });
													saveClique(tmp);
													//check if there is any proposition for be a sequention, 
													printCliquesSize();
													tmp.clear();
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	std::cout << "Clique final time: " << TimeMaster->end() << std::endl;
	//TimeMaster->start();
	//deleteDuplicates();
	//std::cout << "Clique duplicate delete time: " << TimeMaster->end() << std::endl;
}

void graphContainer::printCliquesSize()
{
	std::cout << "Candiates found: " << tmpCliques.size() << std::endl;
}

void graphContainer::printMaxSeqTemp()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	std::list<std::list<std::list<vertex*>>>::iterator it;
	std::list < std::list<vertex*>> maximum = tmpCliques.front();
	for (it = tmpCliques.begin(); it != tmpCliques.end(); ++it) {
		if ((*it).size() > maximum.size()) {
			maximum = (*it);
		}
	}
	std::list<std::list<vertex*>>::iterator it1;
	std::list<vertex*>::iterator it2;
	int firstPositions[4];
	int lastPositions[4];
	int origins[4];
	std::string sequence = "";
	int id = 0;
	int pos = 0;
	for (it1 = maximum.begin(); it1 != maximum.end(); ++it1) {
		pos = 0;
		for (it2 = (*it1).begin(); it2 != (*it1).end(); ++it2) {
			if (id == 0) {
				origins[pos] = (*it2)->getOrigin();
				firstPositions[pos] = (*it2)->getPosition();
				if (pos == 0) {
					sequence += (*it2)->getSequence().substr(0, std::string::npos);
				}
			}
			else if (id == maximum.size() - 1) {
				lastPositions[pos] = (*it2)->getPosition();
				if (pos == 0) sequence += (*it2)->getSequence()[range - 1];
			}
			else{
				if (pos == 0) sequence += (*it2)->getSequence()[range - 1];
			}
			//std::cout << (*it2)->getSequence() << " " << (*it2)->getOrigin() << ":" << (*it2)->getPosition() << " ";
			pos++;
		}
		//std::cout << std::endl;
		id++;
	}
	std::cout << "Summary: " << "size: " << maximum.size() + range - 1 << std::endl;
	std::cout << "Repeating sequence (theme/motif) is: " << sequence << std::endl;
	for (int i = 0; i < 4; i++) {
		std::string::size_type pos;
		pos = sequenceID[i].find(' ', 0);
		sequenceID[i] = sequenceID[i].substr(0, pos);
		std::cout << "At: " << origins[i] << " id: " << sequenceID[i] << " positions: " << firstPositions[i] << "-" << lastPositions[i] + range << std::endl;
	}
	SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
