create table AbsUser (
    name varchar2(20),
    pw varchar2(99),
    primary key (name)
);

create table Admin (
    iAbsUser varchar2(20) references AbsUser(name),
    permissionlevel number,
    primary key (iAbsUser)
);

create table Log (
    id number,
    rAdmin varchar(20) not null references Admin(iAbsUser) on delete cascade,
    message varchar2(255),
    primary key (id,rAdmin)
);

create table User2 (
    iAbsUser varchar2(20) references AbsUser(name), 
    regdate number,
    regtime number,
    primary key (iAbsUser)
);

create table UserWall (
    rUser varchar2(20) references User2(iAbsUser),
    primary key (rUser)
);

create table Board (
    name varchar2(20), 
    permissionlvl number,
    rAdmin varchar2(20),
    foreign key (rAdmin) references Admin(iAbsUser),
    primary key (name)
);

create table Room (
    name varchar2(20),
    islocked number(1),
    datetime date,
    rBoard varchar2(20),
    rAbsUser varchar2(20),
    foreign key (rBoard) references Board(name),
    foreign key (rAbsUser) references AbsUser(name),
    primary key (name)
);

create table Post (
    id number,
    message varchar2(255),
    datetime date,
    rRoom varchar2(20),
    rUserWall varchar2(20),
    rAbsUser varchar2(20),
    foreign key (rRoom) references Room(name),
    foreign key (rUserWall) references UserWall(rUser),
    foreign key (rAbsUser) references AbsUser(name),
    primary key (id)
);

create table Comment2 (
    id number,
    message varchar2(255),
    datetime date,
    rPost number,
    rAbsUser varchar2(20),
    foreign key (rPost) references Post(id),
    foreign key (rAbsUser) references AbsUser(name),
    primary key (id)
);

create table ChatRoom (
    name varchar2(20),
    primary key (name)
);

create table ChatRoom_AbsUser(
    rChatRoom varchar2(20),
    rAbsUser varchar2(20),
    foreign key (rChatRoom) references ChatRoom(name),
    foreign key (rAbsUser) references AbsUser(name),
    primary key (rChatRoom,rAbsUser)
);

create table Message (
    id number,
    message varchar2(255),
    datetime date,
    rChatRoom varchar2(20),
    rAbsUser varchar2(20),
    foreign key (rChatRoom) references ChatRoom(name),
    foreign key (rAbsUser) references AbsUser(name),
    primary key (id)
);