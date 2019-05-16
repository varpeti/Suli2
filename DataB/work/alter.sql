alter table User2 drop (regdate, regtime);
alter table User2 add (regdatetime date default sysdate);
alter table Room modify (datetime date default sysdate);
alter table Post modify (datetime date default sysdate);
alter table Comment2 modify (datetime date default sysdate);
alter table Message modify (datetime date default sysdate);