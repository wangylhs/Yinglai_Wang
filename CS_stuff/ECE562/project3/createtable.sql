rem EE 562 project2
rem Yinglai Wang
rem wang1105

create table GENERAL_WARD(
	Patient_Name varchar2(30),
	G_Admission_Date Date,
	Patient_Type varchar2(10),
	primary key(Patient_Name, G_Admission_Date, Patient_Type),
	CONSTRAINT check_patient_type
	CHECK (Patient_Type IN ('Cardiac','Neuro','General'))
);

create table SCREENING_WARD(
	Patient_Name varchar2(30),
	S_Admission_Date Date,
	Bed_No number,
	Patient_Type varchar2(10),
	primary key(Patient_Name, S_Admission_Date, Patient_Type)
);

create table PRE_SURGERY_WARD(
	Patient_Name varchar2(30),
	Pre_Admission_Date Date,
	Bed_No number,
	Patient_Type varchar2(10),
	primary key(Patient_Name, Pre_Admission_Date, Patient_Type)
);

create table POST_SURGERY_WARD(
	Patient_Name varchar2(30),
	Post_Admission_Date Date,
	Discharge_Date Date,
	Scount number,
	Patient_Type varchar2(10),
	primary key(Patient_Name, Post_Admission_Date, Patient_Type),
	CONSTRAINT check_scount
	CHECK (Scount<=2)
);

create table Patient_Chart(
	Patient_Name varchar2(30),
	Pdate Date,
	Temperature number,
	BP number,
	primary key(Patient_Name, Pdate)
);

create table DR_Schedule(
	Name varchar2(30),
	Ward varchar2(20),
	Duty_Date Date,
	CONSTRAINT check_ward
	CHECK (Ward IN ('GENERAL_WARD', 'SCREENING_WARD', 
		'PRE_SURGERY_WARD', 'POST_SURGERY_WARD', 'Surgery'))
);

create table Surgeon_Schedule(
	Name varchar2(30),
	Surgery_Date Date
);

create table PATIENT_INPUT(
	Patient_Name varchar2(30),
	General_ward_admission_date Date,
	Patient_Type varchar2(10)
);
