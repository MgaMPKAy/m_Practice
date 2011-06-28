public class Student {
	String studentName;
	int studentNumber;

	Student() {
		System.out.println("new student of default prop");
	}

	Student(String name studentName, int studentNumber) {
		this.studentName = studentName;
		this.studentNumber = studentNumber;
		System.out.println("Set Student member var to real arg...");
	}
	void study(){}
}

public class GradStudent extends Student {
	String tutorName;
	String specDirect;

	GradStudent(String name, int studentNumber) {
		super(name, studentNumber);
	}

	GradStudent(