set serveroutput on;

create or replace trigger trg_gen after insert on GENERAL_WARD
for each row
declare
ct_bed int;
min_pre_date date;
potential_date date;

begin
	begin
		select count(*) into ct_bed from SCREENING_WARD s where s.Bed_No is not null;
	EXCEPTION
		WHEN NO_DATA_FOUND THEN
			ct_bed:=0;
	end;

	if(ct_bed<5) then
		ct_bed:=ct_bed+1;
		insert into SCREENING_WARD values(:new.Patient_Name, :new.G_Admission_Date+3, ct_bed, 
										:new.Patient_Type);
	else
		select dbms_random.value(1,5) into ct_bed from dual;
		potential_date:=:new.G_Admission_Date+3;
		select min(tmp.pre_date) into min_pre_date from (select * from(
			select post.patient_name as name, post.post_admission_date as pre_date, 
			post.Patient_Type as p_type from post_surgery_ward post
			where not exists (select * from pre_surgery_ward pre where
			pre.pre_admission_date+2=post.post_admission_date and 
			pre.patient_name=post.patient_name)
			union
			select pre2.patient_name, pre2.pre_admission_date, pre2.Patient_Type 
			from pre_surgery_ward pre2)
			order by pre_date desc)tmp where rownum<=5;
		if(potential_date>=min_pre_date) then
			insert into SCREENING_WARD values(:new.Patient_Name, potential_date, ct_bed, 
										:new.Patient_Type);
		else 
			insert into SCREENING_WARD values(:new.Patient_Name, min_pre_date, ct_bed, 
										:new.Patient_Type);
		end if;
	end if;
end;
/
create or replace trigger trg_scr after insert on SCREENING_WARD
for each row
declare
name varchar2(30);
ct_bed int;
potential_date date;
min_pre_date date;
post_flag number:=0;
special_ct number;
--extra
p_type varchar2(10);
p_date date;
d_date date;
sc number;
cardiac_ct number;
neuro_ct number;

begin
	begin
		select count(*) into ct_bed from PRE_SURGERY_WARD p where p.Bed_No is not null;
	EXCEPTION
		WHEN NO_DATA_FOUND THEN
			ct_bed:=0;
	end;
	name:=:new.Patient_Name;
	p_type:=:new.Patient_Type;
	p_date:=:new.s_admission_date;

	if(ct_bed<4) then
		ct_bed:=ct_bed+1;
		insert into PRE_SURGERY_WARD values(:new.Patient_Name,:new.S_Admission_Date+3,ct_bed,
											:new.Patient_Type);
		--modified start
		if(p_type='General') then
			insert into POST_SURGERY_WARD values(name,:new.S_Admission_Date+5,
											:new.S_Admission_Date+7,1,:new.Patient_Type);
		end if;
		if(p_type='Cardiac') then
			select count(*) into cardiac_ct from Patient_Chart where 
			Patient_Name=name and Pdate>=p_date+5 and Pdate<p_date+7 and (BP<110 or BP>140);
			if(cardiac_ct>=1) then
				insert into POST_SURGERY_WARD values(name,:new.S_Admission_Date+5,
											:new.S_Admission_Date+9,2,:new.Patient_Type);
			else
				insert into POST_SURGERY_WARD values(name,:new.S_Admission_Date+5,
											:new.S_Admission_Date+7,1,:new.Patient_Type);
			end if;
		end if;
		if(p_type='Neuro') then
			select count(*) into neuro_ct from Patient_Chart where
			Patient_Name=name and Pdate>=p_date+5 and Pdate<p_date+7 and 
			((BP<110 or BP>140) or (Temperature<97 or Temperature>100));
			if(neuro_ct>=1) then
				insert into POST_SURGERY_WARD values(name,:new.S_Admission_Date+5,
											:new.S_Admission_Date+9,2,:new.Patient_Type);
			else
				insert into POST_SURGERY_WARD values(name,:new.S_Admission_Date+5,
											:new.S_Admission_Date+7,1,:new.Patient_Type);
			end if;
		end if;
		--modified end
	else
		select dbms_random.value(1,4) into ct_bed from dual;
		name:=:new.Patient_Name;
		potential_date:=:new.S_Admission_Date+3;
		select min(tmp.pre_date) into min_pre_date from (select pre_admission_date as pre_date 
			from pre_surgery_ward 
			order by pre_admission_date desc)tmp where rownum<=4;
		min_pre_date:=min_pre_date+2;
		if(potential_date>=min_pre_date) then
			--dbms_output.put_line('entered normal and name='||name);
			insert into PRE_SURGERY_WARD values(:new.patient_name,potential_date,ct_bed,:new.Patient_Type);

			--modified start
			if(p_type='General') then
			insert into POST_SURGERY_WARD values(name,:new.S_Admission_Date+5,
											:new.S_Admission_Date+7,1,:new.Patient_Type);
			
			elsif(p_type='Cardiac') then
				select count(*) into cardiac_ct from Patient_Chart where 
				Patient_Name=name and Pdate>=p_date+5 and Pdate<p_date+7 and (BP<110 or BP>140);
				if(cardiac_ct>=1) then
				insert into POST_SURGERY_WARD values(name,:new.S_Admission_Date+5,
											:new.S_Admission_Date+9,2,:new.Patient_Type);
				else
				insert into POST_SURGERY_WARD values(name,:new.S_Admission_Date+5,
											:new.S_Admission_Date+7,1,:new.Patient_Type);
				end if;
			
			elsif(p_type='Neuro') then
				select count(*) into neuro_ct from Patient_Chart where
				Patient_Name=name and Pdate>=p_date+5 and Pdate<p_date+7 and 
				((BP<110 or BP>140) or (Temperature<97 or Temperature>100));
				if(neuro_ct>=1) then
				insert into POST_SURGERY_WARD values(name,:new.S_Admission_Date+5,
											:new.S_Admission_Date+9,2,:new.Patient_Type);
				else
				insert into POST_SURGERY_WARD values(name,:new.S_Admission_Date+5,
											:new.S_Admission_Date+7,1,:new.Patient_Type);
				end if;
			end if;
			--modified end
		else
			for i in 1..(min_pre_date-potential_date) loop
				select count(*) into special_ct from Patient_Chart where Patient_Name=name and 
				Pdate>=potential_date-3 and Pdate<=potential_date and 
				Temperature>=97 and Temperature<=100 and BP>=110 and BP<=140;
				--dbms_output.put_line('entered special and name='||name
				--					||' ct='||special_ct||' date='||potential_date);
				if(special_ct=4) then
					--dbms_output.put_line('entered----- and ct='||special_ct);
					post_flag:=1;
					--insert into POST_SURGERY_WARD values(name,potential_date+4,potential_date+6,
					--									1,:new.Patient_Type);
					--modified start
					if(p_type='General') then
					insert into POST_SURGERY_WARD values(name,potential_date-3+4,
													potential_date-3+6,1,:new.Patient_Type);
					
					elsif(p_type='Cardiac') then
						select count(*) into cardiac_ct from Patient_Chart where 
						Patient_Name=name and Pdate>=potential_date-3+4 and 
						Pdate<potential_date-3+6 and (BP<110 or BP>140);
						if(cardiac_ct>=1) then
						insert into POST_SURGERY_WARD values(name,potential_date-3+4,
													potential_date-3+8,2,:new.Patient_Type);
						else
						insert into POST_SURGERY_WARD values(name,potential_date-3+4,
													potential_date-3+6,1,:new.Patient_Type);
						end if;
					
					elsif(p_type='Neuro') then
						select count(*) into neuro_ct from Patient_Chart where
						Patient_Name=name and Pdate>=potential_date-3+4 and 
						Pdate<potential_date-3+6 and
						((BP<110 or BP>140) or (Temperature<97 or Temperature>100));
						if(neuro_ct>=1) then
						insert into POST_SURGERY_WARD values(name,potential_date-3+4,
													potential_date-3+8,2,:new.Patient_Type);
						else
						insert into POST_SURGERY_WARD values(name,potential_date-3+4,
													potential_date-3+6,1,:new.Patient_Type);
						end if;
					end if;
					--modified end
					GOTO end_loop;
				end if;
			potential_date:=potential_date+1;
			end loop;
			--if(post_flag=0) then
			insert into PRE_SURGERY_WARD values(name,min_pre_date,ct_bed,:new.Patient_Type);
			--modified start
					if(p_type='General') then
					insert into POST_SURGERY_WARD values(name,min_pre_date+2,
													min_pre_date+4,1,:new.Patient_Type);
					
					elsif(p_type='Cardiac') then
						select count(*) into cardiac_ct from Patient_Chart where 
						Patient_Name=name and Pdate>=min_pre_date+2 and Pdate<min_pre_date+4 
						and (BP<110 or BP>140);
						if(cardiac_ct>=1) then
						insert into POST_SURGERY_WARD values(name,min_pre_date+2,
													min_pre_date+6,2,:new.Patient_Type);
						else
						insert into POST_SURGERY_WARD values(name,min_pre_date+2,
													min_pre_date+4,1,:new.Patient_Type);
						end if;
					
					elsif(p_type='Neuro') then
						select count(*) into neuro_ct from Patient_Chart where
						Patient_Name=name and Pdate>=min_pre_date+2 and Pdate<min_pre_date+4 
						and ((BP<110 or BP>140) or (Temperature<97 or Temperature>100));
						if(neuro_ct>=1) then
						insert into POST_SURGERY_WARD values(name,min_pre_date+2,
													min_pre_date+6,2,:new.Patient_Type);
						else
						insert into POST_SURGERY_WARD values(name,min_pre_date+2,
													min_pre_date+4,1,:new.Patient_Type);
						end if;
					end if;
					--modified end
				--insert into POST_SURGERY_WARD values(name,min_pre_date,min_pre_date+2,1,:new.Patient_Type);
			--end if;
			<<end_loop>>
			NULL;
		end if;
	end if;
	
end;
/

create or replace trigger trg_post after delete on POST_SURGERY_WARD
for each row
declare
name varchar2(30);
p_type varchar2(10);
p_date date;
d_date date;
sc number;
cardiac_ct number;
neuro_ct number;
begin
	name:=:new.Patient_Name;
	p_type:=:new.Patient_Type;
	p_date:=:new.post_admission_date;
	d_date:=:new.discharge_date;
	if(p_type='Cardiac') then
		select count(*) into cardiac_ct from Patient_Chart where 
		Patient_Name=name and Pdate>=p_date and Pdate<d_date and (BP<110 or BP>140);
		if(cardiac_ct=2) then
			update POST_SURGERY_WARD set Scount=2, discharge_date=d_date+2
			where Patient_Name=name and post_admission_date=p_date;
		end if;
	end if;
	if(p_type='Neuro') then
		select count(*) into neuro_ct from Patient_Chart where
		Patient_Name=name and Pdate>=p_date and Pdate<d_date and (BP<110 or BP>140)
		and (Temperature<97 or Temperature>100);
		if(neuro_ct=2) then
			update POST_SURGERY_WARD set Scount=2, discharge_date=d_date+2
			where Patient_Name=name and post_admission_date=p_date;
		end if;
	end if;
end;
/

