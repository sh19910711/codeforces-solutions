cat $1 | while read line; do
  echo $line | $2
done
