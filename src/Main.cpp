
#include <fstream>
#include <string>
#include "MethodTester.h"
using namespace std;

ofstream outputFile;
int main(int argc, char** argv) {
    outputFile.open(argv[2]);
    MethodTester test(argv[1]);
    outputFile.close();

}