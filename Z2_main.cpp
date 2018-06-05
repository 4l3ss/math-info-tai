#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/stat.h>

#include "Z2_AF.h"

using namespace std;

bool fexists(const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}


string askFilename(){
    string filename = "Z2_none";
    do{
        cout << "Choisir un fichier test (seulement le numero) : ";
        int testNumber;
        cin >> testNumber;

        stringstream path;
        path << "Z2_" << testNumber << ".txt";
        filename = path.str();
    }while(!fexists(filename));

    return filename;
}

int main()
{
    string filename = askFilename();
    cout << "Fichier choisi : " << filename << endl;
    AF automate(filename);
    automate.afficherInfos();
    automate.est_asynchrone();
    return 0;
}
