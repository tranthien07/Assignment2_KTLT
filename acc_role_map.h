#ifndef _ACC_ROLE_MAP_H
#define _ACC_ROLE_MAP_H

#include "common.h"
#include "account.h"
#include "role.h"

class AccRoleMap
{
private:
	string acc_id;
	string role_id;

public:
	AccRoleMap();
	~AccRoleMap();
	
	string GetAccID();
	string GetRoleID();
	void ReadMapInfo(string matched_line);
};

#endif