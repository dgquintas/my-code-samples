package samples;

public class StringSplit {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		String s = "En un lugar de la mancha de cuyo nombre no quiero acordarme. y tal y cual\tfoo bar/ljk " +
				"blabla ";
		
		String[] splits = s.split("\\s+");
		for( String split : splits ){
			System.out.println(split.charAt(0));
		}

	}

}
