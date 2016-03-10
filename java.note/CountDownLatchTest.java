import java.util.Random;
import java.util.concurrent.*;

public class CountDownLatchTest {
	/*
		CountDownLatch: Allows one or more threads to wait until a set of operations being performed in other threads completes (one or more threads wait for other threads).
	 */
	public static void main(String[] args) {
		int numberOfPlayers = 5;

		CountDownLatch latch = new CountDownLatch(numberOfPlayers);
		ExecutorService executor = Executors.newFixedThreadPool(numberOfPlayers);

		for (int i = 0; i<5; i++) {
			executor.submit(new Thread(new Runner(latch, "Player " + (i+1))));
		}

		executor.shutdown(); // shutdown the executor (non-blocking)
		/*
            executor.awaitTermination(); // shutdown the executor (blocking)
            executor.shutdownNow();	 // best-effort attempts to stop processing actively executing task, return a list of the tasks that were awaiting execution.
		 */

		try {
			// The main thread waits until all other threads complete
			latch.await();
			System.out.println("The race has started.");
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
}

class Runner implements Runnable {
	private final CountDownLatch latch;
	private final String name;

	public Runner(CountDownLatch latch, String name) {
		super();
		this.latch = latch;
		this.name = name;
	}

	@Override
	public void run() {
		try {
			int preparationTimeLimit = 5;
			Thread.sleep(1000 * (new Random()).nextInt(preparationTimeLimit));
			System.out.println( name + " is ready.");

			// Decrements the count of the latch
			latch.countDown();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
}
