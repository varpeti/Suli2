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