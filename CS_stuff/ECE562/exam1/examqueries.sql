rem EE 562 exam1
rem Yinglai Wang
rem wang1105

create table PATIENT(
	pid int,
	treatment varchar2(20),
	p_visit_number int,
	duration int,
	primary key(pid, treatment, p_visit_number)
);

create table DOCTOR(
	D_name varchar2(20),
	specialty varchar2(20),
	primary key(D_name, specialty)
);

create table ASSIGNMENT(
	pid int,
	D_name varchar2(20),
	p_visit_number int,
	primary key(pid, D_name, p_visit_number)
);


exec DBMS_OUTPUT.PUT_LINE('Query #1');
select p.treatment from PATIENT p
group by p.treatment
having count(*)>=all(select count(*) from PATIENT px 
					group by px.treatment);

exec DBMS_OUTPUT.PUT_LINE('Query #2');
select d.D_name from DOCTOR d, ASSIGNMENT a, PATIENT p
where d.D_name=a.D_name and a.p_visit_number=p.p_visit_number
group by d.D_name
having count(*)>=all(select count(*) from DOCTOR dx, ASSIGNMENT ax, PATIENT px
					where dx.D_name=ax.D_name and ax.p_visit_number=px.p_visit_number
					group by dx.D_name);

exec DBMS_OUTPUT.PUT_LINE('Query #3');
select d.D_name from DOCTOR d
group by d.D_name
having count(*)>=all(select count(*) from DOCTOR dx
					group by dx.D_name);

exec DBMS_OUTPUT.PUT_LINE('Query #4');
select p.pid from PATIENT p
where p.duration in
(select px.duration from PATIENT px
where px.duration>(select avg(py.duration) from PATIENT py)
);

exec DBMS_OUTPUT.PUT_LINE('Query #5');
select p.pid from PATIENT p
where p.pid in
(select px.pid from PATIENT px
group by px.pid
having count(distinct px.treatment)>=all(select count(distinct py.treatment)
										from PATIENT py
										group by py.pid)
);

exec DBMS_OUTPUT.PUT_LINE('Query #6');
select p.pid from PATIENT p
where not exists
(select * from DOCTOR d where p.treatment=d.specialty);

exec DBMS_OUTPUT.PUT_LINE('Query #7');
select p.p_visit_number from PATIENT p
where p.duration>3
;

exec DBMS_OUTPUT.PUT_LINE('Query #8');
select count(distinct p.treatment)*50 from PATIENT p
group by p.pid;



drop table ASSIGNMENT;
drop table DOCTOR;
drop table PATIENT;