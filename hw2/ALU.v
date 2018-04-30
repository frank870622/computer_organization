`timescale 1ns / 1ps

module ALU( source1,source2,ALU_CTRL,result);
    input [15:0] source1;
    input [15:0] source2;
    input [3:0] ALU_CTRL;
    output [15:0] result;
	 
	   /* add your design */   
	reg [15:0] result;
initial
begin
	if(ALU_CTRL == 0)
		result = source1 & source2;
	else if(ALU_CTRL == 1)
		result = source1 | source2;
	else if(ALU_CTRL == 2)
		result = source1 + source2;
	else if(ALU_CTRL == 6)
		result = source1 - source2;
	else
		if(source1 < source2)
			result = 1;
		else
			result = 0;
end
	

endmodule
