drop table query7;
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
	input_date date:=to_date('02/09/05','mm/dd/yy');

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