//package stud_grad;

class Student {
	String studentName;
	int studentNumber;
	static byte schoolYear = (byte)4;

	Student() {
		System.out.println("new student of default prop");
	}

	Student(String  studentName, int studentNumber) {
		this.studentName = studentName;
		this.studentNumber = studentNumber;
		System.out.println("Set Student member var to real arg...");
	}
	void displaySchoolYear() {
		System.out.println("Undergrauted: " + schoolYear);
	}

	void study(){}
}

class GradStudent extends Student {
	String tutorName;
	String specDirect;
	static int schoolYear = 3;

	GradStudent(String name, int studentNumber) {
		super(name, studentNumber);
	}

	GradStudent(String name, int studentNumber, String tutName, String specDir) {
		this(name, studentNumber);
		tutorName = tutName;
		specDirect = specDir;
	}

	void research(){}

	void displaySchoolYear() {
		System.out.println("Grauted: " + schoolYear);
	}
}
public class Stud_grad {
	public static void main (String[] args) {
		GradStudent gs1 = new GradStudent("A", 123, "B", "CS");
		gs1.displaySchoolYear();

		System.out.println("U: " + Student.schoolYear);
		System.out.println("S: " + GradStudent.schoolYear);

		System.out.println(gs1.getClass());
		System.out.println(gs1.toString());

	}
}