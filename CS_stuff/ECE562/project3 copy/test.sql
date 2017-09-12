set serveroutput on;
drop table OVER_ALL;
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
drop table OVER_ALL_B;
create table OVER_ALL_B(
	Name varchar2(30),
	G_Date Date,
	S_Date Date,
	Pre_Date Date,
	P_Date Date,
	D_Date Date,
	S_count number,
	P_Type varchar2(10),
	primary key(Name, G_Date, P_Type),
	CONSTRAINT check_type
	CHECK (P_Type IN ('Cardiac','Neuro','General'))
);
drop table total_reim;
create table total_reim(
	name varchar2(30),
	g_date date,
	g_cost number,
	s_cost number,
	pre_cost number,
	post_cost number,
	sur_cost number,
	primary key(name,g_date)
);
drop table query1;
create table query1(
	name varchar2(30),
	visits number,
	avg_stay number,
	total_cost number	
);


create or replace procedure big_table is
	--variables to changing out-range date
	tmp_g_date date;
	tmp_s_date date;
	tmp_pre_date date;
	tmp_p_date date;
	tmp_d_date date;
	--variables for populating over_all and over_all_b
	name varchar2(30);
	g_date date;
	s_date date;
	p_date date;
	d_date date;
	s_count number;
	p_type varchar2(10);
	--checking pre_surgery_ward
	pre_name varchar2(30);
	pre_date date;
	pre_type varchar2(10);
	--variables for populating total_reim
	cost_name varchar2(30);
	general_date date;
	screen_date date;
	pre_sur_date date;
	post_sur_date date;
	dis_date date;
	surgery_type varchar2(10);
	surgery_count number;
	general_cost number;
	screen_cost number;
	pre_sur_cost number;
	post_sur_cost number;
	surgery_cost number;

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
		--start populate over_all_B
		for i in(
		select tmp.name as name, tmp.g_date as g_date,tmp.s_date as s_date,tmp.pre_date as pre_date, 
		tmp.p_date as p_date,tmp.d_date as d_date,tmp.p_type as p_type,tmp.S_count as s_count 
		from OVER_ALL tmp
			loop
			--initialize tmp_date
			tmp_g_date:=i.g_date;
			tmp_s_date:=i.s_date;
			tmp_pre_date:=i.pre_date;
			tmp_p_date:=i.p_date;
			tmp_d_date:=i.d_date;
			--update tmp_date based on edge cases
			if(i.s_date<to_date('01/01/05','mm/dd/yy')) then
				tmp_s_date:=to_date('01/01/05','mm/dd/yy');
			elsif (i.s_date>to_date('01/01/06','mm/dd/yy'))
				tmp_s_date:=to_date('01/01/06','mm/dd/yy');
			end if;
			if(i.pre_date<to_date('01/01/05','mm/dd/yy')) then
				tmp_pre_date:=to_date('01/01/05','mm/dd/yy');
			elsif (i.pre_date>to_date('01/01/06','mm/dd/yy'))
				tmp_pre_date:=to_date('01/01/06','mm/dd/yy');
			end if;
			if(i.p_date<to_date('01/01/05','mm/dd/yy')) then
				tmp_p_date:=to_date('01/01/05','mm/dd/yy');
			elsif (i.p_date>to_date('01/01/06','mm/dd/yy'))
				tmp_p_date:=to_date('01/01/06','mm/dd/yy');
			end if;
			
			if(i.g_date<to_date('01/01/05','mm/dd/yy') and 
				i.d_date>to_date('01/01/06','mm/dd/yy')) then
				insert into OVER_ALL values(i.name,to_date('01/01/05','mm/dd/yy'),tmp_s_date,
											tmp_pre_date,tmp_p_date,
											to_date('01/01/06','mm/dd/yy'),i.s_count,i.p_type);
			end if;
			if(i.g_date<to_date('01/01/05','mm/dd/yy') and i.d_date>to_date('01/01/05','mm/dd/yy') and
				i.d_date<=to_date('01/01/06','mm/dd/yy')) then
				insert into OVER_ALL values(i.name,to_date('01/01/05','mm/dd/yy'),tmp_s_date,
											tmp_pre_date,tmp_p_date,i.d_date,
											i.s_count,i.p_type);
			end if;
			if(i.g_date>=to_date('01/01/05','mm/dd/yy') and i.g_date<to_date('01/01/06','mm/dd/yy')
				and i.d_date>to_date('01/01/06','mm/dd/yy')) then
				insert into OVER_ALL values(i.name,i.g_date,tmp_s_date,tmp_pre_date,tmp_p_date,
											tmp_d_date,i.s_count,i.p_type);
			end if;
			--general case
			if(i.g_date>=to_date('01/01/05','mm/dd/yy') and
				i.d_date<=to_date('01/01/06','mm/dd/yy')) then
				insert into OVER_ALL values(i.name,i.g_date,i.s_date,i.pre_date,i.p_date,i.d_date,
											i.s_count,i.p_type);
			end if;
		end loop;
		--finish populate over_all_B;



		--populate total_reim
		for i in(select o.Name as cost_name, o.G_Date as general_date, o.S_Date as screen_date,
				o.Pre_Date as pre_sur_date, o.P_Date as post_sur_date, o.P_Type as surgery_type,
				o.D_Date as dis_date, o.S_count as surgery_count from OVER_ALL o)
		loop
			if(i.surgery_type='Cardiac') then
					surgery_cost:=0.75*3500+(0.7*3500*(i.surgery_count-1));
				elsif(i.surgery_type='Neuro') then
					surgery_cost:=0.85*5000+(0.8*5000*(i.surgery_count-1));
				elsif(i.surgery_type='General') then
					surgery_cost:=0.65*2500+(0.6*2500*(i.surgery_count-1));
			end if;
			if(i.pre_sur_date is null) then
				general_cost:=(0.8*3*50)+(0.7*50*(i.screen_date-i.general_date-3));
				screen_cost:=(0.85*2*70)+(0.75*70*(i.post_sur_date-i.screen_date-2));
				pre_sur_cost:=0;
				post_sur_cost:=0.9*80*(i.dis_date-i.post_sur_date);
				
				insert into total_reim values(i.cost_name,i.general_date,general_cost,screen_cost,
										pre_sur_cost,post_sur_cost,surgery_cost);
			else
				general_cost:=(0.8*3*50)+(0.7*50*(i.screen_date-i.general_date-3));
				screen_cost:=(0.85*2*70)+(0.75*70*(i.pre_sur_date-i.screen_date-2));
				pre_sur_cost:=0.95*90*(i.post_sur_date-i.pre_sur_date);
				post_sur_cost:=0.9*80*(i.dis_date-i.post_sur_date);
				insert into total_reim values(i.cost_name,i.general_date,general_cost,screen_cost,
										pre_sur_cost,post_sur_cost,surgery_cost);

			end if;
		end loop;

	end;
/
--exec big_table;

create or replace procedure q1 is
	name varchar2(30);
	visit_num number;
	stay number;
	total_cost number;
	begin
		for i in(select tmp1.name as name, tmp1.ct as visit_num, tmp2.avg_stay as stay,
				tmp1.total_cost as total_cost from 
				(select t.name, count(*) as ct , 
				sum(t.g_cost+t.s_cost+t.pre_cost+t.post_cost+t.sur_cost) as total_cost 
				from total_reim t group by t.name)tmp1,
				(select o.name, avg(o.D_Date-o.G_Date) as avg_stay 
				from OVER_ALL o group by o.name)tmp2
				where tmp1.name=tmp2.name
				)
		loop
			insert into query1 values(i.name,i.visit_num,i.stay,i.total_cost);
		end loop;

	end;
/
--exec q1;
