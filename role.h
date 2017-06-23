#ifndef _ROLE_H_
#define _ROLE_H_

/* define class Role */

#include "common.h"
#include "user.h"
#include "account.h"
#include "book.h"

class Role
{
private:
	string role_id;
	string role_desc;

public:
	Role(string id, string desc);
	~Role();
	
};

#endif