module traffic_light(clk,rst,pass,R,G,Y);
input clk,rst,pass;
output R,G,Y;

reg [5:0]second;
reg R,G,Y;

always@ (posedge clk, posedge rst, pass)
begin
	if(rst)
	begin
		second = 6'd0;
	end
	else if(pass)
	begin
		if(second < 10 || second >= 22)
		begin
			second = 6'd10;
		end
	end
	else
	begin
		second = second + 6'd1;
	end
	if(second >= 27)
	begin
		second = 0;
	end
	if(second < 10)
	begin
		R = 1;
		G = 0;
		Y = 0;
	end
	else if(second >= 10 && second < 22)
	begin
		R = 0;
		G = 1;
		Y = 0;
	end
	else
	begin
		R = 0;
		G = 0;
		Y = 1;
	end
end


endmodule

