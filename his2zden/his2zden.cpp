#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

int main() {
	// Class Definitions
	class record1 {
	public:
		string header;
	};
	class record2 {
	public:
		int keytrj;
		int imcon;
		int natms;
	};
	class recordi {
	public:
		string timestep;
		int nstep;
		int natms;
		int keytrj;
		int imcon;
		double tstep;
	};
	class recordii {
		double cell1;
		double cell2;
		double cell3;
	};
	class recordiii {
		double cell4;
		double cell5;
		double cell6;
	};
	class recordiv {
		double cell7;
		double cell8;
		double cell9;
	};
	class recorda {
	public:
		string atmnam;
		int iatm;
		double weight;
		double charge;
	};
	class recordb {
	public:
		double xxx;
		double yyy;
		double zzz;
	};
	class recordc {
	public:
		double vxx;
		double vyy;
		double vzz;
	};
	class recordd {
	public:
		double fxx;
		double fyy;
		double fzz;
	};
	// Define some of the variables here
	string inputFilename, outputFilename, buffer;
	float resolution;
	record1 fileHeader;
	record2 fileConfig;
	
	// User input parameters
	cout << "Input filename: ";
	getline (cin, inputFilename);
	cout << "Output filename: ";
	getline (cin, outputFilename);
	cout << "Resolution of densities (Angstroms): ";
	cin >> resolution;
	
	// Open file
	ifstream fin (inputFilename.c_str());
	if (!fin) {
		cout << "Failed to open file \"" << inputFilename << "\"!";
		exit (1);
	}
	
	// Read header
	getline (fin,fileHeader.header);
	cout << "File header: " << endl << fileHeader.header << endl;
	
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
	if(fileConfig.keytrj == 1)
		cout << " and velocities";
	if(fileConfig.keytrj == 2)
		cout << ", velocities and forces";
	cout << "." << endl;


	tokens.empty();
	
	// Here is space for cell parameters
	
	// Start getting atom data

	recordi step1;
	int zden[500];
	memset( zden, 0, sizeof(zden) );

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

		cout << endl << "Processing " << step1.natms << " atoms at timestep " << ( step1.nstep * step1.tstep ) << " ps.";

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
		for ( int i = 0; i < step1.natms; i++ ) {
			//	cout << xyz[i].xxx << " " << xyz[i].yyy << " " << xyz[i].zzz << endl;
			int blah = (int) (100.5 - ((xyz[i].zzz ) / resolution ));
			zden[blah]++;
			//	cout << blah << endl;
		}

	}

	ofstream outPut (outputFilename.c_str());
	for ( int i = 0; i < 500; i++ ) {
		outPut << -resolution*(i-100) << "," << zden[i] << endl;
	}
	outPut.close();
	fin.close();
	return 0;

}

/*
 
atoi()
 
int main(int argc, char
*
argv[])
{
// declare the File pointer object
fstream File;
int NumPoints=0;
cout < <"Please enter the number of points to create"<<endl;
cin >> NumPoints;
// array of points to be written to a file
Point
*
pointsOut = new Point [NumPoints];
// array of points to be read into the file
Point
*
pointsIn = new Point [NumPoints];
// check we have a command line argument
if (argc <=1)
{
cout <<"Usage BinIO [filename] "<<endl;
exit(0);
}
// set the random seed so we get different values each
// time we run the program
srand(time(NULL));
// Open the file for writing
File.open(argv[1],ios::out|ios::binary);
 */


// Stringstreaming
