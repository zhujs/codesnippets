import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.concurrent.*;

/*
 * 
 *
 *          future<T>        Runnable       Callable<T>  
 *              ^              ^
 *              |              |
 *              +------+-------+
 *                     |
 *                     |
 *                     |
 *                 RunnableFuture<T>
 *                     ^
 *                     |
 *                     |
 *                 FutureTask<T>
 *                     public FutureTask(Callable<T>)
 *                     public FutureTask(Runnable, T)
 *
*/


public class ExecutorServiceTest{
    private static int threadNum = 5;
    private static int taskNum = 10;
    public static void main(String []argv) {
        ExecutorService service = Executors.newFixedThreadPool(threadNum);

        List<Future<Integer>> futureList = new ArrayList<>();
        for (int i = 0; i < taskNum; i++) {
            Future<Integer> future = service.submit(new RandomSleepTask(i));
            futureList.add(future);
        }

        try {
            Thread.sleep(2*1000);
            for (Future<Integer> future : futureList) {
                if(future.isDone() == false) {
                    // Cancels the execution of thread if it's running (by calling thread.interrupt())
                    // Chances are that there are some tasks (will not execute) in the BlockingQueue
                    future.cancel(true);
                }
            }

            service.shutdown(); // previously submitted tasks are executed, but no new tasks will be accepted.
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

class RandomSleepTask implements Callable<Integer> {
    private static Random random = new Random();
    private final Integer id;

    public RandomSleepTask (Integer id) {
        this.id = id;
    }

    @Override
    public Integer call() {
        try {
            Thread.sleep(random.nextInt(5) * 1000);

            System.out.println("Task " + this.id + " completed.");
        } catch (InterruptedException e) {
            System.out.println("Task " + this.id + " interrupted.");
        }

        return this.id;
    }
}
