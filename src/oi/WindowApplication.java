package oi;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

import javax.swing.*;

public class WindowApplication extends JFrame {
	
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	
	private class QuitDialog extends JDialog
	{
		/**
		 * 
		 */
		private static final long serialVersionUID = 2L;
		
		private void populateWindow() {
			JButton yes, no;
			
			JLabel label;
			
			JPanel p1, p2;
			
			label = new JLabel("Do you really want to quit?");
			label.setAlignmentX(CENTER_ALIGNMENT);
			
			yes = new JButton("yes");
			no = new JButton("no");
			
			yes.addActionListener((ae) -> {dispose(); 
							WindowApplication.this.dispose();});
			yes.addKeyListener(new KeyAdapter() {
				@Override
				public void keyPressed(KeyEvent e) {
					if(e.getKeyCode() == 10) {
						dispose();
						WindowApplication.this.dispose();
					}
				}
			});
			
			no.addActionListener((ae) -> {dispose();});
			
			no.addKeyListener(new KeyAdapter() {
				@Override
				public void keyPressed(KeyEvent e) {
					if(e.getKeyCode() == 10) {
						dispose();
					}
				}
			});
			
			p1 = new JPanel();
			p2 = new JPanel();
			
			p1.add(label);
			p2.add(yes);
			p2.add(no);
			add(p1, BorderLayout.CENTER);
			add(p2, BorderLayout.SOUTH);
		}

		QuitDialog()
		{
			super(WindowApplication.this);
			super.setDefaultCloseOperation(JDialog.DO_NOTHING_ON_CLOSE);
			setTitle("Quit");
			setResizable(false);
			final int h = 100, w = 200;
			WindowApplication wa = WindowApplication.this;
			
			setBounds(wa.getX() + wa.getWidth() / 2 - w / 2, 
					wa.getY() + wa.getHeight() / 2 - h / 2, 
					w, h);
			
			addWindowListener(new WindowAdapter() {
				@Override
				public void windowClosing(WindowEvent e) {
					dispose();
					WindowApplication.this.dispose();
				}
			});
			
			populateWindow();
			
			setVisible(true);
		}
	}
	
	private void filter(String metrics, String sport, String year, boolean ind, 
			boolean team, String medal){
		System.out.println(metrics + " " + sport + " " + year + " " + ind + " " + 
			team + " " +  medal);
		//TODO
	}
	
	private void populateWindow()
	{
		add(new PieChart());
		
		JPanel choosingPanel = new JPanel(new GridLayout(6, 1));
		choosingPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
		
		JPanel p1, p2, p3, p4, p5, p6;
		
		JComboBox <String> metrics, medal;
		
		JTextField sport, year;
		
		JCheckBox individual, team;
		
		JButton filter;
		
		String[] metr = {"Num of athletes", "Num of events", "Avg height", "Avg weight"};
		metrics = new JComboBox<>(metr);
		p1 = new JPanel();
		p1.add(metrics);
		
		sport = new JTextField(7);
		p2 = new JPanel();
		p2.add(new JLabel("Sport: "));
		p2.add(sport);
		
		year = new JTextField(4);
		p3 = new JPanel();
		p3.add(new JLabel("Year: "));
		p3.add(year);
		
		individual = new JCheckBox("Individual");
		team = new JCheckBox("Team");
		p4 = new JPanel();
		p4.add(individual);
		p4.add(team);
		
		String[] medals = {"", "Gold", "Silver", "Bronze", "None"};
		medal = new JComboBox<>(medals);
		p5 = new JPanel();
		p5.add(new JLabel("Medal: "));
		p5.add(medal);
		
		filter = new JButton("Filter");
		filter.addActionListener((ae)->{
			filter((String) metrics.getSelectedItem(), sport.getText(), year.getText(), 
					individual.isSelected(), team.isSelected(), (String) medal.getSelectedItem());
		});
		p6 = new JPanel();
		p6.add(filter);
		
		choosingPanel.add(p1);
		choosingPanel.add(p2);
		choosingPanel.add(p3);
		choosingPanel.add(p4);
		choosingPanel.add(p5);
		choosingPanel.add(p6);
		add(choosingPanel, BorderLayout.EAST);
	}
	
	WindowApplication()
	{	
		super.setBounds(200, 100, 800, 500);
		super.setMinimumSize(new Dimension(600, 400));
		super.setDefaultCloseOperation(JDialog.DO_NOTHING_ON_CLOSE);
		super.addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				new QuitDialog();
			}
		});
		
		populateWindow();
		
		setVisible(true);
	}
	
	public static void main(String[] args) {
		new WindowApplication();
	}
}
