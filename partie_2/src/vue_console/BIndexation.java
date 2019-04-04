package vue_console;

import controlleur.CIndexation;

public class BIndexation {
	private CIndexation control;

	public BIndexation(CIndexation c)
	{
		control = c;
	}
	
	public void indexation()
	{
		control.indexation();
	}
}
