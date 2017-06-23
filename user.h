#ifndef _USER_H_
#define _USER_H_

/* define class User */

#include "common.h"
#include "account.h"

class User
{
private:
	string 	user_no;
	string 	user_name;
	string 	student_no;
	Date	day_of_birth;
	string 	email;
	string 	user_job;
	//vector<Account*> user_accounts;

public:
	User();
	~User();

	string GetUserNo();
	void SetUserNo(string id);
	
	string GetUserName();
	void SetUserName(string name);

	string GetStudentNo();
	void SetStudentNo(string id);

	Date GetDoB();
	void SetDoB(Date date);

	string GetMail();
	void SetMail(string mail);

	string GetJob();
	void SetJob(string job);

	streampos ReadUserInfo(string input_user_no);
	int WriteUserInfo(streampos pos);
	void PrintUserInfo();
};

#endif