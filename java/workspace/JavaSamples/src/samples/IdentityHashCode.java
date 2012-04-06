package samples;

public class IdentityHashCode {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		final String s1 = "LOL";
		System.out.printf("0x%x", System.identityHashCode(s1));
		final String s11 = s1;
		System.out.println(System.identityHashCode(s11));
		final String s2 = "LOL";
		System.out.println(System.identityHashCode(s2));
		
		Integer i = 1;
		System.out.println(System.identityHashCode(i));
		i = 2;
		System.out.println(System.identityHashCode(i));
	}

}
