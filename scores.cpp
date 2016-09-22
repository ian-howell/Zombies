#include "scores.h"
#include <fstream>
using std::ifstream;
using std::ofstream;
using std::endl;

int read_highscores(const char* filename)
{
    int ret_val = 0;
    ifstream in;
    in.open(filename);

    if (in.is_open())
    {
        in >> ret_val;
        in.close();
    }

    return ret_val;
}

void write_highscores(const char* filename, int score)
{
    ofstream out;
    out.open(filename);

    if (out.is_open())
        out << score << endl;

    return;
}
