drop procedure pro_print_fine;
drop procedure pro_print_borrower;
drop procedure pro_listborr_mon;
drop procedure pro_listborr;
drop procedure pro_list_popular;

drop function fun_return_book;
drop function fun_most_popular;
drop function fun_issue_anyedition;
drop function fun_issue_book;

drop trigger trg_maxbooks;
drop trigger trg_charge;
drop trigger trg_notcharge;
drop trigger trg_renew;


drop table Pending_request;
drop table Issue;
drop table Borrower;
drop table Author;
drop table Books;