procedure test is 

test1:Integer := 1;
test2:Integer := 50;
test3:Integer := 2;

begin

while test2 < 5.0 loop
  test1 := 3;
  if test1 - test2 > 0 then
    while test1 > 0 loop
      test2 := test2 - 1;
    end loop;
  elsif test1 * test3 + test2 > 0 then
    test2 := 0;
  else
    test3 := test1 + test3;
  end if;
end loop;

end test;