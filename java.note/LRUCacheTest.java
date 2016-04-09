import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class LRUCacheTest {
    public static void main(String argv[]) {
        int cacheSize = 3;
        LRUCache cache = new LRUCache(cacheSize);

        // insert KV pair into cache
        for (int i = 0; i<4; i++) {
            cache.put("key" + i, "value" + i);
            cache.printCachedKV();
        }

        cache.get("key2");
        cache.printCachedKV();

        cache.put("key4", "value4");
        cache.printCachedKV();
    }
}

class LRUCache {
    /*
        Simple implementation of LRU cache (can use LinkedHashMap simplify the code, see Java Doc)
     */
    private Map<Object, Entry> cache = null;
    private int cacheSize = 0;
    private int currentSize = 0;

    // keep the entry in the list
    private Entry head;
    private Entry tail;

    public LRUCache (int size) {
        this.cache = new HashMap<>();

        // make sure a valid size parameter
        if (size < 1)
            size = 1;
        this.cacheSize = size;
        this.currentSize = 0;
        this.head = this.tail = null;
    }

    public Object get(Object key) {
        // get the cached value
        Entry entry = this.cache.get(key);

        if (entry == null)
            return null;

        // move the recently accessed Entry to the head of list
        moveToHead(entry);
        return entry.value;
    }

    public void printCachedKV() {
        /*
        Set<Map.Entry<Object,Entry>> entrySet = cache.entrySet();
        if (entrySet != null) {
            System.out.println("------------------Cache KVs--------------");
            for (Map.Entry<Object, Entry> ent : entrySet ) {
                System.out.println("Key = " + ent.getValue().key + " ; Value = " + ent.getValue().value);
            }
            System.out.println("-----------------------------------------");
        }
        */
        // walks through the list
        Entry temp = head;
        System.out.println("---------------Cached KVs (in recently used order)---------------");
        while (temp != null) {
            System.out.println("Key = " + temp.key + " ; Value = " + temp.value);
            temp = temp.next;
        }
        System.out.println("-----------------------------------------------------------------");
    }

    public void put(Object key, Object value) {
        // put the K/V in the cache
        Entry entry = this.cache.get(key);

        if (entry == null) {
            // cache is fully used
            if (currentSize >= cacheSize) {
                cache.remove(tail.key);
                removeLast();
            }
            else {
                currentSize++;
            }

            entry = new Entry();
        }

        // update the K/V in the Entry object
        entry.key = key;
        entry.value = value;
        cache.put(key, entry);

        // move to the head of list
        moveToHead(entry);
    }

    private void removeLast() {
        if (tail != null) {
            if (head == tail) {
                // there is only one entry
                head = tail = null;
            }
            else {
                tail.prev.next = tail.next;
                tail = tail.prev;
            }
        }
    }

    private void moveToHead(Entry entry) {
        if (entry == null)
            return;

        if (entry.next == null && entry.prev == null) {
            // this is a new node
            if (head == null) {
                head = tail = entry;
            } else {
                head.prev = entry;
                entry.next = head;
                head = entry;
            }
        } else {
            // this is a node in the list
            if (head == entry) {
                return;
            } else if (tail == entry) {
                // remove the entry form the list
                entry.prev.next = entry.next;
                tail = entry.prev;
            } else {
                // remove the entry form the list
                entry.prev.next = entry.next;
                entry.next.prev = entry.prev;
            }

            // insert into the head of the list
            head.prev = entry;
            entry.next = head;
            head = entry;
        }
    }

    private class Entry {
        public Entry prev;
        public Entry next;
        public Object key;
        public Object value;

    }
}
