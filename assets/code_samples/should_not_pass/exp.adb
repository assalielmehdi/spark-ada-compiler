procedure exp is

x : Float := 2.0;
fact : Float := 1.0;
pow : Float := 1.0;
result : Float := 1.0;
i : Integer := 1;
n : Integer := 1000;

begin

while i < n
  fact := fact * i;
  pow := pow * x;
  result := result + pow / fact
  i := i + 1;
end loop;

print result;

end exp;