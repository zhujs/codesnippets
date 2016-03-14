public class StaticTest {
    /*
        All the static "statements" will be executed in the declaration order
     */
    static {
        System.out.println("--------------------------------------");
        System.out.println("Loading StaticTest...");

        value = 10;
        // new ObjectWithStaticBlocks(); //uncomment this line to load this class first
        System.out.println("Static block in StaticTest, value = " + StaticTest.value);
    }
    private static int value = 15;

    // if you set obj = null, the ObjectWithStaticBlocks will not be loaded
    private static ObjectWithStaticBlocks obj = new ObjectWithStaticBlocks();

    public static void main(String [] args) {
        System.out.println("--------------------------------------");
        System.out.println("The final value is " + StaticTest.value);
    }
}

class ObjectWithStaticBlocks {
    static {
        System.out.println("--------------------------------------");
        System.out.println("Loading ObjectWithStaticBlocks...");
        System.out.println("Static block in ObjectWithStaticBlocks");
    }
}
