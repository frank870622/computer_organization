`timescale 1ns / 1ps

module ALU_ctrl( funct, ALU_OP,ALU_CTRL );

    	input [5:0] funct;
	input [1:0] ALU_OP;
    	output [3:0]ALU_CTRL;
	   /* add your design */   
	//reg [3:0]ALU_CTRL;

	assign ALU_CTRL = (ALU_OP == 0)? 4'b0010 :
			  (ALU_OP == 1)? 4'b0110 :
			  (funct == 32)? 4'b0010 :
			  (funct == 34)? 4'b0110 :
			  (funct == 36)? 4'b0000 :
			  (funct == 37)? 4'b0001 : 4'b0111;
	/*
	if(ALU_OP == 0)
	begin
		ALU_CTRL = 4'b0010;
	end
	else if(ALU_OP == 1)
	begin
		ALU_CTRL = 4'b0110;
	end
	else if(ALU_OP == 2)
	begin
		if(funct == 32)
		begin
			ALU_CTRL = 4'b0010;
		end
		else if(funct == 34)
		begin
			ALU_CTRL = 4'b0110;
		end
		else if(funct == 36)
		begin
			ALU_CTRL = 4'b0000;
		end
		else if(funct == 37)
		begin
			ALU_CTRL = 4'b0001;
		end
		else
		begin
			ALU_CTRL = 4'b0111;
		end
	end
*/

	
	

	


endmodule
