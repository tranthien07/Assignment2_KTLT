#include "librarian.h"

Librarian::Librarian() : Role::Role("LIBRARIAN", "librarian") {};
Librarian::~Librarian() {};

void Librarian::PrintMenu(string cur_user)
{
    CLR_SCR;
    int option = 0;
    cout << "1. Find book." 		<< endl;
    cout << "2. Add book." 			<< endl;
    cout << "3. Delete book." 		<< endl;
    cout << "4. Edit book." 		<< endl;
    cout << "5. Check request."		<< endl;
    cout << "6. Change password."	<< endl;
    cout << "7. Back." 				<< endl;
    do {
        cout << "Enter the number of option: ";
        cin >> option;
        cin.clear();
        cin.ignore(INT_MAX,'\n');
    } while (cin.fail() || option < 1 || option > 7);
    switch (option) {
    case 1:
        FindBook(cur_user);

        break;
    case 2:

        AddBook(cur_user);
        cin.ignore();
        break;
    case 3:
        DeleteBook(cur_user);

        break;
    case 4:
        EditBook(cur_user);

        break;
    case 5:
        CheckRequestBorrow(cur_user);

        break;
    case 6:
        ChangePassword(cur_user);

        break;
    case 7:
        break;
    }

}
void Librarian::FindBook(string cur_user)
{
    string input_word;
    CLR_SCR;
    cout << "Search book: ";
    getline(cin, input_word);
    ifstream my_file;
    string line, id, name, author, amount;
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
    string option1;
    while (true) {
        cout << "Do you want continue (Y/N) :";
        fflush(stdin);
        getline(cin, option1);
        if (option1 == "Y" || option1 == "y")FindBook(cur_user);
        else {
            PrintMenu(cur_user);
        }
    }

    cin.ignore();

}

int Librarian::FindId()
{
    string id;

    int book_id;
    string line;
    ifstream my_file;
    istringstream iss;
    my_file.open(BOOK_PATH, ios::in);
    while (!my_file.eof()) {

        getline(my_file, line);
        if (line.empty())continue;
        iss.str(line);
        iss >> book_id;

    }

    my_file.close();
    return book_id;

}
void Librarian:: DeleteBook(string cur_user)
{
    CLR_SCR;
    fstream my_file, my_file1, my_file2;
    fstream my_file3, my_file4, my_file5;
    string line;
    string id, name, author, amount;
    istringstream iss;
    string book_id;
    cout << " Enter book id delete : ";
    fflush(stdin);
    getline(cin, book_id);
    while (CheckBookId(BOOK_PATH, book_id) == 0) {
        cout << "NO BOOK ID , Do you want to try again (Y/N): ";
        fflush(stdin);
        getline(cin, book_id);
        if (book_id == "Y" || book_id == "y") {
            cout << "Enter book id delete : ";
            fflush(stdin);
            getline(cin, book_id);
        } else {

            PrintMenu(cur_user);
            break;
        }
    }
    cout << "DELETE SUCCESS :" << endl;
    my_file.open(BOOK_PATH, ios::in);
    my_file1.open(ACCOUNT1_PATH, ios::out | ios::trunc);
    while (!my_file.eof()) {
        getline(my_file, line);
        if (line.empty())continue;
        iss.str(line);
        getline(iss, id, SEP_CHAR);
        getline(iss, name, SEP_CHAR);
        getline(iss, author, SEP_CHAR);
        getline(iss, amount, SEP_CHAR);
        my_file2.open(ACCOUNT1_PATH, ios::out | ios::app);
        if (book_id!=id) {

            my_file2 << id << ";";
            my_file2 << name << ";";
            my_file2 << author << ";";
            my_file2 << amount << ";";
            my_file2 << endl;


        }
        my_file2.close();
    }
    my_file.close();


    my_file3.open(ACCOUNT1_PATH, ios::in);
    my_file4.open(BOOK_PATH, ios::out | ios::trunc);
    while (!my_file3.eof()) {
        getline(my_file3, line);
        if (line.empty())continue;
        iss.str(line);
        getline(iss, id, SEP_CHAR);
        getline(iss, name, SEP_CHAR);
        getline(iss, author, SEP_CHAR);
        getline(iss, amount, SEP_CHAR);
        my_file5.open(BOOK_PATH, ios::out | ios::app);
        my_file5 << id << ";";
        my_file5 << name << ";";
        my_file5 << author << ";";
        my_file5 << amount << ";";
        my_file5 << endl;

        my_file5.close();


    }
    my_file3.close();
    string option1;
    while (true) {
        cout << "Do you want continue (Y/N) :";
        fflush(stdin);
        getline(cin, option1);
        if (option1 == "Y" || option1 == "y")DeleteBook(cur_user);
        else {
            PrintMenu(cur_user);
        }
    }
    cin.ignore();


}
void Librarian::EditBook(string cur_user)
{
    CLR_SCR;
    fstream my_file, my_file1, my_file2;
    fstream my_file3, my_file4, my_file5;
    string line;
    string id, name, author, amount;
    istringstream iss;
    string book_id,book_name,book_author,book_amount;
    cout << " Enter book id  : ";
    fflush(stdin);
    getline(cin, book_id);
    while (CheckBookId(BOOK_PATH, book_id) == 0) {
        cout << "NO BOOK ID , Do you want to try again (Y/N): ";
        fflush(stdin);
        getline(cin, book_id);
        if (book_id == "Y" || book_id == "y") {
            cout << "Enter book id : ";
            fflush(stdin);
            getline(cin, book_id);
        } else {

            PrintMenu(cur_user);
            break;
        }
    }
    cout << " Enter book new name  : ";
    fflush(stdin);
    getline(cin, book_name);
    cout << " Enter book new author : ";
    fflush(stdin);
    getline(cin, book_author);
    cout << " Enter book new amount : ";
    fflush(stdin);
    getline(cin, book_amount);
    cout << "EDIT SUCCESS :" << endl;
    //cin.ignore();
    my_file.open(BOOK_PATH, ios::in);
    my_file1.open(ACCOUNT1_PATH, ios::out | ios::trunc);
    while (!my_file.eof()) {
        getline(my_file, line);
        if (line.empty())continue;
        iss.str(line);
        getline(iss, id, SEP_CHAR);
        getline(iss, name, SEP_CHAR);
        getline(iss, author, SEP_CHAR);
        getline(iss, amount, SEP_CHAR);
        my_file2.open(ACCOUNT1_PATH, ios::out | ios::app);
        if (book_id == id) {



            my_file2 << id << ";" << " ";
            my_file2 << book_name << ";"<<" ";
            my_file2 << book_author << ";"<<" ";
            my_file2 << book_amount << ";"<<" ";
            my_file2 << endl;
            //continue;


        } else {


            my_file2 << id << ";";
            my_file2 << name << ";";
            my_file2 << author << ";";
            my_file2 << amount << ";";
            my_file2 << endl;
        }
        my_file2.close();


    }
    my_file.close();


    my_file3.open(ACCOUNT1_PATH, ios::in);
    my_file4.open(BOOK_PATH, ios::out | ios::trunc);
    while (!my_file3.eof()) {
        getline(my_file3, line);
        if (line.empty())continue;
        iss.str(line);
        getline(iss, id, SEP_CHAR);
        getline(iss, name, SEP_CHAR);
        getline(iss, author, SEP_CHAR);
        getline(iss, amount, SEP_CHAR);
        my_file5.open(BOOK_PATH, ios::out | ios::app);
        my_file5 << id << ";";
        my_file5 << name << ";";
        my_file5 << author << ";";
        my_file5 << amount << ";";
        my_file5 << endl;

        my_file5.close();


    }
    my_file3.close();
    string option1;
    while (true) {
        cout << "Do you want continue (Y/N) :";
        fflush(stdin);
        getline(cin, option1);
        if (option1 == "Y" || option1 == "y")EditBook(cur_user);
        else {
            PrintMenu(cur_user);
        }
    }

    cin.ignore();

}
void Librarian::ChangePassword(string cur_user)
{
    CLR_SCR;
    fstream my_file, my_file1, my_file2;
    fstream my_file3, my_file4, my_file5;
    string line;
    string acc, password, status, id;
    istringstream iss;
    string pass;

    cout << " NOTE: password more than 6 characters and not special characters" << endl;
    cout << " Enter new password : ";
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
    my_file1.open(ACCOUNT1_PATH, ios::out | ios::trunc);
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

            password = pass;

            my_file2 << acc << ";" << " ";
            my_file2 << password << ";";
            my_file2 << id << ";";
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
bool Librarian::check_pass(string pass)
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
bool Librarian::CheckBookId(char *file, string id)
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
int Librarian::GetAmountBook(string id_book)
{
    ifstream my_file;
    string line, id, name, author;
    int amount;
    char n;
    istringstream iss;
    my_file.open(BOOK_PATH, ios::in);
    while (!my_file.eof()) {
        getline(my_file, line);
        iss.str(line);
        getline(iss, id, SEP_CHAR);
        getline(iss, name, SEP_CHAR);
        getline(iss, author, SEP_CHAR);
        iss >> amount;
        /* found */
        if (id == id_book) {
            my_file.close();
            return amount;
            break;
        }
        iss.clear();
    }
    my_file.close();
    return amount;

}
int Librarian::GetAmountBookAccepted(string id_book)
{
    ifstream my_file;
    string line, acc, id, status;
    int amount;
    int count = 0;
    istringstream iss;
    my_file.open(BORROW_BOOK_PATH, ios::in);
    while (!my_file.eof()) {
        getline(my_file, line);
        if (line.empty()) continue;
        iss.str(line);
        getline(iss, acc, SEP_CHAR);
        getline(iss, id, SEP_CHAR);
        getline(iss, status, SEP_CHAR);
        /* found */
        if (id == " " + id_book && status == " ACTIVE") {
            count++;
        }
        iss.clear();
    }
    my_file.close();
    return count;
}
void Librarian::CheckRequestBorrow(string cur_user)
{
    CLR_SCR;
    int count = 0;
    ifstream my_file, my_file1;
    string line, acc, id, date, id1, line1, name, author, amount, status;
    istringstream iss, jss;
    my_file.open(BORROW_BOOK_PATH, ios::in);
    while (!my_file.eof()) {
        getline(my_file, line);
        iss.str(line);
        if (line.empty())continue;
        getline(iss, acc, SEP_CHAR);
        getline(iss, id, SEP_CHAR);
        getline(iss, status, SEP_CHAR);
        getline(iss, date);
        if (status == " DISABLE") {
            cout << acc << " || " << id << " || ";
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
                    count++;
                    cout << name << " || " << author << endl;
                    break;
                }
            }
            my_file1.close();
        }
        iss.clear();
    }
    my_file.close();
    if (count != 0) {

        cout << "Accept Book. Enter ID book: ";
        string id_book;
        string user_book;
        fflush(stdin);
        getline(cin, id_book);
        cout << "Enter Acount: ";
        fflush(stdin);
        getline(cin, user_book);
        while (CheckBookIdUser(user_book, id_book) == 0) {
            cout << "Not Exist" << endl;
            cout << "Enter ID again: ";
            fflush(stdin);
            getline(cin, id_book);
            cout << "Enter Acount: ";
            fflush(stdin);
            getline(cin, user_book);

        }
        if (GetAmountBookAccepted(id_book) < GetAmountBook(id_book)) {
            cout << " ACCEPT SUCCESS" << endl;
            WriteRequest(user_book, id_book);
        } else {
            cout << "NOT ACCEPT" << endl;
            DeleteRequest(user_book, id_book);
        }
    }
    string option1;
    while (true) {
        cout << "Do you want continue (Y/N) :";
        fflush(stdin);
        getline(cin, option1);
        if (option1 == "Y" || option1 == "y")CheckRequestBorrow(cur_user);
        else {
            PrintMenu(cur_user);
        }
    }
    cin.ignore();
}
void Librarian::WriteRequest(string user, string id_book)
{
    fstream my_file, my_file1, my_file2;
    fstream my_file3, my_file4, my_file5;
    string line;
    string id, name, author, amount, acc, status, date;
    istringstream iss;
    my_file.open(BORROW_BOOK_PATH, ios::in);
    my_file1.open(ACCOUNT1_PATH, ios::out | ios::trunc);
    while (!my_file.eof()) {
        getline(my_file, line);
        if (line.empty())continue;
        iss.str(line);
        getline(iss, acc, SEP_CHAR);
        getline(iss, id, SEP_CHAR);
        getline(iss, status, SEP_CHAR);
        getline(iss, date);
        my_file2.open(ACCOUNT1_PATH, ios::out | ios::app);
        if ((" " + id_book) == id&&acc == user&&status==" DISABLE") {

            my_file2 << acc << ";";
            my_file2 << id << ";" << " ";
            my_file2 << "ACTIVE" << ";";
            my_file2 << date << endl;;
        } else {
            my_file2 << acc << ";";
            my_file2 << id << ";";
            my_file2 << status << ";";
            my_file2 << date << endl;
        }
        iss.clear();
        my_file2.close();
    }
    my_file.close();


    my_file3.open(ACCOUNT1_PATH, ios::in);
    my_file4.open(BORROW_BOOK_PATH, ios::out | ios::trunc);
    while (!my_file3.eof()) {
        getline(my_file3, line);
        if (line.empty())continue;
        iss.str(line);
        getline(iss, acc, SEP_CHAR);
        getline(iss, id, SEP_CHAR);
        getline(iss, status, SEP_CHAR);
        getline(iss, date);
        iss.clear();
        my_file5.open(BORROW_BOOK_PATH, ios::out | ios::app);
        my_file5 << acc << ";";
        my_file5 << id << ";";
        my_file5 << status << ";";
        my_file5 << date << endl;
        my_file5.close();
    }
    my_file3.close();
}
void Librarian:: DeleteRequest(string user, string id_book)
{
    fstream my_file, my_file1, my_file2,my_file_not_borrow;
    fstream my_file3, my_file4, my_file5;
    string line;
    string id, name, author, amount, acc, status, date;
    istringstream iss;
    my_file.open(BORROW_BOOK_PATH, ios::in);
    my_file1.open(ACCOUNT1_PATH, ios::out | ios::trunc);

    while (!my_file.eof()) {
        getline(my_file, line);
        if (line.empty())continue;
        iss.str(line);
        getline(iss, acc, SEP_CHAR);
        getline(iss, id, SEP_CHAR);
        getline(iss, status, SEP_CHAR);
        getline(iss, date);
        my_file2.open(ACCOUNT1_PATH, ios::out | ios::app);
        my_file_not_borrow.open(BOOK_NOT_ACCEPT, ios::out | ios::app);
        if ((" " + id_book) == id&&acc == user&&status == " DISABLE") {

            my_file_not_borrow << acc << ";";
            my_file_not_borrow << id << ";";
            my_file_not_borrow << status << ";";
            my_file_not_borrow << date << endl;
        } else {
            my_file2 << acc << ";";
            my_file2 << id << ";";
            my_file2 << status << ";";
            my_file2 << date << endl;
        }
        iss.clear();
        my_file_not_borrow.close();
        my_file2.close();
    }
    my_file.close();


    my_file3.open(ACCOUNT1_PATH, ios::in);
    my_file4.open(BORROW_BOOK_PATH, ios::out | ios::trunc);
    while (!my_file3.eof()) {
        getline(my_file3, line);
        if (line.empty())continue;
        iss.str(line);
        getline(iss, acc, SEP_CHAR);
        getline(iss, id, SEP_CHAR);
        getline(iss, status, SEP_CHAR);
        getline(iss, date);
        iss.clear();
        my_file5.open(BORROW_BOOK_PATH, ios::out | ios::app);
        my_file5 << acc << ";";
        my_file5 << id << ";";
        my_file5 << status << ";";
        my_file5 << date << endl;
        my_file5.close();
    }
    my_file3.close();
}
//bool Librarian::CheckBookId(string id) {
//	ifstream my_file;
//	string line, id_col, temp;
//	istringstream iss;
//	my_file.open(BOOK_PATH, ios::in);
//	while (!my_file.eof()) {
//		getline(my_file, line);
//		iss.str(line);
//		getline(iss, id_col, SEP_CHAR);
//		/* found */
//		if (id_col == id) {
//			my_file.close();
//			return 1;
//			break;
//		}
//	}
//	my_file.close();
//	return 0;
//}
bool Librarian::CheckBookIdUser(string user, string id_book)
{
    ifstream my_file;
    string line, user_name, id, status;
    istringstream iss;
    my_file.open(BORROW_BOOK_PATH, ios::in);
    while (!my_file.eof()) {
        getline(my_file, line);
        iss.str(line);
        getline(iss, user_name, SEP_CHAR);
        getline(iss, id, SEP_CHAR);
        getline(iss, status, SEP_CHAR);
        /* found */
        if ((user_name == user) && (id == (" " + id_book)) && (status == " DISABLE")) {
            my_file.close();
            return 1;
            break;
        }
    }
    my_file.close();
    return 0;
}

void Librarian::AddBook(string cur_user)
{
    fstream my_file;
    fstream book_update_file;
    do {
        CLR_SCR;
        string name_book, author, amount, option;
        int book_id = FindId() + 1;
        cout << "Name book: ";
        fflush(stdin);
        getline(cin, name_book);
        cout << "Author: ";
        getline(cin, author);
        cout << "Amount: ";
        getline(cin, amount);
        my_file.open(BOOK_PATH, ios::out | ios::app);
        book_update_file.open(BOOK_UPDATE_PATH, ios::out | ios::app);
        if (book_id < 10) {
            my_file << "00" << book_id << ";" << " ";
            book_update_file << "00" << book_id << " || " << " ";
        } else if (book_id < 100) {
            my_file << "0" << book_id << ";" << " ";
            book_update_file << "0" << book_id << " || " << " ";
        } else {
            my_file << book_id << ";" << " ";
            book_update_file << book_id << " || " << " ";
        }
        my_file << name_book << ";" << " ";
        book_update_file << name_book << " || " << " ";
        my_file << author << ";" << " ";
        book_update_file << author << " || " << " ";
        my_file << amount << ";" << " " << endl;
        book_update_file << amount << " || " << " " << endl;
        cout << "ADD SUCCESS" << endl;
        cout << "Do you want continue (Y/N): ";
        fflush(stdin);
        getline(cin, option);
        if (option == "Y" || option == "y");
        else {
            PrintMenu(cur_user);
        }
        my_file.close();
    } while (true);

}

void Librarian::CheckRequest(string cur_user)
{
    CLR_SCR;
    int option;
    cout << "1. Check Borrow Book." << endl;
    cout << "2. Check Return Book." << endl;
    cout << "3. Check Expire Book." << endl;
    cout << "4. Check Lost Book." << endl;
    cout << "5. Back."<< endl;
    do {
        cout << "Enter the number of option: ";
        cin >> option;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    } while (cin.fail() || option < 1 || option > 5);
    switch (option) {
    case 1:
        CheckRequestBorrow(cur_user);
        break;
    case 2:
        CheckReturnBook(cur_user);
        break;
    // case 3: CheckExpireBook(cur_user);
    // break;
    case 4:
        CheckLostBook(cur_user);
        break;
    case 5:
        PrintMenu(cur_user);
        break;
    }
}

void Librarian::CheckReturnBook(string cur_user)
{
    int count = 0;
    fstream my_file, my_file1;
    string line,line1;
    istringstream iss, jss;
    string acc, id, status;
    string id1, name, author;
    my_file.open(BORROW_BOOK_PATH, ios::in);
    while (!my_file.eof()) {
        getline(my_file, line);
        iss.str(line);
        if (line.empty())continue;
        getline(iss, acc, SEP_CHAR);
        getline(iss, id, SEP_CHAR);
        getline(iss, status, SEP_CHAR);
        if (status == " ACTIVE") {
            cout << acc << " || " << id << " || ";
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
                    count = 1;
                    cout << name << " || " << author << endl;
                    break;
                }
            }
            my_file1.close();
        }
        iss.clear();
    }
    if (count == 0) {
        CLR_SCR;
        cout << "EMPTY" << endl;
        cout << "Enter to comeback";
        cin.ignore();
        CheckRequest(cur_user);
    } else {
        my_file.close();
        string id_acc, id_book;
        cout << "Input ID Account: ";
        fflush(stdin);
        getline(cin, id_acc);
        cout << "Input ID Book: ";
        fflush(stdin);
        getline(cin, id_book);
        while (CheckBookIdUserStatus(id_acc, id_book) == 0) {
            cout << "NOT EXIST \n";
            cout << "Input ID Account Again: ";
            fflush(stdin);
            getline(cin, id_acc);
            cout << "Input ID Book Again: ";
            fflush(stdin);
            getline(cin, id_book);
            cout << endl;
        }
        string option1;
        EditReturnBook(id_acc, id_book);
        while (true) {
            cout << "Do you want continue (Y/N) :";
            fflush(stdin);
            getline(cin, option1);
            if (option1 == "Y" || option1 == "y") CheckReturnBook(cur_user);
            else {
                CheckRequest(cur_user);
            }
        }
        cin.ignore();
    }
}

void Librarian::CheckLostBook(string cur_user)
{
    time_t now = time(0);
    string dt = ctime(&now);
    string id_acc, id_book;
    cout << "Enter ID Account: ";
    fflush(stdin);
    getline(cin, id_acc);
    cout << "Enter ID Book: ";
    fflush(stdin);
    getline(cin, id_book);
    int count_check = 0;
    while (CheckBookIdUserStatus(id_acc, id_book) == 0) {
        CLR_SCR;
        cout << "NOT EXIST" << endl;
        cout << "Enter ID Account again: ";
        fflush(stdin);
        getline(cin, id_acc);
        cout << "Enter ID Book again: ";
        fflush(stdin);
        getline(cin, id_book);
    }
    string amerce;
    CLR_SCR;
    cout << "Enter Content of Consequences: ";
    getline(cin, amerce);
    fstream amerce_lost_book;
    amerce_lost_book.open(AMERCE_LOST_BOOK, ios::out | ios::app);
    amerce_lost_book << id_acc << "; " << amerce << "; " << dt;
    amerce_lost_book.close();
    fstream my_file, my_file1, my_file2, my_file3, my_file4, my_file5;
    string line, id_account, id_bookes, status_book;
    string date;
    stringstream iss;
    my_file.open(BORROW_BOOK_PATH, ios::in);
    my_file1.open(ACCOUNT1_PATH, ios::out | ios::trunc);
    while (!my_file.eof()) {
        getline(my_file, line);
        if (line.empty()) continue;
        iss.str(line);
        getline(iss, id_account, SEP_CHAR);
        getline(iss, id_bookes, SEP_CHAR);
        getline(iss, status_book, SEP_CHAR);
        getline(iss, date);
        my_file2.open(ACCOUNT1_PATH, ios::out | ios::app);
        if (id_account == id_acc && id_bookes ==" "+ id_book && status_book == " ACTIVE") {
        } else {
            my_file2 << id_account << ";";
            my_file2 << id_bookes << ";";
            my_file2 << status_book << ";";
            my_file2 << date << endl;
        }
        my_file2.close();
        iss.clear();
    }
    my_file.close();
    my_file3.open(ACCOUNT1_PATH, ios::in);
    my_file4.open(BORROW_BOOK_PATH, ios::out | ios::trunc);
    while (!my_file3.eof()) {
        getline(my_file3, line);
        if (line.empty())continue;
        iss.str(line);
        getline(iss, id_account, SEP_CHAR);
        getline(iss, id_bookes, SEP_CHAR);
        getline(iss, status_book, SEP_CHAR);
        getline(iss, date);
        my_file5.open(BORROW_BOOK_PATH, ios::out | ios::app);
        my_file5 << id_account << ";";
        my_file5 << id_bookes << ";";
        my_file5 << status_book << ";";
        my_file5 << date << endl;
        my_file5.close();
        iss.clear();
    }
    my_file3.close();
    cin.ignore();
    CheckRequest(cur_user);
}

bool Librarian::CheckBookIdUserStatus(string user, string id_book)
{
    ifstream my_file;
    string line, user_name, id, status;
    istringstream iss;
    my_file.open(BORROW_BOOK_PATH, ios::in);
    while (!my_file.eof()) {
        getline(my_file, line);
        iss.str(line);
        getline(iss, user_name, SEP_CHAR);
        getline(iss, id, SEP_CHAR);
        getline(iss, status, SEP_CHAR);
        /* found */
        if (user_name == user && id == (" " + id_book) && status == " ACTIVE") {
            my_file.close();
            return 1;
            break;
        }
    }
    my_file.close();
    return 0;
}

void Librarian::EditReturnBook(string user, string id_book)
{
    fstream my_file, my_file1, my_file2, my_file_not_borrow;
    fstream my_file3, my_file4, my_file5;
    string line;
    string id, name, author, amount, acc, status, date;
    istringstream iss;
    time_t now = time(0);
    char* dt = ctime(&now);
    my_file.open(BORROW_BOOK_PATH, ios::in);
    my_file1.open(ACCOUNT1_PATH, ios::out | ios::trunc);
    while (!my_file.eof()) {
        getline(my_file, line);
        if (line.empty())continue;
        iss.str(line);
        getline(iss, acc, SEP_CHAR);
        getline(iss, id, SEP_CHAR);
        getline(iss, status, SEP_CHAR);
        getline(iss, date);
        my_file2.open(ACCOUNT1_PATH, ios::out | ios::app);
        my_file_not_borrow.open(BOOK_NOT_ACCEPT, ios::out | ios::app);
        if ((" " + id_book) == id&&acc == user&&status == " ACTIVE") {

            /*my_file_not_borrow << acc << ";";
            my_file_not_borrow << id << ";";
            my_file_not_borrow << status << ";";
            my_file_not_borrow << date << endl;*/
        } else {
            my_file2 << acc << ";";
            my_file2 << id << ";";
            my_file2 << status << ";";
            my_file2 << date << endl;
        }
        iss.clear();
        my_file_not_borrow.close();
        my_file2.close();
    }
    my_file.close();


    my_file3.open(ACCOUNT1_PATH, ios::in);
    my_file4.open(BORROW_BOOK_PATH, ios::out | ios::trunc);
    while (!my_file3.eof()) {
        getline(my_file3, line);
        if (line.empty())continue;
        iss.str(line);
        getline(iss, acc, SEP_CHAR);
        getline(iss, id, SEP_CHAR);
        getline(iss, status, SEP_CHAR);
        getline(iss, date);
        iss.clear();
        my_file5.open(BORROW_BOOK_PATH, ios::out | ios::app);
        my_file5 << acc << ";";
        my_file5 << id << ";";
        my_file5 << status << ";";
        my_file5 << date << endl;
        my_file5.close();
    }
    my_file3.close();
}
