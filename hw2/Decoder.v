`timescale 1ns / 1ps

module Decoder( OP, Reg_WE, DM_WE, ALU_OP, ALU_src,MEM_to_REG,REG_Dst,funct);
	input [5:0] OP;
	input [5:0] funct;
	output Reg_WE, DM_WE, ALU_src,MEM_to_REG,REG_Dst;
	output [1:0] ALU_OP;
	

   /* add your design */   	
	//reg Reg_WE, DM_WE, ALU_src,MEM_to_REG,REG_Dst;
	//reg [1:0] ALU_OP;

	assign REG_Dst = (OP == 0)? 1 :
			 (OP == 35)? 0 :
			 (OP == 43)? 0 : 0;
	assign ALU_src = (OP == 0)? 0 :
			 (OP == 35)? 1 :
			 (OP == 43)? 1 : 0;
	assign MEM_to_REG = (OP == 0)? 0 :
			    (OP == 35)? 1 :
			    (OP == 43)? 0 : 0;
	assign Reg_WE = (OP == 0)? 1 :
			(OP == 35)? 1 :
			(OP == 43)? 0 : 0;
	assign DM_WE = (OP == 0)? 0 :
		       (OP == 35)? 0 :
		       (OP == 43)? 1 : 0;
	assign ALU_OP = (OP == 0)? 2 :
			(OP == 35)? 0 :
			(OP == 43)? 0 : 1;
	/*
	if(OP == 0)
	begin
		REG_Dst = 1;
		ALU_src = 0;
		MEM_to_REG = 0;
		Reg_WE = 1;
		DM_WE = 0;
		ALU_OP = 2;
		
	end
	else if(OP == 35)
	begin
		REG_Dst = 0;
		ALU_src = 1;
		MEM_to_REG = 1;
		Reg_WE = 1;
		DM_WE = 0;
		ALU_OP = 0;
	end
	else if(OP == 43)
	begin
		REG_Dst = 0;
		ALU_src = 1;
		MEM_to_REG = 0;
		Reg_WE = 0;
		DM_WE = 1;
		ALU_OP = 0;
	end
	else
	begin
		REG_Dst = 0;
		ALU_src = 0;
		MEM_to_REG = 0;
		Reg_WE = 0;
		DM_WE = 0;
		ALU_OP = 1;
	end
	*/
	
	
	
endmodule
