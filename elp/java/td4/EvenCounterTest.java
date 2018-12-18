public class EvenCounterTest {
    public static void main(String args[]) {
        EvenCounter e = new EvenCounter();
        Thread t1 = new Thread(e);
        Thread t2 = new Thread(e);
        t1.start();
        t2.start();

        try {
            t1.join();
            t2.join();
        } catch (InterruptedException err) {
            System.out.println(err);
        }

        System.out.println(">[MAIN]FIN");
    }
}
