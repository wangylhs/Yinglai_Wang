drop table query8;
create table query8(
	s_date date,
	e_date date
);
drop table q8helper;
create table q8helper(
	over_lap_date date
);
drop table q8helper2;
create table q8helper2(
	stay date
);

create or replace procedure q8 is
	name varchar2(30);
	g_s_date date;
	s_s_date date;
	pre_s_date date;
	post_s_date date;
	post_e_date date;
	over_lap_date date;
	start_date date;
	stay date;
	last date;
	q8_size number;
	q8_ct number;
begin
	select tmp2.g_date,tmp2.s_date,tmp2.pre_date,tmp2.p_date,tmp2.d_date 
	into g_s_date,s_s_date,pre_s_date,post_s_date,post_e_date from 
	(select tmp.*, rownum as rownum_a from
	(select * from OVER_ALL o where o.name='B' and o.g_date>=to_date('01/01/05','mm/dd/yy')
	order by o.g_date)tmp)tmp2 where tmp2.rownum_a=3;
	 
	for i in (select duty_date as over_lap_date from dr_schedule where duty_date>=g_s_date
			and duty_date<s_s_date and name='Adams' and ward='GENERAL_WARD') 
	loop
		insert into q8helper values(i.over_lap_date);
	end loop;
	if(pre_s_date is null) then
		for i in (select duty_date as over_lap_date from dr_schedule where duty_date>=s_s_date
				and duty_date<post_s_date and name='Adams' and ward='SCREENING_WARD')
		loop
			insert into q8helper values(i.over_lap_date);
		end loop;
		for i in (select duty_date as over_lap_date from dr_schedule where duty_date>=post_s_date
				and duty_date<post_e_date and name='Adams' and ward='POST_SURGERY_WARD')
		loop
			insert into q8helper values(i.over_lap_date);
		end loop;

	else
		for i in (select duty_date as over_lap_date from dr_schedule where duty_date>=s_s_date
				and duty_date<pre_s_date and name='Adams' and ward='SCREENING_WARD')
		loop
			insert into q8helper values(i.over_lap_date);
		end loop;
		for i in (select duty_date as over_lap_date from dr_schedule where duty_date>=pre_s_date
				and duty_date<post_s_date and name='Adams' and ward='PRE_SURGERY_WARD')
		loop
			insert into q8helper values(i.over_lap_date);
		end loop;
		for i in (select duty_date as over_lap_date from dr_schedule where duty_date>=post_s_date
				and duty_date<post_e_date and name='Adams' and ward='POST_SURGERY_WARD')
		loop
			insert into q8helper values(i.over_lap_date);
		end loop;
	end if;
	start_date:=g_s_date;
	for i in 1..(post_e_date-g_s_date) loop
		insert into q8helper2 values(start_date);
		start_date:=start_date+1;
	end loop;
	select tmp2.stay into start_date from
		(select tmp.stay from (select * from q8helper2 minus select * from q8helper)tmp
			order by tmp.stay)tmp2 where rownum=1;
	select count(*) into q8_size from (select * from q8helper2 minus select * from q8helper);
	last:=start_date;
	q8_ct:=0;
	for i in (select tmp.stay as stay from (select * from q8helper2 minus select * from q8helper)tmp
			order by tmp.stay)
	loop
		q8_ct:=q8_ct+1;
		if(q8_ct=q8_size) then 
			if(i.stay-last>1) then
				insert into query8 values(start_date,last);
				insert into query8 values(i.stay,i.stay);
			else
				insert into query8 values(start_date,i.stay);
			end if;
		elsif(i.stay>(last+1)) then
			insert into query8 values(start_date,last);
			start_date:=i.stay;
		end if;
		last:=i.stay;
	end loop;

end;
/
exec q8;
