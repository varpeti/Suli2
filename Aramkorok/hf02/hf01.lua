--[[                        U0=10V
        +--(L=5H->)--(C=100uF->)--o
        |                          / K1: t(0)=zár
        +--(<-R=10Ohm)------------o

--]]

R=10        --Ohm
L=5         --H
C=100e-6    --F
U0=10       --V

--[[
    Hurok törvény:
    U["R"]+U["L"]+U["C"]-V0=0
    
    ebből:

    +R*i  +dif(L,i,1) +(1/C)*int(0,t,i,r) -V0 = 0

    ebből diffegyenlet:

    (1/C[1])*i +diff(R[1],i,1) +diff(L[1],i,2) = 0
--]]

--[[
    Megoldás keresése i=A*e^(s*t) formában.

    i   = A*e^(s*t)
    i'  = s*A*e^(s*t)
    i'' = s^2*A*e^(s*t)

    Behelyettesítés:

    A*e^(s*t)*(1/C + s*R + s^2*L) = 0

    1/C + s*R + s^2*L = 0       | másodfokó

    s[1]= ( -R+sqrt(R^2-4*L*(1/C)) ) / (2*L)
    s[2]= ( -R-sqrt(R^2-4*L*(1/C)) ) / (2*L)

    s[1]= -1+44.710j
    s[2]= -1-44.710j

--]]

--[[
    Komplex megoldás:
    i = A*e^(-w) * sin(w*t+Đ)

    Behelyettesítve:

    i = A*e^(-t) * sin(44.710*t+Đ)
--]]

--[[
    Kezdeti feltételek:

    t=0
    i[L]=0
    V[L]=V0=L*(di/dt)

    t=0 -> i=0 = A*e^0*sin(Đ)  | ha A véges akkor Đ=0
    V0 = L*(di/dt) = L (-1*A*e^0*sin(0) + 44.710*A*e^0*cos(0))

    A = 10/(5*44.710) = 0.447 
--]]

--[[
    Megoldás:
    i = 0.447*e^(-t)*sin(44.7*t)
]]





