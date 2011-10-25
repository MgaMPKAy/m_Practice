import javax.swing.*;
import java.awt.*;
import java.util.*;
import java.awt.event.*;
import java.awt.Dialog.*;

class JField {

	JField (int row, int col, int numMines) {
		// Set up main frame
		JFrame frame = new JFrame("Mines");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		// Set up layout
		Container pane = frame.getContentPane();
		GridLayout layout = new GridLayout(row, col);
		pane.setLayout(layout);

		// A genneric actionListener
		Digger digger = new Digger();

		// Set up cells
		JCell cells[][]  = new JCell[row + 2][col + 2];
		for (int i = 1; i <= row; ++i) {
			for (int j = 1; j <= col; ++j) {
				
				Random r = new Random();
				boolean isMine = false;
				if (numMines > 0) {
					isMine = r.nextBoolean();
					if (isMine) numMines--;
				}
				
				cells[i][j] = new JCell(i, j, isMine ,cells);
				cells[i][j].setText("  ");
				cells[i][j].addActionListener(digger);
				
				pane.add(cells[i][j]);
				frame.pack();
			}
		}
		for (int i = 1; i <= row; ++i) {
			for (int j = 1; j <= col; ++j) {
				cells[i][j].addNeihbor();
			}
		}
		
		frame.pack();
		frame.setVisible(true);
	}

}

class JCell extends JButton {
	int row, col, numMine;
	JCell cells[][];
	ArrayList neighbor;
	State state;
	static int around[][];
	boolean isMine;
	
	JCell (int row, int col, boolean isMine, JCell cells[][]) {
		this.row = row;
		this.col = col;
		this.cells = cells;
		this.isMine = isMine;
		this.numMine = 0;
		this.neighbor = new ArrayList(8);
		this.state = State.Unclicked;
		this.setText("");
	}

	void addNeihbor() {
		for (int i = -1; i <= 1; ++i) {
			for (int j = -1; j <= 1; ++j) {
				JCell nc = cells[row + i][col + j];
				if (i == 0 && j == 0) {
					// Do nothing
				} else if (nc != null) {
					neighbor.add(nc);
					if (nc.isMine) numMine++;
				}
			}
		}
	}

	public String toString() {
		return "cell " + row + " " + col;
	}

	public void bang() {
		setText("x");
	}
	
	public void showNum() {
		setText("" + numMine);
		state = State.Clicked;
		
		if (numMine == 0) {
			setText("");
			setEnabled(false);
			Iterator iter = neighbor.iterator();
			while (iter.hasNext()) {
				JCell nc = (JCell)iter.next();
				if (nc.state != State.Clicked)
					nc.showNum();
			}
		}
	}
	
}

class Digger implements ActionListener {

	public void actionPerformed(ActionEvent e) {
		JCell cell = (JCell) e.getSource();
		
		if (cell.isMine) {
			cell.bang();
		} else {
			cell.showNum();
		}
	}
	
}

enum State {
	Unclicked, Clicked, Flagged;
}

class Game {

	public static void main(String[] args) {
		new JField(10, 10, 30);
	}
	
}