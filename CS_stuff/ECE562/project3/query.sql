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

delete from DR_Schedule;
delete from Surgeon_Schedule;
exec populate_Dr;
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

create table query4(
	start_day date,
	end_day date,
	sc number,
	dr_name varchar2(30)	
);

create table q4helper(
	sur_date date,
	name varchar2(30)
);

create or replace procedure q4
	is
	start_day date;
	last_day date;
	end_day date;
	q4_size number;
	q4_ct number:=0;
	total_sct number;
	--variables for populating q4helper
	sur_date date;
	name varchar2(30);

	begin
		--populate q4helper
		for i in (select p.Post_Admission_Date as sur_date, s.name as name
				from POST_SURGERY_WARD p, tmp t, Surgeon_Schedule s
				where p.Post_Admission_Date=s.Surgery_Date and t.name=s.name
				and t.area=p.Patient_Type) 
		loop
			insert into q4helper values(i.sur_date,i.name);
		end loop;
		for i in (select p.Post_Admission_Date+2 as sur_date, s.name as name 
						from POST_SURGERY_WARD p, tmp t, Surgeon_Schedule s
						where (p.Post_Admission_Date+2)=s.Surgery_Date and t.name=s.name
						and t.area=p.Patient_Type and p.Scount=2)
		loop
			insert into q4helper values(i.sur_date,i.name);
		end loop;
		--start doing query4, populate query4
		select tmp.sur_date into start_day
		from (select * from q4helper order by sur_date)tmp where rownum=1;
		last_day:=start_day;
		select count(*) into q4_size from q4helper;
		for i in (select q.sur_date as sur_date, q.name as name
				from q4helper q order by q.sur_date)
		loop
			q4_ct:=q4_ct+1;
			if(q4_ct=q4_size) then
				if(i.sur_date-last_day>1) then
					--compute sc in this range
					select count(*) into total_sct from q4helper q 
						where q.sur_date>=start_day and q.sur_date<=last_day;
					--compute dr_name in this range
					for m in (select q.name as d_name from q4helper q
						where q.sur_date>=start_day and q.sur_date<=last_day
						group by q.name 
						having
						count(*)>=all(select count(*) from q4helper q2
									where 
									q2.sur_date>=start_day and q2.sur_date<=last_day
									group by q2.name))
					loop
					insert into query4 values(start_day,last_day,total_sct,m.d_name);
					end loop;
					--compute sc in this range
					select count(*) into total_sct from q4helper q 
						where q.sur_date=i.sur_date;
					--compute dr_name in this range
					for m in (select q.name as d_name from q4helper q
						where q.sur_date=i.sur_date
						group by q.name 
						having
						count(*)>=all(select count(*) from q4helper q2 where 
									q2.sur_date=i.sur_date group by q2.name))
					loop
					insert into query4 values(i.sur_date,i.sur_date,total_sct,m.d_name);
					end loop;
				else
					--compute sc in this range
					select count(*) into total_sct from q4helper q 
						where q.sur_date>=start_day and q.sur_date<=i.sur_date;
					--compute dr_name in this range
					for m in (select q.name as d_name from q4helper q
						where q.sur_date>=start_day and q.sur_date<=i.sur_date
						group by q.name 
						having
						count(*)>=all(select count(*) from q4helper q2
									where 
									q2.sur_date>=start_day and q2.sur_date<=i.sur_date
									group by q2.name))
					loop
					insert into query4 values(start_day,i.sur_date,total_sct,m.d_name);
					end loop;
				end if;

			elsif(i.sur_date>last_day+1) then
				if(q4_ct=q4_size) then last_day:=i.sur_date; end if;
				--compute sc in this range
				select count(*) into total_sct from q4helper q 
						where q.sur_date>=start_day and q.sur_date<=last_day;

				--compute dr_name in this range
				for m in (select q.name as d_name from q4helper q
						where q.sur_date>=start_day and q.sur_date<=last_day
						group by q.name 
						having
						count(*)>=all(select count(*) from q4helper q2
									where 
									q2.sur_date>=start_day and q2.sur_date<=last_day
									group by q2.name))
				loop
					insert into query4 values(start_day,last_day,total_sct,m.d_name);
				end loop;	
			
				start_day:=i.sur_date;
			end if;
			last_day:=i.sur_date;
		end loop;

	end;
/

exec q4;

create table query5(
	s_date date,
	e_date date
);
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
	for i in (select sur_date as chosen_date from q4helper 
			where name='Dr. Gower' or name='Dr. Taylor')
	loop
		delete from q5helper where day_date=i.chosen_date;
	end loop;
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

create table query7(
	p_name varchar2(30),
	s_date date,
	p_type varchar2(10),
	surgeon_name varchar2(30),
	physician varchar2(30)
);

create or replace procedure q7 is
	name varchar2(30);
	s_date date;
	p_type varchar2(10);
	sc number;
	dr_name varchar2(30);
	physician varchar2(30);
	input_date date:=to_date('04/09/05','mm/dd/yy');

begin
	for i in (select p.Patient_Name as name, s.name as dr_name, p.Post_Admission_Date as s_date,
			d.name as physician,p.Scount as sc, p.Patient_Type as p_type
			from POST_SURGERY_WARD p, Surgeon_Schedule s, tmp t, DR_Schedule d
			where p.Patient_Type='Cardiac' and p.Post_Admission_Date=s.Surgery_Date and s.name=t.name
			and t.area='Cardiac' and p.Post_Admission_Date=d.Duty_Date and d.ward='Surgery'
			and p.Post_Admission_Date>=input_date and
			p.Post_Admission_Date<=(input_date+6))
	loop
		insert into query7 values(i.name,i.s_date,i.p_type,i.dr_name,i.physician);
	end loop;
	for i in (select p.Patient_Name as name, s.name as dr_name,(p.Post_Admission_Date+2) as s_date,
			d.name as physician,p.Scount as sc, p.Patient_Type as p_type
			from POST_SURGERY_WARD p, Surgeon_Schedule s, tmp t, DR_Schedule d
			where p.Patient_Type='Cardiac' and (p.Post_Admission_Date+2)=s.Surgery_Date and s.name=t.name
			and t.area='Cardiac' and (p.Post_Admission_Date+2)=d.Duty_Date and d.ward='Surgery'
			and p.Scount=2 and (p.Post_Admission_Date+2)>=input_date and
			(p.Post_Admission_Date+2)<=(input_date+6))
	loop
		insert into query7 values(i.name,i.s_date,i.p_type,i.dr_name,i.physician);
	end loop;
end;
/
exec q7;

create table query8(
	s_date date,
	e_date date
);
create table q8helper(
	over_lap_date date
);
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
	(select * from OVER_ALL o where o.name='Bob' and o.g_date>=to_date('01/01/05','mm/dd/yy')
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

create table query9(
	start_date date,
	end_date date
);
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
			Patient_Chart where Patient_name='Bob' and Pdate=start_date and (BP<110 or BP>140);
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


create table query10(
	name varchar2(30),
	g_date date,
	d_date date,
	sur_name varchar2(30),
	total_cost number
);
create table q10helper(
	name varchar2(30),
	g_date date,
	d_date date,
	sur_name varchar2(30),
	total_cost number
);
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



exec dbms_output.put_line('Query#1');
select * from query1 order by name;

exec dbms_output.put_line('Query#2');
select tmp1.total_cost as total_cost, tmp1.total_cost/tmp2.num as avg_per_patient,
tmp1.total_cost/tmp3.num as avg_per_visit from 
(select sum(q.total_cost) as total_cost from query1 q)tmp1,
(select count(distinct o.name) as num from OVER_ALL_B o)tmp2,
(select count(*) as num from OVER_ALL_B)tmp3;

exec dbms_output.put_line('Query#3');
select o1.Name, q1.avg_stay from OVER_ALL_B o1, query1 q1,
(select tmp2.old_g_date, tmp2.old_d_date from
(select tmp1.*, rownum as rownum_a from
(select * from OVER_ALL_B o where o.Name='Bob'
order by o.old_g_date)tmp1)tmp2 where tmp2.rownum_a=2)tmp3
where o1.old_g_date=tmp3.old_g_date and o1.old_d_date<tmp3.old_d_date
and o1.Name=q1.name
order by o1.Name;

exec dbms_output.put_line('Query#4');

select * from query4 order by sc desc;


exec dbms_output.put_line('Query#5');

select s_date as start_date, e_date as end_date from query5;

exec dbms_output.put_line('Query#6');
select o1.Name, (t.g_cost+t.s_cost+t.pre_cost+t.post_cost+t.sur_cost) as total_reimbursed 
from OVER_ALL o1, total_reim t, 
(select * from
(select tmp1.*, rownum as rownum_a from
(select * from OVER_ALL o where o.Name='Bob' and o.g_date>=to_date('01/01/05','mm/dd/yy')
and o.D_Date<=to_date('01/01/06','mm/dd/yy')
order by o.G_Date)tmp1)tmp2 where tmp2.rownum_a=3)tmp3
where o1.D_Date>=(tmp3.P_Date+2) and o1.D_Date<=(tmp3.P_Date+2+3)
and o1.Name=t.name and o1.G_Date=t.g_date and o1.Name<>'Bob';

exec dbms_output.put_line('Query#7');
select q.p_name as patient_name, q.surgeon_name, q.physician from query7 q order by q.p_name; 

exec dbms_output.put_line('Query#8');
select s_date as start_date, e_date as end_date from query8;

exec dbms_output.put_line('Query#9');
select * from query9 where (end_date-start_date)>=2;

exec dbms_output.put_line('Query#10');
select name, sum(total_cost) from query10 group by name;


drop table OVER_ALL;
drop table OVER_ALL_B;	
drop table total_reim;
drop table query1;
drop table query4;
drop table q4helper;
drop table query5;
drop table q5helper;
drop table query7;
drop table query8;
drop table q8helper;
drop table q8helper2;
drop table query9;
drop table q9helper;
drop table query10;
drop table q10helper;
drop table tmp;




