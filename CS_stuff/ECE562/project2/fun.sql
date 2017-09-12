SET SERVEROUTPUT ON;

create or replace function fun_issue_book
	(borrower_id IN number, 
	book_id IN number, 
	c_date IN date)
	return number is
	tmp Books%ROWTYPE;
	b_id number;
	begin
		b_id := book_id;
		select * into tmp from Books b 
		where b.book_id=b_id;
		if (tmp.status='not charged') then
			insert into Issue values(book_id, borrower_id, c_date, NULL);
			return 1;
		else
			insert into Pending_request values(book_id, borrower_id, c_date, NULL);
			return 0;
		end if;
	end;
/

create or replace function fun_issue_anyedition
	(br_id IN number,
	b_title IN varchar2,
	au_name IN varchar2,
	c_dat IN date)
	return number is
	ct number;
	pend_id number;
	result number;
	l_edition number;
	l_e_bid number;

	begin
		begin
			select count(*) into ct from Books b, Author a
			where b.book_title=b_title and b.author_id=a.author_id
			and a.name=au_name and b.status='not charged';
		exception
			when no_data_found then
				ct:=0;
		end;
		if(ct=0) then
			select tmp.book_id into pend_id from 
			(select b.book_id from Books b, Issue i
			where b.book_id=i.book_id and b.book_title=b_title 
			order by i.issue_date) tmp 
			where rownum=1;

			insert into Pending_request values(pend_id,br_id,c_dat,NULL);
			return 0;
		else
			select max(b1.edition) into l_edition
			from Books b1 where b1.book_id in
				(select b2.book_id from Books b2, Author a2 
				where b2.status='not charged' and a2.author_id=b2.author_id
				and a2.name=au_name and b2.book_title=b_title);
			select b3.book_id into l_e_bid from Books b3, Author a3
			where a3.author_id=b3.author_id and a3.name=au_name
			and b3.edition=l_edition and b3.book_title=b_title;

			insert into Issue values(l_e_bid,br_id,c_dat,NULL);
			return 1;
		end if;
	end;
/

create or replace function fun_most_popular
	(mon IN varchar2) return number is result number;
	input_month number;
	book number;
	month number;
	year number;
	

	begin

		select to_char(to_date(mon,'mm'),'mm') into input_month from dual;

		DBMS_OUTPUT.PUT_LINE(rpad('BOOK_ID',5)||chr(9)||
							rpad('MONTH',5)||chr(9)||
							rpad('YEAR',10));
		for iter in(
			select t3.mon as month, t3.year as year, b.book_id as book
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
				where tmp.mon=input_month
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
				) t3, Books b where t3.b_id=b.book_id 
					)
		loop
			DBMS_OUTPUT.PUT_LINE(rpad(iter.book,5)||chr(9)||
								rpad(iter.month,5)||chr(9)||
								rpad(iter.year,10));

		end loop;
		result:=1;
		return result;
		
	end;
/

create or replace function fun_return_book
	(b_id IN number, ret_dat IN date)
	return number is
	pend_bid number;
	pend_borrower number;
	req_dat date;
	ct number;
	begin
		begin
			select count(*) into ct from Pending_request p 
			where p.book_id=b_id and p.issue_date is null;
		exception
			when NO_DATA_FOUND THEN
				ct:=0;
		end;
		update Issue i set i.return_date=ret_dat where i.book_id=b_id and i.return_date is NULL;

		if(ct=0) then
			return 0;
		else 
			select tmp.book_id, tmp.requester_id, tmp.request_date 
			into pend_bid, pend_borrower, req_dat
			from (select * from (select * from pending_request p2 where p2.book_id=b_id
								and p2.issue_date is null
								order by p2.request_date) where rownum=1) tmp;
			insert into Issue values(pend_bid, pend_borrower, ret_dat, NULL);

			update Pending_request p3 set p3.issue_date=ret_dat
			where p3.book_id=pend_bid and p3.requester_id=pend_borrower and p3.request_date=req_dat;
			return 1;
		end if;
	end;
/

