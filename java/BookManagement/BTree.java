import java.util.Iterator;
import java.util.ArrayList;
import java.io.*;

public class BTree<T extends Comparable>
	implements Serializable {

	public static final String DIR
		= BTree.class.getProtectionDomain().getCodeSource()
		.getLocation().getFile() + File.separator;

	private int rootId;
	
	public BTree() {
		BTreeNode<T> root = new BTreeNode<T>(true);
		rootId = root.getId();
		root.writeToDisk();
		writeToDisk();
	}

	public void add(T target) {
		BTreeNode<T> root = BTreeNode.readFromDisk(rootId);
		if (root.isFull()) {
			BTreeNode<T> parent = new BTreeNode(root);
			rootId = parent.getId();
			writeToDisk();
			parent.add(target);
		} else {
			root.add(target);
		}
	}

	public boolean contains(T target) {
		BTreeNode node = BTreeNode.readFromDisk(rootId);
		while (node != null) {
			double d = node.indexOf(target);
			int i = (int)d;
			if (i == d) {
				return true;
			} else {
				node = node.getChild(i);
			}
		}
		return false;
	}

	public void remove(T target) {
		BTreeNode root = BTreeNode.readFromDisk(rootId);
		root.remove(target);
		if ((root.size() == 1) && (!(root.isLeaf()))) {
			BTreeNode child = root.getChild(0);
			root.deleteFromDisk();
			rootId = child.getId();
			writeToDisk();
		}
	}

	public void update(T target) {
		if (contains(target)) {
			remove(target);
		}
		add(target);
	}

	public T get(T target) {
		BTreeNode node = BTreeNode.readFromDisk(rootId);
		while (node != null) {
			double d = node.indexOf(target);
			int i = (int)d;
			if (i == d) {
				return (T)node.data.get(i);
			} else {
				node = node.getChild(i);
			}
		}
		return null;
	}
	
	public static BTree readFromDisk() {
		try {
			ObjectInputStream in =
				new ObjectInputStream(new FileInputStream(DIR + "btree"));
			return (BTree)(in.readObject());
		} catch (Exception e) {
			// e.printStackTrace();
			// System.exit(1);
			return null;
		}
	}
	
	public void writeToDisk() {
		try {
			ObjectOutputStream out =
				new ObjectOutputStream(new FileOutputStream(DIR + "btree"));
			out.writeObject(this);
			out.close();
		} catch (Exception e) {
			e.printStackTrace();
			System.exit(1);
		}
	}

	public ArrayList<T> toArrayList() {
		BTreeNode<T> root = BTreeNode.readFromDisk(rootId);
		return root.toArrayList();
	}
	
	public int getRootId() {return rootId;}
}
