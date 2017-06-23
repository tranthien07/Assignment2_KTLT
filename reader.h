#ifndef _READER_H_
#define _READER_H_

/* define class Reader */

#include "common.h"
#include "role.h"

class Reader : public Role
{
public:
	Reader();
	~Reader();
	void PrintMenu(string cur_user);
	void FindBook(string cur_user);
	void BorrowBook(string cur_user);
	void ReadInfo(string cur_user);
	void ReadNotification(string cur_user);
	void ReadHistory(string cur_user);
	void ReadHistoryNotAccept(string cur_user);
	void ChangePassword(string cur_user);
	void FindNameBook(char *file, string id, string &buffer);
	bool CheckBookId(char *file, string id);
	bool check_pass(string cur_user);
	bool CheckBookIdBorrow(string cur_user, string id);
};

#endif