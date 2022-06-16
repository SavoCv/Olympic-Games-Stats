package oi;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.font.FontRenderContext;
import java.util.Vector;
import javax.swing.*;

public class PieChart extends Graph {
	
	static final private int pieBorder = 50;
	
	static class Pair{
		String country;
		int br;
		Pair(String d, int b){
			country = d;
			br = b;
		}
	}
	
	Vector <Pair> data = new Vector<>();
	Color[] colors = new Color[100];
	
	static private boolean isSimilarColor(int a, int b)
	{
		int d = 0;
		for(int i = 0; i < 3; ++i) {
			int tmp;
			tmp = (a & 255) - (b & 255);
			a <<= 8;
			b <<= 8;
			d += tmp * tmp;
		}
		return d < 5000;
	}
	
	//Making colors
	{
		int lastTmp = 0;
		for(int i = 0; i < colors.length; ++i) {
			int tmp;
			do
			{
				tmp = (int) (Math.random() * 256 * 256 * 256);
			} while(isSimilarColor(lastTmp, tmp) || isSimilarColor(tmp, 256 * 256 * 256 - 1));
			lastTmp = tmp;
			colors[i] = new Color(tmp);
			
		}
	}
	
	{
		data.add(new Pair("USA", 50));
		data.add(new Pair("Russia", 40));
		data.add(new Pair("Great Britain", 30));
		data.add(new Pair("China", 20));
		data.add(new Pair("Canada", 15));
		data.add(new Pair("Serbia", 10));
		data.add(new Pair("Germany", 9));
		data.add(new Pair("France", 8));
		data.add(new Pair("Spain", 7));
		data.add(new Pair("Brazil", 6));
		data.add(new Pair("Portugal", 5));
	}
	
	native public void getData();
	
	//getting data
	{
		getData();
	}
	
	private int get2R()
	{
		return Math.min(getFWidth() - 2 * pieBorder, getFHeight() - 2 * pieBorder);
	}
	
	private int getPX()
	{
		return getFX() + getFWidth() / 2 - get2R() / 2;
	}
	
	private int getPY()
	{
		return getFY() + getFHeight() / 2 - get2R() / 2;
	}
	
	@Override
	protected void paintComponent(Graphics g) {
		g.setColor(Color.RED);
		g.drawRect(getFX(), getFY(), getFWidth(), getFHeight());
		g.setColor(Color.GRAY);
		drawChart(g);
	}
	
	private void drawChart(Graphics g)
	{
		if(data.size() == 0)
		{
			//NO DATA
		}
		else
		{
			int sum = 0;
			for(int i = 0; i < data.size(); ++i)
			{
				sum += data.get(i).br;
			}
			int lastAngle = 0;
			int angle;
			double leftAngle = 0, tmpAng;
			int strX, strY, rx, ry, R;
			for(int i = 0; i < data.size(); ++i)
			{
				angle = (int)(360 * data.get(i).br * 1. / sum + leftAngle);
				leftAngle = 360 * data.get(i).br * 1. / sum + leftAngle - angle;
				g.setColor(colors[i]);
				g.fillArc(getPX(), getPY(), get2R(), get2R(), lastAngle, angle);
				lastAngle += angle;
				
				R = get2R() / 2;
				rx = getPX() + R;
				ry = getPY() + R;
				R += 10;
				tmpAng = - 2 * (lastAngle - angle * 1. / 2) / 360. * Math.PI;
				strX = (int)(rx + Math.cos(tmpAng) * R);
				strY = (int)(ry + Math.sin(tmpAng) * R);
				strY += g.getFont().getSize() / 2;
				if(lastAngle - angle / 2 > 90 && lastAngle - angle / 2 < 270) 
					strX -= g.getFontMetrics().stringWidth(data.get(i).country);
				g.drawString(data.get(i).country, strX, strY);
			}
		}
	}
}
