@dropall
@createtable
@populate
@trg
@fun
@pro

declare
myvar number;
begin
	myvar:=fun_issue_anyedition(2,'DATA MANAGEMENT','C.J. DATES',to_date('03/03/05','MM/DD/YY'));
end;
/
declare
myvar number;
begin
	myvar:=fun_issue_anyedition(4,'CALCULUS','H. ANTON',to_date('03/04/05','MM/DD/YY'));
end;
/
declare
myvar number;
begin
	myvar:=fun_issue_anyedition(5,'ORACLE','ORACLE PRESS',to_date('03/04/05','MM/DD/YY'));
end;
/
declare
myvar number;
begin
	myvar:=fun_issue_anyedition(10,'IEEE MULTIMEDIA','IEEE',to_date('02/27/05','MM/DD/YY'));
end;
/
declare
myvar number;
begin
	myvar:=fun_issue_anyedition(2,'MIS MANAGEMENT','C.J. CATES',to_date('05/03/05','MM/DD/YY'));
end;
/
declare
myvar number;
begin
	myvar:=fun_issue_anyedition(4,'CALCULUS II','H. ANTON',to_date('03/04/05','MM/DD/YY'));
end;
/
declare
myvar number;
begin
	myvar:=fun_issue_anyedition(10,'ORACLE','ORACLE PRESS',to_date('03/04/05','MM/DD/YY'));
end;
/
declare
myvar number;
begin
	myvar:=fun_issue_anyedition(5,'IEEE MULTIMEDIA','IEEE',to_date('02/26/05','MM/DD/YY'));
end;
/
declare
myvar number;
begin
	myvar:=fun_issue_anyedition(2,'DATA STRUCTURE','W. GATES',to_date('03/03/05','MM/DD/YY'));
end;
/
declare
myvar number;
begin
	myvar:=fun_issue_anyedition(4,'CALCULUS III','H. ANTON',to_date('04/04/05','MM/DD/YY'));
end;
/
declare
myvar number;
begin
	myvar:=fun_issue_anyedition(11,'ORACLE','ORACLE PRESS',to_date('03/08/05','MM/DD/YY'));
end;
/
declare
myvar number;
begin
	myvar:=fun_issue_anyedition(6,'IEEE MULTIMEDIA','IEEE',to_date('02/17/05','MM/DD/YY'));	
	--DBMS_OUTPUT.PUT_LINE(myvar);
end;
/
declare
myvar number;
begin
	myvar:=fun_issue_book(8,12,to_date('01/17/06','MM/DD/YY'));	
	--DBMS_OUTPUT.PUT_LINE(myvar);
end;
/
declare
myvar number;
begin
	myvar:=fun_issue_book(9,11,to_date('10/17/06','MM/DD/YY'));	
	--DBMS_OUTPUT.PUT_LINE(myvar);
end;
/
declare
myvar number;
begin
	myvar:=fun_issue_book(3,8,to_date('12/17/06','MM/DD/YY'));	
	--DBMS_OUTPUT.PUT_LINE(myvar);
end;
/

execute pro_print_borrower;

execute pro_print_fine('10-APR-05');

declare
myvar number;
begin
	myvar:=fun_return_book(1,'06-MAR-05');
end;
/
declare
myvar number;
begin
	myvar:=fun_return_book(2,'07-MAR-05');
end;
/
declare
myvar number;
begin
	myvar:=fun_return_book(4,'01-MAR-05');
end;
/

select * from Pending_request;
select * from Issue;

execute pro_listborr_mon(4,'MAR');

execute pro_listborr_mon(4,'FEB');

execute pro_listborr;

execute pro_list_popular;

select avg(p.issue_date-p.request_date) AVG_WAIT_TIME from Pending_request p
where p.issue_date is not NULL;

select p.requester_id, b.name from Pending_request p, Borrower b
where (p.issue_date-p.request_date)=(select max(p1.issue_date-p1.request_date) from Pending_request p1
									where p.issue_date is not NULL)
		and p.requester_id=b.borrower_id;
















