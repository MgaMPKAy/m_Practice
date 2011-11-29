import java.util.ArrayList;

public class BTree <T extends Comparable<T>>  implements Cloneable {
	private static final int MINIMUM = 2;
	private static final int MAXIMUM = 2 * MINIMUM;

	ArrayList<T> data;
	BTree[] subset;
	int dataCount;
	int childCount;
	
	public BTree() {
		dataCount = 0;
		childCount = 0;
		data = new ArrayList<T>(MAXIMUM + 1);
		subset = new BTree[MAXIMUM + 2];
	}
	
	public void add(T element) throws OutOfMemoryError {
		looseAdd(element);
		if (dataCount > MAXIMUM) {
			BTree newChild = new BTree();
			newChild.dataCount = dataCount;
			newChild.childCount = childCount;
			newChild.data = (ArrayList<T>)data.clone();
			System.arraycopy(subset, 0, newChild.subset, 0, childCount);

			dataCount = 0;
			childCount = 1;
			subset[0] = newChild;
			fixExcess(0);
		}

	}

	public BTree clone() throws OutOfMemoryError {
		BTree newTree = new BTree();
	
		//newTree.data = (ArrayList<T>)data.clone();
		for (int i = 0; i < dataCount; i++) {
			newTree.data.add(i, data.get(i));
		}
		
		for (int i = 0; i < childCount; i++) {
			newTree.subset[i] = subset[i].clone();
		}
		return newTree;
	}

	public boolean contains(T target) {
		int i = firstGE(target);
	
		if (i < dataCount && data.get(i).compareTo(target) == 0) {
			return true;
		} else if (childCount > 0) {
			return subset[i].contains(target);
		} else {
			return false;
		}
	}
	
	public boolean remove(T target) {
		boolean answer = looseRemove(target);
		
		if (dataCount == 0 && childCount == 1) {
			dataCount = subset[0].dataCount;
			childCount = subset[0].childCount;
			data = subset[0].data;
			subset = subset[0].subset;
		}
		return answer;
	}

	
	public void print(int indent) {
		final int EXTRA_INDENTATION = 4;
		int i;
		int space;

		for (space = 0; space < indent; space++)
			System.out.print(" ");
		for (i = 0; i < dataCount; i++)
			System.out.print(data.get(i) + " ");
		System.out.println();

		for (i = 0; i < childCount; i++)
			subset[i].print(indent + EXTRA_INDENTATION);

	}
	
	
	private T deleteData(int removeIndex)	{
		dataCount--;
		return data.remove(removeIndex);
	}

	private BTree deleteSubset(int removeIndex) {
		BTree hold = subset[removeIndex].clone();
		for (int i = removeIndex; i < childCount - 1; i++)
			subset[i] = subset[i + 1];
	
		childCount--;
		return hold;
	}

	private int firstGE(T target) {
		for (int i = 0; i < dataCount; i++) {
			if (data.get(i).compareTo(target) >= 0) {
				return i;
			}
		}
		return dataCount;
	}

	private void fixExcess(int i) {

		T middle = (T)subset[i].data.get(subset[i].dataCount / 2);
	
		BTree newNode = new BTree();
		
		for (int j = 0; j < subset[i].dataCount / 2; j++) {
			newNode.data.add(subset[i].data.get(j + subset[i].dataCount / 2 + 1));
		}
		System.arraycopy(subset[i].subset, (subset[i].childCount / 2),
		 		 newNode.subset, 0, subset[i].childCount / 2);
	
		subset[i].dataCount /= 2;
		subset[i].childCount /= 2;
	
		newNode.dataCount = subset[i].dataCount;
		newNode.childCount = subset[i].childCount;

		insertData(firstGE(middle), middle);
		insertSubset(i + 1, newNode);
	}

	private void fixShortage(int i) {
		if (i > 0 && subset[i - 1].dataCount > MINIMUM) {
			transferRight(i - 1);
		} else if (i < dataCount && subset[i + 1].dataCount > MINIMUM) {
			transferLeft(i + 1);
		} else if (i > 0 && subset[i - 1].dataCount == MINIMUM) {
			mergeWithNextSubset(i - 1);
		} else {
			mergeWithNextSubset(i);
		}
	}

	private void insertData(int insertIndex, T entry) {
		data.add(insertIndex, entry);
		dataCount++;
	}

	private void insertSubset(int insertIndex, BTree set) {
		for (int i = childCount; i > insertIndex; i--)
			subset[i] = subset[i - 1];
		subset[insertIndex] = set;
		childCount++;
	}

	private boolean isLeaf() {
		return (childCount == 0);
	}

	private void looseAdd(T element) throws OutOfMemoryError {
		int i = firstGE(element);
		if (i < dataCount && data.get(i).compareTo(element) == 0) {
			return;
		} else if (childCount > 0) {
			subset[i].looseAdd(element);
			if (subset[i].dataCount > MAXIMUM) fixExcess(i);
		} else	{
			insertData(i, element);
		}
	}

	private boolean looseRemove(T target)	{
	
		int i = firstGE(target);
		
		if (i < dataCount && data.get(i).compareTo(target) != 0  && childCount == 0) {
			return false;
		} else if (i < dataCount && data.get(i).compareTo(target) == 0 && childCount == 0) {
			deleteData(i);
			return true;
		} else if (childCount > 0 && (i == dataCount ||
					      (i < dataCount && data.get(i).compareTo(target) != 0 ))) {
			subset[i].looseRemove(target);
			
			if (subset[i].dataCount < MINIMUM) fixShortage(i);
			return true;
		} else 	{
			data.set(i, (T)subset[i].removeBiggest());
			if (subset[i].dataCount < MINIMUM) fixShortage(i);
			return true;
		}
	}

	private void mergeWithNextSubset(int i) {
		subset[i].insertData(subset[i].dataCount, deleteData(i));
		while (subset[i + 1].dataCount > 0)
			subset[i].insertData(subset[i].dataCount,
					     subset[i + 1].deleteData(0));
		while (subset[i + 1].childCount > 0)
			subset[i].insertSubset(subset[i].childCount,
					       subset[i + 1].deleteSubset(0));
	}

	private T removeBiggest() {
		if (childCount == 0) {
			return data.remove(--dataCount);
		} else {
			T answer = (T)subset[childCount - 1].removeBiggest();
			if (subset[childCount - 1].dataCount < MINIMUM)
				fixShortage(childCount - 1);
			return answer;
		}
	}

	private void transferLeft(int i){
		subset[i - 1].insertData(subset[i - 1].dataCount, deleteData(i - 1));
		insertData(i - 1, (T)subset[i].deleteData(0));
		if (subset[i].childCount > 0) {
			subset[i - 1].insertSubset(subset[i - 1].childCount,
						   subset[i].deleteSubset(0));
			
		}
	}

	private void transferRight(int i){
		subset[i + 1].insertData(0, deleteData(i));
		insertData(i, (T)subset[i].deleteData(subset[i].dataCount - 1));
		if (subset[i].childCount > 0) {
			subset[i + 1].insertSubset(0,
						   subset[i].deleteSubset(subset[i].childCount - 1));
		}
	}
}