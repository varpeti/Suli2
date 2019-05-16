math.randomseed(3773)

local function randUPch()
    return string.char( math.random(65,90) )
end

local function randLOch()
    return string.char( math.random(97,122) )
end

local function randtext(num)
    local text = ""
    if math.random(0,1)==1 then text = text .. randUPch()
    else text = text .. randLOch(); end
    local i = -3
    while (i<0 or math.random(0,3)~=1 ) do
        if math.random(10)==1 then text = text .. randUPch()
        else text = text .. randLOch() end
        i=i+1
        if i>4 then break end
    end

    if (num==1 and text:len()<8 ) then 
        while (math.random(0,2)~=1) do
            text = text..math.random(0,9)
        end
    end
    return text
end

local function randname()
    return randtext(math.random(1))
end

local function randmsg()
    local ret = randtext(0)
    while (math.random(0,10)~=3) do
        ret = ret .." ".. randtext(0)
        if ret:len()>150 then break end
    end
    return ret
end

local function randdate()
    local Y = ""..math.random(2000,2017)
    local M = ""..math.random(1,12) if M:len()<2 then M="0"..M end
    local D = ""..math.random(1,28) if D:len()<2 then D="0"..D end
    local H = ""..math.random(0,23) if H:len()<2 then H="0"..H end
    local m = ""..math.random(0,59) if m:len()<2 then m="0"..m end
    local S = ""..math.random(0,59) if S:len()<2 then S="0"..S end
    return "TO_DATE('"..D.."/"..M.."/"..Y.." "..H..":"..m..":"..S.."', 'DD/MM/YYYY HH24:MI:SS')"
end

local Boards = {}
local Names = {} local function getrandName() return Names[math.random(1,#Names)] end

--Admin
for i=1,10 do
    local name = randname() table.insert(Names,name)
    local lvl = 7-(i>6 and 7 or i)
    print([[insert into AbsUser values (']]..name..[[',']]..math.random(0,9999999999)..math.random(0,9999999999)..[[');]] )
    print([[insert into Admin values (']]..name..[[',']]..lvl..[[');]] )
    
    --Log
    print([[insert into Log values (]].."0"..[[,']]..name..[[',']]..name..[[ created.');]] )
    while (math.random(0,1)==0) do
        print([[insert into Log values (]]..math.random(999999999)..[[,']]..name..[[',']]..randmsg()..[[');]] )
    end

    --Board
    if lvl>0 then
        local Board = randtext(0) table.insert(Boards,Board)
        print([[insert into Board values (']]..Board..[[',']]..lvl..[[',']]..name..[[');]] )
        
    end
end

--User2
for i=1,81 do
    local name = randname() table.insert(Names,name)
    print([[insert into AbsUser values (']]..name..[[',']]..math.random(9999999999)..math.random(9999999999)..[[');]] )
    print([[insert into User2 values (']]..name..[[',]]..randdate()..[[);]] )
    
    --UserWall
    print([[insert into UserWall values (']]..name..[[');]] )

        --Post
        while (math.random(0,7)~=0) do
            local Post = math.random(9999999999)
            print([[insert into Post values (]]..Post..[[,']]..randmsg()..[[',]]..randdate()..[[,]].."NULL"..[[,']]..name..[[',']]..getrandName()..[[');]] )
        
            --Comment2
            while (math.random(0,5)~=0) do
                print([[insert into Comment2 values (]]..math.random(9999999999)..[[,']]..randmsg()..[[',]]..randdate()..[[,]]..Post..[[,']]..getrandName()..[[');]] )
            end
        end
end

--Room
for i,board in ipairs(Boards) do
    while (math.random(0,10)~=0) do
        local Room = randtext(0)
        print([[insert into Room values (']]..Room..[[',]].."0"..[[,]]..randdate()..[[,']]..board..[[',']]..getrandName()..[[');]] )
        
        --Post
        while (math.random(0,5)~=0) do
            local Post = math.random(9999999999)
            print([[insert into Post values (]]..Post..[[,']]..randmsg()..[[',]]..randdate()..[[,']]..Room..[[',]].."NULL"..[[,']]..getrandName()..[[');]] )
        
            --Comment2
            while (math.random(0,5)~=0) do
                print([[insert into Comment2 values (]]..math.random(9999999999)..[[,']]..randmsg()..[[',]]..randdate()..[[,]]..Post..[[,']]..getrandName()..[[');]] )
            end
        end
    end
end

--ChatRoom
for i=1,31 do
    local ChatRoom = randtext(0)
    print([[insert into ChatRoom values (']]..ChatRoom..[[');]] )

    --ChatRoom_AbsUser
    while (math.random(0,5)~=0) do
        print([[insert into ChatRoom_AbsUser values (']]..ChatRoom..[[',']]..getrandName()..[[');]] )
        while (math.random(0,5)~=0) do
            print([[insert into Message values (]]..math.random(9999999999)..[[,']]..randmsg()..[[',]]..randdate()..[[,']]..ChatRoom..[[',']]..getrandName()..[[');]] )
        end
    end
end

