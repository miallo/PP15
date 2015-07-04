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
    int i = 0;
    ifstream in ("../Datenpunkte.txt");
    while(!in.eof()){
	   string dateiname, a;
	   stringstream ass;
	   in >> a;
	   ass << a;
	   dateiname = ass.str();
	   dateiname = "../OriginalMessdaten/" + dateiname;
	   //Automatisches erstellen einer Rahmendatei für Gnuplot und anschließendes plotten
	   ofstream plot ("plot.gp");
	   plot << "reset" << endl;
	   plot << "set terminal postscript color" << endl << "set output '" << dateiname << ".eps'" << endl;
	   //plot << "set yrange [0:4]" << endl;
	   plot<< "set title 'noch Schritte: " << 36-i << "     " << dateiname << "'" << endl;
// Temperatur Ranges:
		  // plot << "set xrange [1200:1500]" << endl;
	//	   plot << "set yrange [20:40]" << endl;
// Tiefe Range:
	   //plot << "set yrange [1200:1500]" << endl;
//	   plot << "p '" << dateiname.c_str() << "' u 0:(log($5)), '" << dateiname.c_str() << "' u 0:(($4-1013)/20), '" << dateiname.c_str() << "' u 0:(log($6))" << endl;
	   plot << "p '"<< dateiname.c_str() << "' u ($10*1.1):2" << endl;//, '" << dateiname.c_str() << "' u 0:
 	   plot << "set output" << endl;
	 //  plot << "pause 0.5"; //Wenn das Fenster immer geöffnet bleiben soll, ist die 10 zu ersetzen mit -1
	   plot.close();
	   system("gnuplot plot.gp");
	   //cin.get(); // Wartet auf Enter
	   //system("sleep 0.5");
	   i++;
	}
    in.close();
    system("rm -f plot.gp");

    return 0;
}
