import java.util.*;

public class GroupeEtudiant {
    public ArrayList<Etudiant> grp;

    public GroupeEtudiant() {
        grp = new ArrayList<Etudiant>();
    }

    public void add(Etudiant e) {
        grp.add(e);
    }

    public boolean recherche(String s) {
        for (Etudiant e : grp) {
            if (e.aCeNom(s)) {
                return true;
            }
        }

        return false;
    }
}
