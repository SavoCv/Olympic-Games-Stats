package oi;

import java.awt.BorderLayout;

import javax.swing.*;

public class GraphPanel extends JPanel {
	
	GraphPanel(Graph g)
	{
		super(new BorderLayout());
		super.add(g);
		super.add(new GraphLegend(g), BorderLayout.SOUTH);
		super.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
	}
	
}
