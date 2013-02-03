public class TestT{
	public TestT(){
		System.out.println("this is default");
	}
	public TestT(int a){
		System.out.println("this is not default");
	}
	public static void main(String[] args)
	{
		B b = new B(1);
	}
}

class B extends TestT{
	B(int a){
		// super(a);
		System.out.println("b created");
	}
}