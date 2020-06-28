local kamera = {}
kamera.kx = 0
kamera.ky = 0
kamera.sx = 1
kamera.sy = 1
kamera.r = 0


-- set,unset
function kamera:set()
    love.graphics.push()
    love.graphics.scale(1/self.sx,1/self.sy)
    love.graphics.translate(love.graphics.getWidth()/(2/self.sx), love.graphics.getHeight()/(2/self.sy))
    love.graphics.rotate(-self.r)
    love.graphics.translate(-self.kx, -self.ky)
end

function kamera:unset()
    love.graphics.pop()
end
 
-- Position

function kamera:rPos(x,y) --relat
    self.kx = self.kx+x
    self.ky = self.ky+y 
end

function kamera:aPos(x, y) --abs
    self.kx = x 
    self.ky = y 
end

function kamera:gPos() --get
    return self.x, self.y
end

-- Zoom

function kamera:rScale(sx,sy) --relat
	self.sx = self.sx+self.sx*sx
	self.sy = self.sy+self.sy*(sy or sx)
end

function kamera:aScale(sx,sy) --abs -- original: 1,1
    self.sx = sx
    self.sy = (sy or sx)
end

function kamera:gScale() --get
    return self.sx,self.sy
end

-- Rotation 

function kamera:rRot(r) --relat
	self.r = self.r+self.r*r
end

function kamera:aRot(r) --abs -- original: 0
    self.r = r
end

function kamera:gRot() --get
    return self.r
end

-- coordsystems

function kamera:camCoords(x,y)
  local c,s = math.cos(-self.r), math.sin(-self.r)
  local x,y = x - self.kx, y - self.ky
  x,y = c*x - s*y, s*x + c*y
  return x*self.sx, y*self.sy
end

function kamera:worldCoords(x,y)
  local c,s = math.cos(self.r), math.sin(self.r)
  local x,y = x*self.sx, y*self.sy
  x,y = c*x - s*y, s*x + c*y
  return x+self.kx, y+self.ky
end

return kamera