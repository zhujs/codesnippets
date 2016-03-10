import java.util.Random;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class CyclicBarrierTest {
	/*
		CyclicBarrier: Allows a set of threads to all wait for each other to reach a common barrier point (threads are wait for each other).
	 */
	public static void main(String[] args) {
		int numberOfPlayers = 5;

		CyclicBarrier barrier = new CyclicBarrier(numberOfPlayers);
		ExecutorService executor = Executors.newFixedThreadPool(numberOfPlayers);

		for (int i = 0; i<5; i++) {
			executor.submit(new Thread(new Runner(barrier, "Player " + (i+1))));
		}

		executor.shutdown(); // shutdown the executor (non-blocking)
		/*
            executor.awaitTermination(); // shutdown the executor (blocking)
            executor.shutdownNow();	 // best-effort attempts to stop processing actively executing task, return a list of the tasks that were awaiting execution.
		 */
	}
}

class Runner implements Runnable {
	private final CyclicBarrier barrier;
	private final String name;

	public Runner(CyclicBarrier barrier, String name) {
		super();
		this.barrier = barrier;
		this.name = name;
	}

	@Override
	public void run() {
		try {
			int preparationTimeLimit = 5;
			Thread.sleep(1000 * (new Random()).nextInt(preparationTimeLimit));
			System.out.println( name + " is ready.");

			// Waits until all parties have invoked await on this barrier
			barrier.await();
		} catch (InterruptedException e) {
			e.printStackTrace();
		} catch (BrokenBarrierException e) {
			e.printStackTrace();
		}
		System.out.println(name + " go!");
	}
}
