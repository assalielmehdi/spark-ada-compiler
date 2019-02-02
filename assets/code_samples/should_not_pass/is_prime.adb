procedure isPrime is

n : Integer := 49;
i : Integer := 2;
result : Boolean;

begin

if n = 1 then
  result := false;
end if;

while (i * i <= n) and (result = true) loop
  if n mod i = 0 then
    result := false;
  end if;
  i := i + 1;
end loop;

print result;

end isPrime;