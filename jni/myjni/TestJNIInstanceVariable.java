package myjni;

public class TestJNIInstanceVariable {
   static {
      System.loadLibrary("myjni"); // myjni.dll (Windows) or libmyjni.so (Unixes)
   }
 
   // Instance variables
   private int number = 88;
   private String message = "Hello from Java";
 
   // Declare a native method that modifies the instance variables
   private native void modifyInstanceVariable();
 
   // Test Driver   
   public static void main(String args[]) {
      myjni.TestJNIInstanceVariable test = new myjni.TestJNIInstanceVariable();
      test.modifyInstanceVariable();
      System.out.println("In Java, int is " + test.number);
      System.out.println("In Java, String is " + test.message);
   }
}


