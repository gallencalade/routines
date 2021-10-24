package myjni;

public class TestJNICallBackMethodBase {
   static {
      System.loadLibrary("myjni"); // myjni.dll (Windows) or libmyjni.so (Unixes)
   }

   // Declare a native method that calls back the Java methods below
   public native void nativeMethod();

   // To be called back by the native code
   public void callback() {
      System.out.println("In Java in base");
   }

   public void callback(String message) {
      System.out.println("In Java in base with " + message);
   }

   public double callbackAverage(int n1, int n2) {
      return ((double)n1 + n2) / 2.0;
   }

   // Static method to be called back
   public static String callbackStatic() {
      return "From static Java base method";
   }

   // Test Driver
   public static void main(String args[]) {
      new myjni.TestJNICallBackMethodBase().nativeMethod();
   }
}
