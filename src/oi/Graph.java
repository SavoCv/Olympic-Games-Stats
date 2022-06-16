package oi;

import javax.swing.*;

abstract public class Graph extends JComponent {
	
	final static protected int borders = 20;
	
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
