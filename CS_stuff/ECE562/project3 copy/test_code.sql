set serveroutput on;
create or replace procedure test_code is
out number;

begin
	for i in 1..10 loop
		dbms_output.put_line(i||' ');
		if(i=5) then
			goto end_loop;
		end if;
	end loop;
	dbms_output.put_line('loop finished--');
	<<end_loop>>
	null;
end;
/