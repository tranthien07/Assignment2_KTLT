#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

/* define class Account */

#include "common.h"
#define	DEFAULT_PASSWORD	"LIBPRO162"

enum AccStatus {
	DISABLE = 0,
	ACTIVE = 1,
};

class Account
{
private:
	string acc_id;
	string acc_password;
	string user_no;
	AccStatus acc_status;

public:
	Account();
	~Account();

	string GetAccID();
	void SetAccID(string id);

	void SetPassword(string password);
	bool MatchedPassword(string input_password);
	string GeneratePassword();

	string GetUserNo();
	void SetUserNo(string id);

	AccStatus GetAccStatus();
	void SetAccStatus(AccStatus status);

	/* functions that read/write info to/from file */
	streampos ReadAccInfo(string input_acc_id);
	int WriteAccInfo(streampos pos);
	
};

#endif