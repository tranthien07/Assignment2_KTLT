#include "common.h"


/*
 * FindID			: use to seach string in the first collumn of file
 * char *file 		: input - path of file
 * string id		: input - ID to search in file
 * string &buffer	: output - store whole line that contains id
 * return			: if found, return 1, else return 0
 */
streampos FindID(char *file, string id, string &buffer)
{
    ifstream my_file;
    string line, id_col;
    istringstream iss;
    streampos mactch_line_pos;

    my_file.open(file, ios::in);
    while (!my_file.eof()) {
        mactch_line_pos = my_file.tellg();
        getline(my_file, line);
        iss.str(line);
        getline(iss, id_col, SEP_CHAR);
        /* found */
        if (id_col == id) {
            buffer = line;
            my_file.close();
            return mactch_line_pos;
        }
    }
    /* not found */
    return (streampos)EOF;
}

int FindID(char *file, string id, string &buffer, streampos &mactch_line_pos)
{
    ifstream my_file;
    string line, id_col;
    istringstream iss;
    my_file.open(file, ios::in);
    while (!my_file.eof()) {
        mactch_line_pos = my_file.tellg();
        getline(my_file, line);
        iss.str(line);
        getline(iss, id_col, SEP_CHAR);
        /* found */
        if (id_col == id) {
            buffer = line;
            my_file.close();
            return 1;
        }
    }
    /* not found */
    my_file.seekg(0, ios::end);
    mactch_line_pos = my_file.tellg();
    my_file.close();
    return 0;
}

/*
 * ReadLineInfo : separate infomation line into different elements of vector
 * line			: line that store infomation
 * info 		: vector that store separated info
 */
void ReadLineInfo(string line, vector<string> &info)
{
    string str;
    istringstream iss(line);
    while (getline(iss, str, SEP_CHAR)) {
        if (info.size() > 0)	// remove first space character
            str = str.substr(1, str.length());
        info.push_back(str);
    }
}

void PressEnter()
{
    string s;
    cout << endl;
    cout << "Press Enter to continue..." << endl;
    cin.ignore(INT_MAX, '\n');
}

bool ValidNumber(string input_number, size_t len)
{
    if (input_number.length() != len)
        return 0;

    for (unsigned int i = 0; i < input_number.length(); ++i) {
        if (input_number[i] < '0' || input_number[i] > '9') {
            return 0;
        }
    }

    return 1;
}
