import java.util.*;
import java.io.*;
	
class WordFreq {
	public static void main(String[] args) throws FileNotFoundException {
		HashMap<String, Integer> dict = new HashMap<String, Integer>();
		Scanner sc = new Scanner(new File("dict.txt"));

		while (sc.hasNext()) {
			String word = sc.next();
			Integer count = dict.get(word);
			if (count == null) {
				dict.put(word, 1);
			} else {
				dict.put(word, count + 1);
			}
		}

		Iterator it = dict.entrySet().iterator();
		while (it.hasNext()) {
			Map.Entry pairs = (Map.Entry) it.next;
			System.out.println(pairs.getKey() + " " + pairs.getKeyValue());
		}
		
	}

}