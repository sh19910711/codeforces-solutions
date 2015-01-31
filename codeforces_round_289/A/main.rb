n = gets.to_i
A = []
A[0] = (1..n).map { 1 }
n.times do |i|
  next if i == 0
  A[i] = (1..n).map { 1 }
  n.times do |j|
    next if j == 0
    A[i][j] = A[i-1][j] + A[i][j-1]
  end
end
puts A[n-1][n-1]
