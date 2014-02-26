require 'prime'

n = gets.to_i
a = Array.new(n, 0).map { gets.to_i }
b = a.sort

sum = 0
Prime.each {|x|
  sum += x
  break if x > 1000000
}

p sum


