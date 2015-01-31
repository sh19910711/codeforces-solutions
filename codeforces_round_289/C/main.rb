N = gets.to_i
A = N.times.map { gets.to_i }

def f(sum)
  cnt = 10.times.map {0}
  (2..9).reverse_each do |x|
    cnt[x] = sum / x
    sum -= x * cnt[x]
  end
  cnt[1] = sum
  cnt
end

def g(list)
  list.each.with_index.inject("") do |s, (x, i)|
    s += "#{i}" * x
    s
  end
end

def less_than_equal(s1, s2)
  return true if s1 == s2
  if s1.length == s2.length
    (s1 <=> s2) < 0
  else
    s1.length < s2.length
  end
end

last = ""
A.map do |x|
  s = g(f x)
  while less_than_equal(s, last)
    s += "0"
  end
  last = s
end.each do |x|
  puts x
end

