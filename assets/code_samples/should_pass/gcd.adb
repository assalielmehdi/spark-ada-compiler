procedure gcd is

a : Integer := 15;
b : Integer := 12;
temp : Integer := 0;

begin

while b /= 0 loop
  temp := a;
  a := b;
  b := temp mod b;
end loop;

print a;

end gcd;