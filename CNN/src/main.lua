
-- Egy átalakító a gyors számoláshoz
function d2b(str)
    local ret = ""
    local num = "1"
    for c in str:gmatch"." do
        for i=1,tonumber(c) do
            ret = ret..num
        end 
        if num=="1" then num="0" else num="1" end
    end
    return ret
end

local ether = "10011011111000" --122153



-- lehetséges inputok

local one    = "1"
local random = "1110000100110001010010011011111111111011001110011001101111111101011001010110011100110011010101"
local ethers = "" for i=1,4 do ethers=ethers..ether end
local A1     = ethers..d2b("1221")..ethers 
local A2     = ethers..d2b("3153")..ethers
local A3     = ethers..d2b("3133")..ethers
local A4     = ethers..d2b("221")..ethers 
local B1     = ethers..ethers..d2b("53")..ether
local Bv1    = ethers..ethers..d2b("13223173")..ether
local C1     = ethers..d2b("1323")..ethers
local C2     = ethers..d2b("152153")..ethers
local C3     = ethers..d2b("83")..ethers
local D1     = ethers..d2b("122131132153")..ethers
local D2     = ethers..d2b("622153")..ethers
local Ev1    = ethers..ethers..d2b("13222353")..ether
local E1     = ethers..ethers..d2b("172153")..ether
local E2     = ethers..ethers..d2b("1721322153")..ether
local F1     = ethers..ethers..d2b("9")..ethers --Itt látható pluszba még egy A+B ütközés amik kioltják egymást



-- A kezdeti érték
local input      = F1
-- Az iterációk száma
local iterations = 100


-- Nyilakkal vagy WASD-vel lehet mozgatni a kamerát
-- Egér görgővel lehet közelíteni vagy eltávolodni
-- Szóköz vagy az Enter nyomvatartásával lehet új sorokat generálni

-- 110 szabály
local rule = 
{
    ["000"] = "0",
    ["001"] = "1",
    ["010"] = "1",
    ["011"] = "1",
    ["100"] = "0",
    ["101"] = "1",
    ["110"] = "1",
    ["111"] = "0",
}

-- Eltárolt sorok
local lines = {}

-- Szabály alkalmazásával az új sor kiszámolása
function getNextLine(str)
    
    ret = ""

    -- 2 nullás az elejére
    local p1 = "0" 
    local p2 = "0"
    local p3 = "0"

    -- 2 nullás a végére
    str = str.."00" 

    -- A szabály alapján kiszámítjuk a gyermek értékét
    for c in str:gmatch"." do
        p1 = p2
        p2 = p3
        p3 = c
        ret = ret..rule[p1..p2..p3]
    end

    -- Kitöröljük a felesleges 0-okat a végéről | EZT CSAK A 110-es szabály miatt tehetjük meg!
    ret = ret:sub(1,-2)

    return ret
end

-- Megjelenítés, felhasználói interakciók

kamera = require('kamera')

local speed = 500
local size = 10
local gap = 1


function drawLines()
    for y,line in ipairs(lines) do
        local x = -y
        for c in line:gmatch"." do
            if c == "0" then 
                love.graphics.setColor(0, 0, 0, 1)
            else
                love.graphics.setColor(1, 1, 1, 1)
            end
            love.graphics.rectangle("fill", x*size, y*size, size-gap, size-gap )
            x = x + 1
        end
    end
end

function love.load()
    local line = input
    table.insert(lines,line)
    for i=1,iterations do
        line = getNextLine(line)
        table.insert(lines,line)
    end

    love.window.setTitle("110")
end


local kx,ky = -love.graphics.getWidth()/2+#input*size,love.graphics.getHeight()/2
function love.update(dt)
    if love.keyboard.isDown("right") or love.keyboard.isDown("d") then
        kx = kx + (speed * dt)
    end
    if love.keyboard.isDown("left")  or love.keyboard.isDown("a") then
        kx = kx - (speed * dt)
    end
    if love.keyboard.isDown("down")  or love.keyboard.isDown("s") then
        ky = ky + (speed * dt)
    end
    if love.keyboard.isDown("up")    or love.keyboard.isDown("w") then
        ky = ky - (speed * dt)
    end
    if love.keyboard.isDown("space") or love.keyboard.isDown("return") then
        table.insert(lines,getNextLine(lines[#lines]))
    end

    if love.keyboard.isDown("escape") then
        love.event.quit()
    end
end

function love.wheelmoved(x,y)
    if y>0 then kamera:rScale(-0.0125) speed=speed*0.999 end
    if y<0 then kamera:rScale(0.0125)  speed=speed*1.001 end

    if speed > 505 then gap = 0 else gap = 1 end
end

function love.keypressed( key, scancode, isrepeat )
    if key == "space" then
        
    end
end

function love.draw()
    kamera:aPos(kx,ky)
    kamera:set()
        drawLines()
    kamera:unset()
end