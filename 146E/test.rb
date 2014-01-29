
def is_lucky(x)
  ! (/[^47]/ =~ x.to_s)
end

list = (1..1000000000).select {|x| is_lucky x }
p list.length
p list
