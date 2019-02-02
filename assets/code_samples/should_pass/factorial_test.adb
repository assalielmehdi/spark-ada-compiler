procedure factorial is

fact : Integer := 1;
n : Integer := 10;

begin

while n > 0 loop
  fact := fact * n;
  n := n - 1;
end loop;

print fact;

end factorial;