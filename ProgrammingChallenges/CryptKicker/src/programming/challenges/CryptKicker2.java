/**
 * 
 */
package programming.challenges;

import java.io.InputStream;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.Set;
import java.util.TreeSet;

/**
 * @author dgquintas
 *
 */
public class CryptKicker2 {

	private List<String> cryptphrases = new ArrayList<String>();
	private Map<Integer, List<String> > plainwords = new HashMap<Integer, List<String>>();
	
	public void parseInput(InputStream input){
		final Scanner scanner = new Scanner(input);
		final int n = scanner.nextInt();
		for(int i=0; i<n; i++){
			String word = scanner.next();
			plainwords.put(word);
		}
		while( scanner.hasNextLine() ){
			String nextLine = scanner.nextLine();
			if( !nextLine.isEmpty() ){
				cryptphrases.add( nextLine );
			}
		}
	}
	
	public void solveFor(String cryptphrase){
		Set<String> cryptwords = new TreeSet<String>(lengthComparator);
		
	}
	
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}

