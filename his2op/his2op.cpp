#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <complex>
#include "classdef.h"
using namespace std;

void bubbleSort(recordb a[], int n)
/* Sorts in increasing order the array A of the size N */
{
	int k;
	int bound = n - 1;
	recordb t;
	int last_swap;

	while (bound) {
		last_swap = 0;
		for ( k = 0; k < bound; k++ ) {
			t.zzz = a[k].zzz; /* t is a maximum of A[0]..A[k] */
			if ( t.zzz > a[k + 1].zzz ) {
				t.xxx = a[k].xxx;
				t.yyy = a[k].yyy;
				a[k].xxx = a[k + 1].xxx;
				a[k].yyy = a[k + 1].yyy;
				a[k].zzz = a[k + 1].zzz;
				a[k + 1].xxx = t.xxx; /*swap*/
				a[k + 1].yyy = t.yyy; /*swap*/
				a[k + 1].zzz = t.zzz; /*swap*/
				last_swap = k; /* mark the last swap position */
			} //if
		} //for
		bound = last_swap; /*elements after bound already sorted */
	} //while
} // bubbleSort

int main() {
	// Define some of the variables here
	string inputFilename, outputFilename, buffer;
	int atomsInLayer;
	record1 fileHeader;
	record2 fileConfig;
	recordb k; // Reciprocal lattice vector

	// User input parameters
	cout << "Input filename: ";
	getline (cin, inputFilename);
	cout << "Output filename: ";
	getline (cin, outputFilename);
	cout << "Number of atoms in a layer:";
	cin >> atomsInLayer;
	cout << "Reciprocal lattice vector, k:" << endl << "kx: ";
	cin >> k.xxx;
	cout << "ky: ";
	cin >> k.yyy;

	// Open file
	ifstream fin (inputFilename.c_str());
	if (!fin) {
		cout << "Failed to open file \"" << inputFilename << "\"!";
		exit (1);
	}
	ofstream outPut (outputFilename.c_str());

	// Read header
	getline (fin, fileHeader.header);
	cout << "File header:" << endl << fileHeader.header << endl;

	// Read record2
	getline (fin, buffer);
	string buf;
	stringstream ss(buffer);
	vector<string> tokens;
	while (ss >> buf) {
		tokens.push_back(buf);
	}
	switch (tokens.size()) {
		case 3:
		fileConfig.natms = atoi(tokens[2].c_str());  // This is to deal with GULP files missing this value
		break;
		default:
		fileConfig.keytrj = atoi(tokens[0].c_str());
		fileConfig.imcon = atoi(tokens[1].c_str());
	}
	cout << "File has positions";
	if (fileConfig.keytrj == 1)
		cout << " and velocities";
	if (fileConfig.keytrj == 2)
		cout << ", velocities and forces";
	cout << "." << endl << endl;


	tokens.empty();

	// Here is space for cell parameters

	// Start getting atom data

	recordi step1;

	while (!fin.eof()) {

		fin >> step1.timestep;
		fin >> buffer;
		step1.nstep = atoi(buffer.c_str());
		fin >> buffer;
		step1.natms = atoi(buffer.c_str());
		fin >> buffer;
		step1.keytrj = atoi(buffer.c_str());
		fin >> buffer;
		step1.imcon = atoi(buffer.c_str());
		fin >> buffer;
		step1.tstep = strtod(buffer.c_str(), NULL);

		if (step1.natms == 0 ) {
			return 0;
		}
		cout << "Getting " << step1.natms << " atoms at timestep " << ( step1.nstep * step1.tstep ) << " ps." << endl;

		recordb xyz[step1.natms];
		getline(fin, buffer);
		for ( int i = 0; i < step1.natms ; i++ ) {
			fin >> buffer;
			fin >> buffer;
			fin >> buffer;
			fin >> buffer;  // This is where recorda is
			fin >> buffer;
			xyz[i].xxx = strtod(buffer.c_str(), NULL);
			fin >> buffer;
			xyz[i].yyy = strtod(buffer.c_str(), NULL);
			fin >> buffer;
			xyz[i].zzz = strtod(buffer.c_str(), NULL);
			fin >> buffer;
			fin >> buffer;
			fin >> buffer;
		}

		double S[( step1.natms / atomsInLayer )];
		memset( S, 0, sizeof(S) );

//		cout << "Processing " << ( step1.natms / atomsInLayer ) << " layers." << endl;

		bubbleSort ( xyz , step1.natms );

		for ( int layer = 0; layer < ( step1.natms / atomsInLayer ); layer++ ) {
			for ( int i = (0 + (atomsInLayer * layer)); i < (0 + (atomsInLayer*(layer + 1))); i++ ) {
				for ( int j = (0 + (atomsInLayer * layer)); j < (0 + (atomsInLayer*(layer + 1))); j++ ) {
					complex<double> omega (0.0 , ( ( xyz[i].xxx - xyz[j].xxx ) * k.xxx ) + ( (xyz[i].yyy - xyz[j].yyy ) * k.yyy ) );
					S[layer] = S[layer] + real ( exp ( omega ) );
				}
			}
			outPut << S[layer] / ( atomsInLayer * atomsInLayer ) << ",";
		}
		outPut << endl;
		//		cout << ( S / 64.0 ) << endl << ( ( S / 64.0 ) / 64.0 ) << endl;

	}

	outPut.close();
	fin.close();
	return 0;

}

/*
 
#include <iostream>
#include <complex>
using namespace std;
 
int main() {
	complex<double> yy(1.1,2.4), bb;
	bb=exp(yy);
	cout << yy << endl << bb;
	return 0;
}
*/
