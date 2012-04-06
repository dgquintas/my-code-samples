package programming.challenges;

import java.io.InputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.NavigableMap;
import java.util.NavigableSet;
import java.util.Scanner;
import java.util.Set;
import java.util.TreeMap;
import java.util.TreeSet;

class Input {

	final public List<String> cryptphrases = new ArrayList<String>();

	final public Dictionary plainwords = new Dictionary();
	final public Dictionary cryptwords = new Dictionary();

	public void parseInput(InputStream in) {
		final Scanner scanner = new Scanner(in);
		final int n = scanner.nextInt();
		for (int i = 0; i < n; i++) {
			String word = scanner.next();
			plainwords.add(word);
		}
		while (scanner.hasNextLine()) {
			String nextLine = scanner.nextLine();
			if (!nextLine.isEmpty()) {
				cryptphrases.add(nextLine);
			}
		}
	}

}

public class CryptKicker {

	final private Input input;

	public CryptKicker(Input input) {
		this.input = input;
	}

	public Map<Character, Character> solve(int level) {
		NavigableSet<String> cryptwords = input.cryptwords.getByLength(level);
		NavigableSet<String> plainwords = input.plainwords.getByLength(level);
		if (cryptwords.size() > plainwords.size() || cryptwords.isEmpty()) {
			return null;
		} else {
			// form all possible pairs
			for (String pw : plainwords) {
				for (String cw : cryptwords) {
					Map<Character, Character> rule = extractRule(pw, cw);
					if (testRule(level, rule)) {
						return rule;
					}
				}
			}
		}
		return null;
	}

	private boolean testRule(int level, Map<Character, Character> rule) {
		NavigableSet<String> cryptwords = input.cryptwords.getByLength(level);
		// test for current level first
		Map<Integer, Character> matches = new HashMap<Integer, Character>();
		for( String cryptword : cryptwords ){
			for(int i=0; i < cryptword.length(); i++){
				if( rule.containsKey(cryptword.charAt(i)) ){
					matches.put(i, rule.get(cryptword.charAt(i)));
				}
			}
			//check that the resulting cryptword with the substitutions could still belong to the plainwords dict
			input.cryptwords.check(matches);
			
		}
		// then rest of the input
		
		return false;
	}
	
	

	private Map<Character, Character> extractRule(String plainword,
			String cryptword) {
		// plainword.length() == cryptword.length()
		Map<Character, Character> mapping = new HashMap<Character, Character>(
				plainword.length());
		for (int i = 0; i < plainword.length(); i++) {
			final char pc = plainword.charAt(i);
			final char cc = cryptword.charAt(i);
			mapping.put(cc, pc);
		}
		return mapping;
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		final Input input = new Input();
		input.parseInput(System.in);
		final CryptKicker ck = new CryptKicker(input);
		Map<Character, Character> rules = new HashMap<Character, Character>();

		for (String cryptphrase : input.cryptphrases) {
			final Dictionary cryptwords = new Dictionary();
			for (String cryptword : cryptphrase.split("\\s+")) {
				cryptwords.add(cryptword);
			}

			// extract first level
			for (int i : cryptwords.keys()) {
				Map<Character, Character> newRules = ck.solve(i);
				if (newRules != null) {
					rules.putAll(newRules);
				} else {
					// fail
					System.out.println("No solution");
					break;
				}
			}
		}
		System.out.println(rules);
	}
}

class Dictionary {

	// length-addressable list of words
	final private NavigableMap<Integer, TreeSet<String>> wordsByLength = new TreeMap<Integer, TreeSet<String>>();
	final private Map<Integer, HashMap<Character, TreeSet<String>>> charPosLookups = new HashMap<Integer, HashMap<Character, TreeSet<String>>>();

	public void add(String word) {
		final int length = word.length();
		TreeSet<String> set = wordsByLength.get(length);
		if (set == null) {
			set = new TreeSet<String>();
			wordsByLength.put(length, set);
		}
		set.add(word);
		
		for(int i=0; i < word.length(); i++ ){
			HashMap<Character, TreeSet<String>> map;
			if( charPosLookups.get(i) == null ){
				map = new HashMap<Character, TreeSet<String>>(26);
				for(char c='a'; c <= 'z'; c++){
					map.put(c, new TreeSet<String>());
				}
				charPosLookups.put(i, map);
			}
			else{
				map = charPosLookups.get(i);
			}
			map.get( word.charAt(i) ).add(word);
		}
	}

	public boolean check(Map<Integer, Character> matches) {
		Set<String> candidates = null;
		for ( Map.Entry<Integer, Character> match: matches.entrySet() ) {
			int pos = match.getKey();
			char ch = match.getValue();
			
			if( candidates == null ){
				candidates = charPosLookups.get(pos).get(ch);
			}
			else{
				candidates.retainAll(charPosLookups.get(pos).get(ch));
			}
		}
		
		return !candidates.isEmpty();
	}

	public NavigableSet<String> getByLength(int length) {
		TreeSet<String> words = wordsByLength.get(length);
		TreeSet<String> res;
		if (words == null) {
			res = new TreeSet<String>();
		} else {
			res = new TreeSet<String>(words);
		}

		return res;
	}

	public Entry<Integer, TreeSet<String>> popFirst() {
		return wordsByLength.pollFirstEntry();
	}

	public Set<Integer> keys() {
		return wordsByLength.keySet();
	}

	public void remove(String word) {
		int key = word.length();
		wordsByLength.get(key).remove(word);
	}

}
