SIZE = 10**5
table = Hash.new

def odd_loop func
  (3..SIZE).each do |k|
    if k % 2 == 0
      next
    end
    func.call k
  end
end

def even_loop func
  (2..SIZE).each do |k|
    if k % 2 == 1
      next
    end
    func.call k
  end
end

def inc_loop start, last, diff, func
  i = start
  while i < last do
    func.call i
    i += diff
  end
end

even_loop ->(k) do
  table[k] = false
end
table[2] = true

odd_loop ->(k) do
  table[k] = true
end

odd_loop ->(k) do
  next if ! table[k]

  inc_loop k+k, SIZE, k, ->(k) do
    table[k] = false
  end
end

arr = (1..SIZE).map {|x|
  table[x]
}

puts arr.count true
