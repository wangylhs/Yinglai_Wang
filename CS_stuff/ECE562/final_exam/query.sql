rem EE 562 finalexam
rem Yinglai Wang
rem wang1105

exec DBMS_OUTPUT.PUT_LINE('Query #a');
select distinct treatment, pid from PATIENT order by treatment;

exec DBMS_OUTPUT.PUT_LINE('Query #b');
select d.D_name from DOCTOR d
group by d.D_name
having count(*)<=all(select count(*) from DOCTOR dd
					group by dd.D_name);

exec DBMS_OUTPUT.PUT_LINE('Query #c');
select pid, count(*)/max(p_visit_number) from PATIENT where pid in
(select p.pid from PATIENT p
group by p.pid
having count(distinct p.treatment)>=all(select count(distinct p2.treatment)
										from PATIENT p2 group by p2.pid)
)
group by pid;

exec DBMS_OUTPUT.PUT_LINE('Query #d');
select a.pid from ASSIGNMENT a group by a.pid, a.p_visit_number
having count(*)=1 and a.pid in
(select p.pid from PATIENT p group by p.pid, p.p_visit_number
having count(*)=2);

exec DBMS_OUTPUT.PUT_LINE('Query #e');
select d.D_name from DOCTOR d where d.specialty in
(select p.treatment from PATIENT p
group by p.treatment having count(distinct p.pid)=10);