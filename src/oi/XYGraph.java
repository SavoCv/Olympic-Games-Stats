package oi;

import java.awt.Color;
import java.awt.Graphics;
import java.util.Vector;

public class XYGraph extends Graph {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = -3424219463081282704L;
	
	static final private int xyBorder = 50;
	
	native public void getData();
	
	static class Pair{
		double year, val;
		boolean summer = true;
		Pair(double y, double v)
		{
			year = y;
			val = v;
		}
	}
	
	Vector <Pair> data = new Vector<>();
	double minVal, maxVal;
	double minYear, maxYear;
	
	synchronized public void add(double yaer, double num)
	{
		data.add(new Pair(yaer, num));
	}
	
	private void rpnt()
	{
		revalidate();
		repaint();
	}
	
	@Override
	public void updateData()
	{
		data.clear();
		Thread t = new Thread(){
			public void run() {
				gettingData = 1;
				rpnt();
				getData();
				for(int i = 0; i < data.size(); ++i)
					if(data.get(i).year < 0)
					{
						data.get(i).summer = false;
						data.get(i).year = -data.get(i).year;
					}
				
				if(data.size() != 0) {
					minVal = maxVal = data.get(0).val;
					minYear = maxYear = data.get(0).year;
				}
				for(int i = 1; i < data.size(); ++i)
				{
					if(data.get(i).val > maxVal)
						maxVal = data.get(i).val;
					if(data.get(i).val < minVal)
						minVal = data.get(i).val;
					if(data.get(i).year > maxYear)
						maxYear = data.get(i).year;
					if(data.get(i).year < minYear)
						minYear = data.get(i).year;
				}
				gettingData = 2;
				//System.out.println("repaint called");
				rpnt();
			};
		};
		t.start();
	}
	
	@Override
	synchronized protected void paintComponent(Graphics g) {
		super.paintComponent(g);
		drawGraph(g);
	}
	
	private int getXYWidth() {
		return getFWidth() - 2 * xyBorder;
	}
	
	private int getXYHeight() {
		return getFHeight() - 2 * xyBorder;
	}
	
	private void translate(Graphics g)
	{
		g.translate(xyBorder + getFX(), xyBorder + getFY() + getXYHeight());
	}
	
	private void reTranslate(Graphics g)
	{
		g.translate(-(xyBorder + getFX()), -(xyBorder + getFY() + getXYHeight()));
	}
	
	private void drawGraph(Graphics g)
	{
		if(data.size() == 0)
		{
			//NO DATA
			g.setColor(Color.RED);
			if(gettingData == 1)
				g.drawString("Please wait", xyBorder, xyBorder);
			else
				g.drawString("No data", xyBorder, xyBorder);;
		}
		else
		{
			final int del = 5;
			g.drawRect(xyBorder + getFX() - del, xyBorder + getFY() - del, getXYWidth() + 2 * del, getXYHeight() + del);
			
			minVal = 0; // maybe is better
			translate(g);
			
			int increment;
			increment = (int)((maxYear - minYear) / (getXYWidth() / g.getFontMetrics().stringWidth("0000"))) + 1;
			
			for(int i = (int)minYear; i <= maxYear; i += increment)
			{
				String year = ((Integer)(int)i).toString();
				int centerX = (int)((i - minYear) / (maxYear - minYear) * getXYWidth());
				int strX = centerX -  g.getFontMetrics().stringWidth(year) / 2;
				g.drawString(year, strX, g.getFont().getSize());
			}
			
			increment = (int)((maxVal - minVal) / (getXYHeight() * 1. / g.getFont().getSize())) + 1;
			for(double i = minVal; i < maxVal; i += increment)
			{
				String str = ((Integer)(int)i).toString(); 
				int centerY = -(int)((i - minVal) / (maxVal - minVal) * getXYHeight());
				int strY = centerY + g.getFont().getSize() / 2;
				g.drawString(str, -g.getFontMetrics().stringWidth(str) - 10, strY);
				//String val = ((Double)i).toString();
			}
			
			
			for(int i = 0; i < data.size(); ++i)
			{
				//System.out.println(data.get(i).year + " " + data.get(i).summer + " " + data.get(i).val);
				int centerX, centerY, R = 3;
				centerX = (int)((data.get(i).year - minYear) / (maxYear - minYear) * getXYWidth());
				centerY = -(int)((data.get(i).val - minVal) / (maxVal - minVal) * getXYHeight());
				if(data.get(i).summer)
					g.setColor(Color.RED);
				else
					g.setColor(Color.BLUE);
				g.fillOval(centerX - R, centerY - R, 2 * R, 2 * R);
			}
			
			
			
			reTranslate(g);
		}
	}
	
}
