#include "reader.h"
#include "libpro.h"
Reader::Reader() : Role::Role("READER", "Reader") {};
Reader::~Reader() {};

void Reader::PrintMenu(string cur_user)
{
    int option = 0;
    do {
        CLR_SCR;
        cout << "1. Find book." << endl;
        cout << "2. Borrow book." << endl;
        cout << "3. Read info." << endl;
        cout << "4. Read notification." << endl;
        cout << "5. Read history." << endl;
        cout << "6. Change password." << endl;
        cout << "7. Back." << endl;
        do {
            cout << "Enter the number of option: ";
            cin >> option;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        } while (cin.fail() || option < 1 || option > 7);
        switch (option) {
        case 1:
            FindBook(cur_user);
            break;
        case 2:
            BorrowBook(cur_user);
            break;
        case 3:
            ReadInfo(cur_user);
            break;
        case 4:
            ReadNotification(cur_user);
            break;
        case 5:
            ReadHistory(cur_user);
            break;
        case 6:
            ChangePassword(cur_user);
            break;
        }
    } while (option != 7);
}

void Reader::FindBook(string cur_user)
{
    string input_word;
    CLR_SCR;
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
    if (count == 0)cout << "Empty" << endl;
    else {
        int choice = 0;
        do {
            cout << "Choose option: " << endl;
            cout << "1.Borrow book :" << endl;
            cout << "2.Continue Search :" << endl;
            cout << "3.Return :" << endl;

            cin >> choice;
            cin.clear();
            cin.ignore(INT_MAX, '\n');


        } while (cin.fail()||choice<1||choice>3);
        if(choice==1)
            BorrowBook(cur_user);
        else if (choice == 2)FindBook(cur_user);
        else if(choice == 3) PrintMenu(cur_user);
    }
    cin.ignore();

}
void Reader::BorrowBook(string cur_user)
{
    CLR_SCR;
    time_t hientai = time(0);
    char* dt = ctime(&hientai);

    string option;

    cout << "Choose book id: ";
    fflush(stdin);
    getline(cin, option);
    while (CheckBookId(BOOK_PATH, option) == 0|| CheckBookIdBorrow(cur_user,option)==1) {
        cout << "NO BOOK ID OR EXISTED , Do you want to try again (Y/N): ";
        fflush(stdin);
        getline(cin, option);
        if (option == "Y" || option == "y") {
            cout << "Choose book id: ";
            fflush(stdin);
            getline(cin, option);
        } else {

            PrintMenu(cur_user);
            break;
        }
    }
    if (CheckBookId(BOOK_PATH, option) == 1) {
        cout << "Borrow success" << endl;
        fstream my_file;
        my_file.open(BORROW_BOOK_PATH, ios::out | ios::app);
        my_file << cur_user << ";" << " ";
        my_file << option << ";" << " " ;
        my_file << "DISABLE" << ";" << " ";
        my_file << dt ;
        my_file.close();
    }

    string option1;
    while (true) {
        cout << "Do you want continue (Y/N) :";
        fflush(stdin);
        getline(cin, option1);
        if (option1 == "Y" || option1 == "y")BorrowBook(cur_user);
        else {
            PrintMenu(cur_user);
        }
    }
    cin.ignore();
}
void Reader::ReadInfo(string cur_user)
{
    CLR_SCR;
    cout << "BOOKS HAVEN'T RETURNED YET" << endl;
    ifstream book_is_not_return;
    string line;
    int number = 0;
    book_is_not_return.open(BOOK_NOT_RETURNED, ios::in);
    while (!book_is_not_return.eof()) {
        getline(book_is_not_return, line);
        if (line.empty()) continue;
        cout << ++number << ": " << line << endl;
    }
    cout << endl;
    cout << "BORROWED AND RETURNED BOOKS" << endl << endl;
    ifstream book_borrowed;
    number = 0;
    book_borrowed.open(BOOK_BORROWED_RETURNED, ios::in);
    cout << "BOOK BORROWED: " << endl;
    while (!book_borrowed.eof()) {
        getline(book_borrowed, line);
        if (line.empty()) continue;
        cout << ++number << ": " << line << endl;
    }
    ifstream book_returned;
    number = 0;
    cout << endl;
    cout << "BOOK RETURNED: " << endl;
    book_returned.open(BOOK_RETURNED_BORROWED, ios::in);
    while (!book_returned.eof()) {
        getline(book_returned, line);
        if (line.empty()) continue;
        cout << ++number << ": " << line << endl;
    }

    PressEnter();
}
void Reader::ReadHistory(string cur_user)
{
    CLR_SCR;
    ifstream my_file,my_file1;
    string line, acc, id, date,id1,line1,name,author,amount,status;
    istringstream iss,jss;
    my_file.open(BORROW_BOOK_PATH, ios::in);
    while (!my_file.eof()) {
        getline(my_file, line);

        iss.str(line);
        if (line.empty())continue;
        getline(iss, acc, SEP_CHAR);
        getline(iss, id, SEP_CHAR);
        getline(iss, status, SEP_CHAR);
        getline(iss, date);
        if (acc == cur_user) {
            cout << date<<" || "<<status<<" || "<<" ID : "<<id<<" || ";
            my_file1.open(BOOK_PATH, ios::in);
            while (!my_file1.eof()) {
                getline(my_file1, line1);
                jss.str(line1);
                if (line1.empty())continue;
                getline(jss, id1, SEP_CHAR);
                getline(jss, name, SEP_CHAR);
                getline(jss, author, SEP_CHAR);

                id1 = (" " + id1);
                if (id == id1) {
                    cout<<" || " << name<<" || "<<author<< endl;
                    break;
                }
            }
            my_file1.close();
        }
        iss.clear();
    }
    my_file.close();
    ReadHistoryNotAccept(cur_user);
    string option1;
    while (true) {
        cout << "Do you want continue (Y/N) :";
        fflush(stdin);
        getline(cin, option1);
        if (option1 == "Y" || option1 == "y")ReadHistory(cur_user);
        else {
            PrintMenu(cur_user);
        }
    }
    cin.ignore();
}
void Reader:: ReadHistoryNotAccept(string cur_user)
{
    ifstream my_file, my_file1;
    string line, acc, id, date, id1, line1, name, author, amount, status;
    istringstream iss, jss;
    my_file.open(BOOK_NOT_ACCEPT, ios::in);
    while (!my_file.eof()) {
        getline(my_file, line);

        iss.str(line);
        if (line.empty())continue;
        getline(iss, acc, SEP_CHAR);
        getline(iss, id, SEP_CHAR);
        getline(iss, status, SEP_CHAR);
        getline(iss, date);
        if (acc == cur_user) {
            cout << date << " || " << status << " || " << " ID : " << id << " || ";
            my_file1.open(BOOK_PATH, ios::in);
            while (!my_file1.eof()) {
                getline(my_file1, line1);
                jss.str(line1);
                if (line1.empty())continue;
                getline(jss, id1, SEP_CHAR);
                getline(jss, name, SEP_CHAR);
                getline(jss, author, SEP_CHAR);

                id1 = (" " + id1);
                if (id == id1) {
                    cout << " || " << name << " || " << author << endl;
                    break;
                }
            }
            my_file1.close();
        }
        iss.clear();
    }
    my_file.close();
}
void Reader::ChangePassword(string cur_user)
{
    CLR_SCR;
    fstream my_file, my_file1,my_file2;
    fstream my_file3, my_file4, my_file5;
    string line;
    string acc,password,status,id;
    istringstream iss;
    string pass;

    cout << " NOTE: password more than 6 characters and not special characters" << endl;
    cout << " Enter new password : " ;
    fflush(stdin);
    getline(cin, pass);
    while (check_pass(pass) == 0) {
        cout << "Do you want to try again (Y/N): ";
        fflush(stdin);
        getline(cin, pass);
        if (pass == "Y" || pass == "y") {
            cout << " Enter new password : ";
            fflush(stdin);
            getline(cin, pass);
        } else {
            break;
            PrintMenu(cur_user);
        }
    }
    if (check_pass(pass) == 1) {
        cout << "Change password success" << endl;
    }
    //cin.ignore();
    my_file.open(ACCOUNT_PATH, ios::in);
    my_file1.open(ACCOUNT1_PATH, ios::out|ios::trunc);
    while (!my_file.eof()) {
        getline(my_file, line);
        if (line.empty())continue;
        iss.str(line);
        getline(iss, acc, SEP_CHAR);
        getline(iss, password, SEP_CHAR);
        getline(iss, id, SEP_CHAR);
        getline(iss, status, SEP_CHAR);
        my_file2.open(ACCOUNT1_PATH, ios::out | ios::app);
        if (acc == cur_user) {

            password =pass;

            my_file2 << acc << ";" << " ";
            my_file2 << password << ";" ;
            my_file2 << id << ";" ;
            my_file2 << status << ";";
            my_file2 << endl;
            //continue;


        } else {


            my_file2 << acc << ";";
            my_file2 << password << ";";
            my_file2 << id << ";";
            my_file2 << status << ";";
            my_file2 << endl;
        }
        my_file2.close();


    }
    my_file.close();


    my_file3.open(ACCOUNT1_PATH, ios::in);
    my_file4.open(ACCOUNT_PATH, ios::out | ios::trunc);
    while (!my_file3.eof()) {
        getline(my_file3, line);
        if (line.empty())continue;
        iss.str(line);
        getline(iss, acc, SEP_CHAR);
        getline(iss, password, SEP_CHAR);
        getline(iss, id, SEP_CHAR);
        getline(iss, status, SEP_CHAR);
        my_file5.open(ACCOUNT_PATH, ios::out | ios::app);
        my_file5 << acc << ";";
        my_file5 << password << ";";
        my_file5 << id << ";";
        my_file5 << status << ";";
        my_file5 << endl;

        my_file5.close();


    }
    my_file3.close();
    cin.ignore();

}

bool Reader::CheckBookId(char *file, string id)
{
    ifstream my_file;
    string line, id_col, temp;
    istringstream iss;
    my_file.open(file, ios::in);
    while (!my_file.eof()) {
        getline(my_file, line);
        iss.str(line);
        getline(iss, id_col, SEP_CHAR);
        /* found */
        if (id_col == id) {
            my_file.close();
            return 1;
            break;
        }
    }
    my_file.close();
    return 0;
}
bool Reader::CheckBookIdBorrow(string cur_user, string id)
{
    ifstream my_file;
    string line, acc_user, id_book;
    istringstream iss;
    my_file.open(BORROW_BOOK_PATH, ios::in);
    while (!my_file.eof()) {
        getline(my_file, line);
        iss.str(line);
        getline(iss, acc_user, SEP_CHAR);
        getline(iss, id_book, SEP_CHAR);
        /* found */
        if (cur_user == acc_user&&(" "+id)==id_book) {
            my_file.close();
            return 1;
            break;
        }
    }
    my_file.close();
    return 0;
}
bool Reader::check_pass(string pass)
{
    int count = 0;
    istringstream iss(pass);
    while (iss) {
        string  sub;
        iss >> sub;
        count += sub.length();
    }
    if (pass.length() > count) {
        return 0;
    }
    if (pass.length() < 6) {
        return 0;
    }
    return 1;
}
void Reader::ReadNotification(string cur_user)
{
    CLR_SCR;
    cout << "LIST OF BOOKS IS UPDATED" << endl;
    ifstream book_update_info;
    string line;
    book_update_info.open(BOOK_UPDATE_PATH, ios::in);
    int number = 0;
    int i = 0;
    while (!book_update_info.eof()) {
        getline(book_update_info, line);
        if (line.empty()) continue;
        cout << ++number << ": " << line << endl;
        i++;
    }
    number = 0;
    cout << endl << "LIST OF BOOKS IS BORROWED" << endl;
    ifstream book_borrowed_info;
    book_borrowed_info.open(BOOK_BORROWED, ios::in);
    while (!book_borrowed_info.eof()) {
        getline(book_borrowed_info, line);
        if (line.empty()) continue;
        cout << ++number << ": " << line << endl;
        i++;
    }
    if (i == 0)
        CLR_SCR;
    cout << "TODAY ISN'T ACTIVE" << endl;

    PressEnter();
}
