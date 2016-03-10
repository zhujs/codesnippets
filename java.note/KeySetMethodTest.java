import java.util.HashMap;
import java.util.Map;
import java.util.Set;


public class KeySetMethodTest {
	public static void main(String[] args) {
		Map<String, String> map = new HashMap<String, String>();
		map.put("key1", "value1");

		Set<String> set1= map.keySet();
		System.out.println("set1 = " + set1);

		map.put("key2", "key2");

		Set<String> set2= map.keySet();
		System.out.println("set1 = " + set1);
		System.out.println("set2 = " + set2);


		if (set1 == set2 ) {
			System.out.println("The keySet method " 
				       + "return a Set view, so set1 == set2");
		}
		System.exit(-1);
	}
}
