if [[ ! -r $1 ]]; then
  echo "First arg must be a readable file"
  exit 1
fi

i=0
while read FIRST REST; do
  if [[ -z "$FIRST" || "$FIRST" =~ ^# ]]; then
    continue
  fi
  echo "$i -> $FIRST - $REST";
  let i=i+1
done < $1

#basura!!
