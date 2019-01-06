echo "Execution of samples in './test_samples' directory:" > out
for entry in "test_samples"/*
do
  echo "\n\nFile '$entry' execution:" >> out
  ./main < $entry >> out || echo "Execution error ! (segmentation fault ?)" >> out
done

