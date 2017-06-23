#ifndef _COMMON_H_
#define _COMMON_H_

/* define structures, functions that use many time in this project */

#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <climits>
#include <iomanip>
#include <ctime>

/* define clear screen command */
#define CLR_SCR					system("cls")

/* define character use to separate info on each line */
#define SEP_CHAR				';'

/* define path to storage files */
#define USER_PATH				"data/user.txt"
#define TMP_USER_PATH			"data/tmp_user.txt"
#define ACCOUNT_PATH			"data/account.txt"
#define TMP_ACCOUNT_PATH		"data/tmp_account.txt"
#define ROLE_PATH				"data/role.txt"
#define BOOK_PATH				"data/book.txt"
#define ACC_ROLE_MAP_PATH		"data/acc_role_map.txt"
#define ACCOUNT1_PATH			"data/temp.txt"
#define	TMP_FILE				"data/temp.txt"
#define BORROW_BOOK_PATH		"data/borrow_book.txt"
#define BOOK_BORROWED			"data/book_borrowed.txt"
#define BOOK_UPDATE_PATH		"data/book_update.txt"
#define BOOK_NOT_RETURNED		"data/book_not_returned.txt"
#define BOOK_BORROWED_RETURNED	"data/book_borrowed_returned.txt"
#define BOOK_RETURNED_BORROWED	"data/book_returned_borrowed.txt"
#define BOOK_NOT_ACCEPT			"data/book_not_accept.txt"
#define AMERCE_LOST_BOOK		"data/amerce_lost_book.txt"

/* define length of user_no, student_no, password */
#define	USER_NO_LEN				7
#define STUDENT_NO_LEN			7
#define MIN_PASSWORD_LEN		8

/* define position type of file */
typedef unsigned long long position_t;

struct Date
{
	unsigned int day, month, year;
};

using namespace std;

streampos FindID(char *file, string id, string &buffer);
int FindID(char *file, string id, string &buffer, streampos &mactch_line_pos);

void ReadLineInfo(string line, vector<string> &info);

void PressEnter();

bool ValidNumber(string input_number, size_t len);

#endif