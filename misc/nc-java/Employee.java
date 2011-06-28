class Employee {
	private String emplName;
	private int emplAge;
	private char emplGender;
	private double emplBaseSalary;

	public Employee(String name, int age, char gender, double baseSalary) {
		this.emplName = name;
		this.emplAge = age;
		this.emplGender = gender;
		this.emplBaseSalary = baseSalary;
	}

	public String getName() {
		return this.emplName;
	}

	public int getAge() {
		return this.emplAge;
	}

	public char getGender() {
		return this.emplGender;
	}

	public double getBaseSalary() {
		return this.emplBaseSalary;
	}

	public static void main(String args[]) {
		Employee emplA = new Employee("A", 20, 'm', 1500);
		Employee emplB = new Employee("B", 30, 'w', 2000);

		System.out.println("Name  : " + emplA.getName());
		System.out.println("Age   : " + emplA.getAge());
		System.out.println("Salary: " + emplA.getBaseSalary());
		System.out.println("Gender: " + emplA.getGender() + "\n");
		System.out.println("Name  : " + emplB.getName());
		System.out.println("Age   : " + emplB.getAge());
		System.out.println("Salary: " + emplB.getBaseSalary());
		System.out.println("Gender: " + emplB.getGender());
	}
}
