SET SERVEROUTPUT ON;

create or replace procedure pro_print_borrower is
	 
	name varchar2(30);
	title varchar2(50);
	day number;
	begin
		DBMS_OUTPUT.PUT_LINE(rpad('BORROWER_NAME',20)||chr(9)||
							rpad('BOOK_TITLE',20)||chr(9)||
							rpad('<=5DAYS',9)||
							rpad('<=10DAYS',9)||
							rpad('<=15DAYS',9)||
							rpad('>=15DAYS',9));
		DBMS_OUTPUT.PUT_LINE(rpad('----------',20)||chr(9)||
							rpad('----------',20)||chr(9)||
							rpad('--------',9)||
							rpad('--------',9)||
							rpad('--------',9)||
							'--------');
		for iter in (select bo.name as name, b.book_title as title, 
					round(current_date-i.issue_date,0) as day
					from Books b, Borrower bo, Issue i
					where b.book_id=i.book_id and bo.borrower_id=i.borrower_id 
					and i.return_date is NULL)
			loop
				if(iter.day<=5) then
					DBMS_OUTPUT.PUT_LINE(rpad(iter.name,20)||chr(9)||
										rpad(iter.title,20)||rpad(chr(9),7)||
										rpad(iter.day,9));
				elsif(iter.day<=10) then
					DBMS_OUTPUT.PUT_LINE(rpad(iter.name,20)||chr(9)||
										rpad(iter.title,20)||chr(9)||
										rpad(chr(9),8)||
										rpad(iter.day,9));
				elsif(iter.day<=15) then
					DBMS_OUTPUT.PUT_LINE(rpad(iter.name,20)||chr(9)||
										rpad(iter.title,20)||chr(9)||
										rpad(chr(9),8)||rpad(chr(9),8)||
										rpad(iter.day,9));
				else
					DBMS_OUTPUT.PUT_LINE(rpad(iter.name,20)||chr(9)||
										rpad(iter.title,20)||chr(9)||
										chr(9)||rpad(chr(9),9)||chr(9)||
										rpad(iter.day,9));
				end if;
			end loop;
	end;
/

create or replace procedure pro_print_fine 
	(c_dat IN date)
	is
	name varchar(30);
	id number;
	dat date;
	fine number;
	day number;
	begin
		DBMS_OUTPUT.PUT_LINE(rpad('BORROWER_NAME',20)||chr(9)||
							rpad('BOOK_ID',10)||chr(9)||
							rpad('ISSUE_DATE',10)||chr(9)||
							rpad('FINE',10));
		DBMS_OUTPUT.PUT_LINE(rpad('-------------',20)||chr(9)||
							rpad('-------',10)||chr(9)||
							rpad('----------',10)||chr(9)||
							rpad('----',10));
		for iter in (select bo.name as name, i.book_id as id,
					i.issue_date as dat, round(c_dat-i.issue_date,0) as day
					from Borrower bo, Issue i
					where bo.borrower_id=i.borrower_id and i.return_date is NULL)
			loop
				if(iter.day>5) then
					fine:=5*iter.day;
					DBMS_OUTPUT.PUT_LINE(rpad(iter.name,20)||chr(9)||
										rpad(iter.id,10)||chr(9)||
										rpad(iter.dat,10)||chr(9)||
										rpad(fine,10));
				end if;
			end loop;
	end;
/

create or replace procedure pro_listborr_mon 
	(borrower_id IN number, mon IN varchar2) 
	is
	input_month number;
	name varchar(30);
	br_id number;
	b_id number;
	title varchar2(50);
	is_dat date;
	re_dat date;
	month number;
	b number :=borrower_id;
	begin

		select to_char(to_date(mon,'mm'),'mm') into input_month from dual;
		DBMS_OUTPUT.PUT_LINE(rpad('BR_ID',5)||chr(9)||
							rpad('BORROWER_NAME',20)||chr(9)||
							rpad('BK_ID',5)||chr(9)||
							rpad('BOOK_TITLE',20)||chr(9)||
							rpad('ISSU_DATE',9)||chr(9)||
							rpad('RETU_DATE',9));
		for iter in (select bo.borrower_id as br_id, bo.name as name, i.book_id as b_id,
					b.book_title as title, i.issue_date as is_dat, i.return_date as re_dat,
					to_char(i.issue_date,'mm') as month
					from Borrower bo, Books b, Issue i
					where i.book_id=b.book_id and i.borrower_id=bo.borrower_id
					and i.borrower_id=b)
			loop
				if(iter.month=input_month) then
					DBMS_OUTPUT.PUT_LINE(rpad(iter.br_id,5)||chr(9)||
										rpad(iter.name,20)||chr(9)||
										rpad(iter.b_id,5)||chr(9)||
										rpad(iter.title,20)||chr(9)||
										rpad(iter.is_dat,9)||chr(9)||
										rpad(iter.re_dat,9));
				end if;
			end loop;
	end;
/

create or replace procedure pro_listborr 
	is
	name varchar2(30);
	b_id number;
	is_dat date;

	begin
		DBMS_OUTPUT.PUT_LINE(rpad('BORROWER_NAME',20)||chr(9)||
							rpad('BOOK_ID',10)||chr(9)||
							rpad('ISSUE_DATE',10));
		for iter in (select bo.name as name, i.book_id as b_id, i.issue_date as is_dat
					from Borrower bo, Issue i
					where i.borrower_id=bo.borrower_id and i.return_date is NULL)
		loop
			DBMS_OUTPUT.PUT_LINE(rpad(iter.name,20)||chr(9)||
								rpad(iter.b_id,10)||chr(9)||
								rpad(iter.is_dat,10));
		end loop;

	end;
/

create or replace procedure pro_list_popular is 
	month number;
	au_name varchar2(30);
	ed number;
	year number;
	i number;

	begin
		i:=1;
		DBMS_OUTPUT.PUT_LINE(rpad('MONTH',5)||chr(9)||
							rpad('YEAR',8)||chr(9)||
							rpad('AUTHOR_NAME',20)||chr(9)||
							rpad('EDITION',10));
		for iter in(
			select t3.mon as month, t3.year as year, au.name as au_name, b.edition as ed
				from 
				(select tmp.b_id, tmp.mon, tmp.year from 
					(select book_id as b_id, borrower_id as br_id, issue_date as is_dat,
					extract(month from(issue_date)) as mon, 
					extract(year from(issue_date)) as year
					from Issue
					union all 
					select book_id as b_id, requester_id as br_id, request_date as is_dat,
					extract(month from(request_date)) as mon, 
					extract(year from(request_date)) as year
					from Pending_request
					where issue_date is null) tmp
				group by tmp.b_id, tmp.mon, tmp.year
				having count(*)>=all(select count(*) from 
					(select book_id as b_id, borrower_id as br_id, issue_date as is_dat,
					extract(month from(issue_date)) as mon, 
					extract(year from(issue_date)) as year
					from Issue
					union all 
					select book_id as b_id, requester_id as br_id, request_date as is_dat,
					extract(month from(request_date)) as mon, 
					extract(year from(request_date)) as year
					from Pending_request
					where issue_date is null) t2
									where t2.mon=tmp.mon and t2.year=tmp.year
									group by t2.b_id, t2.mon, t2.year)
				) t3, Author au, Books b
			where t3.b_id=b.book_id and b.author_id=au.author_id
			order by t3.mon
					)
		loop	
				for iter2 in i..(iter.month-1)
				loop
					DBMS_OUTPUT.PUT_LINE(rpad(iter2,5));
				end loop;
				
				DBMS_OUTPUT.PUT_LINE(rpad(iter.month,5)||chr(9)||
									rpad(iter.year,8)||chr(9)||
									rpad(iter.au_name,20)||chr(9)||
									rpad(iter.ed,10));
				i:=iter.month+1;

		end loop;
		for iter2 in i..12
				loop
					DBMS_OUTPUT.PUT_LINE(rpad(iter2,5));
				end loop;
		
	end;
/

