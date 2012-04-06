while read FROM TO; 
do
  find . -type f \( -name '*.cpp' -o -name '*.h' -o -name '*' \) -a ! -wholename '*svn*' -print0 |\
  xargs -0 sed -i s/"$FROM"/"$TO"/g;
done

