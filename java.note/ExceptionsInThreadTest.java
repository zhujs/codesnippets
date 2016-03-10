import java.lang.Thread.UncaughtExceptionHandler;

class ExceptionHandler implements UncaughtExceptionHandler {
	public void uncaughtException(Thread t, Throwable e) {
		System.out.printf("An exception has been captured\n");
		System.out.printf("\tThread --> %s\n", t.getId());
		System.out.printf("\tException --> %s : %s\n", e.getClass().getName(), e.getMessage());
		System.out.printf("\tThread status --> %s\n", t.getState());
        e.printStackTrace(System.out);
	}
}


public class ExceptionsInThreadTest {
	public static void main(String[] args) {
		Thread thread = new Thread(new Runnable() {
			@Override
			public void run() {
                Integer.parseInt("NaN");
			}
		});
        thread.setUncaughtExceptionHandler(new ExceptionHandler());
		thread.start();
	}
}
