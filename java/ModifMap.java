import java.util.*;

class ModifMap{

  public static void main(String[] args){
    Map<String, List<Integer>> mapa = new HashMap<String, List<Integer>>(1);
    final List<Integer> l = new ArrayList<Integer>(1);
    l.add(1);
    mapa.put("Uno", l);

    Collection<List<Integer>> values = mapa.values();
    final List<Integer> ll = values.iterator().next();
    ll.set( 0, 33);


    for(Map.Entry<String, List<Integer>> e: mapa.entrySet()){
      final List<Integer> v = e.getValue();
      System.out.println(e.getKey() + " -> " + v + " " + ((Object)v).hashCode() );
    }

  }
}
