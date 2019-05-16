function aramok=gyak4_f44_BUGE0Q(R1,R2,R3,R4,R5,R6,V1,V2,V3)
matrix = [1 -1 -1;(R5+R4+R1) (R3) 0;0 (-R3) (R6+R2)];
vektor = [0;(-V2-V1);(V3+V2)];
aramok=matrix\vektor;
end