#include "fileService.h"
#include "graphContainer.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	string nameFasta, nameQual;
	int frameSize = 4, qualityLine = 20, threshold = 50;
	fileService * fsv = new fileService();
	graphContainer * graph = new graphContainer();
	cout << "Enter FASTA file name: ";
	cin >> nameFasta;
	cout << "Enter Qual file name: ";
	cin >> nameQual;
	fsv->setInputFasta(nameFasta);
	cout << "Name 1 set!" << endl;
	fsv->setInputQual(nameQual);
	cout << "Name 2 set!" << endl;
	cout << "Enter frame size: ";
	cin >> frameSize;
	graph->setRange(frameSize);
	//cout << "Enter quality, above which nucleotydes are correct: ";
	qualityLine = 30;
	graph->setDeadLine(qualityLine);
	cout << "Enter percentage value, of which frame size sequention part are correct: ";
	cin >> threshold;
	graph->setThresh(threshold);
	cout << "Read sequence start... " << endl;
	fsv->reader(graph);
	cout << "Reading done. Transcribing data from set to graph." << endl;
	fsv->setSize(frameSize);
	fsv->saveData(graph);
	cout << "Transribing done. Genereting connection beetwen nodes." << endl;
	//graph->printGraph();
	graph->genereteSuccesors();
	cout << "Genereting done. Cliques finding procedure initializing..." << endl;
	//graph->initTomita();
	graph->exactAlgorithm();
	graph->printCliquesSize();
	cout << "All cliques found. Cliques sequention finding procedure initializing..." << endl;
	//graph->findSequence();
	cout << "Cliques sequention finding procedure done. Maximum motif is: " << endl;
	graph->printMaxSeqTemp();
	system("pause");
}