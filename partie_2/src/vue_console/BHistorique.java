package vue_console;

public class BHistorique {
	
	private CHistorique control;
	
	public BHistorique(CHistorique c)
	{
		control = c;
	}
	
	public void AffichageHistorique()
	{
		control.toString();
	}
	
}
