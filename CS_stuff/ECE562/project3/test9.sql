drop table query9;
create table query9(
	start_date date,
	end_date date
);
drop table q9helper;
create table q9helper(day_date date);

create or replace procedure q9 is
	g_date date;
	d_date date;
	start_date date;
	special_ct number:=0;
	last date;
	q9_ct number;
	q9_size number;
	chosen_date date;

begin
	for i in (select o.g_date as g_date, o.d_date as d_date from OVER_ALL o
			where o.name='G' and o.g_date>=to_date('01/01/05','mm/dd/yy') and 
			o.d_date<=to_date('01/01/06','mm/dd/yy'))
	loop
		start_date:=i.g_date;
		for j in 1..(i.d_date-i.g_date) loop
			select count(*) into special_ct from 
			Patient_Chart where Patient_name='G' and Pdate=start_date and (BP<110 or BP>140);
			if(special_ct=0) then
				insert into q9helper values(start_date);
			end if;
			start_date:=start_date+1;
		end loop;
		select day_date into start_date from (select * from q9helper order by day_date) where rownum=1;
		last:=start_date;
		q9_ct:=0;
		select count(*) into q9_size from q9helper;
		for k in (select day_date as chosen_date from q9helper order by day_date) loop
			q9_ct:=q9_ct+1;
			if(q9_ct=q9_size) then 
				if(k.chosen_date-last>1) then
					insert into query9 values(start_date,last);
					insert into query9 values(k.chosen_date,k.chosen_date);
				else
					insert into query9 values(start_date,k.chosen_date);
				end if;
			elsif(k.chosen_date>(last+1)) then
				insert into query9 values(start_date,last);
				start_date:=k.chosen_date;
			end if;
			last:=k.chosen_date;
		end loop;
		delete from q9helper;
	end loop;
end;
/
exec q9;