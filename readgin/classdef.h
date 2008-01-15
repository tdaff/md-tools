#include <string>
using namespace std;

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
public:
	double cell1;
	double cell2;
	double cell3;
};
class recordiii {
public:
	double cell4;
	double cell5;
	double cell6;
};
class recordiv {
public:
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

