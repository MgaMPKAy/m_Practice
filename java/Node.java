import java.util.Iterator;
import java.util.Scanner;

class NodeTest {
	public static void main(String[] args) {
		Node head = Node.newHeadNode();

		String prompt1 = "Enter some numbers," +
			"stop by enter non-number or EOF(Ctrl-D in Linux)";

		System.out.println(prompt1);
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextFloat()) {
			head.insert(sc.nextFloat());
		}

		System.out.println("Sorted numbers:");
		for (Node iter : head) {
			System.out.print(iter + " ");
		}
		System.out.print("\n");

	}
}

public class Node implements Iterator<Node>, Iterable<Node> {
	public float num;
	private Node next, iter;

	/* Constructor for head node */
	private Node() {
		this.num = Integer.MIN_VALUE;
		this.next = null;
		this.iter = this;    //make it iterable
	}

	/** Create a normal node **/
	public Node(float num) {
		this();
		this.num = num;
	}

	/** Get a new head node **/
	public static Node newHeadNode() {
		return new Node();
	}

	/** Return a string that represents the Node **/
	public String toString() {
		return this.num + "";
	}

	/** Insert a new Node
	*   @param newNode A Node instance
	**/
	public void insert(Node newNode) {
		if (this.next == null) {
			this.next = newNode;
		} else if (this.next.num > newNode.num) {
			newNode.next = this.next;
			this.next = newNode;
		} else {
			this.next.insert(newNode);
		}
	}

	/** Insert a new Node
	*   @param num A float
	**/
	public void insert(float num) {
		Node newNode = new Node(num);
		this.insert(newNode);
	}


	/* Implement interface Iterator<Node> */
	/** Returns true if the iteration has more Nodes
	*   @return true if the iteration has more Nodes
	**/
	public boolean hasNext() {
		boolean has =  iter.next != null;
		if (has) {
			iter = iter.next;
		} else {
			iter = this;
		}
		return has;
	}

	/** Returns the next Node
	*   @return Next Node
	**/
	public Node next () {
		return iter;
	}

	/** Not implement yet **/
	public void remove() {}

	/** Reset the iterator.
	*   Useful when you don't loop through all nodes.
	**/
	public void reset() { this.iter = this; }


	/* Implement interface Iterable<Node>, enable foreach loop*/
	/** @return a Iterator **/
	public Iterator<Node> iterator() {return this;}
}