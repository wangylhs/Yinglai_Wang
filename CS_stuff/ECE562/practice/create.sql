create table S(
	s# varchar2(2) primary key,
	sname varchar2(10),
	status int,
	city varchar2(10)
);

create table P(
	p# varchar2(2) primary key,
	pname varchar2(10),
	color varchar2(10),
	weight int,
	city varchar2(10)
);

create table J(
	j# varchar2(2) primary key,
	janme varchar2(10),
	city varchar2(10)
);

create table SPJ(
	s# varchar2(2),
	p# varchar2(2),
	j# varchar2(2),
	qty int,
	primary key(s#, p#, j#),
	foreign key(s#) references S(s#),
	foreign key(p#) references P(p#),
	foreign key(j#) references J(j#)
);

		
