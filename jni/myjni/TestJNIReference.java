package myjni;

public class TestJNIReference {
   static {
      System.loadLibrary("myjni"); // myjni.dll (Windows) or libmyjni.so (Unixes)
      System.loadLibrary("myjni"); // myjni.dll (Windows) or libmyjni.so (Unixes)
      System.loadLibrary("myjni"); // myjni.dll (Windows) or libmyjni.so (Unixes)
      System.loadLibrary("myjni"); // myjni.dll (Windows) or libmyjni.so (Unixes)
      System.loadLibrary("myjni"); // myjni.dll (Windows) or libmyjni.so (Unixes)
   }
 
   // A native method that returns a java.lang.Integer with the given int.
   private native Integer getIntegerObject(int number);
 
   // Another native method that also returns a java.lang.Integer with the given int.
   private native Integer anotherGetIntegerObject(int number);
 
   public static void main(String args[]) {
      System.out.println("fasfdsafs");
      myjni.TestJNIReference test = new myjni.TestJNIReference();
      System.out.println(test.getIntegerObject(1));
      System.out.println(test.getIntegerObject(2));
      System.out.println(test.anotherGetIntegerObject(11));
      System.out.println(test.anotherGetIntegerObject(12));
      System.out.println(test.getIntegerObject(3));
      System.out.println(test.anotherGetIntegerObject(13));
   }
}
