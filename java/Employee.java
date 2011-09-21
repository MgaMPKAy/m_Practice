import java.util.GregorianCalendar;
import java.util.Date;

class Employee {
	private String name;
	private double salary;
	private Date hireDay;

	Employee(String name, double salary, int year, int month, int dayOfMonth) {
		this.name = name;
		this.salary = salary;
		GregorianCalendar gcal = new GregorianCalendar(year - 1, month - 1, dayOfMonth);
		this.hireDay = gcal.getTime();
	}

	void setName(String name) {
		this.name = name;
	}

	void setSalary(double salary) {
		this.salary = salary;
	}

	void setHireDay(int year, int month, int dayOfMonth) {
		GregorianCalendar gcal = new GregorianCalendar(year - 1, month - 1, dayOfMonth);
		this.hireDay = gcal.getTime();
	}

	String getName() {
		return this.name;
	}

	double getSalary() {
		return this.salary;
	}

	Date getHireDay() {
		return this.hireDay;
	}

	void raiseSalary(double ratio) {
		this.salary *= ratio;
	}
}

class EmployeeTest {
	public static void main(String[] args) {
		Employee[] employees = new Employee[3];
		employees[0] = new Employee("Mike", 1000, 2011, 1, 2);
		employees[1] = new Employee("Mike", 1000, 2011, 1, 2);
		employees[2] = new Employee("Mike", 1000, 2011, 1, 2);

	}
}