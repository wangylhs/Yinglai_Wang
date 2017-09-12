rem EE 562 Project 1
rem Yinglai Wang
rem wang1105



create table student(
	sid int primary key,
	sname varchar2(15),
	major varchar2(3),
	levels varchar2(2),
	age int
);

create table faculty(
	fid int primary key,
	fname varchar2(20),
	dept varchar2(5)
);

create table class(
	cnum varchar2(6) primary key,
	meets_at date,
	room varchar2(6),
	fid int,
	foreign key(fid) references faculty(fid)
);


create table enrolled(
	cnum varchar2(6),
	sid int,
	primary key(cnum, sid),
	foreign key(cnum) references class(cnum),
	foreign key(sid) references student(sid)
);

create table prerequisite(
	cnum varchar2(6),
	prereq varchar2(6),
	primary key(cnum, prereq),
	foreign key(cnum) references class(cnum)
);
