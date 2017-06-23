#include "account.h"

Account::Account() {};

Account::~Account() {};

string Account::GetAccID()
{
    return acc_id;
}

void Account::SetAccID(string id)
{
    acc_id = id;
}

void Account::SetPassword(string password)
{
    acc_password = password;
}

bool Account::MatchedPassword(string input_password)
{
    return acc_password == input_password;
}

string Account::GetUserNo()
{
    return user_no;
}

void Account::SetUserNo(string id)
{
    user_no = id;
}

AccStatus Account::GetAccStatus()
{
    return acc_status;
}

void Account::SetAccStatus(AccStatus status)
{
    acc_status = status;
}

streampos Account::ReadAccInfo(string input_acc_id)
{
    string matched_line;
    streampos matched_line_pos;
    if(!FindID((char*)ACCOUNT_PATH, input_acc_id, matched_line, matched_line_pos)) {
        return (streampos)EOF;
    }

    vector<string> info;
    ReadLineInfo(matched_line, info);

    acc_id = info[0];
    acc_password = info[1];
    user_no = info[2];
    acc_status = (info[3] == "ACTIVE")?ACTIVE:DISABLE;
    //cout << acc_id << acc_password << user_no << acc_status << endl;

    return matched_line_pos;
}

int Account::WriteAccInfo(streampos pos)
{
    fstream account_f;
    account_f.open(ACCOUNT_PATH, ios::out | ios::in);
    if (!account_f.is_open()) {
        cout << "Error! Cannot open file!" << endl;
        return 0;
    }

    if (pos == (streampos)EOF) {
        account_f.seekp(0, account_f.end);
        if (account_f.tellp() != streampos(0))
            account_f << '\n';
        account_f << acc_id << "; " << acc_password << "; " << user_no << "; " << ((acc_status == ACTIVE)?"ACTIVE":"DISABLE") << ";";
    } else {
        fstream tmp_f;
        tmp_f.open(TMP_FILE, ios::out);

        if (!tmp_f.is_open()) {
            cout << "Cannot open file" << endl;
            return 0;
        }

        string line;
        while (!account_f.eof()) {
            if (account_f.tellg() != streampos(0))
                tmp_f << '\n';
            if (account_f.tellg() == pos) {
                getline(account_f, line);
                tmp_f << acc_id << "; " << acc_password << "; " << user_no << "; " << ((acc_status == ACTIVE)?"ACTIVE":"DISABLE") << ";";
            } else {
                getline(account_f, line);
                tmp_f << line;
            }
        }
        remove(ACCOUNT_PATH);
        rename(TMP_FILE, ACCOUNT_PATH);

        tmp_f.close();
    }
    account_f.close();
    return 1;
}

string Account::GeneratePassword()
{
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    acc_password = "";
    for (int i = 0; i < MIN_PASSWORD_LEN; ++i) {
        acc_password += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return acc_password;
}
