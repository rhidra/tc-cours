MACHINE 
   ExempleTD

VARIABLES
   xx, yy

INVARIANT
   xx: NATURAL & yy : NATURAL & xx > yy

INITIALISATION
   xx:=1 || yy:=0

OPERATIONS

incr = 
   CHOICE
      xx:=xx+1
   OR
       IF yy+1 >= xx THEN
           xx := xx+1
       ELSE
           yy := yy+1
       END
   END ;

reset =
   ANY nx, ny WHERE 
       nx : NATURAL & ny : NATURAL & nx>ny
   THEN
       xx:=nx || 
       yy:=ny
   END
   
END
