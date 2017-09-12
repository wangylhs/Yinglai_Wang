set serveroutput on;

create or replace procedure populate_Dr is
	type namearray is varray(6) of varchar2(30);
	type wardarray is varray(5) of varchar2(20);
	wards wardarray;
	names namearray;
	total number;
	first_day date := to_date('01/01/2005','MM/DD/YYYY');
	ind number;
	ind2 number;
	extr number :=6;
	week number;
	begin
		names:=namearray('James','Robert','Mike','Adams','Tracey','Rick');
		wards:=wardarray('GENERAL_WARD','SCREENING_WARD','PRE_SURGERY_WARD','POST_SURGERY_WARD','Surgery');

		for i in 0..364 loop
			select (mod(i,6)+1) into ind from dual;
			for j in 0..4 loop
				ind2:=ind+j;
				if ind2>6 then
					ind2:=ind2-6;
				end if;
				insert into DR_Schedule values(names(ind2),wards(j+1),first_day);
			end loop;
			select mod(i,7) into week from dual;
			if week=0 then
				insert into DR_Schedule values(names(extr),wards(5),first_day);
				extr:=extr+1;
				if(extr>6) then
					extr:=extr-6;
				end if;
			end if;
			first_day:=first_day+1;
		end loop;	
	end;
/

create or replace procedure populate_Sur is
	type namearray is varray(6) of varchar2(30);
	names namearray;
	dat_day date:=to_date('01/01/2005','MM/DD/YYYY');
	wek_day varchar2(3);
	begin
		names:=namearray('Dr. Smith','Dr. Charles','Dr. Richards','Dr. Gower','Dr. Taylor','Dr. Rutherford');

		for i in 0..364 loop
			select to_char(dat_day,'DY') into wek_day from dual;
			if(wek_day='SUN' or wek_day='MON' or wek_day='THU') then
				insert into Surgeon_Schedule values(names(1),dat_day);
				insert into Surgeon_Schedule values(names(2),dat_day);
				insert into Surgeon_Schedule values(names(5),dat_day);
					
			elsif(wek_day='TUE' or wek_day='WED' or wek_day='FRI' or wek_day='SAT') then
				insert into Surgeon_Schedule values(names(3),dat_day);
				insert into Surgeon_Schedule values(names(4),dat_day);
				insert into Surgeon_Schedule values(names(6),dat_day);						
			end if;
			dat_day:=dat_day+1;
		end loop;


	end;
/

create table tmp(
	name varchar2(30),
	area varchar2(10),
	primary key(name, area)
);
insert into tmp values('Dr. Smith','General');
insert into tmp values('Dr. Richards','General');
insert into tmp values('Dr. Charles','Cardiac');
insert into tmp values('Dr. Gower','Cardiac');
insert into tmp values('Dr. Taylor','Neuro');
insert into tmp values('Dr. Rutherford','Neuro');

create or replace function verify
	return number
	is
	weeks int;
	type namearray is varray(6) of varchar2(30);
	type wardarray is varray(5) of varchar2(20);
	wards wardarray;
	names namearray;
	first_day date := to_date('01/01/2005','MM/DD/YYYY');
	ct number;
	name1 varchar2(30);
	name2 varchar2(30);
	name3 varchar2(30);
	--variables for check surgeon_schedule
	names_sur namearray;
	ct_cardiac number;
	ct_neuro number;

	begin
		--check dr_schedule
		names:=namearray('James','Robert','Mike','Adams','Tracey','Rick');
		wards:=wardarray('GENERAL_WARD','SCREENING_WARD','PRE_SURGERY_WARD','POST_SURGERY_WARD','Surgery');
		weeks:=365/7;
		for i in 1..weeks loop
			for j in 1..6 loop
				select count(*) into ct from dr_schedule d where d.name=names(j) and 
					d.duty_date>=first_day and d.duty_date<=first_day+6;
				if ct<>6 then
					dbms_output.put_line(names(j)||' does not work 6 days in a week.');
				end if;
			end loop;
		first_day:=first_day+7;
		end loop;
		first_day:=to_date('01/01/2005','MM/DD/YYYY');
		for i in 1..363 loop
			for j in 1..4 loop
				select d.name into name1 from dr_schedule d where d.duty_date=first_day
					and d.ward=wards(j);
				select d.name into name2 from dr_schedule d where d.duty_date=first_day+1
					and d.ward=wards(j);
				select d.name into name3 from dr_schedule d where d.duty_date=first_day+2
					and d.ward=wards(j);
				if(name1=name2 and name1=name3) then
					dbms_output.put_line(name1||' has worked in '||wards(j)||' for 3 consecutive days.');
				end if;
			end loop;
		first_day:=first_day+1;
		end loop;

		--check surgeon_schedule
		names_sur:=namearray('Dr. Smith','Dr. Charles','Dr. Richards','Dr. Gower','Dr. Taylor','Dr. Rutherford');
		first_day:=to_date('01/01/2005','MM/DD/YYYY');
		for i in 1..365 loop
			begin
			select count(*) into ct_cardiac from surgeon_schedule s, tmp t where
				s.surgery_date=first_day and s.name=t.name and t.area='Cardiac';
			exception
			when no_data_found then
				ct_cardiac:=0;
			end;
			begin
			select count(*) into ct_neuro from surgeon_schedule s, tmp t where
				s.surgery_date=first_day and s.name=t.name and t.area='Ceuro';
			exception
			when no_data_found then
				ct_neuro:=0;
			end;
			if(ct_cardiac<1) then
				dbms_output.put_line('No Cardiac surgeon on duty on '||first_day);
			end if;
			if(ct_neuro<1) then
				dbms_output.put_line('No Neuro surgeon on duty on '||first_day);
			end if;
			first_day:=first_day+1;
		end loop;


		return null;
	end;
/
--populate dr_schedule and surgeon_schedule;
delete from DR_Schedule;
exec populate_Dr;
delete from surgeon_schedule;
exec populate_Sur;

create table OVER_ALL(
	Name varchar2(30),
	G_Date Date,
	S_Date Date,
	Pre_Date Date,
	P_Date Date,
	D_Date Date,
	S_count number,
	P_Type varchar2(10),
	primary key(Name, G_Date, P_Type),
	CONSTRAINT check_p_type
	CHECK (P_Type IN ('Cardiac','Neuro','General'))
);
create or replace procedure full_schedule is
	--variables for populating over_all
	name varchar2(30);
	g_date date;
	s_date date;
	p_date date;
	d_date date;
	s_count number;
	p_type varchar2(10);
begin
	--populate over_all
		for i in(
		select tmp1.Patient_Name as name, tmp1.G_Admission_Date as g_date,
		tmp3.S_Admission_Date as s_date, tmp2.Post_Admission_Date as p_date, 
		tmp2.Discharge_Date as d_date, tmp1.Patient_Type as p_type,
		tmp2.Scount as s_count from 
			(select g1.*, rownum as rownum_a from (select * from GENERAL_WARD g 
			order by g.Patient_Name, g.G_Admission_Date)g1)tmp1,
			(select s1.*, rownum as rownum_c from (select * from SCREENING_WARD s 
			order by s.Patient_Name, s.S_Admission_Date)s1)tmp3,
			(select p1.*, rownum as rownum_b from (select * from POST_SURGERY_WARD p
			order by p.Patient_Name, p.Post_Admission_Date)p1)tmp2 
		where tmp1.rownum_a=tmp2.rownum_b and tmp1.rownum_a=tmp3.rownum_c
		)
			loop
			insert into OVER_ALL values(i.name,i.g_date,i.s_date,null,i.p_date,i.d_date,
										i.s_count,i.p_type);
		end loop;

		for i in(select pre.Patient_Name as pre_name, pre.Pre_Admission_Date as pre_date,
				pre.Patient_Type as pre_type from PRE_SURGERY_WARD pre)
		loop
			update OVER_ALL o set o.Pre_Date=i.pre_date where o.Name=i.pre_name and o.P_Type=i.pre_type
				and i.pre_date>o.S_Date and (o.P_Date-2)=i.pre_date;
		end loop;
		--finish populate over_all
end;
/

--populate over_all
delete from OVER_ALL;
exec full_schedule;
--display complete schedule for each patient
select * from OVER_ALL;
--display dr_schedule
select * from dr_schedule;
--display surgeon_schedule;
select * from surgeon_schedule;

create table PSV(
	patient_name varchar2(30),
	patient_surgery_date date,
	surgeon_name varchar2(30)
);

create or replace procedure populate_PSV is
	name varchar2(30);
	s_date date;
	p_type varchar2(10);
	sc number;
	dr_name varchar2(30);

begin
	for i in (select p.Patient_Name as name, s.name as dr_name, p.Post_Admission_Date as s_date,
			p.Scount as sc, p.Patient_Type as p_type
			from POST_SURGERY_WARD p, Surgeon_Schedule s, tmp t
			where p.Patient_Type=t.area and p.Post_Admission_Date=s.Surgery_Date and s.name=t.name
			)
	loop
		insert into PSV values(i.name,i.s_date,i.dr_name);
	end loop;
	for i in (select p.Patient_Name as name, s.name as dr_name,(p.Post_Admission_Date+2) as s_date,
			p.Scount as sc, p.Patient_Type as p_type
			from POST_SURGERY_WARD p, Surgeon_Schedule s, tmp t
			where p.Patient_Type=t.area and (p.Post_Admission_Date+2)=s.Surgery_Date and s.name=t.name
			and p.Scount=2
			)
	loop
		insert into PSV values(i.name,i.s_date,i.dr_name);
	end loop;
end;
/

exec populate_PSV;
--create view Patient_Surgery_View
create or replace view Patient_Surgery_View as select * from PSV 
	order by patient_name,patient_surgery_date;
--display view
select * from Patient_Surgery_View;
drop table OVER_ALL;
drop table PSV;
drop table tmp;






























