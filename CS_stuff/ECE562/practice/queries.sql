SET SERVEROUTPUT ON;
exec DBMS_OUTPUT.PUT_LINE('Query #1');
select spj1.s# from SPJ spj1 
where spj1.j#='J1' and spj1.s# in 
(select spj2.s# from SPJ spj2 where spj2.j#='J2');

select spj1.s# from SPJ spj1
where spj1.j#='J1' and exists
(select * from SPJ spj2 where spj1.s#=spj2.s# and spj2.j#='J2');

exec DBMS_OUTPUT.PUT_LINE('Query #2');
select s1.s# from S s1, J j1, P p1, SPJ spj1
where s1.s#=spj1.s# and spj1.j#=j1.j# and spj1.p#=p1.p# 
and (j1.city='london' or j1.city='paris') and p1.color='red';

exec DBMS_OUTPUT.PUT_LINE('Query #3');
select spj1.p# from SPJ spj1, S s1, J j1
where spj1.j#=j1.j# and spj1.s#=s1.s# and j1.city='london' and s1.city='london';

exec DBMS_OUTPUT.PUT_LINE('Query #4');
select distinct s1.city, j1.city from S s1, J j1, SPJ spj1
where spj1.s#=s1.s# and spj1.j#=j1.j# and s1.city<>j1.city;

exec DBMS_OUTPUT.PUT_LINE('Query #5');
select spj1.j# from SPJ spj1 where spj1.s#='S1'
minus
select spj2.j# from SPJ spj2 where spj2.s#<>'S1';

exec DBMS_OUTPUT.PUT_LINE('Query #6');
select distinct spj1.p# from SPJ spj1
where not exists
	(select * from J j1 where j1.city='london' and not exists
		(select * from SPJ spj2 where spj2.j#=j1.j# and spj2.p#=spj1.p#
		)
	);

exec DBMS_OUTPUT.PUT_LINE('Query #7');
select spj3.j# from SPJ spj3 where spj3.p# in(
(select spj1.p# from SPJ spj1)
minus
(select spj2.p# from SPJ spj2, S s2 where spj2.s#=s2.s# and s2.s#<>'S1')
);
