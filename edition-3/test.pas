var
x,y:integer;
i,j:integer;
begin
  read(x);
  y := x^3;
  writeln(y);

  for i:=1 to 10 do
  begin
    for j:=1 to 10 do
	begin
	  if i%3==0 then
	    if j%4==0 then
		  writeln(i,j);
	end;
  end;
end.
