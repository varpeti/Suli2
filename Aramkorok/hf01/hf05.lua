function reciposszeg(A,B)
    return 1/(1/A+1/B)
end
R={} U={} I={}

-- A -> mindenhol az áram iránya
--[[
    
    +---(R1=12)---+---------(R2=3)---+
    |             |                  |
    |             +(R3=6)+           |
    |                    |           |
    +--(<-Ug=42)---------+-(Uf=35->)-+

--]]

R[1]=12
R[2]=3
R[3]=6
Uf=35
Ug=42

--Szuperpozíció

function rovidzar1()
    local U, I = {},{}

    --[[
        
        +---(R1=12)---+---------(R2=3)---+
        |             |                  |
        |             +(R3=6)+           |
        |                    |           |
        +--(<-Ug=42)---------+-----------+
    
    --]]

    R["32"]=reciposszeg(R[3],R[2])
    R["321"]=R["32"]+R[1]

    U["321"]=Ug
    I["321"]=U["321"]/R["321"]

        I["32"]=I["321"]
        U["32"]=I["32"]*R["32"]

            U[3]=U["32"]
            I[3]=U[3]/R[3]

            U[2]=U["32"]
            I[2]=U[2]/R[2]

        I[1]=I["321"]
        U[1]=I[1]*R[1]

    for i=1,3 do
        print("R["..i.."]="..R[i],"I["..i.."]="..I[i],"U["..i.."]="..U[i])
    end
    print("")

    return U,I
end

function rovidzar2()
    local U, I = {},{}

    --[[
        
        +---(R1=12)---+---------(R2=3)---+
        |             |                  |
        |             +(R3=6)+           |
        |                    |           |
        +--------------------+-(Uf=35->)-+
    
    --]]

    R["31"]=reciposszeg(R[3],R[1])
    R["312"]=R["31"]+R[2]

    U["312"]=Uf
    I["312"]=U["312"]/R["312"]

        I["31"]=I["312"]
        U["31"]=I["31"]*R["31"]

            U[3]=U["31"]
            I[3]=U[3]/R[3]

            U[1]=U["31"]
            I[1]=U[1]/R[1]

        I[2]=I["312"]
        U[2]=I[2]*R[2]

    for i=1,3 do
        print("R["..i.."]="..R[i],"I["..i.."]="..I[i],"U["..i.."]="..U[i])
    end
    print("")

    return U,I
end

r1U,r1I  = rovidzar1()
r2U,r2I  = rovidzar2()


U[1], I[1] = (r1U[1] or 0)-(r2U[1] or 0),  (r1I[1] or 0)-(r2I[1] or 0)
U[2], I[2] = (r2U[2] or 0)-(r1U[2] or 0),  (r2I[2] or 0)-(r1I[2] or 0)
U[3], I[3] = (r1U[3] or 0)+(r2U[3] or 0),  (r1I[3] or 0)+(r2I[3] or 0)


for i=1,3 do
    print("R["..i.."]="..R[i],"I["..i.."]="..I[i],"U["..i.."]="..U[i])
end
print("")
