set serveroutput on;
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
(select * from OVER_ALL o where o.Name='A' and o.g_date>=to_date('01/01/05','mm/dd/yy')
and o.D_Date<=to_date('01/01/06','mm/dd/yy')
order by o.G_Date)tmp1)tmp2 where tmp2.rownum_a=3)tmp3
where o1.D_Date>=(tmp3.P_Date+2) and o1.D_Date<=(tmp3.P_Date+2+3)
and o1.Name=t.name and o1.G_Date=t.g_date and o1.Name<>'A';

exec dbms_output.put_line('Query#7');
select q.p_name as patient_name, q.surgeon_name, q.physician from query7 q order by q.p_name; 

exec dbms_output.put_line('Query#8');
select s_date as start_date, e_date as end_date from query8;

exec dbms_output.put_line('Query#9');
select * from query9 where (end_date-start_date)>=2;

exec dbms_output.put_line('Query#10');
select name, sum(total_cost) from query10 group by name;

