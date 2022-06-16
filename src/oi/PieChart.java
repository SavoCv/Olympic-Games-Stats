package oi;

import java.awt.Color;
import java.awt.Graphics;

import javax.swing.*;

public class PieChart extends Graph {
	
	@Override
	protected void paintComponent(Graphics g) {
		//super.paintComponent(g);
		g.setColor(Color.RED);
		g.fillOval(20, 20, 90, 90);
	}
}
