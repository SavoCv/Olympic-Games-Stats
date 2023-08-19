package oi;

import javax.swing.*;

abstract public class Graph extends JComponent {

	/**
	 * 
	 */
	private static final long serialVersionUID = -977775518176503285L;

	final static protected int borders = 20;
	
	static protected class Filter
	{
		String metrics = "", sport = "", medal = "";
		int year = 0;
		boolean ind = true, team = true;
	};
	
	protected Filter filter = new Filter();
	
	int gettingData = 0;
	abstract protected void updateData();
	
	
	public void setFilter(String metrics, String sport, String year, boolean ind, 
			boolean team, String medal)
	{
		if(gettingData == 1)
			return;
		filter.metrics = metrics;
		filter.sport = sport;
		try {
			filter.year = Integer.parseInt(year);
		}
		catch(Exception e) {
			filter.year = 0;
		}
		filter.ind = ind;
		filter.team = team;
		filter.medal = medal;
		updateData();
		revalidate();
		repaint();
	}
	
	protected int getFHeight()
	{
		return super.getHeight() - 2 * borders;
	}
	
	protected int getFWidth()
	{
		return super.getWidth() - 2 * borders;
	}
	
	protected int getFX()
	{
		return super.getX() + borders;
	}
	
	protected int getFY()
	{
		return super.getY() + borders;
	}
}
