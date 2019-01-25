procedure test is 

a:Integer := 50;
b:Float := 10.2;
c:Boolean := "true";
d:String := 's';
e:Character;

begin

case a is
  when b =>
    if (c) then
    elsif a <= b then
    else
    end if;
  when (a + b) =>
  when others =>
end case;

myLoop:
while (b < 5.0) loop
  a := 3;
end loop myLoop;

loop
  if e < 0 then
    b := 1.0;
  end if;
end loop;

f := 10;

end test;