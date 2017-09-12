rem EE 562 Project 1
rem Yinglai Wang
rem wang1105

SET SERVEROUTPUT ON;
exec DBMS_OUTPUT.PUT_LINE('Query #1');
select MAX(S.age) from student S
where (S.major='CS') or S.sid in 
(select E.sid from class C, enrolled E, faculty F 
	where E.cnum=C.cnum and C.fid=F.fid and F.fname='Prof.Brown');

exec DBMS_OUTPUT.PUT_LINE('Query #2');
select C.cnum from class C
where C.room='115' or C.cnum in
(select E.cnum from enrolled E
group by E.cnum having COUNT(*)>=5);

exec DBMS_OUTPUT.PUT_LINE('Query #3');
select S.sname from student S
where S.sid in 
(select E1.sid from 
enrolled E1, enrolled E2, class C1, class C2 
where E1.sid=E2.sid and E1.cnum<>E2.cnum 
and E1.cnum=C1.cnum and E2.cnum=C2.cnum and C1.meets_at=C2.meets_at);

exec DBMS_OUTPUT.PUT_LINE('Query#4');
select F.fname from faculty F
where not exists(
(select C1.room from class C1)
minus
(select C2.room from class C2 where C2.fid=F.fid )
);

exec DBMS_OUTPUT.PUT_LINE('Query#5');
select F.fname from faculty F
where 8<(select COUNT(E.sid) from enrolled E, class C where C.fid=F.fid and C.cnum=E.cnum);

exec DBMS_OUTPUT.PUT_LINE('Query#6');
select S.levels, AVG(S.age) from student S
where S.levels<>'JR'
group by S.levels;

exec DBMS_OUTPUT.PUT_LINE('Query#7');
select distinct S.sname from student S
where S.sid in
(select E1.sid from enrolled E1 group by E1.sid 
having COUNT(*)>=all(select COUNT(*) from enrolled E2 group by E2.sid));

exec DBMS_OUTPUT.PUT_LINE('Query#8');
select S.sname from student S
where S.sid in
((select S1.sid from student S1)
minus
(select E.sid from enrolled E));

exec DBMS_OUTPUT.PUT_LINE('Query#9');
select S.age, S.levels from student S
group by S.age, S.levels
having S.levels in 
(select S1.levels from student S1 where S1.age=S.age group by S1.levels, S1.age 
having COUNT(*)>=
all(select COUNT(*) from student S2 where S1.age=S2.age group by S2.levels, S2.age))
order by S.age;

exec DBMS_OUTPUT.PUT_LINE('Query#10');
select (select COUNT(*) from
enrolled E join class C on E.cnum=C.cnum join faculty F on C.fid=F.fid
where F.dept='EE')/(select COUNT(*) from faculty F2 where F2.dept='EE')-((select COUNT(*) from
enrolled E join class C on E.cnum=C.cnum join faculty F on C.fid=F.fid
where F.dept='CS')/(select COUNT(*) from faculty F2 where F2.dept='CS')) as DIFFERENCE
from faculty F3 where F3.fid=1;

exec DBMS_OUTPUT.PUT_LINE('Query#11');
select F3.fname from faculty F3
where F3.fid in
(select F.fid from enrolled E join class C on E.cnum=C.cnum join faculty F on C.fid=F.fid 
group by F.fid 
having COUNT(*)>((select COUNT(*) from
enrolled E1 join class C1 on E1.cnum=C1.cnum join faculty F1 on C1.fid=F1.fid
where F1.dept='EE')/(select COUNT(*) from faculty F2 where F2.dept='EE')));

exec DBMS_OUTPUT.PUT_LINE('Query#12');
select F.fname from faculty F
where not exists
(
select C.fid from class C where C.fid=F.fid and C.meets_at in
(select C1.meets_at from class C1, faculty F where C1.fid=F.fid and F.fname='Prof.Wasfi')
) and F.dept in (select F.dept from faculty F where F.fname='Prof.Wasfi');


exec DBMS_OUTPUT.PUT_LINE('Query#13');
select S.sname from student S where S.sid in(
	select E2.sid from enrolled E2 where E2.cnum in
	(select E.cnum from enrolled E where E.cnum not in
		(select E1.cnum from enrolled E1, prerequisite P1 
		where E1.cnum=P1.cnum)
	)
);

exec DBMS_OUTPUT.PUT_LINE('Query#14');
select C.cnum from class C
where not exists
(select P.cnum from prerequisite P where C.cnum=P.cnum and C.meets_at in
	(select C1.meets_at from class C1 where P.prereq=C1.cnum)
);

exec DBMS_OUTPUT.PUT_LINE('Query#15');
select F.fname from faculty F where exists
(select tmp.cnum from 
	(select C2.cnum from class C2
	minus
	select C.cnum from class C where exists( 
		select P.cnum from prerequisite P, class C1 
		where P.cnum=C.cnum and C1.cnum=P.prereq and C.fid<>C1.fid)
	) tmp, class C3 where F.fid=C3.fid and C3.cnum=tmp.cnum
) order by F.fid;

exec DBMS_OUTPUT.PUT_LINE('Query#16');
select C.cnum from class C 
minus(
select P.cnum from prerequisite P where P.prereq in
	(select P1.cnum from prerequisite P1 where P1.cnum=P.prereq and P1.prereq in
		(select P2.cnum from prerequisite P2 where P2.cnum=P1.prereq and P2.prereq in
			(select P3.cnum from prerequisite P3 where P3.cnum=P2.prereq)
		)
	)
);

exec DBMS_OUTPUT.PUT_LINE('Query#17');
select S.sname, tmp.cnum, P5.prereq as extendedprereq from
student S, enrolled E, prerequisite P4, prerequisite P5, 
(
select P.cnum from prerequisite P where P.prereq in
	(select P1.cnum from prerequisite P1 where P1.cnum=P.prereq)
minus
(select P0.cnum from prerequisite P0 where P0.prereq in
	(select P1.cnum from prerequisite P1 where P1.cnum=P0.prereq and P1.prereq in
		(select P2.cnum from prerequisite P2 where P2.cnum=P1.prereq)
	)
)
) tmp where S.sid=E.sid and E.cnum=tmp.cnum and P4.cnum=tmp.cnum 
and P5.cnum=P4.prereq;


exec DBMS_OUTPUT.PUT_LINE('CREATE VIEW A');
create view VIEWA as
select F.fid, F.fname, C.cnum 
from faculty F, class C
where F.fid=C.fid
order by F.fid;

exec DBMS_OUTPUT.PUT_LINE('CREATE VIEW B');
create view VIEWB as
select S.sid, S.sname, E.cnum
from student S, enrolled E
where S.sid=E.sid
order by S.sid;



