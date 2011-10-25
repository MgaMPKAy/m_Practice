module HC74 (
   // Outputs
   D1, D2, CP1,CP2, RD1N, RD2N, SD1N , SD2N,   
   // Inputs
   Q1, Q2, Q1N, Q2N,
   ) ;
   
   input  D1, D2;
   input  RD1N, SD1N, CP1;
   input  RD2N, SD2N, CP2;
   output Q1, Q1N, Q2, Q2N;
   reg 	  Q1, Q2;
   
   assign Q1N =~ Q1;
   assign Q2N =~ Q2;

   always @ (posedge CP1) begin
      if (!RD1N)
	Q1 <= 0;
      else if (!SD1N)
	Q1 <= 1;
      else
	Q1 <= D1;
   end

   always @ (posedge CP2) begin
      if (!RD2N)
	Q2 <= 0;
      else if (!SD2N)
	Q2 <= 1;
      else
	Q2 <= D2;
   end
   
endmodule // HC74

`timescale 1ns/1ns
module testbench_74HC74;
   reg D1, D2, RD1N, RD2N, CP1, CP2, SD1N, SD2N;
   wire Q1, Q2, Q1N, Q2N;

   initial begin
      CP1 = 0;
   end

   parameter clock_period = 20;
   always #(clock_period / 2) CP1 =~ CP2;

   initial begin
      CP2 = 0;
   end
   
   always #(clock_period/2) CP2 =~ CP2;
   
   initial begin
      D1 = 0;
      repeat (20) begin
	 #20 D1 = $random;
      end
   end

   initial begin
      D2 = 0;
      repeat (20) begin
	 #20 D2 = $random;
      end
   end

   initial begin
      RD1N = 0;
      repeat (20) begin
	 #20 RD1N = $random;
      end
   end

   initial begin
      RD2N = 0;
      repeat (20) begin
	 #20 RD2N = $random;
      end
   end
   
   initial begin
      SD1N = 0;
      repeat (20) begin
	 #20 SD1N = $random;
      end
   end

   initial begin
      SD2N = 0;
      repeat (20) begin
	 #20 SD2N = $random;
      end
   end

   HC74 testbench_74HC74(.CP1 (CP1),
	     .CP2 (CP2),
	     .D1 (D1),
	     .D2 (D2),
	     .RD1N (RD1N),
	     .RD2N (RD2N),
	     .SD1N (SD1N),
	     .SD2N (SD2N),

	     .Q1 (Q1),
	     .Q1N (Q1N),
	     .Q2 (Q2),
	     .Q2N (Q2N));
   
   initial begin
      $dumpfile("74hc74.vcd");
      $dumpvars(0, CP1);
      $dumpvars(0, CP2);
      $dumpvars(0, D1);
      $dumpvars(0, D2);
      $dumpvars(0, RD1N);
      $dumpvars(0, RD2N);
      $dumpvars(0, SD1N);
      $dumpvars(0, SD2N);
      $dumpvars(0, Q1);
      $dumpvars(0, Q1N);
      $dumpvars(0, Q2);
      $dumpvars(0, Q2N);
      #400 $finish;
   end
   
endmodule // test_74HC74

