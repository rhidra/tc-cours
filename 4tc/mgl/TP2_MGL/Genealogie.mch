MACHINE
    Genealogie

SETS
    PERSONNES  /* Ensemble des personnes ayant existe ou qui existeront un jour */

CONSTANTS
    H0, F0     /* Ensemble des hommes et des femmes originaux. */
PROPERTIES
    H0<:PERSONNES &
    F0<:PERSONNES &
    H0/\F0={}

VARIABLES
    Hommes, Femmes
    /* Introduire les elements a modeliser par etapes */
    , PereDe, MereDe
    /*, Maries*/

INVARIANT
    Hommes <: PERSONNES &
    Femmes <: PERSONNES &
    Hommes /\ Femmes = {} &
    
    MereDe: (Hommes\/Femmes)-H0-F0 --> Femmes &
    PereDe: (Hommes\/Femmes)-H0-F0 --> Hommes &
    
    H0 <: Hommes & 
    F0 <: Femmes
    
    /*PERSONNES = H0 \/ F0 \/ ran(Fils) \/ ran(Fille) */
    /***** a completer *****/

    /* Memorisation de la relation de paternite et celle de maternite (lien genealogique direct)
       Par ailleurs, toute personne ayant un pere ou une mere en a au plus 1 de chaque */

    /* Un couple marie est necessairement forme d'un homme et d'une femme;
       Chaque homme est marie au plus une fois;
       Chaque femme est mariee au plus une fois;
       Toute personne n'est pas necessairement mariee.
    */

    /* Deux parents d'une meme personne sont maries ensembles. */


INITIALISATION
    Hommes:=H0 || Femmes:=F0 || MereDe := {} || PereDe := {}
    /***** a completer *****/


OPERATIONS
    /* Choisi une nouvelle personne et l'ajoute dans la structure de donnees generale */
    naitre(papa, maman) =
    PRE
        papa: Hommes &
        maman: Femmes
    THEN  
        ANY alien WHERE
            alien:PERSONNES-Femmes-Hommes
        THEN
           MereDe(alien) := maman ||
           PereDe(alien) := papa ||
           CHOICE
               Hommes := Hommes \/ {alien}
           OR
               Femmes := Femmes \/ {alien}
           END
        END
	 END

/*;


    / * Fait se marier 2 personnes * /
    marier(p1, p2) =
    PRE
 	    / ***** a completer ***** /
    THEN
	    / ***** a completer ***** /
	END;


    / * Renvoie si une personne p1 est un descendant direct de p2 * /
    res <-- estParent(p1, p2) =
    PRE
 	    / ***** a completer ***** /
    THEN
 	    / ***** a completer ***** /
    END;



    / * Renvoie si une personne p1 est un descendant direct ou indirect de p2 * /
    res <-- estAncetre(p1, p2) =
    PRE
 	    / ***** a completer ***** /
    THEN
 	    / ***** a completer ***** /
    END
*/
END
