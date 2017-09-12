alter session set NLS_DATE_FORMAT='mm/dd/yy';
insert into patient_chart values('G','1/2/05',97,100);
insert into patient_chart values('G','1/3/05',97,110);
insert into patient_chart values('G','1/4/05',97,110);
insert into patient_chart values('G','1/5/05',97,100);
insert into patient_chart values('G','1/6/05',97,120);
insert into patient_chart values('G','1/7/05',97,120);
insert into patient_chart values('G','1/8/05',97,120);
insert into patient_chart values('G','1/9/05',97,120);
insert into patient_chart values('G','1/10/05',97,100);
insert into patient_chart values('G','1/11/05',97,100);
insert into patient_chart values('G','1/12/05',97,120);
insert into patient_chart values('G','1/13/05',97,120);
insert into patient_chart values('G','1/14/05',97,120);


--test queries
insert into GENERAL_WARD values('A', '1/1/05', 'Cardiac');
insert into SCREENING_WARD values('A', '1/4/05', 1, 'Cardiac');
insert into PRE_SURGERY_WARD values('A','1/7/05',1,'Cardiac');
insert into POST_SURGERY_WARD values('A', '1/9/05','1/11/05',2,'Cardiac');


insert into GENERAL_WARD values('C', '1/1/05', 'Neuro');
insert into SCREENING_WARD values('C', '1/4/05', 3, 'Neuro');
insert into PRE_SURGERY_WARD values('C','1/7/05',3,'Neuro');
insert into POST_SURGERY_WARD values('C', '1/9/05','1/13/05',2,'Neuro');

insert into GENERAL_WARD values('D', '1/1/05', 'Neuro');
insert into SCREENING_WARD values('D', '1/4/05', 4, 'Neuro');
insert into PRE_SURGERY_WARD values('D','1/7/05',4,'Neuro');
insert into POST_SURGERY_WARD values('D', '1/9/05','1/11/05',2,'Neuro');

insert into GENERAL_WARD values('E', '1/1/05', 'Cardiac');
insert into SCREENING_WARD values('E', '1/4/05', 5, 'Cardiac');
insert into PRE_SURGERY_WARD values('E','1/9/05',1,'Cardiac');
insert into POST_SURGERY_WARD values('E', '1/11/05','1/15/05',2,'Cardiac');

insert into GENERAL_WARD values('F','1/1/05', 'Cardiac');
insert into SCREENING_WARD values('F','1/7/05', 1, 'Cardiac');

insert into POST_SURGERY_WARD values('F','1/11/05','1/13/05',1,'Cardiac');

insert into GENERAL_WARD values('G', '1/2/05', 'General');
insert into SCREENING_WARD values('G', '1/7/05', 2, 'General');
insert into PRE_SURGERY_WARD values('G','1/10/05',2,'General');
insert into POST_SURGERY_WARD values('G', '1/12/05','1/14/05',1,'General');

insert into GENERAL_WARD values('A','2/1/05','Cardiac' );
insert into SCREENING_WARD values('A','2/4/05',1,'Cardiac' );
insert into PRE_SURGERY_WARD values('A','2/7/05',1,'Cardiac' );
insert into POST_SURGERY_WARD values('A','2/9/05','2/13/05',2,'Cardiac' );

insert into GENERAL_WARD values('A','2/19/05','Neuro');
insert into SCREENING_WARD values('A','2/22/05',1,'Neuro');
insert into PRE_SURGERY_WARD values('A','2/28/05',1,'Neuro');
insert into POST_SURGERY_WARD values('A','3/2/05','3/4/05',2,'Neuro' );



insert into GENERAL_WARD values('B','2/1/05','Cardiac' );
insert into SCREENING_WARD values('B','2/4/05',2,'Cardiac' );
insert into PRE_SURGERY_WARD values('B','2/7/05',2,'Cardiac' );
insert into POST_SURGERY_WARD values('B','2/9/05','2/13/05',2,'Cardiac' );


insert into GENERAL_WARD values('C','2/1/05','Cardiac' );
insert into SCREENING_WARD values('C','2/4/05',3,'Cardiac' );
insert into PRE_SURGERY_WARD values('C','2/7/05',3,'Cardiac' );
insert into POST_SURGERY_WARD values('C','2/9/05','2/11/05',2,'Cardiac' );


insert into GENERAL_WARD values('D','2/1/05','Cardiac' );
insert into SCREENING_WARD values('D','2/4/05',4,'Cardiac' );
insert into PRE_SURGERY_WARD values('D','2/7/05',4,'Cardiac' );
insert into POST_SURGERY_WARD values('D','2/9/05','2/13/05',2,'Cardiac' );

insert into GENERAL_WARD values('E','2/1/05','Cardiac' );
insert into SCREENING_WARD values('E','2/4/05',5,'Cardiac' );

insert into POST_SURGERY_WARD values('E','2/8/05','2/12/05',2,'Cardiac' );

insert into GENERAL_WARD values('F','2/1/05','Cardiac' );
insert into SCREENING_WARD values('F','2/7/05',1,'Cardiac' );
insert into PRE_SURGERY_WARD values('F','2/10/05',1,'Cardiac' );
insert into POST_SURGERY_WARD values('F','2/12/05','2/16/05',2,'Cardiac' );

insert into GENERAL_WARD values('A','2/14/05','Cardiac' );
insert into SCREENING_WARD values('A','2/17/05',1,'Cardiac' );

insert into POST_SURGERY_WARD values('A','2/21/05','2/23/05',1,'Cardiac' );

insert into GENERAL_WARD values('H','2/14/05','Cardiac' );
insert into SCREENING_WARD values('H','2/17/05',1,'Cardiac' );

insert into POST_SURGERY_WARD values('H','2/21/05','2/25/05',1,'Cardiac' );


insert into GENERAL_WARD values('B','2/26/05','Neuro' );
insert into SCREENING_WARD values('B','2/28/05',1,'Neuro' );
insert into PRE_SURGERY_WARD values('B','3/7/05',1,'Neuro' );
insert into POST_SURGERY_WARD values('B','3/9/05','3/13/05',2,'Neuro' );

insert into GENERAL_WARD values('B','3/22/05','Cardiac' );
insert into SCREENING_WARD values('B','4/9/05',1,'Cardiac' );

insert into POST_SURGERY_WARD values('B','4/13/05','4/15/05',2,'Cardiac' );


insert into GENERAL_WARD values('H','12/24/05','Cardiac' );
insert into SCREENING_WARD values('H','12/27/05',1,'Cardiac' );
insert into PRE_SURGERY_WARD values('H','12/31/05',1,'Cardiac' );
insert into POST_SURGERY_WARD values('H','1/2/06','1/4/06',1,'Cardiac' );
