package myjni;

public class HelloJNI {
  static {
    System.loadLibrary("hello");
  }

  private native void sayHello();

  public static void main(String[] args) {
    new myjni.HelloJNI().sayHello();
  }
}

