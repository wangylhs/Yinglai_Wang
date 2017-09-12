drop table query4;
create table query4(
	start_day date,
	end_day date,
	sc number,
	dr_name varchar2(30)	
);

drop table q4helper;
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


