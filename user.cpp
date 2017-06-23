#include "user.h"

User::User() {};
User::~User() {};

/*
 * ===============================
 * GETTER / SETTER
 * ===============================
 */
string User::GetUserNo()
{
    return user_no;
}

void User::SetUserNo(string id)
{
    user_no = id;
}

void User::SetUserName(string name)
{
    user_name = name;
}

void User::SetStudentNo(string id)
{
    student_no = id;
}


void User::SetMail(string mail)
{
    email = mail;
}

void User::SetJob(string job)
{
    user_job = job;
}

/*
 * ===============================
 * READ / WRITE FILE
 * ===============================
 */

streampos User::ReadUserInfo(string input_user_no)
{
    // find
    string matched_line;
    streampos matched_line_pos;
    if(!FindID((char*)USER_PATH, input_user_no, matched_line, matched_line_pos)) {
        return 0;
    }

    vector<string> info;
    ReadLineInfo(matched_line, info);

    user_no = info[0];
    user_name = info[1];
    student_no = info[2];
    //day_of_birth.day = stoi(info[3].substr(0,2));
    email = info[4];
    user_job = info[5];
    //cout << user_no << " " << user_name << " " << student_no << " " << email << " " << user_job << endl;

    return matched_line_pos;
}

int User::WriteUserInfo(streampos pos)
{
    fstream user_f;
    user_f.open(USER_PATH, ios::out | ios::in);
    if (!user_f.is_open()) {
        cout << "Error! Cannot open file!" << endl;
        return 0;
    }
    // write new user at end of find
    user_f.seekp(0, ios::end);
    if (pos == (streampos)EOF) {
        user_f.seekp(0, ios::end);
        user_f << "\n" << user_no << "; " << user_name << "; " << student_no << "; " << "day of birth" << "; " << email << "; " << user_job << ";";
    }
    // write edited or deleted user in temporary file, and rename it
    else {
        fstream tmp_f;
        tmp_f.open(TMP_FILE, ios::out);
        if (!tmp_f.is_open()) {
            cout << "Error! Cannot open file!" << endl;
            return 0;
        }

        string line;
        getline(user_f, line);
        tmp_f << line;

        while (!user_f.eof()) {
            if (user_f.tellg() == pos && user_no != "") {
                getline(user_f, line);
                tmp_f << '\n' << user_no << "; " << user_name << "; " << student_no << "; " << "day of birth" << "; " << email << "; " << user_job << ";";
            } else if (user_f.tellg() != pos) {
                getline(user_f, line);
                tmp_f << '\n' << line;
            } else
                getline(user_f, line);
        }
        remove(USER_PATH);
        rename(TMP_FILE, USER_PATH);
        tmp_f.close();
    }
    user_f.close();
    return 1;
}

void User::PrintUserInfo()
{
    cout << left
         << setw(15) << "User number" 	 << ": " << user_no 	<< endl
         << setw(15) << "Name" 			 << ": " << user_name 	<< endl
         << setw(15) << "Student number" << ": " << student_no 	<< endl
         << setw(15) << "Email" 		 << ": " << email 		<< endl
         << setw(15) << "Job" 			 << ": " << user_job 	<< endl;
}
