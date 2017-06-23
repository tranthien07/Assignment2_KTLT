#include "manager.h"

/*
 * ===============================
 * CONSTRUCTOR AND DESTRUCTOR
 * ===============================
 */

Manager::Manager() : Role::Role("MANAGER", "manager") {};
Manager::~Manager() {};

/*
 * ===============================
 * PRINT MENU
 * ===============================
 */

void Manager::PrintMenu()
{
    int option = 0;
    do {
        CLR_SCR;
        cout << "MANAGER" << endl;
        cout << "1. Find user." 			<< endl;
        cout << "2. Find account." 			<< endl;
        cout << "3. Create user / account."	<< endl;
        cout << "4. Back." 					<< endl;
        do {
            cout << "Enter the number of option: ";
            cin >> option;
            cin.clear();
            cin.ignore(INT_MAX,'\n');
        } while (cin.fail() || option < 1 || option > 4);

        switch (option) {
        case 1:
            FindUser();
            break;
        case 2:
            FindAccount();
            break;
        case 3:
            CreateUser();
            break;
        }
    } while (option != 4);
}

/*
 * ===============================
 * FIND USER
 * ===============================
 */

// menu
void Manager::FindUser()
{
    int option = 0;
    do {
        CLR_SCR;
        cout << "FIND USER" << endl;
        cout << "1. Find by user number." << endl;
        cout << "2. Find by user name." << endl;
        cout << "3. Find by student number." << endl;
        cout << "4. Back." << endl;
        do {
            cout << "Enter the number of option: ";
            cin >> option;
            cin.clear();
            cin.ignore(INT_MAX,'\n');
        } while (cin.fail() || option < 1 || option > 4);

        switch (option) {
        case 1: {
            FindUserNo();
            break;
        }
        case 2:
            FindUserName();
            break;
        case 3: {
            FindStudentNo();
            break;
        }
        }
    } while (option != 4);
}

// find user by user number
void Manager::FindUserNo()
{
    string input_user_no;
    User *found_user = new User;

    CLR_SCR;
    cout << "FIND USER BY USER NUMBER" << endl;
    cout << "Enter user number: ";
    getline(cin, input_user_no);

    // check validity of input user number
    while (!ValidNumber(input_user_no, USER_NO_LEN)) {
        cout << "User number must contain 7 digits!" << endl;
        cout << "Enter user number: ";
        getline(cin, input_user_no);
    }

    // open user.txt
    streampos matched_line_pos = found_user->ReadUserInfo(input_user_no);
    if (matched_line_pos != streampos(0))
        ChooseAction(found_user, matched_line_pos);
    else
        cout << "NOT FOUND!" << endl;

    if (found_user != NULL)
        delete found_user;
    PressEnter();
}

// find by user name
void Manager::FindUserName()
{
    CLR_SCR;
    cout << "FIND USER BY NAME" << endl;
    cout << "Enter user name: ";
    string input_user_name;
    getline(cin, input_user_name);

    // open file and file all name that matched
    ifstream user_f;
    string line;
    vector<string> matched_line;
    vector<streampos> matched_line_pos;
    user_f.open(USER_PATH, ios::in);
    getline(user_f, line);				// ignore first line, contain next id
    while (!user_f.eof()) {
        vector<string> info;
        getline(user_f, line);
        ReadLineInfo(line, info);
        if (info[1].find(input_user_name) != std::string::npos) {
            matched_line.push_back(line);
            matched_line_pos.push_back(user_f.tellg());
        }
    }
    user_f.close();

    if (matched_line.size() > 0) {
        // print all user has been found
        cout << "FOUND " << matched_line.size() << " RESULT(s)!" << endl;
        int num_user;
        for (num_user = 0; num_user < matched_line.size(); ++num_user) {
            vector<string> info;
            ReadLineInfo(matched_line[num_user], info);
            User *found_user = new User;
            found_user->ReadUserInfo(info[0]);
            cout << endl << num_user+1 << ". " << endl;
            cout << "----------" << endl;
            found_user->PrintUserInfo();
            cout << "----------" << endl;
            if (found_user != NULL)
                delete found_user;
        }
        cout << endl << num_user+1 << ". Back" << endl;

        // choose user to edit / delete
        int option = 0;
        do {
            cout << "Choose user: ";
            cin >> option;
            cin.clear();
            cin.ignore(INT_MAX,'\n');
        } while (cin.fail() || option < 1 || option > num_user + 1);

        if (option == num_user + 1)
            return;

        User *found_user = new User;
        found_user->ReadUserInfo(matched_line[option-1].substr(0, USER_NO_LEN));
        CLR_SCR;
        ChooseAction(found_user, matched_line_pos[option-1]);
    } else
        cout << "NOT FOUND!" << endl;

    PressEnter();
}

// find by student number
void Manager::FindStudentNo()
{
    User *found_user = new User;

    CLR_SCR;
    cout << "FIND USER BY STUDENT NUMBER" << endl;
    cout << "Enter student number: ";
    string input_student_no;
    getline(cin, input_student_no);

    // check validity
    while (!ValidNumber(input_student_no, STUDENT_NO_LEN)) {
        cout << "Student number must contain 7 digits!" << endl;
        cout << "Enter your student number: ";
        getline(cin, input_student_no);
    }

    // find
    ifstream user_f;
    string line;
    streampos matched_line_pos;
    bool found = false;
    user_f.open(USER_PATH, ios::in);
    getline(user_f, line);				// ignore first line, contain next id
    while (!user_f.eof()) {
        vector<string> info;
        matched_line_pos = user_f.tellg();
        getline(user_f, line);
        ReadLineInfo(line, info);
        if (info[2] == input_student_no) {
            found = true;
            found_user->SetUserNo(info[0]);
            found_user->SetUserName(info[1]);
            found_user->SetStudentNo(info[2]);
            //day_of_birth.day = stoi(info[3].substr(0,2));
            found_user->SetMail(info[4]);
            found_user->SetJob(info[5]);
            break;
        }
    }
    user_f.close();

    if (found)
        ChooseAction(found_user, matched_line_pos);
    else
        cout << "NOT FOUND!" << endl;

    if (found_user != NULL)
        delete found_user;

    PressEnter();
}

/*
 * ===============================
 * EDIT & DELETE USER
 * ===============================
 */

void Manager::ChooseAction(User *user, streampos matched_line_pos)
{
    cout << "FOUND! INFOMATION: " << endl;
    user->PrintUserInfo();
    int option = 0;
    cout << "Choose action: " << endl;
    cout << "1. Edit user." 	<< endl;
    cout << "2. Delete user." 	<< endl;
    cout << "3. Back."			<< endl;
    do {
        cout << "Enter the number of option: ";
        cin >> option;
        cin.clear();
        cin.ignore(INT_MAX,'\n');
    } while (cin.fail() || option < 1 || option > 3);

    switch (option) {
    case 1:
        EditUser(user, matched_line_pos);
        break;
    case 2:
        DeleteUser(user, matched_line_pos);
        break;
    }
}

void Manager::EditUser(User *user, streampos matched_line_pos)
{
    CLR_SCR;
    cout << "EDIT USER" << endl;
    cout << "(Press Enter to ignore infomation that you dont want to edit.)" << endl;

    // get new info
    string tmp_str = "";
    cout << "Enter new user name: ";
    getline(cin, tmp_str);
    if (tmp_str != "")
        user->SetUserName(tmp_str);

    tmp_str = "";
    cout << "Enter new student number: ";
    getline(cin, tmp_str);
    while (tmp_str != "" && !ValidNumber(tmp_str, STUDENT_NO_LEN)) {
        cout << "Student number must contain 7 digits!" << endl;
        cout << "Enter new student number: ";
        getline(cin, tmp_str);
    }
    if (tmp_str != "")
        user->SetStudentNo(tmp_str);

    tmp_str = "";
    cout << "Enter new email: ";
    getline(cin, tmp_str);
    if (tmp_str != "")
        user->SetMail(tmp_str);

    tmp_str = "";
    cout << "Enter new job: ";
    getline(cin, tmp_str);
    if (tmp_str != "")
        user->SetJob(tmp_str);

    // write new info to file
    if (user->WriteUserInfo(matched_line_pos))
        cout << "Edit user successfully!" << endl;
}

void Manager::DeleteUser(User *user, streampos matched_line_pos)
{
    string s = "";
    do {
        cout << "Are you sure you want to delete this user? (Y/N): ";
        getline(cin, s);
    } while (s != "Y" && s != "y" && s != "N" && s != "n");

    // if not, return
    if (s == "N" || s == "n")
        return;

    // if yes, disable all account that belong to this user
    ifstream account_f;
    string line;
    vector<string> acc_matched_line;
    vector<streampos> acc_matched_line_pos;
    account_f.open(ACCOUNT_PATH, ios::in);
    getline(account_f, line);              // ignore first line, contain next id
    while (!account_f.eof()) {
        vector<string> info;
        getline(account_f, line);
        ReadLineInfo(line, info);
        if (info[2].find(user->GetUserNo()) != std::string::npos) {
            acc_matched_line.push_back(line);
            acc_matched_line_pos.push_back(account_f.tellg());
        }
    }
    account_f.close();

    user->SetUserNo("");
    if (user->WriteUserInfo(matched_line_pos))
        cout << "Delete user successfully!" << endl;
}

/*
 * ===============================
 * FIND ACCOUNT
 * ===============================
 */

void Manager::FindAccount()
{
    Account *found_acc = new Account;

    CLR_SCR;
    cout << "FIND ACCOUNT" << endl;
    cout << "Enter account id: ";
    string input_acc_id;
    getline(cin, input_acc_id);

    streampos matched_line_pos = found_acc->ReadAccInfo(input_acc_id);

    if (matched_line_pos != (streampos)EOF)
        ChooseAction(found_acc, matched_line_pos);
    else
        cout << "NOT FOUND!" << endl;

    PressEnter();

    if (found_acc != NULL)
        delete found_acc;
}

/*
 * ===============================
 * EDIT ACCOUNT & RESET PASSWORD
 * ===============================
 */

void Manager::ChooseAction(Account *acc, streampos matched_line_pos)
{
    cout << "FOUND! INFOMATION: " << endl;
    cout << left
         << setw(14) << "Account id"	 << ": " << acc->GetAccID() << endl
         << setw(14) << "User number" 	 << ": " << acc->GetUserNo() << endl
         << setw(14) << "Account status" << ": " << ((acc->GetAccStatus() == ACTIVE)?"ACTIVE":"DISABLE") << endl;

    int option = 0;
    cout << "Choose action: " << endl;
    cout << "1. Edit account." 		<< endl;
    cout << "2. Reset password." 	<< endl;
    cout << "3. Back."				<< endl;
    do {
        cout << "Enter the number of option: ";
        cin >> option;
        cin.clear();
        cin.ignore(INT_MAX,'\n');
    } while (cin.fail() || option < 1 || option > 3);

    switch (option) {
    case 1:
        EditAcc(acc, matched_line_pos);
        break;
    case 2:
        ResetPassword(acc, matched_line_pos);
        break;
    }
}

void Manager::EditAcc(Account *acc, streampos matched_line_pos)
{
    CLR_SCR;
    cout << "EDIT USER" << endl;

    // get new user_no
    string tmp_str = "";
    cout << "Link this account to another user (press Enter to ignore)." << endl;
    cout << "Enter new user number: ";
    getline(cin, tmp_str);
    while (tmp_str != "" && !ValidNumber(tmp_str, USER_NO_LEN)) {
        cout << "User number must contain 7 digits!" << endl;
        cout << "Enter new student number: ";
        getline(cin, tmp_str);
    }
    if (tmp_str != "")
        acc->SetUserNo(tmp_str);

    // active / disable account
    do {
        cout << "Do you want to " << (((acc->GetAccStatus() == ACTIVE)?"DISABLE":"ACTIVE")) << " this account? (Y/N): ";
        getline(cin, tmp_str);
    } while (tmp_str != "Y" && tmp_str != "y" && tmp_str != "N" && tmp_str != "n");
    if (tmp_str == "Y" || tmp_str == "y")
        ((acc->GetAccStatus() == ACTIVE)?acc->SetAccStatus(DISABLE):acc->SetAccStatus(ACTIVE));

    // write new info to file
    if (acc->WriteAccInfo(matched_line_pos))
        cout << "Edit account successfully!" << endl;
}

void Manager::ResetPassword(Account *acc, streampos matched_line_pos)
{
    string s;
    do {
        cout << "Are you sure you want to reset password of this account? (Y/N): ";
        getline(cin, s);
    } while (s != "Y" && s != "y" && s != "N" && s != "n");

    // if not, return
    if (s == "N" || s == "N")
        return;

    string new_password = "";
    // if yes, reset password
    if (s == "Y" || s == "y") {
        new_password = acc->GeneratePassword();
    }

    if (acc->WriteAccInfo(matched_line_pos)) {
        cout << "Reset password successfully!" << endl;
        cout << "New password is: " << new_password << endl;
    }

    PressEnter();
}

/*
 * ===============================
 * CREATE USER / ACCOUNT
 * ===============================
 */

void Manager::CreateUser()
{
    User *new_user = new User;

    CLR_SCR;
    cout << "Enter student number: ";
    string input_student_no;
    getline(cin, input_student_no);

    // check validity
    while (!ValidNumber(input_student_no, STUDENT_NO_LEN)) {
        cout << "Student number must contain 7 digits!" << endl;
        cout << "Enter your student number: ";
        getline(cin, input_student_no);
    }

    // find
    ifstream user_f;
    string line;
    streampos matched_line_pos;
    bool found = false;
    user_f.open(USER_PATH, ios::in);
    getline(user_f, line);				// ignore first line, contain next id
    while (!user_f.eof()) {
        vector<string> info;
        matched_line_pos = user_f.tellg();
        getline(user_f, line);
        ReadLineInfo(line, info);
        if (info[2] == input_student_no) {
            found = true;
            new_user->SetUserNo(info[0]);
            new_user->SetUserName(info[1]);
            new_user->SetStudentNo(info[2]);
            //day_of_birth.day = stoi(info[3].substr(0,2));
            new_user->SetMail(info[4]);
            new_user->SetJob(info[5]);
            break;
        }
    }
    user_f.close();

    if (found) {
        cout << "Student number already exist!" << endl;
        string s;
        do {
            cout << "Do you want to create new account for this user? (Y/N): ";
            getline(cin, s);
        } while (s != "Y" && s != "y" && s != "N" && s != "n");
        if (s == "Y" || s == "y")
            CreateAcc(new_user->GetUserNo());
    } else {
        CLR_SCR;
        new_user->SetUserNo(NextUserNo());
        new_user->SetStudentNo(input_student_no);

        cout << "CREATE NEW USER" << endl;
        string str;
        cout << "Enter your full name: ";
        getline(cin, str);
        new_user->SetUserName(str);
        cout << "Enter your email: ";
        getline(cin, str);
        new_user->SetMail(str);
        cout << "Enter your job: ";
        getline(cin, str);
        new_user->SetJob(str);

        new_user->WriteUserInfo((streampos)EOF);
        CreateAcc(new_user->GetUserNo());
    }

    if (new_user != NULL)
        delete new_user;

    PressEnter();
}

string Manager::NextUserNo()
{
    fstream user_f;
    istringstream iss;
    string line;
    string next_user_no = "";
    user_f.open(USER_PATH, ios::in | ios::out);
    // temp user_no is on the first line of file with format:
    // "next id; xxxxxxx"
    // so we need get first line and remove "next id; "
    if (getline(user_f, line)) {
        iss.str(line);
        getline(iss, next_user_no, SEP_CHAR);
        getline(iss, next_user_no, SEP_CHAR);
        iss.clear();
        // remove first space
        next_user_no = next_user_no.substr(1, next_user_no.length());

        // increase user_no by 1
        iss.str(next_user_no);
        int next_number = 0;
        iss >> next_number;
        next_number++;
        user_f.clear();
        user_f.seekp(0, ios::beg);
        user_f << "next_id; " << setfill('0') << setw(7) << next_number << "\n";
    }
    user_f.close();
    return next_user_no;
}

void Manager::CreateAcc(string input_user_no)
{
    Account *new_acc = new Account;
    CLR_SCR;
    string input_acc_id, matched_line;
    cout << "CREATE NEW ACCOUNT" << endl;
    cout << "Enter account: ";
    getline(cin, input_acc_id);

    if(FindID((char*)ACCOUNT_PATH, input_acc_id, matched_line) != (streampos)EOF) {
        cout << "Account already exist!" << endl;
        return;
    }
    new_acc->SetAccID(input_acc_id);
    new_acc->SetPassword(DEFAULT_PASSWORD);
    new_acc->SetUserNo(input_user_no);
    new_acc->SetAccStatus(ACTIVE);

    new_acc->WriteAccInfo((streampos)EOF);
    cout << "Create account successfully!" << endl;

    if (new_acc != NULL)
        delete new_acc;
}
