procedure sin is

x : Float := 1.047197551196598;
pow : Float := 1.047197551196598;
fact : Float := 1.0;
result : Float := 0.0;
i : Integer := 1.0;
n : Integer := 20;
sign : Integer := 1;

begin

while i < n loop
  result := result + sign * (pow / fact);
  sign := sign * -1;
  pow := pow * x * x;
  fact := fact * (i + 1) * (i + 2);
  i := i + 2;
end loop;

print result;

end sin;