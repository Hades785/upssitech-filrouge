package vue_console;

import java.util.Scanner;

import controlleur.CIdentification;

public class BIdentification {
	private static Scanner scanner = new Scanner(System.in);
	private CIdentification control;

	public BIdentification(CIdentification c)
	{
		control = c;
	}
	
	public boolean isIdentified()
	{
		return control.isIdentified();
	}
	
	public void identification()
	{
		String login;
		String mdp;
		
		System.out.println("Veuillez entrer le login utilisateur");
		login = scanner.nextLine();
		System.out.println("Veuillez entrer le mot de passe administrateur :");
		mdp = scanner.nextLine();
		
		if(control.connexionAdmin(login, mdp))
		{
			System.out.println("Connecte en temps qu'admin.");
		}
		else
		{
			System.out.println("Mot de passe invalide.");
		}
	}
}
