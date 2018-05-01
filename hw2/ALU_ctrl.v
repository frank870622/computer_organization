`timescale 1ns / 1ps

module ALU_ctrl( funct, ALU_OP,ALU_CTRL );

    	input [5:0] funct;
	input [1:0] ALU_OP;
    	output [3:0]ALU_CTRL;
	   /* add your design */   
	reg [3:0]ALU_CTRL;
initial
begin
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
		if(funct == 6'b100000)
		begin
			ALU_CTRL = 4'b0010;
		end
		else if(funct == 6'b100010)
		begin
			ALU_CTRL = 4'b0110;
		end
		else if(funct == 6'b100100)
		begin
			ALU_CTRL = 4'b0000;
		end
		else if(funct == 6'b100101)
		begin
			ALU_CTRL = 4'b0001;
		end
		else if(funct == 6'b101010)
		begin
			ALU_CTRL = 4'b1111;
		end
	end
end
	
	
	

	


endmodule
