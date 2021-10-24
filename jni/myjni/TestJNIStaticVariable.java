package myjni;

public class TestJNIStaticVariable {
   static {
      System.loadLibrary("myjni"); // nyjni.dll (Windows) or libmyjni.so (Unixes)
   }
 
   // Static variables
   private static double number = 55.66;
 
   // Declare a native method that modifies the static variable
   private native void modifyStaticVariable();
 
   // Test Driver
   public static void main(String args[]) {
      myjni.TestJNIStaticVariable test = new myjni.TestJNIStaticVariable();
      test.modifyStaticVariable();
      System.out.println("In Java, the double is " + number);
   }
}
