module HC00 (/*AUTOARG*/
   // Outputs
   Y,
   // Inputs
   A, B
   );
   input  [4:1] A, B;
   output [4:1] Y;
   assign Y = ~(A & B);
endmodule // HC00

module HC02 (/*AUTOARG*/
   // Outputs
   Y,
   // Inputs
   A, B
   );
   input  [4:1] A, B;
   output [4:1] Y;
   assign Y = ~(A | B);
   
endmodule // HC02

module HC04 (/*AUTOARG*/
   // Outputs
   Y,
   // Inputs
   A
   ) ;
   output [6:1] Y;
   input [6:1] 	A;
   assign Y = ~A;
endmodule // HC04

module HC08 (/*AUTOARG*/
   // Outputs
   Y,
   // Inputs
   A, B
   ) ;
   input  [4:1] A, B;
   output [4:1] Y;
   assign Y = A & B;
endmodule // HC08

module HC32 (/*AUTOARG*/
   // Outputs
   Y,
   // Inputs
   A, B
   ) ;
   input  [4:1] A, B;
   output [4:1] Y;
   assign Y = A | B;
endmodule // HC32

module HC86 (/*AUTOARG*/
   // Outputs
   Y,
   // Inputs
   A, B
   ) ;
   input  [4:1] A, B;
   output [4:1] Y;
   assign Y = A ^ B;
endmodule // HC86
