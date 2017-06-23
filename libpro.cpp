#include "libpro.h"

/*
 * ===============================
 * CONSTRUCTOR AND DESTRUCTOR
 * ===============================
 */

Libpro::Libpro() : executing(1), is_login(0) {}
Libpro::~Libpro() {}


/*
 * ===============================
 * MAIN FUNCTION OF CLASS LIBPRO
 * ===============================
 */

int Libpro::Execute()
{
    while (executing) {
        if (!is_login)
            MainMenu();
        else
            ChooseRole();
    }

    return 0;
}

/*
 * ===============================
 * IF NOT LOGIN, PRINT MAIN MENU
 * ===============================
 */

void Libpro::MainMenu()
{
    CLR_SCR;
    int option = 0;
    cout << " ====================" 	<< endl;
    cout 								<< endl;
    cout << "  WELCOME TO LIBPRO! " 	<< endl;
    cout 								<< endl;
    cout << " ====================" 	<< endl;
    cout 								<< endl;
    cout << " 1. Log in." 				<< endl;
    cout 								<< endl;
    cout << " 2. Find book."			<< endl;
    cout 								<< endl;
    cout << " 3. About us." 			<< endl;
    cout 								<< endl;
    cout << " 4. Exit."					<< endl;
    cout 								<< endl;

    do {
        cout << "Choose option: ";
        cin >> option;
        cin.clear();
        cin.ignore(INT_MAX,'\n');
    } while (cin.fail() || option < 1 || option > 4);

    switch (option) {
    case 1:
        LogIn();
        break;
    case 2:
        FindBook();
        break;
    case 3:
        AboutUs();
        break;
    case 4:
        Exit();
        break;
    }
}

/*
 * ===============================
 * LOGIN
 * ===============================
 */

void Libpro::LogIn()
{

    cur_acc = new Account;

    while (!is_login) {
        CLR_SCR;
        string input_account, input_password;
        cout << " ====================" << endl;
        cout 							<< endl;
        cout << "        LOG IN       "	<< endl;
        cout 							<< endl;
        cout << " ====================" << endl;
        cout 							<< endl;
        cout << "Enter your account : ";
        getline(cin, input_account);
        cout 							<< endl;
        cout << "Enter your password: ";
        getline(cin, input_password);
        cout 							<< endl;

        /* find account_id and check password */
        cur_acc->SetAccID(input_account);
        if (cur_acc->ReadAccInfo(input_account) == (streampos)EOF ||					// can't find account_id
                !cur_acc->MatchedPassword(input_password)) {// password is not matched
            string s;
            cout << "Account or Password not matched!" << endl;
            do {
                cout << "Do you want to try again? (Y/N): ";
                getline(cin, s);
                if (s == "N" || s == "n") {
                    delete cur_acc;
                    return;
                }
            } while (s != "Y" && s != "y" && s != "N" && s != "n");
        }

        /* account and password are matched
         * cur_acc also has been read successfully
         */
        else if (cur_acc->GetAccStatus() == DISABLE) {
            cout << "Account is disable. Contact admin for more infomation!" << endl;
            PressEnter();
        } else {
            is_login = 1;
            Setup();
            cout << "Login success!" << endl;
            PressEnter();
        }
    }
}


/*
 * ===============================
 * IF LOGIN, PRINT CHOOSE ROLE MENU
 * ===============================
 */

void Libpro::ChooseRole()
{
    CLR_SCR;
    cout << "Choose role: " << endl;
    int option = 0;
    int i;
    for (i = 0; i < cur_map.size(); ++i) {
        cout << i+1 << ". " << cur_map[i]->GetRoleID() << endl;
    }
    cout << i+1 << ". LOG OUT." << endl;
    cout << i+2 << ". EXIT." << endl;
    do {
        cout << "Enter the number of role: ";
        cin >> option;
        cin.clear();
        cin.ignore(INT_MAX,'\n');
    } while (cin.fail() || option < 1 || option > i+2);

    if (option == i+2)
        Exit();
    else if (option == i+1)
        LogOut();
    else if (option > 0 && option <= i) {
        string role_id = cur_map[option-1]->GetRoleID();
        if (role_id == "READER")
            reader->PrintMenu(cur_acc->GetAccID());
        else if (role_id == "LIBRARIAN")
            librarian->PrintMenu(cur_acc->GetAccID());
        else if (role_id == "MANAGER")
            manager->PrintMenu();
    } else
        cout << "Something wrong..." << endl;
}

/*
 * ===============================
 * EXIT & LOG OUT
 * ===============================
 */

void Libpro::Exit()
{
    // if is login, then log out first
    if (is_login)
        LogOut();

    CLR_SCR;
    cout << "LIBPRO exited!" << endl;
    executing = 0;
}

void Libpro::LogOut()
{
    is_login = 0;
    for (unsigned int i = 0; i < cur_map.size(); ++i) {
        if (cur_map[i]->GetRoleID() == "READER" && reader != NULL)
            delete reader;
        else if (cur_map[i]->GetRoleID() == "LIBRARIAN" && librarian != NULL)
            delete librarian;
        else if (cur_map[i]->GetRoleID() == "MANAGER" && manager != NULL)
            delete manager;
        delete cur_map[i];
    }
    cur_map.erase(cur_map.begin(), cur_map.end());
    if (cur_acc != NULL)
        delete cur_acc;
    if (cur_user != NULL)
        delete cur_user;
}

/*
 * ===============================
 * FUNCTIONS USED IN LogIn()
 * ===============================
 */

/* read all necessary infomation from file */
void Libpro::Setup()
{
    cur_user = new User;
    cur_user->ReadUserInfo(cur_acc->GetUserNo());
    int n_role = FindRole();
    if (n_role == 0) {
        string s;
        cout << "This account doesn't have any role! Press Enter to logout...";
        getline(cin, s);
        is_login = 0;
    } else {
        for (int i = 0; i < n_role; ++i) {
            //cout << cur_map[i]->GetRoleID() << endl;
            if (cur_map[i]->GetRoleID() == "READER")
                reader = new Reader;
            else if (cur_map[i]->GetRoleID() == "LIBRARIAN")
                librarian = new Librarian;
            else if (cur_map[i]->GetRoleID() == "MANAGER")
                manager = new Manager;
        }
    }
}

/* find out which roles are belong to current accout, return number of roles */
int Libpro::FindRole()
{
    int n_role = 0;
    ifstream acc_role_f;
    string line;
    istringstream iss;
    AccRoleMap *tmp_map = new AccRoleMap;
    acc_role_f.open(ACC_ROLE_MAP_PATH, ios::in);

    while (!acc_role_f.eof()) {
        getline(acc_role_f, line);
        tmp_map->ReadMapInfo(line);
        /* found */
        if (tmp_map->GetAccID() == cur_acc->GetAccID()) {
            n_role++;
            cur_map.push_back(tmp_map);
            tmp_map = new AccRoleMap;
        }
    }
    delete tmp_map;
    acc_role_f.close();
    return n_role;
}

/*
 * ===============================
 * FIND BOOK
 * ===============================
 */

void Libpro::FindBook()
{
    string input_word;
    CLR_SCR;
    cout << " ====================" << endl;
    cout 							<< endl;
    cout << "        FIND BOOK	  "	<< endl;
    cout 							<< endl;
    cout << " ====================" << endl;
    cout 							<< endl;
    cout << "Note: You can find books here, but you have to log in to borrow books!" << endl;
    cout << "-----" << endl;
    cout << "Search book: ";
    getline(cin, input_word);
    ifstream my_file;
    string line, id, name,author,amount;
    istringstream iss;
    my_file.open(BOOK_PATH, ios::in);
    int check = 2;
    int count = 0;
    cout << "ID; NAME BOOK; AUTHOR; AMOUNT" << endl;
    while (!my_file.eof()) {
        getline(my_file, line);
        if (line.empty())continue;
        iss.str(line);
        getline(iss, id, SEP_CHAR);
        getline(iss, name, SEP_CHAR);
        getline(iss, author, SEP_CHAR);
        getline(iss, amount, SEP_CHAR);
        int j = 0;
        int k = 0;
        for (int i = 1; i < name.length(); i++) {
            if (name[i] == input_word[0]) {
                j = 0;
                if (input_word.length() == 1) {
                    check = 1;
                    break;
                } else {
                    k = i;
                    while (j < (input_word.length() - 1)) {
                        j += 1;
                        k += 1;
                        if (name[k] == input_word[j]) {
                            check = 1;
                            continue;
                        } else {

                            check = 0;
                            break;
                        }
                    }
                    if (check != 1)i++;
                    else break;
                }

            } else {
                check = 0;
            }
        }
        if (check == 1) {
            //cout << line << endl;
            cout << id << "  " << name << "  " << author << "  " << amount << endl;
            count++;
        }
    }
    if (count == 0)
        cout << "Not found!" << endl;

    PressEnter();
}

/*
 * ===============================
 * ABOUT US
 * ===============================
 */

void Libpro::AboutUs()
{
    CLR_SCR;
    cout << " ====================" << endl;
    cout 							<< endl;
    cout << "       ABOUT US      " << endl;
    cout 							<< endl;
    cout << " ====================" << endl;
    cout 							<< endl;
    cout << " 1. Nguyen Mau Vinh." 	<< endl;
    cout 							<< endl;
    cout << " 2. Le Trong Hieu." 	<< endl;
    cout 							<< endl;
    cout << " 3. Nguyen Huu Khoa." 	<< endl;
    cout 							<< endl;
    cout << " 4. Tran Ngoc Thien." 	<< endl;

    PressEnter();
}
