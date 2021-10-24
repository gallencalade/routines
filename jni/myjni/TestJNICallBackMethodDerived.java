package myjni;

public class TestJNICallBackMethodDerived extends myjni.TestJNICallBackMethodBase {
   // To be called back by the native code
   public void callback() {
      System.out.println("In Java in derived");
   }

   public void callback(String message) {
      System.out.println("In Java in derived with " + message);
   }

   public double callbackAverage(int n1, int n2) {
      return ((double)n1 + n2) / 2.0;
   }

   // Static method to be called back
   public static String callbackStatic() {
      return "From static Java derived method";
   }

   // Test Driver
   public static void main(String args[]) {
      new myjni.TestJNICallBackMethodDerived().nativeMethod();
   }
}
