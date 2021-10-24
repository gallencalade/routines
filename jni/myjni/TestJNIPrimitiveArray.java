package myjni;

public class TestJNIPrimitiveArray {
   static {
      System.loadLibrary("myjni"); // myjni.dll (Windows) or libmyjni.so (Unixes)
   }
 
   // Declare a native method sumAndAverage() that receives an int[] and
   //  return a double[2] array with [0] as sum and [1] as average
   private native double[] sumAndAverage(int[] numbers);
 
   // Test Driver
   public static void main(String args[]) {
      int[] numbers = {22, 33, 33};
      double[] results = new myjni.TestJNIPrimitiveArray().sumAndAverage(numbers);
      System.out.println("In Java, the sum is " + results[0]);
      System.out.println("In Java, the average is " + results[1]);
   }
}
