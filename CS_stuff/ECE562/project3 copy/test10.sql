drop table query10;
create table query10(
	name varchar2(30),
	g_date date,
	d_date date,
	sur_name varchar2(30),
	total_cost number
);
drop table q10helper;
create table q10helper(
	name varchar2(30),
	g_date date,
	d_date date,
	sur_name varchar2(30),
	total_cost number
);
set serveroutput on;
create or replace procedure q10 is
	name varchar2(30);
	g_date date;
	d_date date;
	sur_name varchar2(30);
	sur_name1 varchar2(30);
	sur_name2 varchar2(30);
	last_total number;
	total_cost number;
	tmp_name varchar2(30);
	tmp_g_date date;
	last_name varchar2(30);
	last_g date;
	last_d date;
	last_sur varchar2(30);
	ct number;
	q10_size number;

begin
	for i in (select o.name as name, o.g_date as g_date, o.d_date as d_date from over_all o
		where o.s_count=2 and o.g_date>=to_date('01/01/05','mm/dd/yy')
		and o.d_date<=to_date('01/01/06','mm/dd/yy') and o.name in
		(select o1.name from over_all o1 group by o1.name having count(*)>1))

	loop
		insert into q10helper values(i.name,i.g_date,i.d_date,null,null);
	end loop;
	
	for i in (select q.name as name,q.g_date as g_date from q10helper q) loop
		tmp_name:=i.name;
		tmp_g_date:=i.g_date;
		select s.name into sur_name1 from surgeon_schedule s, tmp t, over_all o
		where o.name=tmp_name and o.g_date=tmp_g_date and s.surgery_date=o.p_date
		and s.name=t.name and t.area=o.p_type;
		select s.name into sur_name2 from surgeon_schedule s, tmp t, over_all o
		where o.name=tmp_name and o.g_date=tmp_g_date and s.surgery_date=o.p_date+2
		and s.name=t.name and t.area=o.p_type;
		if(sur_name1=sur_name2) then
			update q10helper set sur_name=sur_name1 where name=tmp_name and g_date=tmp_g_date;
		end if;
	end loop;
	delete from q10helper where sur_name is null;
	delete from q10helper where name in (select name from q10helper group by name 
										having count(*)<2);
	ct:=0;
	select count(*) into q10_size from q10helper;
	for i in (select q.name as name, q.g_date as g_date, q.sur_name as sur_name,
			q.d_date as d_date 
			from q10helper q order by q.name, q.g_date) 
	loop
	ct:=ct+1;

	if(ct>1) then
		if(i.name=last_name and (i.g_date-last_d)>5 and (i.g_date-last_d)<14
			and i.sur_name<>last_sur) then
	select (t.g_cost+t.s_cost+t.pre_cost+t.post_cost+t.sur_cost) into last_total
	from total_reim t where t.name=last_name and t.g_date=last_g;
	select (t.g_cost+t.s_cost+t.pre_cost+t.post_cost+t.sur_cost) into total_cost
	from total_reim t where t.name=i.name and t.g_date=i.g_date;
	--DBMS_OUTPUT.PUT_LINE(tmp_name||tmp_g_date||total_cost);
	if(ct<>q10_size) then
		insert into query10 values(last_name,last_g,last_d,last_sur,last_total);
	end if;
	insert into query10 values(i.name,i.g_date,i.d_date,i.sur_name,total_cost);
		end if;
	end if;
	last_d:=i.d_date;
	last_g:=i.g_date;
	last_name:=i.name;
	last_sur:=i.sur_name;
	end loop;
end;
/
exec q10;
