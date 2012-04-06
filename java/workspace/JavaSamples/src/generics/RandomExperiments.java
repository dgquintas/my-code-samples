package generics;

import java.util.ArrayList;
import java.util.List;

public class RandomExperiments {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		
		Object[] objectArray = new Long[1]; // because, arrays being covariant, Long[] is-a Object[]
		try{
			objectArray[0] = "I don't fit in"; // which only leads to clusterfucks
		}
		catch (Exception e) {
			System.err.println("Meeeec: " + e.toString());
		}
		
		// the following won't even compile
//		List<Object> ol = new ArrayList<Long>();
//		ol.add("I don't fit in");
		
		List<Integer> ol = new ArrayList<Integer>();
		Object[] oa = ol.toArray();

	}

}
