package code.snippet;



public class ConstructorTest {
    public static void main(String[] args) {
        System.out.println("Rule 1: Compiler will try to invoke the default constructor found in base class if no super() call.");
        System.out.println("Rule 2: Compiler will generate the default constructor for classes that without constructors.");
        System.out.println("Rule 3: Calling a non-final method in constructors is error-prone.");
        System.out.println("-----------------------------------------------------------------------------------------------------");

        Manager tommy = new Manager("Tommy", 15000 , 5000);
        Manager kate = new Manager();
        System.out.println("-----------------------------------------------------------------------------------------------------");
        Derived derived = new Derived();
        System.out.println( "The value is not what you want --> " + derived.value());
    }
}

class Person {

    private String name;

    public Person()
    {
        System.out.println("Person --> default constructor");
    }

    public Person(String name) {
        //super();
        this.name = name;
        System.out.println("Person -> constructor with name: " + getName());
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }
}


class Employee extends Person {
    private double salary;

    public Employee()
    {
        // an implicit super() call here
        System.out.println("Employee --> default constructor");
    }

    public Employee(String name,double s)
    {
        super(name);
        this.salary = s;
        System.out.println("Employee --> constructor with name: " + getName() + ", salary: " + getSalary());
    }

    public double getSalary() {
        return salary;
    }

    public void setSalary(double salary) {
        this.salary = salary;
    }
}



class Manager extends Employee {
    private double bonus;

    public Manager(String name, double salary, double bonus) {
        super(name, salary);
        this.bonus= bonus;
        System.out.println("Manager --> constructor with name: " + getName() + ", salary: " + getSalary() + ", bonus: " + getBonus());
    }

    public Manager() {
        // an implicit super() call here
        System.out.println("Manager --> default constructor");
    }

    public double getBonus() {
        return bonus;
    }

    public void setBonus(double bonus) {
        this.bonus = bonus;
    }
}


class Base {
    public int val;
    public  Base() {
        val = getVal(); // If subclass overrides this getVal method...
    }

    public int getVal()
    {
        return 6;
    }

    public int value()
    {
        return val;
    }
}

class  Derived extends Base {
    public int val = 16;
    public int getVal()
    {
        // when the base class invokes it, val is not initialized, so getVal return 0
        return  val;
    }
}
