#ifndef _LIBRATIAN_H_
#define _LIBRATIAN_H_

/* define role Librarian */

#include "common.h"
#include "role.h"

class Librarian : public Role
{
public:
	Librarian();
	~Librarian();
	
	void PrintMenu(string cur_user);
	void FindBook(string cur_user);
	void AddBook(string cur_user);
	void DeleteBook(string cur_user);
	void EditBook(string cur_user);
	void CheckRequest(string cur_user);
	void ChangePassword(string cur_user);
	bool check_pass(string cur_user);
	bool CheckBookId(char *file, string id);
	int GetAmountBookAccepted(string id_book);
	int GetAmountBook(string id_book);
	void WriteRequest(string user, string id_book);
	bool CheckBookIdUser(string user, string id_book);
	void CheckRequestBorrow(string cur_user);
	void DeleteRequest(string user, string id_book);
	void CheckDay();
	int FindId();
	void CheckReturnBook(string cur_user);
	void CheckLostBook(string cur_user);
	bool CheckBookIdUserStatus(string user, string id_book);
	void EditReturnBook(string user, string id_book);
};

#endif