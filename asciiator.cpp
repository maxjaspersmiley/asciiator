#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//grabs characters from front of array until a comma or
//a newline is found. Returns the 1 to 3 digit integer
//from the head of the csv list, or -1 on failure. sets
//'good' to false if a newline character is found.

int pop_int(char* line, int& pos, bool& good){
    int rc = atoi(&line[pos]);
    int len = to_string(rc).length();
    if(line[pos + len] != ','){
        good = false;
        return -1;
    }
    pos += (len + 1);
    return rc;
}

int main(int argc, char** argv){
    if(argc != 3){
        cout << "Usage: ./asciiator [input_file] [output_file]\n";
        return -1;
    }
    ifstream infile;
    infile.open(argv[1]);
    if(!infile.good()){
        cout << "invalid input file\n";
        infile.close();
        return -1;
    }
    ofstream outfile;
    outfile.open(argv[2]);

    char line[2400] = {'\0'};

    while(!infile.eof()){
    infile.getline(line, 2400);

    int pos = 0;
    int count = 0;
    bool good = true;

    int expected = pop_int(line, pos, good);
    outfile << "__________________________\n";
    outfile << "Expected: " << expected << endl;
        while(good){ 
            if(pop_int(line,pos,good) < 128){
                outfile << " ";
            }
            else{
                outfile << "@";
            }
            count++;
            if(count % 28 == 0)
                outfile << endl;
        }
    outfile << "__________________________\n\n\n\n\n";
    }

    infile.close();
    outfile.close();
    return 0;
}
