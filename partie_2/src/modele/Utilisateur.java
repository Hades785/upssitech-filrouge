package modele;

public class Utilisateur {
	private final String login = "admin";
	private final String motDePasse = "admin";
	private boolean admin = false;

	public void definirAdmin() {
		admin = true;
	}

	public boolean connexionAdmin(String login, String motDePasse) {
		if(this.login.equals(login) && this.motDePasse.equals(motDePasse))
			admin = true;
		return admin;
	}

}
