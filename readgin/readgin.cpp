#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "classdef.h"
using namespace std;

int main(int argc, char *argv[]) {

	// Will become a routine to read .gin files
	// Would like to extract vectors, atoms per layer, dhkl, output filenames, runtime

	if (argc == 1) {
		cout << "Suggested use:" << endl << "readgin filename.gin" << endl;
		exit(0);
	}

	// Define some of the variables here
	string inputFilename, outputFilename, outputFilename2, buffer, historyFilename, buf;
	recordii cella;
	recordiii cellb;
	recordiv cellc;
	bool surface = false;
	double dhkl;

	// First argument is filename
	inputFilename = argv[1];


	// User input parameters
	cout << "Reading input file:\n";
	cout << inputFilename << endl ;

	// Open file
	ifstream fin (inputFilename.c_str());
	if (!fin) {
		cout << "Failed to open file!";
		exit (1);
	}

	// Read header
	while (fin >> buffer) {
		if (!buffer.compare(0, 8, "svectors")) {
			surface = true;
			fin >> buffer;
			cella.cell1 = strtod(buffer.c_str(), NULL);
			fin >> buffer;
			cella.cell2 = strtod(buffer.c_str(), NULL);
			fin >> buffer;
			cellb.cell4 = strtod(buffer.c_str(), NULL);
			fin >> buffer;
			cellb.cell5 = strtod(buffer.c_str(), NULL);
			cella.cell3 = cellb.cell6 = cellc.cell7 = cellc.cell8 = 0.0;
			cellc.cell9 = 1.0;
		}
		if (buffer == "output") {
			fin >> buffer;
			if (buffer == "history") {
				fin >> historyFilename;
			}
		}

		if (buffer == "dhkl") {
			fin >> buffer;
			dhkl = strtod(buffer.c_str(),NULL);
		}

		if (!buffer.compare(0, 4, "dump")) {
			getline (fin, buffer);
			getline (fin, buffer);
			getline (fin, buffer);
			getline (fin, buffer);
		} 
	}
	
	// Calculate k
	
	recordb fa, fb, fc;
	
	fa.xxx = ( 2 * pi() * ( cellb.cell5 * cellc.cell9 - cellb.cell6 * cellc.cell8 /*b x c / a.bxc*/ )
	
	fin.close();
	cout << "End!";
	getchar();
	return 0;

}
