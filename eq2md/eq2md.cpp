#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
	
	if (argc!=5) {
		cout << "Use me properly\nprocess T1 T2 eqtime mdtime";
		exit(0);
	}
	
	// Define some of the variables here
	string inputFilename,outputFilename,outputFilename2,buffer;
	
	// User input parameters
	cout << "Input filename:\n";
	cout << argv[1] << "Keq.res" << endl ;
	cout << "Output filename:\n";
	cout << argv[2] << "Keq.gin" << " and " << argv[1] << "Kmd.res" << endl;
	
	inputFilename = "Keq.res";
	inputFilename.insert(0,argv[1]);
	
	outputFilename = "Keq.gin";
	outputFilename.insert(0,argv[2]);
	outputFilename2 = "Kmd.gin";
	outputFilename2.insert(0,argv[1]);
	
	// Open file
	ifstream fin (inputFilename.c_str());
	ofstream fout (outputFilename.c_str());  // fout is equilibriation for higher temperature
	ofstream fout2 (outputFilename2.c_str());  // fout2 is md for first temperature
	if (!fin) {
		cout << "Failed to open file!";
		exit (1);
	}
	
	// Read header
	while (!fin.eof()) {
		getline (fin,buffer);
		if (!buffer.compare(0,4,"dump")) {
			fout << "dump " << argv[2] << "Keq.res\noutput movie arc " << argv[2] << "Keq.arc\noutput xyz " << argv[2] << "Keq.xyz\noutput history " << argv[2] << "Keq.his\nmdarchive " << argv[2] << "Keq.arc\n";
			fout2 << "dump " << argv[1] << "Kmd.res\noutput movie arc " << argv[1] << "Kmd.arc\noutput xyz " << argv[1] << "Kmd.xyz\noutput history " << argv[1] << "Kmd.his\nmdarchive " << argv[1] << "Kmd.arc\n";
			getline (fin,buffer);
			getline (fin,buffer);
			getline (fin,buffer);
			getline (fin,buffer);
		}
		/* Dummy dump
		dump 100Keq.res                                                
		output movie arc 100Keq.arc                                                  
		output xyz 100Keq.xyz                                                  
		output history 100Keq.his                                                  
		mdarchive 100Keq.arc
		*/
		else {
			if (!buffer.compare(0,11,"temperature")){
				fout << "temperature " << argv[2] << "\n";
				fout2 << "temperature " << argv[1] << "\n";
			}
			else {
				if (!buffer.compare(0,12,"equilibriate")){
					fout << "equilibriate " << argv[3] << " ps\n";
					fout2 << "production " << argv[4] << " ps\n";
				}
				else {
					if (!buffer.compare(0,12,"current_time")){
					fout << "current_time 0 ps\n";
					fout2 << "current_time 0 ps\n";
					}
					else {
						fout << buffer << endl;
						fout2 << buffer << endl;
					}
				}
			}	
		}
	}
	fout.close();
	fout2.close();
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
