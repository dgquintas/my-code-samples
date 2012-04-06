#removes the extension from the file
# ie, foo.bar -> foo

for i in *; do
  basename=${i%.*}; 
  echo $basename; 
done
