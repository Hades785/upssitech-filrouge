package modele;

public class Utilisateur {
	private final String login = "admin";
	private final String motDePasse = "admin";
	private boolean admin = false;

	// si une fonction n'a pas pour but d etre appelee dans une autre classe,
	// autant la definir en private
	private void definirAdmin() {
		admin = true;
	}
	
	public boolean isIdentified()
	{
		return admin;
	}

	public boolean connexionAdmin(String login, String motDePasse) {
		// si les variables locales n avaient pas le meme nom que les attributs,
		// le mot-cle this n aurait pas ete necessaire
		if(this.login.equals(login) && this.motDePasse.equals(motDePasse))
			this.definirAdmin(); // le mot-cle this n est pas necessaire
		return admin;
	}

}
