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
	old_g_date date,
	G_Date Date,
	old_s_date date,
	S_Date Date,
	old_pre_date date,
	Pre_Date Date,
	old_p_date date,
	P_Date Date,
	old_d_date date,
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
	--variables for populating over_all and over_all_b and total_reim
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
	g_cost number;
	screen_cost number;
	pre_cost number;
	post_cost number;
	surgery_cost number;
	--dates used to calculate surgery charges
	old_g_date date;
	old_s_date date;
	old_pre_date date;
	old_p_date date;
	old_d_date date;
	pp_date date;

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
		from(select * from OVER_ALL)tmp)
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
			elsif (i.s_date>to_date('01/01/06','mm/dd/yy')) then
				tmp_s_date:=to_date('01/01/06','mm/dd/yy');
			end if;
			if(i.pre_date<to_date('01/01/05','mm/dd/yy')) then
				tmp_pre_date:=to_date('01/01/05','mm/dd/yy');
			elsif (i.pre_date>to_date('01/01/06','mm/dd/yy')) then
				tmp_pre_date:=to_date('01/01/06','mm/dd/yy');
			end if;
			if(i.p_date<to_date('01/01/05','mm/dd/yy')) then
				tmp_p_date:=to_date('01/01/05','mm/dd/yy');
			elsif (i.p_date>to_date('01/01/06','mm/dd/yy')) then
				tmp_p_date:=to_date('01/01/06','mm/dd/yy');
			end if;
			
			if(i.g_date<to_date('01/01/05','mm/dd/yy') and 
				i.d_date>to_date('01/01/06','mm/dd/yy')) then
				insert into OVER_ALL_B values(i.name,i.g_date,to_date('01/01/05','mm/dd/yy'),
											i.s_date,tmp_s_date,i.pre_date,tmp_pre_date,
											i.p_date,tmp_p_date,i.d_date,
											to_date('01/01/06','mm/dd/yy'),i.s_count,i.p_type);
			end if;
			if(i.g_date<to_date('01/01/05','mm/dd/yy') and i.d_date>to_date('01/01/05','mm/dd/yy') and
				i.d_date<=to_date('01/01/06','mm/dd/yy')) then
				insert into OVER_ALL_B values(i.name,i.g_date,to_date('01/01/05','mm/dd/yy'),
											i.s_date,tmp_s_date,i.pre_date,tmp_pre_date,
											i.p_date,tmp_p_date,i.d_date,i.d_date,
											i.s_count,i.p_type);
			end if;
			if(i.g_date>=to_date('01/01/05','mm/dd/yy') and i.g_date<to_date('01/01/06','mm/dd/yy')
				and i.d_date>to_date('01/01/06','mm/dd/yy')) then
				insert into OVER_ALL_B values(i.name,i.g_date,i.g_date,i.s_date,tmp_s_date,
											i.pre_date,tmp_pre_date,i.p_date,tmp_p_date,i.d_date,
											to_date('01/01/06','mm/dd/yy'),i.s_count,i.p_type);
			end if;
			--general case
			if(i.g_date>=to_date('01/01/05','mm/dd/yy') and
				i.d_date<=to_date('01/01/06','mm/dd/yy')) then
				insert into OVER_ALL_B values(i.name,i.g_date,i.g_date,i.s_date,i.s_date,
											i.pre_date,i.pre_date,i.p_date,i.p_date,
											i.d_date,i.d_date,i.s_count,i.p_type);
			end if;
		end loop;
		--finish populate over_all_B;

		--populate total_reim

		for i in(select o.Name as cost_name,o.old_g_date as old_g_date,o.G_Date as g_date,
				o.old_s_date as old_s_date,o.S_Date as s_date, 
				o.old_pre_date as old_pre_date,o.Pre_Date as pre_date,
				o.old_p_date as old_p_date,o.P_Date as p_date, 
				o.old_d_date as old_d_date,o.D_Date as dis_date,
				o.P_Type as surgery_type,o.S_count as surgery_count
				from OVER_ALL_B o)
		loop
			--compute surgery cost
			if(i.old_p_date<=to_date('12/29/05','mm/dd/yy') and i.old_p_date>=to_date('01/01/05','mm/dd/yy')) then
				--patient who can have 1 or 2 surgeries in 2005
				if(i.surgery_type='Cardiac') then
					surgery_cost:=0.75*3500+(0.7*3500*(i.surgery_count-1));
				elsif(i.surgery_type='Neuro') then
					surgery_cost:=0.85*5000+(0.8*5000*(i.surgery_count-1));
				elsif(i.surgery_type='General') then
					surgery_cost:=0.65*2500+(0.6*2500*(i.surgery_count-1));
				end if;
			elsif (i.old_p_date<to_date('01/01/06','mm/dd/yy') and i.old_p_date>to_date('12/29/05','mm/dd/yy')) then
				--patient can only have 1st surgery
				if(i.surgery_type='Cardiac') then
					surgery_cost:=0.75*3500;
				elsif(i.surgery_type='Neuro') then
					surgery_cost:=0.85*5000;
				elsif(i.surgery_type='General') then
					surgery_cost:=0.65*2500;
				end if;
			elsif ((i.old_p_date=to_date('12/30/04','mm/dd/yy')
				 	or i.old_p_date=to_date('12/31/04','mm/dd/yy'))
					and i.surgery_count=2) then
				if(i.surgery_type='Cardiac') then
					surgery_cost:=0.7*3500;
				elsif(i.surgery_type='Neuro') then
					surgery_cost:=0.8*5000;
				elsif(i.surgery_type='General') then
					surgery_cost:=0.6*2500;
				end if;
			else
				surgery_cost:=0;
			end if;
			
			if(i.pre_date is null) then
				pre_cost:=0;
				if(i.old_s_date<to_date('01/01/05','mm/dd/yy') and i.old_p_date<=to_date('01/01/06','mm/dd/yy')
					and i.old_p_date>=to_date('01/01/05','mm/dd/yy')) then
					--s in 04, post in 05
					if(i.p_date-i.s_date=0) then screen_cost:=0; end if;
					if(i.p_date-i.s_date>0) then
						if(i.s_date-i.old_s_date>=2) then screen_cost:=0.75*70*(i.old_p_date-i.s_date);
						elsif(i.s_date-i.old_s_date=1) then screen_cost:=0.85*70+0.75*70*(i.old_p_date-i.s_date-1); 
						end if;
					end if;
				elsif(i.old_s_date<to_date('1/1/05','MM/DD/YY') and i.old_p_date<to_date('1/1/05','MM/DD/YY')) then
					--s in 04, post in 04
					screen_cost:=0;
				elsif(i.old_s_date>to_date('1/1/06','MM/DD/YY') and i.old_p_date>to_date('1/1/06','MM/DD/YY')) then
					--s in 06, post in 06
					screen_cost:=0;
				elsif(i.old_s_date<=to_date('12/31/05','MM/DD/YY') and i.old_s_date>=to_date('1/1/05','MM/DD/YY') 
					and i.old_p_date>to_date('1/1/06','MM/DD/YY')) then
					--s in 05, post in 06
					if(i.p_date-i.s_date=0) then screen_cost:=0; end if;
					if(i.p_date-i.s_date>0) then
						if(i.p_date-i.s_date<=2) then screen_cost:=0.85*70*(i.p_date-i.s_date);
						else screen_cost:=0.85*2*70+0.75*70*(i.p_date-i.s_date-2); 
						end if;
					end if;
				elsif(i.old_s_date<to_date('1/1/05','MM/DD/YY') and i.old_p_date>to_date('1/1/06','MM/DD/YY')) then
					--s in 04, post in 06
					screen_cost:=0.85*70*2+0.75*70*363;
				else
					screen_cost:=0.85*70*2+0.75*70*(i.p_date-i.s_date-2);
				end if;
			end if;
				
			if(i.pre_date is not null) then
				if(i.old_pre_date<=to_date('12/30/05','MM/DD/YY') and i.old_pre_date>=to_date('1/1/05','MM/DD/YY')) then
				--pre in 05
					pre_cost:=0.95*90*2;
				elsif(i.old_pre_date=to_date('12/31/05','MM/DD/YY') or i.old_pre_date=to_date('12/31/04','MM/DD/YY')) then
					pre_cost:=0.95*90;
				else pre_cost:=0;
				end if;
				if(i.old_s_date<to_date('01/01/05','mm/dd/yy') and i.old_pre_date<=to_date('01/01/06','mm/dd/yy')
					and old_pre_date>=to_date('01/01/05','mm/dd/yy')) then
					--s in 04, post in 05
					if(i.pre_date-i.s_date=0) then screen_cost:=0; end if;
					if(i.pre_date-i.s_date>0) then
						if(i.s_date-i.old_s_date>=2) then screen_cost:=0.75*70*(i.old_pre_date-i.s_date);
						elsif(i.s_date-i.old_s_date=1) then screen_cost:=0.85*70+0.75*70*(i.old_pre_date-i.s_date-1); 
						end if;
					end if;
				elsif(i.old_s_date<to_date('1/1/05','MM/DD/YY') and i.old_pre_date<to_date('1/1/05','MM/DD/YY')) then
					--s in 04, post in 04
					screen_cost:=0;
				elsif(i.old_s_date>to_date('1/1/06','MM/DD/YY') and i.old_pre_date>to_date('1/1/06','MM/DD/YY')) then
					--s in 06, post in 06
					screen_cost:=0;
				elsif(i.old_s_date<=to_date('12/31/05','MM/DD/YY') and i.old_s_date>=to_date('1/1/05','MM/DD/YY') 
					and i.old_pre_date>to_date('1/1/06','MM/DD/YY')) then
					--s in 05, post in 06
					if(i.pre_date-i.s_date=0) then screen_cost:=0; end if;
					if(i.pre_date-i.s_date>0) then
						if(i.pre_date-i.s_date<=2) then screen_cost:=0.85*70*(i.pre_date-i.s_date);
						else screen_cost:=0.85*2*70+0.75*70*(i.pre_date-i.s_date-2); 
						end if;
					end if;
				elsif(i.old_s_date<to_date('1/1/05','MM/DD/YY') and i.old_pre_date>to_date('1/1/06','MM/DD/YY')) then
					--s in 04, post in 06
					screen_cost:=0.85*70*2+0.75*70*363;
				else
					screen_cost:=0.85*70*2+0.75*70*(i.pre_date-i.s_date-2);
				end if;
			end if;

			--g
			if(i.old_g_date<to_date('1/1/05','MM/DD/YY') and i.old_s_date<=to_date('1/1/06','MM/DD/YY') 
				and i.old_s_date>=to_date('1/1/05','MM/DD/YY')) then
				--s in 05 g in 04
				if(i.s_date-g_date=0) then g_cost:=0; end if;
				if(i.s_date-g_date>0) then
					if(i.g_date-i.old_g_date>=3) then 
						g_cost:=0.7*50*(i.old_s_date-i.g_date);
					elsif(i.g_date-i.old_g_date=2) then 
						g_cost:=0.8*50+0.7*50*(i.old_s_date-i.g_date-1);
					elsif(i.g_date-i.old_g_date=1) then
						g_cost:=0.8*50*2+0.7*50*(i.s_date-i.g_date-2);
					end if;
				end if;
			elsif(i.old_g_date<to_date('1/1/05','MM/DD/YY') and i.old_s_date<to_date('1/1/05','MM/DD/YY')) then
				--g in 04 s in 04
				g_cost:=0;
			elsif(i.old_g_date>to_date('1/1/06','MM/DD/YY') and i.old_s_date>to_date('1/1/06','MM/DD/YY')) then
				--g in 06 s in 06
				g_cost:=0;
			elsif(i.old_g_date<=to_date('12/31/05','MM/DD/YY') and i.old_g_date>=to_date('1/1/05','MM/DD/YY') 
				and i.old_s_date>to_date('1/1/06','MM/DD/YY')) then
				--g in 05 s in 06
				if(i.s_date-i.g_date=0) then g_cost:=0; end if;
				if(i.s_date-i.g_date>0) then
					if(i.s_date-g_date<=3) then 
						g_cost:=0.8*50*(i.s_date-i.g_date);
					else 
						g_cost:=0.8*3*50+0.7*50*(i.s_date-i.g_date-3);
					end if;
				end if;
			elsif(i.old_g_date<to_date('1/1/05','MM/DD/YY') and i.old_s_date>to_date('1/1/06','MM/DD/YY')) then
				--g in 04, s in 06
				g_cost:=0.8*50*3+0.7*50*362;
			else
				g_cost:=0.8*50*3+0.7*50*(i.old_s_date-i.old_g_date-3);
			end if;
			--p
			if(i.old_p_date<=to_date('12/28/05','MM/DD/YY') and i.old_p_date>=to_date('1/1/05','MM/DD/YY')) then
			--p in 05
				post_cost:=0.9*80*2*i.surgery_count;
			elsif(i.old_p_date=to_date('12/29/05','MM/DD/YY')) then
				post_cost:=0.9*80*(i.surgery_count+1);
			elsif i.old_p_date=to_date('12/30/05','MM/DD/YY') then
				post_cost:=0.9*80*2;
			elsif i.old_p_date=to_date('12/31/05','MM/DD/YY') then
				post_cost:=0.9*80;
			elsif (i.old_p_date=to_date('12/29/04','MM/DD/YY') and i.surgery_count=2) then
				post_cost:=0.9*80;
			elsif (i.old_p_date=to_date('12/30/04','MM/DD/YY') and i.surgery_count=2) then
				post_cost:=0.9*80*2;
			elsif (i.old_p_date=to_date('12/31/04','MM/DD/YY') and i.surgery_count=1) then
				post_cost:=0.9*80;
			elsif (i.old_p_date=to_date('12/31/04','MM/DD/YY') and i.surgery_count=2) then
				post_cost:=0.9*80*3;
			else
				post_cost:=0;
			end if;

			insert into total_reim values(i.cost_name,i.g_date,g_cost,screen_cost,
										pre_cost,post_cost,surgery_cost);
		end loop;

	end;
/

exec big_table;

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
				from OVER_ALL_B o group by o.name)tmp2
				where tmp1.name=tmp2.name
				)
		loop
			insert into query1 values(i.name,i.visit_num,i.stay,i.total_cost);
		end loop;

	end;
/

exec q1;



















