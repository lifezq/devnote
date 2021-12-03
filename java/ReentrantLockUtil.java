import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class ReentrantLockUtil {
    private static ReentrantLock lock = new ReentrantLock();
    private static Condition c1 = lock.newCondition();
    private static Condition c2 = lock.newCondition();


    private static void do1() {
        lock.lock();
        try {
            c1.await();
            System.out.println("do1 running...");
            Thread.sleep(3 * 1000);
            c2.signal();
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            lock.unlock();
        }
    }

    private static void do2() {
        lock.lock();
        try {
            c1.signal();
            c2.await();
            System.out.println("do2 running...");
            Thread.sleep(3 * 1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            lock.unlock();
        }
    }

    public static void main(String[] args) throws InterruptedException {
        new Thread(() -> {
            for (int i = 0; i < 10; i++) {
                do1();
            }
        }).start();


        new Thread(() -> {
            for (int i = 0; i < 10; i++) {
                do2();
            }
        }).start();

        Thread.sleep(10 * 1000);
        System.out.println("exit...");
    }
}
