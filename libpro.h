#ifndef _LIBPRO_H_
#define _LIBPRO_H_

/* define functions which not belong any class */

#include "common.h"
#include "user.h"
#include "account.h"
#include "book.h"
#include "role.h"
#include "reader.h"
#include "librarian.h"
#include "manager.h"
#include "acc_role_map.h"

class Libpro
{
private:
	bool executing;					// while (executing) {run libpro}
	bool is_login;					// determine state of libpro (is login or not)
	Account *cur_acc;				// current account is login
	User *cur_user;					// current user is login
	vector<AccRoleMap*> cur_map;	// map from current account to to roles
	Reader *reader;
	Librarian *librarian;
	Manager *manager;

	void MainMenu();
	void ChooseRole();

	
	void LogIn();

	void Exit();
	void LogOut();

	int FindRole();
	void Setup();

	void FindBook();

	void AboutUs();

public:
	Libpro();
	~Libpro();

	int Execute();
};
    
#endif