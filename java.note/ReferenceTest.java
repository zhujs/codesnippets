import java.lang.ref.*;
import java.util.*;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;

/*
There are four types of REFERENCES in Java (the first two types also exist in Python):
    Strong References: Objects that are reachable through strong references are not eligible for garbage collection.
    Weak References: Objects that are identified as only weakly reachable will be collected at the next GC cycle.
    Soft References: Like weak references, but soft references will not be cleared by GC if there are enough memory.
    Phantom References: Used for scheduling pre-mortem cleanup actions in a more flexible way (mainly to clean up the object's non-memory resources).


    For soft (weak) reference, at the time when GC determines the object is softly (weakly) reachable (or at some later time, before finalization)
    it will enqueue those newly-cleared soft (weak) references that are registered with reference queues. For phantom reference,
    it will be enqueued after the referent is finalized and phantom reference is not clear by GC.
        https://docs.oracle.com/javase/7/docs/api/java/lang/ref/package-summary.html

    Excellent article found in:
        http://kdgregory.com/index.php?page=java.refobj
 */

public class ReferenceTest {

    private static ReferenceQueue<LargeObject> referenceQueue = new ReferenceQueue<LargeObject>();

    private static class CheckRefQueueThread extends Thread {
        private AtomicBoolean running = new AtomicBoolean(true);

        public void stopThread() {
            this.running.set(false);
        }

        @Override
        public void run() {
            while (this.running.get()) {
                checkQueue();
                attemptGC();
            }
            System.out.println("Exit from the checkQueueThread.");
        }
    }

    private static class StopThreadTask extends TimerTask {

        private final CheckRefQueueThread thread;

        public StopThreadTask(CheckRefQueueThread thread) {
            this.thread = thread;
        }

        @Override
        public void run() {
            System.out.println("Stopping the checkQueueThread...");
            this.thread.stopThread();
        }

    }

    public static void checkQueue() {
        /*
            Soft and weak references will be cleared by GC before enqueued in the registered queue.
         */
        Reference<? extends LargeObject> reference = referenceQueue.poll();
        if (reference != null)
            System.out.println("Reference in queue, type: " + reference + " --> " + reference.get());
    }

    private static void attemptGC()
    {
        // A tricky way to drive the GC...
        List<byte[]> foo = new ArrayList<byte[]>();
        for (int ii = 0 ; ii < 1000 ; ii++)
            foo.add(new byte[1024]); // change the array size to observe the GC's behavior

        System.gc();
    }

    public static void main(String[] args) {
        /*
        Note that the output of the program depends on the implement of JVM (GC)
         */

        final int size = 10;

        Set<SoftReference<LargeObject>> softReferenceSet = new HashSet<SoftReference<LargeObject>>();
        for (int i = 0; i < size; i++) {
            SoftReference<LargeObject> ref = new SoftReference<LargeObject>(new LargeObject("Soft " + i), referenceQueue);
            System.out.println("Just created: " + ref.get());
            softReferenceSet.add(ref);
        }
        attemptGC();


        Set<PhantomReference<LargeObject>> phantomReferenceSet = new HashSet<PhantomReference<LargeObject>>();
        for (int i = 0; i < size; i++) {
            PhantomReference<LargeObject> ref = new PhantomReference<LargeObject>(new LargeObject("Phantom " + i), referenceQueue);

            // ref.get() will always return null, than often you must maintain
            // at least another strong reference to those resources needed ot clean up
            System.out.println("Just created: " + ref.get());
            phantomReferenceSet.add(ref);
        }
        attemptGC();

        Set<WeakReference<LargeObject>> weakReferenceSet = new HashSet<WeakReference<LargeObject>>();
        for (int i = 0; i < size; i++) {
            WeakReference<LargeObject> ref = new WeakReference<LargeObject>(new LargeObject("Weak " + i), referenceQueue);
            System.out.println("Just created: " + ref.get());
            weakReferenceSet.add(ref);
        }
        attemptGC();

        // Check the reference queue in another thread
        CheckRefQueueThread thread = new CheckRefQueueThread();
        TimerTask timeTask = new StopThreadTask(thread);

        Timer timer = new Timer();
        timer.schedule(timeTask, TimeUnit.SECONDS.toMillis(5));

        try {
            thread.start();
            thread.join();
            timer.cancel();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}


class LargeObject {

    // Every instance occupies about 80K
    private static final int SIZE = 10000;
    private double[] doubles = new double[SIZE];

    private String name;
    public LargeObject(String name) {
        this.name = name;
    }
    public String toString() {
        return name;
    }
    public void finalize() {
        System.out.println("Finalizing: " + name);
    }
}









/*
public class CyclicBarrierTest {

	public static void main(String[] args) throws IOException, InterruptedException {
		//如果将参数改为4，但是下面只加入了3个选手，这永远等待下去
		//Waits until all parties have invoked await on this barrier.
		CyclicBarrier barrier = new CyclicBarrier(3);

		ExecutorService executor = Executors.newFixedThreadPool(3);
		executor.submit(new Thread(new Runner(barrier, "1号选手")));
		executor.submit(new Thread(new Runner(barrier, "2号选手")));
		executor.submit(new Thread(new Runner(barrier, "3号H选手")));

		executor.shutdown();
	}
}

class Runner implements Runnable {
	// 一个同步辅助类，它允许一组线程互相等待，直到到达某个公共屏障点 (common barrier point)
	private CyclicBarrier barrier;

	private String name;

	public Runner(CyclicBarrier barrier, String name) {
		super();
		this.barrier = barrier;
		this.name = name;
	}

	@Override
	public void run() {
		try {
			Thread.sleep(1000 * (new Random()).nextInt(8));
			System.out.println(name + " 准备好了...");
			// barrier的await方法，在所有参与者都已经在此 barrier 上调用 await 方法之前，将一直等待。
			barrier.await();
		} catch (InterruptedException e) {
			e.printStackTrace();
		} catch (BrokenBarrierException e) {
			e.printStackTrace();
		}
		System.out.println(name + " 起跑！");
	}
}
 */
