#ifndef _MANAGER_H_
#define _MANAGER_H_

/* define role Manager */

#include "common.h"
#include "role.h"

class Manager : public Role
{
public:
	Manager();
	~Manager();
	
	void PrintMenu();

	void FindUser();
	void FindUserNo();
	void FindUserName();
	void FindStudentNo();

	void ChooseAction(User *user, streampos matched_line_pos);
	void EditUser(User *user, streampos matched_line_pos);
	void DeleteUser(User *user, streampos matched_line_pos);

	void FindAccount();

	void ChooseAction(Account *acc, streampos matched_line_pos);
	void EditAcc(Account *acc, streampos matched_line_pos);
	void ResetPassword(Account *acc, streampos matched_line_pos);

	void CreateUser();
	string NextUserNo();
	void CreateAcc(string input_user_no);
};

#endif