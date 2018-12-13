procedure test is 

test1:constant Integer :=50;
test1:constant Float :=50.1;
test1:constant Character :='A';
test1:constant String :="OMG";
test1:constant Boolean :=true;
test1:constant Boolean :=false;

test2:Integer :=50;
test2:Float :=50.1;
test2:Character :='A';
test2:String :="OMG";
test2:Boolean :=true;
test2:Boolean :=false;

test3:Integer;
test3:Float;
test3:Character;
test3:String;
test3:Boolean;
test3:Boolean;

begin

myLoop:
while (test1 < 5.0) loop
  test1 := 3;
end loop myLoop;

loop
  if test1 < 0 then
    test := 1.0;
  end if;
end loop;

end test;