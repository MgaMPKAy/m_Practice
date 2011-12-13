module HC112 (/*AUTOARG*/ ) ;
   input  J1, J2, K1, K2;
   input  RD1N, SD1N, CPN1;
   input  RD2N, SD2N, CPN2;
   output Q1, Q1N, Q2, Q2N;

   reg   Q1, Q2;

   assign Q1N = ~Q1;
   assign Q2N = ~Q2;

   always @ ( /*AUTOSENSE*/ ) begin
      if (!RD1N)
	Q1 <= 0;
      else if (!SD1N)
	Q1 <= 1;
      else
	case ({J1, K1})
   end
   
     
endmodule // HC112
