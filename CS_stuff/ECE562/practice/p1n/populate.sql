rem EE 562 Project 1
rem Yinglai Wang
rem wang1105

insert into student values(1, 'John', 'EE', 'FR', 18);
insert into student values(2, 'Tim', 'EE', 'FR', 19);
insert into student values(3, 'Richard', 'EE', 'SO', 20);
insert into student values(4, 'Edward', 'EE', 'SO', 21);
insert into student values(5, 'Alber', 'CS', 'JR', 22);
insert into student values(6, 'Mary', 'EE', 'JR', 22);
insert into student values(7, 'Jack', 'EE', 'SR', 23);
insert into student values(8, 'Julian', 'EE', 'SR', 22);
insert into student values(9, 'Sam', 'CS', 'SR', 24);
insert into student values(10, 'Ram', 'EE', 'SR', 23);
insert into student values(11, 'Rick', 'EE', 'SR', 24);

insert into faculty values(1,'Prof.James','EE');
insert into faculty values(2,'Prof.Brown','CS');
insert into faculty values(3,'Prof.Wasfi','EE');
insert into faculty values(4,'Prof.Latif','EE');
insert into faculty values(5,'Prof.Rutherford','MA');
insert into faculty values(6,'Prof.Additional','EE');

ALTER SESSION SET NLS_DATE_FORMAT='HH24:MI';
insert into class values('EE101', '9:00', '117', 1);
insert into class values('EE102', '10:00', '117', 2);
insert into class values('EE104', '13:00', '117', 3);
insert into class values('EE151', '15:00', '117', 4);
insert into class values('EE261', '9:00', '118', 4);
insert into class values('MA365', '10:00', '118', 5);
insert into class values('EE347', '13:00', '118', 1);
insert into class values('EE404', '9:00', '115', 3);
insert into class values('MA448', '12:00', '115', 5);
insert into class values('CS480', '13:00', '115', 1);
insert into class values('EE562', '14:00', '115', 6);
insert into class values('EE565', '15:00', '115', 6);


insert into enrolled values('EE101', 1);
insert into enrolled values('EE101', 2);
insert into enrolled values('EE101', 3);
insert into enrolled values('EE101', 4);
insert into enrolled values('EE102', 1);
insert into enrolled values('EE102', 2);
insert into enrolled values('EE102', 4);
insert into enrolled values('EE104', 1);
insert into enrolled values('EE104', 2);
insert into enrolled values('EE104', 3);
insert into enrolled values('EE151', 4);
insert into enrolled values('EE151', 5);
insert into enrolled values('EE151', 6);
insert into enrolled values('EE261', 1);
insert into enrolled values('EE261', 2);
insert into enrolled values('EE261', 3);
insert into enrolled values('EE261', 4);
insert into enrolled values('EE261', 5);
insert into enrolled values('EE261', 7);
insert into enrolled values('MA365', 5);
insert into enrolled values('MA365', 6);
insert into enrolled values('MA365', 7);
insert into enrolled values('MA365', 8);
insert into enrolled values('EE347', 5);
insert into enrolled values('EE347', 7);
insert into enrolled values('EE347', 8);
insert into enrolled values('EE347', 9);
insert into enrolled values('EE404', 9);
insert into enrolled values('EE404', 10);
insert into enrolled values('EE404', 7);
insert into enrolled values('MA448', 7);
insert into enrolled values('MA448', 8);
insert into enrolled values('MA448', 9);
insert into enrolled values('MA448', 10);
insert into enrolled values('CS480', 6);
insert into enrolled values('CS480', 7);
insert into enrolled values('CS480', 8);
insert into enrolled values('CS480', 9);

insert into prerequisite values('EE261', 'EE151');
insert into prerequisite values('EE104', 'EE102');
insert into prerequisite values('EE102', 'EE101');
insert into prerequisite values('MA448', 'MA365');
insert into prerequisite values('EE347', 'EE261');
insert into prerequisite values('CS480', 'MA365');
insert into prerequisite values('MA365', 'EE102');
insert into prerequisite values('EE562', 'EE104');
insert into prerequisite values('EE565', 'EE562');
