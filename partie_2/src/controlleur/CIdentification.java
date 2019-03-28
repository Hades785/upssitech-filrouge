package controlleur;

import modele.Utilisateur;

// SINGLETON
public class CIdentification {
	private Utilisateur user = new Utilisateur();
	
	public boolean isIdentified()
	{
		return user.isIdentified();
	}
	
	// retourne le resultat pour afficher un message dans la vue
	// permettant de savoir si l identification a ete effectuee
	public boolean connexionAdmin(String login, String motDePasse) {
		return user.connexionAdmin(login, motDePasse);
	}
}
