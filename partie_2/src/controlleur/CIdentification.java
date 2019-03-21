package controlleur;


// SINGLETON
public class CIdentification {
	private boolean identified = false;
	// TODO stocke ici de maniere temporaire
	private String mdp = "admin"; 
	
	private CIdentification() {}
	
	public static class CIdentificationHolder{
		private static final CIdentification instance = new CIdentification();
	}
	
	public static CIdentification getInstance()
	{
		return CIdentificationHolder.instance;
	}

	public boolean isIdentified()
	{
		return identified;
	}
	
	// retourne le resultat pour afficher un message dans la vue
	// permettant de savoir si l identification a ete effectuee
	public boolean identification(String motDePasse)
	{
		if(mdp.equals(motDePasse))
		{
			identified = true;
		}
		
		return identified;
	}
}
