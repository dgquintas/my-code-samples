package threading;

import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.Random;

public class DinningPhilosophers {

	private final static int NUM_PLATES = 5;


	private Chopsticks chopsticks = new Chopsticks();

	private Philosopher[] philosophers = new Philosopher[NUM_PLATES];

	private class Chopsticks {

		private boolean[] csAvailable = new boolean[NUM_PLATES];

		public Chopsticks() {
			for (int i = 0; i < csAvailable.length; i++) {
				csAvailable[i] = true;
			}
		}

		public synchronized boolean pickUp(int i) throws InterruptedException {
			if (!csAvailable[i]) {
				wait(500);
			}
			if (!csAvailable[i]) {
				return false;
			}
			csAvailable[i] = false;
			return true;
		}

		public synchronized void putDown(int i) {
			assert (csAvailable[i] == false);
			csAvailable[i] = true;
			notifyAll();
		}
	}
	private class Philosopher extends Thread {

		private Random rnd = new Random();

		private int i;

		public long lastTimeEaten;

		public Philosopher(int i) {
			this.i = i;
			lastTimeEaten = Long.MIN_VALUE;
			this.setName("Philosopher" + i);
		}

		private void think() throws InterruptedException {
			System.out.println("Philosopher " + i + " thinks");
			Thread.sleep(rnd.nextInt(500));
		}

		private void sitDown() {

		}

		private void pickChopsticks() throws InterruptedException {
			// philosopher sitting at the plate i needs chopsticks
			// (i, (i+1) % n), with n the total number of plates
			boolean hasLeftCS = false;
			boolean hasRightCS = false;
			boolean hasBoth;
			do {
				hasLeftCS = chopsticks.pickUp(i);
				// assert (hasBoth);
				// System.out.println("Ph " + i + " owns cs " + i);
				if (i == 0) {
					Thread.sleep(800);
				}
				final int secondCS = (i + 1) % NUM_PLATES;
				// System.out.println("Ph " + i + " trying to get cs "
				// + secondCS);
				hasRightCS = chopsticks.pickUp(secondCS);
				hasBoth = (hasLeftCS && hasRightCS);
				if (!hasBoth) {
					// if we couldn't pick up cs i, put down
					// the other one if we had it, to give a chance
					// to the other philosopher to continue and avoid
					// deadlock
					if (hasLeftCS) { // has left but not right one
						// System.out.println("Ph " + i + " yielding cs "
						// + ownedChopstick);
						chopsticks.putDown(i);
						Thread.yield();
					} else if (hasRightCS) { // has right but not left
						// one
						// System.out.println("Ph " + i + " yielding cs "
						// + ownedChopstick);
						chopsticks.putDown(secondCS);
						Thread.yield();
					} else { // has neither one
						// keep waiting hoping that eventually a suitable CS
						// is freed
					}
				} else {
					// System.out.println("Ph " + i + " got 2nd cs "
					// + secondCS);
				}
			} while (!hasBoth);
		}

		private void eat() throws InterruptedException {
			System.out.println("Philosopher " + i + " eats");
			Thread.sleep(rnd.nextInt(300));
			this.lastTimeEaten = System.currentTimeMillis();
		}

		private void standUp() {
			chopsticks.putDown(i);
			chopsticks.putDown((i + 1) % NUM_PLATES);
		}

		public void run() {
			try {
				//while (!this.isInterrupted()) {
				while (true) {
					think();
					sitDown();
					pickChopsticks();
					eat();
					standUp();
				}
			} catch (InterruptedException e) {
				System.out.println("Thread " + this.getName() + " finished");
			}

		}

	}

	public DinningPhilosophers() {
		for (int i = 0; i < philosophers.length; i++) {
			philosophers[i] = new Philosopher(i);
		}
	}

	public void startProblem() {
		for (int i = 0; i < philosophers.length; i++) {
			philosophers[i].start();
		}
	}

	public void stopProblem() {
		for (int i = 0; i < philosophers.length; i++) {
			philosophers[i].interrupt();
		}
	}

	public void checkStarvation() {
		Comparator<Philosopher> comp = new Comparator<Philosopher>() {

			public int compare(Philosopher arg0, Philosopher arg1) {
				if (arg0.lastTimeEaten < arg1.lastTimeEaten) {
					return -1;
				} else if (arg0.lastTimeEaten > arg1.lastTimeEaten) {
					return 1;
				} else {
					return 0;
				}
			}
		};

		long _max = Collections.max(Arrays.asList(philosophers), comp).lastTimeEaten;
		long _min = Collections.min(Arrays.asList(philosophers), comp).lastTimeEaten;
		System.out.println("max dif = " + (_max - _min));
	}

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		DinningPhilosophers dp = new DinningPhilosophers();
		dp.startProblem();
		try {
			Thread.sleep(6000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		dp.checkStarvation();
		dp.stopProblem();

	}

}
