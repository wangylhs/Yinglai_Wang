insert into S values('S1', 'smith', 20, 'london');
insert into S values('S2', 'jones', 10, 'paris');
insert into S values('S3', 'blake', 30, 'paris');
insert into S values('S4', 'clark', 20, 'london');
insert into S values('S5', 'adams', 30, 'athens');

insert into P values('P1','nut', 'red', 12, 'london');
insert into P values('P2','bolt', 'green', 17, 'paris');
insert into P values('P3','screw', 'blue', 17, 'rome');
insert into P values('P4','screw', 'red', 14, 'london');
insert into P values('P5','cam', 'blue', 12, 'paris');
insert into P values('P6','cog', 'red', 19, 'london');

insert into J values('J1', 'sorter', 'paris');
insert into J values('J2', 'display', 'rome');
insert into J values('J3', 'ocr', 'athens');
insert into J values('J4', 'console', 'athens');
insert into J values('J5', 'raid', 'london');
insert into J values('J6', 'eds', 'oslo');
insert into J values('J7', 'tape', 'london');

insert into SPJ values('S1','P1','J1',200);
insert into SPJ values('S1','P1','J4',700);
insert into SPJ values('S2','P3','J1',400);
insert into SPJ values('S2','P3','J2',200);
insert into SPJ values('S2','P3','J3',200);
insert into SPJ values('S2','P3','J4',500);
insert into SPJ values('S2','P3','J5',600);
insert into SPJ values('S2','P3','J6',400);
insert into SPJ values('S2','P3','J7',800);
insert into SPJ values('S2','P5','J2',100);

insert into SPJ values('S3','P3','J1',200);
insert into SPJ values('S3','P4','J2',500);
insert into SPJ values('S4','P6','J3',300);
insert into SPJ values('S4','P6','J7',300);
insert into SPJ values('S5','P2','J2',200);
insert into SPJ values('S5','P2','J4',100);
insert into SPJ values('S5','P5','J5',500);
insert into SPJ values('S5','P5','J7',100);
insert into SPJ values('S5','P6','J2',200);
insert into SPJ values('S5','P1','J4',100);

insert into SPJ values('S5','P3','J4',200);
insert into SPJ values('S5','P4','J4',800);
insert into SPJ values('S5','P5','J4',400);
insert into SPJ values('S5','P6','J4',500);



