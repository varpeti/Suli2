###### Introduction​ ​ to​ ​ Database​ ​ Systems

# Database for a simple forum website

Project by: **Váraljai Péter**

Project Supervisor: **Gábor​ Csaba**

---

## Introduction​

I would like to create a small database to show examples of all types of entities and relationships. I will store the data of a small forum, including useres, admins, their messages, post, and comments. (ect)

## Description

- **Board:**
Figurarly this is the "main menu" every **Room** is listed under different **Board**. It can be created or modified by any **Admin** who has a right permission level.

- **Room:**
**Room**s are attached to **Board**s. Every **Room** contain different **Post** from different **User**s. It can be created by any **User**. It has creation time, and it can be locked by any **Admin**.

- **Post:**
**Post** are attached to **Room**s or **UserWall**s. Users can **Comment** any **Post**s (except if the **Room** is locked).
It has creation time, belongs to an **User**, and contains a message.

- **Comment:**
Every **User** can **Comment** their/other **User**s **Post**.
It has creation time, belongs to an **User**, and contains a message.

- **ChatRoom:**
**Chatroom**s are automaticaly created rooms where **User**s and **Admin**s can send **Message**s to each other.
Multiple **User**s can be in the same **ChatRoom**, and **User**s can be in multiple **ChatRoom**s.

- **Message:**
Every **User** can send **Message**s to other **User**s are in the same **ChatRoom**.
It has creation time, belongs to a **User**, and contains a message.

- **AbsUser:**
This is the abstract user. It stores username and hashed and encrypted password.

- **User:**
This is an ISA subclass of AbsUser. It has registration date and **UserWall**.

- **Admin:**
This is an ISA subclass of AbsUser. It has permission level, and a **Log**ger.

- **UserWall:**
This is belongs to a **User**. Other **User**s can **Post** their opinions here.

- **Log:**
This is a weak table. It is belongs to an **Admin** and cointains every modifications an **Admin** done.


## E/R Diagramm

![ER Diagramm](./Varaljai_Peter_Balazs_ER.png "ER Diagramm")


## Relational model

`primary key(s)`

**Board**(`name`, permissionlvl, rAdmin)

**Plvl_Board**(`rBoard`,`lvl`)

**Room**(`name`, islocked, date, time, rBoard, rAdmin)

**Post**(`id`, message, date, time, rRoom, rUserWall, rAbsUser)

**Comment**(`id`, message, date, time, rPost, rAbsUser)

**ChatRoom**(`id`)

**ChatRoom_AbsUser**(`rChatRoom`,`rAbsUser`)

**Message**(`id`, message, date, time, rChatroom, rAbsUser)

**AbsUser**(`name`, pw)

**User**(`iAbsUser`, regdate, regtime)

**Admin**(`iAbsUser`, permissionlvl)

**Plvl_Admin**(`rAdmin`,`lvl`)

**UserWall**(`rUser`)

**Log**(`rAdmin`,message)

## Querries

### 1.

Melyik az a top 10 **Post** aminek a legtöbb **Comment**je van?

What are the top 10 most popular **Post**?

```sql
select *
from 
( 
    select Post.id, count(Comment2.id) as Comments
    from Post, Comment2 
    where Comment2.rPost = Post.id
    group by Post.id
    order by Comments desc
)
where rownum <=10
;
```

Output:
```bash
        ID   COMMENTS
---------- ----------
 263887968         40
1318491853         35
  56601904         34
  56132275         33
 623349058         29
 264115052         29
1344876445         28
 468665454         28
 404364516         27
 139001579         27

 10 rows selected.
```

Relational algebra:
```
σ rownum() > 0 and rownum() ≤ 10 ρ t1 ( τ Comments desc π Post.id, Comments γ Post.id; COUNT(Comment2.id)→Comments σ Comment2.rPost = Post.id Post ⨯ Comment2)
```

### 2.

Melyek azok a **Board**ok, és ki csinálta, amiket nem 6-os vagy 4-es jogú **Admin** készített?

What are the name of the **Board**s and who are the creators, where the creator **Admin** permissionlvl isn't 6 nor 4?

```sql
select Board.name as BoardName, AbsUser.name as AdminName
from AbsUser, Board
where AbsUser.name like Board.rAdmin
    and AbsUser.name != all 
    (
        select Admin.iAbsUser
        from Admin
        where permissionlevel = any (4,6)
    )
;
```

Output:
```bash
BOARDNAME            ADMINNAME           
-------------------- --------------------
Atmg                 Hgkn5               
rXmhxjUq             efmd09583           
Vfiem                pyejoy0             
dmxcjz               ngjrRcgyx           
```

Relational algebra:
```
ρ BoardName←Board.name, AdminName←AbsUser.name π Board.name, AbsUser.name σ AbsUser.name = Board.rAdmin and AbsUser.name in ρ t1 ( π Admin.iAbsUser σ permissionlevel = 4 or permissionlevel = 6 Admin ) AbsUser ⨯ Board
```

### 3.

Melyek azok a **Post**ok melyek alatt a 2 legfőbb Admin is **Comment**elt (mindekető)?

What are the ids of the **Post**s, where the 2 Big Bosses are **Comment**ed (both)?   

```sql
create view TheBigBosses as
    select *
    from 
    (
        select Admin.iAbsUser as username
        from Admin
        order by Admin.permissionlevel desc
    ) 
    where rownum <=2
;

create view PnC as
    select Post.id as pid, Comment2.id as cid, Comment2.rAbsUser as username
    from Post, Comment2
    where Comment2.rPost = Post.id
;

select PnC.pid
from PnC, TheBigBosses
where PnC.username = TheBigBosses.username
group by PnC.pid
having  min(PnC.username) = ( select min(TheBigBosses.username) from TheBigBosses )
    and max(PnC.username) = ( select max(TheBigBosses.username) from TheBigBosses )
;

drop view TheBigBosses;
drop view PnC;
```

Output:
```bash
View THEBIGBOSSES created.

View PNC created.

       PID
----------
 453140951
 549571820
 946073490
 964047727
1352258535
  56601904
  40506796
1267821697
1216134633
  64251270
 579701661
 858015113
 380910673
 831785068
1108668441

15 rows selected. 

View THEBIGBOSSES dropped.

View PNC dropped.
```

Relational algebra:
```
TheBigBosses: σ rownum() > 0 and rownum() ≤ 2 ρ t1 ( τ Admin.permissionlevel desc ρ username←Admin.iAbsUser π Admin.iAbsUser, permissionlevel Admin)

SnC: ρ pid←Post.id, cid←Comment2.id, username←Comment2.rAbsUser π Post.id, Comment2.id, Comment2.rAbsUser σ Comment2.rPost = Post.id Post ⨯ Comment2


π username (SnC ÷ TheBigBosses)
```

### 4.

Mennyi az **Admin**ok által készített tartalom összesen **Room**okra, **Post**okra és **Comment**ekre lebontva?

How many contents made by the staff by **Room**s, **Post**s and **Comment**s? 

```sql
create table R_P_C (type varchar2(20));
insert into R_P_C values ('Comments');
insert into R_P_C values ('Posts');
insert into R_P_C values ('Rooms');

select type, count(rAbsUser) as num
from Comment2, Admin, R_P_C
where Comment2.rAbsUser = Admin.iAbsUser
    and R_P_C.type like 'Comments'
group by type
union
select type, count(rAbsUser)
from Post, Admin, R_P_C
where Post.rAbsUser = Admin.iAbsUser
    and R_P_C.type like 'Posts'
group by type
union
select type, count(rAbsUser)
from Room, Admin, R_P_C
where Room.rAbsUser = Admin.iAbsUser
    and R_P_C.type like 'Rooms'
group by type
;

drop table R_P_C;
```

Output:
```bash
Table R_P_C created.
1 row inserted.
1 row inserted.
1 row inserted.

TYPE                        NUM
-------------------- ----------
Comments                    970
Posts                       196
Rooms                         7

Table R_P_C dropped.
```

### 5.

Az "yyg" egy súlyos káromkodás, elég sokszor elrejtik egy szóban hogy ne tűnjön annyira durvának.
Melyek azok a **User**ek, akik nem **Admin**ok és "yyg"-vel káromkodtak?

Who are the **User**s (aren't **Admin**s), used the bad word "yyg"?

```sql
select Comment2.rAbsUser as Wall_Of_Shame
from Comment2 
where Comment2.message like '%yyg%'
union
select Post.rAbsUser
from Post
where Post.message like '%yyg%'
union
select Message.rAbsUser
from Message
where Message.message like '%yyg%'
minus
select Admin.iAbsUser 
from Admin
;
```

Output:
```bash
WALL_OF_SHAME       
--------------------
Fpkxol2895          
Hwbin8              
Vzrmj570            
Yxfkf               
dtvmpffnu           
srpu3082            

6 rows selected.
```

### 6. 

Mennyit **Post**ot írtak a **UserWall**jára az 5 legrégebbi tagnak?

How many **Post**s written to the 5 oldest memeber of **Users**?

```sql
select UserName, count(Post.id) as Wall_Posts, (cast(days/365 as int)) as Age
from Post, UserWall,
(
    select *
    from
    (
        select User2.iAbsUser as UserName, (sysdate - User2.regdatetime) as days
        from User2
        order by days desc
    )
    where rownum <= 5
)
where Post.rUserWall = UserWall.rUser
    and  UserWall.rUser = UserName
group by UserName, days
order by days desc 
;
```

Output:
```bash
USERNAME             WALL_POSTS        AGE
-------------------- ---------- ----------
vvCpo43                      14         18
netifqqbF                    11         18
kpml8                        12         18
Fpkxol2895                    2         17
XrOsfsf690                   19         17
```

### 7.

Kik azok akik benne vannak a top 20 legtöbbet **Comment**elők és a top 20 legtöbb **Message**t küldőkben is?

Who are the **AbsUsers**, are in the top 20 most posted **Comment**s and in the top 20 most sent **Message**s group?

```sql
select *
from 
( 
    select AbsUser.name
    from AbsUser, Comment2 
    where Comment2.rAbsUser = AbsUser.name
    group by AbsUser.name
    order by count(Comment2.id) desc
)
where rownum <=20
intersect
select *
from 
( 
    select AbsUser.name
    from AbsUser, Message 
    where Message.rAbsUser = AbsUser.name
    group by AbsUser.name
    order by count(Message.id) desc
)
where rownum <=20
;
```

Output:
```bash
NAME                
--------------------
Hgkn5               
Woccvjdcv           
pjmDhaqrg           
```

## View 

Melyik **Board**okat használják legtöbbet, a **Room**ok (x5) és **Post**ok (x2) és **Comment**ek (x1) száma alapján?

```sql
drop view TopPosts;
drop view TopRooms;
drop view TopBoards;

create view TopPosts as
    select Post.id, count(Comment2.id) as num
    from Post, Comment2 
    where Comment2.rPost = Post.id
    group by Post.id
    order by num desc
;

create view TopRooms as
    select Room.name, count(Post.id) as num
    from Room, Post
    where Post.rRoom = Room.name
    group by Room.name
    order by num desc
;

create view TopBoards as
    select Board.name, (count(Room.name)*5+count(TopRooms.name)*2+count(TopPosts.id)) as num
    from Board, Room, Post, TopPosts, TopRooms
    where Post.id = TopPosts.id and Room.name = TopRooms.name and Room.rBoard = Board.name
    group by Board.name
    order by num desc
;

select * from TopBoards;
```

## Normal forms

The database should be normalized to avoid anomalies. Below I summarize the main normal forms. I will check my tables and decide in which normal form they are.


### First Normal Form (**1NF**)

In **First Normal Form**, any row must not have a column in which more than one value is saved, like separated with commas. Rather than that, we must separate such data into multiple rows.


### Second Normal Form (**2NF**)

A database is in **2NF** if it is in **First Normal Form** and all non-key attributes are fully functional dependent on any candidate key.


### Boyce-Codd Normal Form (**BCNF**)

A database is in **Boyce-Codd Normal Form** if it is in **2NF** and there is no transitive functional dependency and attributes depend only on any super key.
**BCNF** is one of the most important normal form, because there is always a lossless decomposition in **BCNF**.

## Normalization

I will check the normal forms of all the tables. First, I write down the Functional Dependencies on the given table. After it, I can define in what normal form is the table.

**AbsUser**(`name`, pw)

F[**AbsUser**] {name->pw}

```bash
1NF     true
2NF     true
BCNF    true
```
---
**Admin**(`iAbsUser`, permissionlvl)

F[**Admin**] = {iAbsUser->permissionlvl}

```bash
1NF     true
2NF     true
BCNF    true
```
---
**Log**(`timestm`,message)

F[**Log**] = {timestm->message}

```bash
1NF     true
2NF     true
BCNF    true
```
---
**User2**(`iAbsUser`, regdate, regtime)

F[**User2**] = {iAbsUser->regdate, iAbsUser->regtime}

```bash
1NF     true
2NF     true
BCNF    true
```
---
**UserWall**(`rUser`)

F[**UserWall**] = {}

```bash
1NF     true
2NF     true
BCNF    true
```
---
**Board**(`name`, permissionlvl, rAdmin)

F[**Board**] = {name->permissionlvl, name->rAdmin}

```bash
1NF     true
2NF     true
BCNF    true
```
---
**Room**(`name`, islocked, date, time, rBoard, rAdmin)

F[**Room**] = {name->islocked, name->date, name->time, name->rBoard, name->rAdmin}

```bash
1NF     true
2NF     true
BCNF    true
```
---
**Post**(`id`, message, date, time, rRoom, rUserWall, rAbsUser)

F[**Post**] = {id->message, id->date, id->time, id->rRoom, id->rUserWall, id->rAbsUser}

```bash
1NF     true
2NF     true
BCNF    true
```
---
**Comment2**(`id`, message, date, time, rPost, rAbsUser)

F[**Comment2**] = {id->message, id->date, id->time, id->rPost, id->rAbsUser}

```bash
1NF     true
2NF     true
BCNF    true
```
---
**ChatRoom**(`id`)

F[**Chatroom**] = {}

```bash
1NF     true
2NF     true
BCNF    true
```
---
**ChatRoom_AbsUser**(`rChatRoom`,`rAbsUser`)

F[**ChatRoom_AbsUser**] = {}

```bash
1NF     true
2NF     true
BCNF    true
```
---
**Message**(`id`, message, date, time, rChatroom, rAbsUser)

F[**Message**] = {id->message, id->date, id->time, id->rChatroom, id->rAbsUser}

```bash
1NF     true
2NF     true
BCNF    true
```
---

### Trigger

I create a logging trigger, so when I **insert**, **update**, or **delete** a row in the given table, the trigger will add a new row into my **Log** table.

```sql
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
```