#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "Sistema.h"

using namespace std;

int main(int argc, char *argv[]){
    Sistema app;
    app.start();
    app.save();

    return 0;
}