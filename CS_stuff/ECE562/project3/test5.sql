drop table query5;
create table query5(
	s_date date,
	e_date date
);
drop table q5helper;
create table q5helper(day_date date);

create or replace procedure q5 is
	start_date date:=to_date('01/01/05','mm/dd/yy');
	chosen_date date;
	last date;
	q5_size number;
	q5_ct number;

begin
	for i in 1..365 loop
		insert into q5helper values(start_date);
		start_date:=start_date+1;
	end loop;
	for i in (select sur_date as chosen_date from q4helper where sur_date>=to_date('04/01/05','mm/dd/yy')
			and sur_date<=to_date('04/30/05','mm/dd/yy') and name='Dr. Gower' or name='Dr. Taylor')
	loop
		delete from q5helper where day_date=i.chosen_date;
	end loop;
	delete from q5helper where day_date<to_date('04/01/05','mm/dd/yy') or 
								day_date>to_date('04/30/05','mm/dd/yy');
	select day_date into start_date from 
	(select * from q5helper order by day_date) where rownum=1;
	last:=start_date;
	select count(*) into q5_size from q5helper;
	q5_ct:=0;
	for i in (select day_date as chosen_date from q5helper order by day_date)
	loop
		q5_ct:=q5_ct+1;
		if(q5_ct=q5_size) then
			if(i.chosen_date-last>1) then
				insert into query5 values(start_date, last);
				insert into query5 values(i.chosen_date, i.chosen_date);
			else
				insert into query5 values(start_date, i.chosen_date);
			end if;
		elsif(i.chosen_date>(last+1)) then
			insert into query5 values(start_date, last);
			start_date:=i.chosen_date;
		end if;
		last:=i.chosen_date;
	end loop;
end;
/
exec q5;
