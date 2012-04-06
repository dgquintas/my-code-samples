package samples;

import java.util.Collections;
import java.util.List;

public class Singletons {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		List<Integer> sl = Collections.singletonList(88);
		sl.add(1);
	}

}
