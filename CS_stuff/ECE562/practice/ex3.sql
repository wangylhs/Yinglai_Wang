SET SERVEROUTPUT ON;
exec DBMS_OUTPUT.PUT_LINE('Query #1');
select distinct s.sname from S, SPJ where S.s#=SPJ.s# and SPJ.p#='P2';

exec DBMS_OUTPUT.PUT_LINE('Query #2');
select distinct s1.sname from S s1, SPJ spj1, P p1
where spj1.p#=p1.p# and spj1.s#=s1.s# and p1.color='red';

exec DBMS_OUTPUT.PUT_LINE('Query #3');
select s1.sname from S s1
where not exists
(select * from SPJ spj1 where spj1.s#=s1.s# and spj1.p#='P2');

exec DBMS_OUTPUT.PUT_LINE('Query #4');
select distinct s1.sname from S s1
where not exists
(select * from P p1 where not exists
(select * from SPJ spj1 where spj1.p#=p1.p# and spj1.s#=s1.s#)
); 

exec DBMS_OUTPUT.PUT_LINE('Query #5');
select distinct s1.s# from S s1, SPJ spj2 where spj2.s#=s1.s# and spj2.p# in
(select spj1.p# from SPJ spj1 where spj1.s#='S2');

exec DBMS_OUTPUT.PUT_LINE('Query #6');
select s1.s#, s2.s# from S s1, S s2
where s1.s#<s2.s# and s1.city=s2.city;

exec DBMS_OUTPUT.PUT_LINE('Query #7');
select distinct s1.s#, s1.sname, p1.p#, p1.pname, s1.city, s1.status, spj1.qty
from S s1, P p1, SPJ spj1 
where s1.s#=spj1.s# and spj1.p#=p1.p# and s1.city=p1.city
order by s1.s#;

exec DBMS_OUTPUT.PUT_LINE('Query #8');
select * from SPJ spj1 where spj1.qty>=300 and spj1.qty<=700;

exec DBMS_OUTPUT.PUT_LINE('Query #9');
select s1.s#, p1.p#, j1.j# from S s1, P p1, J j1, SPJ spj1
where spj1.s#=s1.s# and spj1.p#=p1.p# and spj1.j#=j1.j#
and s1.city=p1.city and p1.city=j1.city;

select s1.s#, p1.p#, j1.j# from S s1, P p1, J j1
where s1.city=p1.city and p1.city=j1.city;

exec DBMS_OUTPUT.PUT_LINE('Query #10');

select distinct s1.city, j1.city from S s1, J j1, SPJ spj1
where spj1.s#=s1.s# and spj1.j#=j1.j# and s1.city<>j1.city;

exec DBMS_OUTPUT.PUT_LINE('Query #11');
select s.city from s
union
select p.city from p
union
select j.city from j;

exec DBMS_OUTPUT.PUT_LINE('Query #12');
select s1.s#, p1.p# from S s1, P p1
where not exists
(select * from SPJ spj1 where spj1.s#=s1.s# and spj1.p#=p1.p#);

select s1.s#, p1.p# from S s1, P p1
minus
select spj1.s#, spj1.p# from SPJ spj1;

exec DBMS_OUTPUT.PUT_LINE('Query #13');
select distinct spj1.s#, spj1.p# as PX, spj2.p# as PY from SPJ spj1, SPJ spj2
where spj1.s#=spj2.s# and spj1.p#<spj2.p#;









