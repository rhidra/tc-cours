public class RayTracing {
    public Vecteur src;
    public Vecteur direction;
    public double indice;
    public Objet[] obj;
    public int currentBounce;
    public double power;

	// Nombre de rebonds maximals qu'un rayon peut effectuer
	public static int MAX_BOUNCES = 11;

    public RayTracing() {}

    public RayTracing(Vecteur src, Vecteur, direction, double indice, Objet[] obj, int currentBounce, double power = 1) {
        this.src = src;
        this.direction = direction;
        this.indice = indice;
        this.obj = obj;
        this.currentBounce = currentBounce;
    }

	/**
	 * Calcule tous les rayons créés par une source au point src, dans une direction dir
	 * et dans un environnement constitués de obj[] Objets qui peuvent interagir avec des rayons.
	 * La méthode utilise Objet.intersection(Rayon) pour calculer un point d'intersection.
	 * Elle calcule ensuite un angle de réflection (s'il existe) et un angle de réfraction,
	 * et fait repartir un rayon dans cette nouvelle direction.
	 * L'algorithme utilisé fait apparaître de la récursivité, en se rappelant lui-même,
	 * tant que le rayon traité rencontre des intersection dans son environnement.
	 *
	 * @param src Point d'origine du rayon.
	 * @param dir Direction d'origine du rayon.
	 * @param obj Ensemble des objets présents dans l'environnement
	 *
	 * @return Tableau des rayons créés par l'algorithme de traçage.
	 */
	public static ArrayList<Rayon> tracer(RayTracing rt) {
		ArrayList<Rayon> rayons = new ArrayList<Rayon>(1);
        rt.currentBounce++;

		// On crée un rayon qui part à l'infini
		Rayon r = rayonInfini(rt.src, rt.direction, rt.indice, rt.power);
		rayons.add(r);

		Objet objIntersectantRayon = null;

		for (Objet o : obj) {
			objIntersectantRayon = this.intersecte(o);
		}
		// A ce moment, r est le plus petit rayon qui n'intersecte rien
		// objIntersectantRayon est l'objet qui est touché par le rayon

		// Si le rayon a rencontré un objet sur sa course
		if (objIntersectantRayon != null && rt.currentBounce <= MAX_BOUNCES) {

			// Si l'objet touché est un miroir
            rayons.addAll(gererMiroir(rt, r, objIntersectantRayon));

			// Si l'objet touché est un objet optique (lentille ou autre)
			rayons.addAll(gererObjOptique(rt, r, objIntersectantRayon));

			// Si l'objet touché est un écran, il ne se passe rien
			// Si l'objet touché est une source, il ne se passe rien
		}

		return rayons;
	}

    public static ArrayList<Rayon> gererMiroir(RayTracing rt, Rayon r, Objet o) {
        if (o instanceof Miroir) {
            Vecteur dirReflect = rt.direction.substract(o.direction.multiply(2*rt.direction.scalaire(o.direction)));

            // On calcule le nouveau rayon réfléchi et ses conséquences
            // puis on l'ajoute aux rayons déjà calculés
            rt.src = r.end;
            rt.direction = dirReflect;
            return RayTracing.tracer(rt);
        }
        return null;
    }

    public static ArrayList<Rayon> gererObjOptique(RayTracing rt, Rayon r, Objet o) {
        if (objIntersectantRayon instanceof ObjetOptique) {
            ArrayList<Rayon> rayons = new ArrayList<Rayon>(0);
            ObjetOptique o = (ObjetOptique)objIntersectantRayon;

            Vecteur n = o.getNormale(r.end).vecteurNormalise();
            n = (objIntersectantRayon.direction.scalaire(dir) > 0) ? n.opposite() : n;
            // Réflexion
            rayons.addAll(gererReflexion(rt, r, o));

            // Réfraction
            rayons.addAll(gererRefraction(rt, r, o));

            return rayons;
        }
        return null;
    }

    public static ArrayList<Rayon> gererReflexion(RayTracing rt, Rayon r, ObjetOptique o) {
        Vecteur n = o.getNormale(r.end).vecteurNormalise();
        n = (objIntersectantRayon.direction.scalaire(dir) > 0) ? n.opposite() : n;

        double angleIncident = rt.dir.angle(n);
        Vecteur dirReflect = rt.dir.opposite().rotation(2*angleIncident);

        RayTracing ray = new RayTracing(r.end, dirReflect, r.indiceMilieu, rt.obj, rt.currentBounce+1, r.puissance/4);
        return tracer(ray);
    }

    public static ArrayList<Rayon> gererRefraction(RayTracing rt, Rayon r, ObjetOptique o) {
        Vecteur n = o.getNormale(r.end).vecteurNormalise();
        n = (objIntersectantRayon.direction.scalaire(dir) > 0) ? n.opposite() : n;

        // Indice de réfraction
        double n1 = r.indiceMilieu;
        double n2 = (r.indiceMilieu == o.indice) ? Simulation.indiceEnvironnement : o.indice;

        double c = - n.scalaire(dir);
        double sq = 1 - (n1/n2)*(n1/n2)*(1-c*c);
        if (sq >= 0) {
            Vecteur dirRefract = rt.dir.multiply(n1/n2).add(n.multiply((n1/n2) - Math.sqrt(sq))).vecteurNormalise();

            rt.src = r.end.add(dirRefract.multiply(0.001));
            rt.direction = dirRefract;
            rt.indice = n2;
            return tracer(rt);
        }
    }
}
