rem EE 562 project2
rem Yinglai Wang
rem wang1105


create table Books(
	book_id number primary key,
	book_title varchar2(50),
	author_id number,
	year_of_publication number,
	edition number,
	status varchar2(20)
);

create table Author(
	author_id number primary key,
	name varchar2(30)
);

create table Borrower(
	borrower_id number primary key,
	name varchar2(30),
	status varchar2(20)
);

create table Issue(
	book_id number,
	borrower_id number,
	issue_date date,
	return_date date,
	primary key(book_id, borrower_id, issue_date),
	foreign key(book_id) references Books(book_id),
	foreign key(borrower_id) references Borrower(borrower_id)
);

create table Pending_request(
	book_id number,
	requester_id number,
	request_date date,
	issue_date date,
	primary key(book_id, requester_id, request_date),
	foreign key(book_id) references Books(book_id)
);