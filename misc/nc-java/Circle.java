abstract class Shape {
	public enum Color{red, yellow, blue, white, black};
	protected Color lineColor;
	protected Color fillColor;

	Shape() {
		lineColor = Color.white;
		fillColor = Color.black;
	}

	public void setColor() {
		this.lineColor = lineColor;
		this.fillColor = fillColor;
	}

	abstract void draw();

	abstract double getArea();
}

class Circle extends Shape {
	public static final double PI = 3.1515926;
	private double radius;

	Circle(){};
	Circle(double radius) {
		this.radius = radius;
	}

	public void draw() {
		System.out.println("Drawing a circle");
	}

	public double getArea() {
		return PI * radius * radius;
	}

	public static void main(String args[]) {
		System.out.println("Hello");
	}
}

