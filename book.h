#ifndef _BOOK_H_
#define _BOOK_H_

/*
 * define class Book
 * */
#include "common.h"
#define NUM_BOOKS	100

enum BookStatus {
	LOAN = 0,
	AVAILABLE = 1,
};

class Book {
private:
	string 			book_id;
	string 			book_name;
	BookStatus		book_status[NUM_BOOKS];	// status of each book (LOAN or AVAILABLE)
	vector<string> 	author;					// maybe there are more than 1 author
	int 			remain;					// number of remain books

public:
	Book();
	~Book();
	string GetBookName();
	void SetBookName(string name);
	
};

#endif