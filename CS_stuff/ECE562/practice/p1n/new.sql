SET SERVEROUTPUT ON;
exec DBMS_OUTPUT.PUT_LINE('Query #1');
select MAX(s1.age) from student s1
where s1.major='CS' or s1.sid in
(select e1.sid from enrolled e1, class c1, faculty f1
where e1.cnum=c1.cnum and c1.fid=f1.fid and f1.fname='Prof.Brown');

exec DBMS_OUTPUT.PUT_LINE('Query #2');
select c1.cnum from class c1
where c1.room='115' or c1.cnum in
(select e1.cnum from enrolled e1 
group by e1.cnum having count(*)>=5);

exec DBMS_OUTPUT.PUT_LINE('Query #3');
select distinct s1.sname from student s1, enrolled e1, enrolled e2, class c1, class c2
where e1.sid=s1.sid and e1.cnum=c1.cnum and e2.sid=e1.sid and e2.cnum=c2.cnum
and c1.meets_at=c2.meets_at and e1.cnum<>e2.cnum;

exec DBMS_OUTPUT.PUT_LINE('Query #4');
select f1.fname from faculty f1, class c1
where f1.fid=c1.fid
group by f1.fname
having count(*)=(select count(distinct c1.room) from class c1);

exec DBMS_OUTPUT.PUT_LINE('Query #5');
select f1.fname from faculty f1, enrolled e1, class c1
where f1.fid=c1.fid and e1.cnum=c1.cnum
group by f1.fname
having count(*)>8;

exec DBMS_OUTPUT.PUT_LINE('Query #6');
select s1.levels, avg(s1.age) from student s1
where s1.levels<>'JR'
group by s1.levels;

exec DBMS_OUTPUT.PUT_LINE('Query #7');
select s1.sname from student s1 where s1.sid in
(select e1.sid from enrolled e1
group by e1.sid
having count(*)>=all(select count(*) from enrolled e2 group by e2.sid));

exec DBMS_OUTPUT.PUT_LINE('Query #8');
select s1.sname from student s1 
where not exists
(select e1.sid from enrolled e1 where e1.sid=s1.sid);

exec DBMS_OUTPUT.PUT_LINE('Query #9');
select s1.age, s1.levels from student s1
group by s1.age, s1.levels
having s1.levels in
(select s2.levels from student s2 where s2.age=s1.age 
group by s2.levels, s2.age
having count(*)>=all(select count(*) from student s3
where s2.age=s3.age group by s3.levels, s3.age)
);

exec DBMS_OUTPUT.PUT_LINE('Query #10');
select distinct
(select count(e1.sid) as ee from enrolled e1, class c1, faculty f1
where e1.cnum=c1.cnum and c1.fid=f1.fid and f1.dept='EE')/
(select count(f3.fid) from faculty f3 where f3.dept='EE')
-
(
(select count(e2.sid) as cs from enrolled e2, class c2, faculty f2
where e2.cnum=c2.cnum and c2.fid=f2.fid and f2.dept='CS')/
(select count(f4.fid) from faculty f4 where f4.dept='CS')
) as diff from faculty f;

exec DBMS_OUTPUT.PUT_LINE('Query #11');
select f1.fname from faculty f1
where f1.fid in
(select f2.fid from faculty f2, enrolled e1, class c1
where f2.fid=c1.fid and c1.cnum=e1.cnum
group by f2.fid
having count(*)>((select count(e1.sid) from enrolled e1, class c1, faculty f1
where e1.cnum=c1.cnum and c1.fid=f1.fid and f1.dept='EE')/
(select count(f3.fid) from faculty f3 where f3.dept='EE'))
);

exec DBMS_OUTPUT.PUT_LINE('Query #12');
select f1.fname from faculty f1
where f1.fid not in
(select c1.fid from class c1 where c1.fid=f1.fid and c1.meets_at in
(select c2.meets_at from class c2, faculty f2
where c2.fid=f2.fid and f2.fname='Prof.Wasfi')
) and f1.dept in
(select f3.dept from faculty f3 where f3.fname='Prof.Wasfi');

exec DBMS_OUTPUT.PUT_LINE('Query #13');
select s1.sname from student s1
where s1.sid in
(select e1.sid from enrolled e1 where e1.cnum not in
(select e2.cnum from enrolled e2, prerequisite p2 where e2.cnum=p2.cnum)
);

exec DBMS_OUTPUT.PUT_LINE('Query #14');
select c1.cnum from class c1
where not exists
(select c1.cnum from prerequisite p1, class c2 
where c1.cnum=p1.cnum and c2.cnum=p1.prereq and c1.meets_at=c2.meets_at);

exec DBMS_OUTPUT.PUT_LINE('Query#15');
select distinct f1.fname from faculty f1, class c
where f1.fid=c.fid and c.cnum in
(select c1.cnum from class c1
minus
select c2.cnum from class c2 where exists
(select p2.cnum from prerequisite p2, class c3
where p2.cnum=c2.cnum and c3.cnum=p2.prereq and c3.fid<>c2.fid)
);

exec DBMS_OUTPUT.PUT_LINE('Query#16');

(select c1.cnum from class c1)
minus
(select p1.cnum from prerequisite p1 where p1.prereq in
	(select p2.cnum from prerequisite p2 where
 	p2.cnum=p1.prereq and p2.prereq in
		(select p3.cnum from prerequisite p3 where
		p3.cnum=p2.prereq and p3.prereq in
			(select p4.cnum from prerequisite p4 where
			p4.cnum=p3.prereq)
		)
	)
);

exec DBMS_OUTPUT.PUT_LINE('Query#17');

select s1.sname, temp.cnum, p5.prereq as exprereq from
student s1, enrolled e1, prerequisite p4, prerequisite p5,
(
	(select p1.cnum from prerequisite p1 where p1.prereq in
		(select p2.cnum from prerequisite p2 where p2.cnum=p1.prereq)
	)
	minus
	(select p1.cnum from prerequisite p1 where p1.prereq in
		(select p2.cnum from prerequisite p2 where 
		p2.cnum=p1.prereq and p2.prereq in
			(select p3.cnum from prerequisite p3 where
			p3.cnum=p2.prereq)
		)
	)
) temp
where temp.cnum=e1.cnum and s1.sid=e1.sid and p4.cnum=temp.cnum 
and p5.cnum=p4.prereq;














