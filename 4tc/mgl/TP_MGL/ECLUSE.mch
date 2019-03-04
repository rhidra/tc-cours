MACHINE 

    ECLUSE

SETS

    NIVEAU = {haut,bas};
    PORTE = {ouverte,fermee}

VARIABLES

    sas,		/* niveau de l'eau dans le sas */
    pav,		/* etat de la porte aval */
    pam		/* etat de la porte amont */
    
INVARIANT

    sas: NIVEAU	
    & pav: PORTE	
    & pam: PORTE	

    /* Les portes ne sont pas ouvertes en même temps */
    & (pav = ouverte => pam = fermee)
    & (pam = ouverte => pav = fermee)
    
    /* Le niveau du sas correspond au niveau du fleuve */
    & (pam = ouverte => sas = haut)
    & (pav = ouverte => sas = bas)

INITIALISATION

    sas, pav, pam := haut, fermee, fermee

OPERATIONS

remplir =
	PRE
	    pav = fermee & pam = fermee & pav = fermee
	THEN
	    sas := haut
	END
    ;
    
vider =
	PRE
	    pav = fermee & pam = fermee
	THEN
	    sas := bas
	END
    ;
    
ouvrir_amont =
	PRE
	    pav = fermee & sas = haut
	THEN
	    pam := ouverte
	END
    ;
    
fermer_amont =
	PRE
	    pav = fermee & sas = haut
	THEN
	    pam := fermee
	END
    ;
    
ouvrir_aval =
	PRE
	   pam = fermee & sas = bas
	THEN
	    pav := ouverte
	END
    ;
    
fermer_aval =
	PRE
	    pam = fermee & sas = bas
	THEN
	    pav := fermee
	END
END
