alter session set NLS_DATE_FORMAT='mm/dd/yy';
insert into GENERAL_WARD values('A', '4/1/04', 'Cardiac');
insert into SCREENING_WARD values('A', '5/4/05', 1, 'Cardiac');
insert into PRE_SURGERY_WARD values('A','5/7/05',1,'Cardiac');
insert into POST_SURGERY_WARD values('A', '5/9/05','5/13/05',1,'Cardiac');

insert into GENERAL_WARD values('B', '4/1/05', 'Cardiac');
insert into SCREENING_WARD values('B', '5/4/05', 1, 'Cardiac');
insert into PRE_SURGERY_WARD values('B','5/7/06',1,'Cardiac');
insert into POST_SURGERY_WARD values('B', '5/9/06','5/13/06',1,'Cardiac');

insert into GENERAL_WARD values('C', '4/1/05', 'Cardiac');
insert into SCREENING_WARD values('C', '5/4/05', 1, 'Cardiac');
insert into PRE_SURGERY_WARD values('C','5/7/05',1,'Cardiac');
insert into POST_SURGERY_WARD values('C', '5/9/05','5/13/05',1,'Cardiac');






	select to_date('05/04/05','mm/dd/yy')-to_date('01/01/05','mm/dd/yy') from dual;