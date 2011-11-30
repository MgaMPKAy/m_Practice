import java.io.*;
import java.util.ArrayList;

public class BTreeNode<T extends Comparable> implements Serializable {

	public static final int HALF_MAX = 2;

	public ArrayList<T> data;

	public ArrayList<Integer> children;

	private int id;

	public BTreeNode (boolean leaf) {
		this.id = IdGenerator.nextId();
		data = new ArrayList<T>((HALF_MAX * 2) - 1);
		if (!leaf) {
			children = new ArrayList<Integer>(HALF_MAX * 2);
		}
	}

	public BTreeNode(BTreeNode child) {
		this(false);
		children.add(child.getId());
		splitChild(0, child);
	}

	public void add(T target) {
		BTreeNode node = this;
		while (!(node.isLeaf())) {
			double d = node.indexOf(target);
			int i = (int)d;
			if (i == d) {
				return;
			} else {
				BTreeNode child = node.getChild(i);
				if (child.isFull()) {
					node.splitChild(i, child);
				} else {
					node.writeToDisk();
					node = child;
				}
			}
		}
		node.addLocally(target);
		node.writeToDisk();
	}

	protected void addLocally(T target) {
		double d = indexOf(target);
		int i = (int)d;
		if (i != d) {
			data.add(i, target);
			if (!isLeaf()) {
				children.add(i + 1, 0);
			}
		}
	}


	protected BTreeNode createRightSibling() {
		BTreeNode<T> sibling = new BTreeNode<T>(isLeaf());
		for (int i = HALF_MAX; i < (HALF_MAX * 2) - 1; i++) {
			sibling.data.add(data.remove(HALF_MAX));
		}
		if (!isLeaf()) {
			for (int i = HALF_MAX; i < HALF_MAX * 2; i++) {
				sibling.children.add(children.remove(HALF_MAX));
			}
		}
		sibling.writeToDisk();
		return sibling;
	}


	public void deleteFromDisk() {
		try {
			File file = new File(BTree.DIR + "b" + id + ".node");
			file.delete();
		} catch (Exception e) {
			e.printStackTrace();
			System.exit(1);
		}
	}


	public BTreeNode getChild(int index) {
		if (isLeaf()) {
			return null;
		} else {
			return readFromDisk(children.get(index));
		}
	}


	public int getId() {
		return id;
	}

	public double indexOf(T target) {
		for (int i = 0; i < data.size(); i++) {
			T checking = (T)data.get(i);
			if (checking.compareTo(target) == 0) {
				return i;
			}
			if (checking.compareTo(target) > 0) {
				return i + 0.5;
			}
		}
		return size() - 0.5;
	}


	public boolean isFull() {
		return size() == HALF_MAX * 2;
	}


	public boolean isLeaf() {
		return children == null;
	}


	public boolean isMinimal() {
		return size() == HALF_MAX;
	}


	protected void mergeChildren(int i, BTreeNode child, BTreeNode sibling) {
		child.data.add(data.remove(i));
		children.remove(i + 1);
		if (!(child.isLeaf())) {
			child.children.add(sibling.children.remove(0));
		}
		for (int j = 0; j < HALF_MAX - 1; j++) {
			child.data.add(sibling.data.remove(0));
			if (!(child.isLeaf())) {
				child.children.add(sibling.children.remove(0));
			}
		}
		sibling.deleteFromDisk();
	}


	public static BTreeNode readFromDisk(int id) {
		try {
			ObjectInputStream in
				= new ObjectInputStream
				(new FileInputStream(BTree.DIR + "b" + id + ".node"));
			return (BTreeNode)(in.readObject());
		} catch (Exception e) {
			e.printStackTrace();
			System.exit(1);
			return null;
		}
	}

	public void remove(T target) {
		double d = indexOf(target);
		int i = (int)d;
		if (isLeaf()) {
			if (i == d) {
				data.remove(i);
				writeToDisk();
			}
		} else if (i == d) {
			removeFromInternalNode(i, target);
		} else {
			removeFromChild(i, target);
		}
	}


	protected void removeFromChild(int i, T target) {
		BTreeNode child = getChild(i);
		if (child.isMinimal()) {
			if (i == 0) {             // Target in first child
				BTreeNode sibling = getChild(1);
				if (sibling.isMinimal()) {
					mergeChildren(i, child, sibling);
				} else {
					rotateLeft(i, child, sibling);
				}
			} else if (i == size() - 1) { // Target in last child
				BTreeNode sibling = getChild(i - 1);
				if (sibling.isMinimal()) {
					mergeChildren(i - 1, sibling, child);
					child = sibling;
				} else {
					rotateRight(i - 1, sibling, child);
				}
			} else {                  // Target in middle child
				BTreeNode rightSibling = getChild(i + 1);
				BTreeNode leftSibling = getChild(i - 1);
				if (!(rightSibling.isMinimal())) {
					rotateLeft(i, child, rightSibling);
				} else if (!(leftSibling.isMinimal())) {
					rotateRight(i - 1, leftSibling, child);
				} else {
					mergeChildren(i, child, rightSibling);
				}
			}
		}
		writeToDisk();
		child.remove(target);
	}


	protected void removeFromInternalNode(int i, T target) {
		BTreeNode child = getChild(i);
		BTreeNode sibling = getChild(i + 1);
		if (!(child.isMinimal())) {
			data.set(i, (T)child.removeRightmost());
			writeToDisk();
		} else if (!(sibling.isMinimal())) {
			data.set(i, (T)sibling.removeLeftmost());
			writeToDisk();
		} else {
			mergeChildren(i, child, sibling);
			writeToDisk();
			child.remove(target);
		}
	}


	protected T removeLeftmost() {
		BTreeNode node = this;
		while (!(node.isLeaf())) {
			BTreeNode child = node.getChild(0);
			if (child.isMinimal()) {
				BTreeNode sibling = node.getChild(1);
				if (sibling.isMinimal()) {
					node.mergeChildren(0, child, sibling);
				} else {
					node.rotateLeft(0, child, sibling);
				}
			}
			node.writeToDisk();
			return (T)child.removeLeftmost();
		}
		T result = (T)node.data.remove(0);
		node.writeToDisk();
		return result;
	}


	protected T removeRightmost() {
		BTreeNode node = this;
		while (!(node.isLeaf())) {
			BTreeNode child = node.getChild(size() - 1);
			if (child.isMinimal()) {
				BTreeNode sibling = node.getChild(size() - 2);
				if (sibling.isMinimal()) {
					node.mergeChildren(size() - 2, sibling, child);
					child = sibling;
				} else {
					node.rotateRight(size() - 2, sibling, child);
				}
			}
			node.writeToDisk();
			return (T)child.removeRightmost();
		}
		T result = (T)node.data.remove(size() - 2);
		node.writeToDisk();
		return result;
	}


	protected void rotateLeft(int i, BTreeNode child,
				  BTreeNode sibling) {
		child.data.add(data.get(i));
		if (!(child.isLeaf())) {
			child.children.add(sibling.children.remove(0));
		}
		data.set(i, (T)sibling.data.remove(0));
		sibling.writeToDisk();
	}

	protected void rotateRight(int i, BTreeNode sibling,
				   BTreeNode child) {
		child.data.add(0, data.get(i));
		if (!(child.isLeaf())) {
			child.children.add(0,
					   sibling.children.remove(sibling.size() - 1));
		}
		data.set(i, (T)(sibling.data.remove(sibling.size() - 2)));
		sibling.writeToDisk();
	}


	public void setLeaf(boolean value) {
		if (value) {
			children = null;
		} else {
			children = new ArrayList<Integer>(HALF_MAX * 2);
		}
	}


	public int size() {
		return data.size() + 1;
	}

	protected void splitChild(int i, BTreeNode child) {
		BTreeNode sibling = child.createRightSibling();
		addLocally((T)child.data.remove(HALF_MAX - 1));
		child.writeToDisk();
		children.set(i + 1, sibling.getId());
	}


	public void writeToDisk() {
		try {
			ObjectOutputStream out	=
				new ObjectOutputStream(new FileOutputStream(BTree.DIR + "b" + id + ".node"));
			out.writeObject(this);
			out.close();
		} catch (Exception e) {
			e.printStackTrace();
			System.exit(1);
		}
	}

	public ArrayList<T> toArrayList() {
		ArrayList<T> al = new ArrayList<T>();
		for (T item : data) {
			al.add(item);
		}
		if (!isLeaf()) {
			for (Integer childId : children) {
				BTreeNode child = BTreeNode.readFromDisk(childId);
				ArrayList<T> childAL = child.toArrayList();
				for (T item : childAL) {
					al.add(item);
				}
			}
		}
		return al;
	}
	
	public boolean update(T target) {
		return true;
	}

	public T get(T target) {
		BTreeNode node = this;
		double d = indexOf(target);
		int i = (int)d;
		return (T)data.get(0);
	}
}