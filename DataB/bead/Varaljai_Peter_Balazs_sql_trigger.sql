drop table Log CASCADE CONSTRAINTS;

create table Log (
    timestm timestamp,
    message varchar2(255),
    rBoard varchar2(20),
    foreign key(rBoard) references Board(name),
    primary key (timestm)
);

create or replace trigger log_event
    after
        insert or
        update or
        delete
    on Board
    for each row
begin
    case
        when INSERTING then
            insert into Log values
                (
                    systimestamp,
                    'INSERT',
                    :NEW.name
                );
        when UPDATING then
            insert into Log values
                (
                    systimestamp,
                    'UPDATE',
                    :NEW.name
                );
        when DELETING then
            insert into Log values
                (
                    systimestamp,
                    'DELETE',
                    :OLD.name
                );
    end case;
end;