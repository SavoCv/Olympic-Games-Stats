package oi;

import java.awt.Color;
import java.awt.Graphics;
import java.util.Vector;

public class PieChart extends Graph {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = -4898433648774474452L;
	static final private int pieBorder = 50;
	
	static class Pair{
		String country;
		int num;
		Pair(String d, int b){
			country = d;
			num = b;
		}
	}
	
	Vector <Pair> data = new Vector<>();
	Color[] colors = new Color[10000];
	
	{
		updateData();
	}
	
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
	
	native public void getData();
	
	@Override
	public void updateData()
	{
		//System.out.println(getGraphics());
		data.clear();
		Thread t = new Thread(){
			public void run() {
				gettingData = 1;
				repaint();
				getData();
				data.sort((p1, p2)->{return - p1.num + p2.num;});
				Pair other = new Pair("Other", 0);
				int sum = 0;
				for(int i = 0; i < data.size(); ++i)
					sum += data.get(i).num;
				
				for(int i = data.size() - 1; i >= 0; --i)
				{
					if(data.get(i).num * 1. / sum < 0.02) {
						other.num += data.get(i).num;
						data.remove(i);
					}
				}
				if(other.num != 0)
					data.add(other);
				gettingData = 2;
				repaint();
			};
		};
		t.start();
	}
	
	synchronized public void add(String s, int num)
	{
		data.add(new Pair(s, num));
	}
	
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
	synchronized protected void paintComponent(Graphics g) {
		super.paintComponent(g);
		drawChart(g);
	}
	
	private void drawChart(Graphics g)
	{
		if(gettingData == 1) {
			g.setColor(Color.RED);
			g.drawString("Please wait", pieBorder, pieBorder);
		} else if(data.size() == 0)
		{
			//NO DATA
			g.setColor(Color.RED);
			g.drawString("No data", pieBorder, pieBorder);;
		}
		else
		{
			int sum = 0;
			for(int i = 0; i < data.size(); ++i)
			{
				sum += data.get(i).num;
			}
			int lastAngle = 0;
			int angle;
			double leftAngle = 0, tmpAng;
			int strX, strY, rx, ry, R;
			for(int i = 0; i < data.size(); ++i)
			{
				angle = (int)(360 * data.get(i).num * 1. / sum + leftAngle);
				if(i == data.size() - 1)
					angle = 360 - lastAngle;
				leftAngle = 360 * data.get(i).num * 1. / sum + leftAngle - angle;
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
