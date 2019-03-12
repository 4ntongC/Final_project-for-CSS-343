//
// Created by lloyd on 2019.03.11.
//

#include <iostream>
#include <fstream>
#include "Blockbuster.h"

using namespace std;

int main(){
    Blockbuster();

    ifstream commands ("data4commands.txt");
    string line;
    if (commands.is_open()){
        while (getline(commands, line)){
            cout << line << endl;
        }
        commands.close();
    }
    else{
        cout << "File not found." << endl;
    }
    return 0;
}