#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;
double array[3][3];
double num;
int main(int argc, char** argv) {

  ifstream inFile;
  inFile.open("test.txt");
  if( !inFile) {
    cout << "Unable to open file";
  }

  int i = 0;
  while (inFile >> num) {
    (*array)[i] = num;
    // cout<<(*array)[i] <<endl;
    i++;
  }

  inFile.close();
  for( int row = 0; row < 2; row++ ) {
    for( int col = 0; col < 3; col++ ) {
      cout<< array[row][col];
    }
  }

  return 0;
}
