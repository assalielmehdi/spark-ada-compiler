procedure isPrime is

n : Integer := 49;
i : Integer := 2;
result : Boolean := true;

begin

while (i * i <= n) loop
  if n mod i = 0 then
    result := false;
  end if;
  i := i + 1;
end loop;

end isPrime;