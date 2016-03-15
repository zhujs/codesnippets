/*
 * Difference between synchronized and reentrantlock:
 *      http://stackoverflow.com/questions/11821801/why-use-a-reentrantlock-if-one-can-use-synchronizedthis
 *      http://stackoverflow.com/questions/9072422/difference-between-synchronized-and-reentrantlock-pros-and-cons
 *
 *      1. reentrantlock supports interruptible lock polling (time-out)
 *      2. need to wrap lock acquisitions in a try/finally block (not for synchronized)
 *      3. reentrantLock also supports configurable fairness policy, allowing more flexible thread scheduling.
 *      4. allow to check for the state of lock (being held or not, the list of waiting threads)
 *      5. performance difference??
 *
*/

public class SynchronizedTest {
    public static void main(String[] args) {
        // Every Java object (including the class object) has a reentrant lock
        final SynchronizedCounter counter = new SynchronizedCounter();

        System.out.println("The counter's initial value is: " + counter.getValue());

        Thread thread1 = new Thread(new Runnable() {
            @Override
            public void run() {
                System.out.println("Increment the counter 1000 times in thread1");
                for (int i = 0; i<1000; i++) {
                    counter.increment();
                }
            }
        });

        Thread thread2 = new Thread(new Runnable() {
            @Override
            public void run() {
                System.out.println("Decrement the counter 1000 times in thread2");
                for (int i = 0; i<1000; i++) {
                    counter.decrement();
                }
            }
        });

        thread1.start();
        thread2.start();

        try {
            thread1.join();
            thread2.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("The counter's final value is: " + counter.getValue());
    }
}

class SynchronizedCounter {
    /*
        Alternative way to implement the class: use AtomicInteger

        Generally, use the following syntax to get a fine-grained control
            public void methodAccessSharedResource() {
                ...
                synchronized (object) {
                    //lock the object
                    //access the shared resource here
                    ...
                }
                ...
            }
    */
    private int counter = 0;

    public SynchronizedCounter() {
        counter = 0;
    }

    public SynchronizedCounter(int counter) {
        this.counter = counter;
    }

    /*
    I guess the compiler will translate it into the following method:
        public void increment() {
            synchronized (this) {
                counter++;
            }
        }
     */
    public synchronized void increment() {
        counter++;
    }

    public synchronized void decrement() {
        counter--;
    }

    public synchronized int getValue() {
        return counter;
    }
}
