public class SyncCubbyHole extends CubbyHole {
    synchronized public Product get() {
    	Product res = myProduct;
    	myProduct = null;
    	System.out.println("["+Thread.currentThread().getName()+"]"+"get " + res);
        try {
            notifyAll();
            wait();
        } catch (Exception err) {
            System.out.println(err);
        }
    	return res;
    }

    synchronized public void put(Product aProduct) {
    	myProduct = aProduct;
    	System.out.println("["+Thread.currentThread().getName()+"]"+"put " + myProduct);
        try {
            notifyAll();
            wait();
        } catch (Exception err) {
            System.out.println(err);
        }
    }
}
