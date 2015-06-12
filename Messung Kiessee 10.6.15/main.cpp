#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <unistd.h>
using namespace std;


int main()
{
    ifstream in ("Datenpunkte.txt");
    while(!in.eof()){
	   string dateiname, a;
	   stringstream ass;
	   in >> a;
	   ass << a;
	   dateiname = ass.str();
	   
	   //Automatisches erstellen einer Rahmendatei für Gnuplot und anschließendes plotten
	   ofstream plot ("plot.gp");
	   plot << "reset" << endl;
	   //plot << "set yrange [0:4]" << endl;
	   plot<< "set title '" << dateiname << "'" << endl;
	   plot << "set xrange [1200:1500]" << endl;
	   plot << "set yrange [20:35]" << endl;
	   plot << "p '" << dateiname.c_str() << "' u 3:2" << endl << "pause 0.3"; //Wenn das Fenster immer geöffnet bleiben soll, ist die 10 zu ersetzen mit -1
	   plot.close();
	   system("gnuplot plot.gp");
	}
    in.close();
    system("rm -f plot.gp");

    return 0;
}
