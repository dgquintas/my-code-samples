	package threading;

import java.util.ArrayList;

public class WaitAndNotify {

	private static class SharedResource {
		public synchronized void criticalMethod(int x) {
			if (x % 2 == 0) {
				try {
					System.out.println("blocking thread on x = " + x);
					wait();
					System.out.println("woken up thread on x = " + x);
				} catch (InterruptedException e) {
					Thread.currentThread().interrupt();
				}
			} else if (x == 123) {
				System.out.println("thread x = " + x + " notifying all");
				notifyAll();
			} else {
				System.out.println("odd thread x = " + x + " passing by");
			}
		}
	}

	private static class User implements Runnable {

		private SharedResource sr;

		private int x;

		public User(SharedResource sr, int x) {
			this.sr = sr;
			this.x = x;
		}

		public void run() {
			sr.criticalMethod(x);
		}
	}

	/**
	 * @param args
	 * @throws InterruptedException 
	 */
	public static void main(String[] args) throws InterruptedException {
		ArrayList<Thread> hilos = new ArrayList<Thread>();
		
		SharedResource sharedResource = new SharedResource();
		
		for (int i = 0; i < 9; i++) {
			hilos.add(new Thread(new WaitAndNotify.User(sharedResource,
					(int) ((Math.random() * 1000) % 100)), "Hilo " + i));
		}
		Thread notifyingThread = new Thread(new WaitAndNotify.User( sharedResource, 123));

		for (Thread t : hilos) {
			t.start();
		}
		
		for (Thread t : hilos) {
			System.out.println(t.getName() + " is " + t.getState().toString());
		}
		
		notifyingThread.start();
		
		for (Thread t : hilos) {
			t.join();
		}
		
		for (Thread t : hilos) {
			System.out.println(t.getName() + " is " + t.getState().toString());
		}

	}

}
