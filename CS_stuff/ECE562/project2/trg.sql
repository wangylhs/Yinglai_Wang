CREATE OR REPLACE TRIGGER trg_maxbooks BEFORE INSERT 
ON Issue 
FOR EACH ROW
DECLARE
	b_count number;
	b_status varchar2(20);
	max_books EXCEPTION;
BEGIN
	BEGIN
		select count(*) into b_count
		from Issue i
		where i.borrower_id=:new.borrower_id and i.return_date is NULL;
	EXCEPTION
		WHEN NO_DATA_FOUND THEN
			b_count:=0;
	END;

	select b.status into b_status
	from Borrower b
	where b.borrower_id=:new.borrower_id;
	IF (b_count>=2 and b_status='student') THEN
		raise max_books;
	END IF;
	IF (b_count>=3 and b_status='faculty') THEN
		raise max_books;
	END IF;
EXCEPTION
	WHEN max_books THEN
		raise_application_error(-20300, 'borrower '||to_char(:new.borrower_id)||' has reached its maximum books as a '||b_status);
END;
/

CREATE OR REPLACE TRIGGER trg_charge AFTER INSERT ON Issue
FOR EACH ROW
BEGIN
	UPDATE Books b SET b.status='charged' where b.book_id=:new.book_id;
END;
/

CREATE OR REPLACE TRIGGER trg_notcharge AFTER UPDATE OF return_date
ON Issue
FOR EACH ROW
BEGIN
	UPDATE Books b SET b.status='not charged' where b.book_id=:new.book_id;	
END;
/

CREATE OR REPLACE TRIGGER trg_renew BEFORE INSERT
ON Pending_request
FOR EACH ROW
DECLARE
	ct_i number;
	ct_p number;
	ct_p_self number;
	ct_not_ret number;
	max_reached EXCEPTION;
	pend_exist EXCEPTION;
	not_returned EXCEPTION;

BEGIN
	BEGIN
		select count(*) into ct_p_self from Pending_request p
		where p.requester_id=:new.requester_id and p.book_id=:new.book_id;
	EXCEPTION
		WHEN NO_DATA_FOUND THEN
			ct_p_self:=0;
	END;
	BEGIN
		select count(*) into ct_not_ret from Issue i
		where i.borrower_id=:new.requester_id and i.book_id=:new.book_id and i.return_date is NULL;
	EXCEPTION
		WHEN NO_DATA_FOUND THEN
			ct_not_ret:=0;
	END;

	BEGIN
		select count(*) into ct_i from Issue i
		where i.borrower_id=:new.requester_id and i.return_date is NULL;
	EXCEPTION
		WHEN NO_DATA_FOUND THEN
			ct_i:=0;
	END;
	BEGIN
		select count(*) into ct_p from Pending_request p
		where p.requester_id=:new.requester_id;
	EXCEPTION
		WHEN NO_DATA_FOUND THEN
			ct_p:=0;
	END;
	
	IF (ct_p_self>0) THEN
		raise pend_exist;
	ELSIF (ct_not_ret>0) THEN
		raise not_returned;
	ELSIF ((ct_i+ct_p)>=7) THEN
		raise max_reached;
	END IF;
EXCEPTION
	WHEN max_reached THEN
		raise_application_error(-20300,'Pending_request denied, 
								requester reached its maximum number on pending and borrow books.');
	WHEN pend_exist THEN
		raise_application_error(-20301,'Pending_request denied,
								pendingrequest already exist.');
	WHEN not_returned THEN
		raise_application_error(-20302,'Pending_request denied,
								book was borrowed by this requester and not returned yet.');

END;
/



