`timescale 1ns / 1ps

module ALU( source1,source2,ALU_CTRL,result);
    input [15:0] source1;
    input [15:0] source2;
    input [3:0] ALU_CTRL;
    output [15:0] result;
	 
	   /* add your design */   
	//reg [15:0] result;

	//wire [3:0] CTRL_temp;
	//wire [15:0] source1_temp, source2_temp;

	//assign CTRL_temp = ALU_CTRL;
	//assign source1_temp = source1;
	//assign source2_temp = source2;

	assign result = (ALU_CTRL == 4'b0000)? source1 & source2 :
			(ALU_CTRL == 4'b0001)? source1 | source2 :
			(ALU_CTRL == 4'b0010)? source1 + source2 :
			(ALU_CTRL == 4'b0110)? source1 - source2 :
			(ALU_CTRL == 4'b0111 && source1 < source2)? 1 :
			(ALU_CTRL == 4'b0111 && source1 >= source2)? 0 : 0;


/*
always@
begin
	if(CTRL_temp == 4'b0000)
		result = source1 & source2;
	else if(CTRL_temp == 1)
		result = source1 | source2;
	else if(CTRL_temp == 2)
		result = source1 + source2;
	else if(CTRL_temp == 6)
		result = source1 - source2;
	else if(CTRL_temp == 7)
		if(source1 < source2)
			result = 1;
		else
			result = 0;
end
*/


endmodule
