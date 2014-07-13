import sys

class InputIterator:
  def __init__(self, s):
    self.list = s.split()
    self.i = 0
    
  def __iter__(self):
    return self
    
  def __next__(self):
    if self.i >= len(self.list):
      raise StopIteration
    res = self.list[self.i]
    self.i += 1
    return res
    
  def has_next(self):
    return self.i < len(self.list)

class Solver:
  def __init__(self, input_iter):
    self.input_iter = input_iter
    self.grid = []
    
  def input(self):
    self.n, self.m = map(int, [next(self.input_iter), next(self.input_iter)])
    for i in range(self.n):
      self.grid.append(next(self.input_iter))
    return self
    
  def mat(self, h, w, value = False):
    return [[value for c in range(w)] for r in range(h)]
  
  def solve(self):
    self.ok = self.mat(self.n, self.m, True)
    for r in range(self.n):
      for c in range(self.m):
        if self.grid[r][c] == "-":
          self.ok[r][c] = False
    self.color = self.mat(self.n, self.m, False)
    for r in range(self.n):
      for c in range(self.m):
        self.color[r][c] = ( r % 2 == 0 ) == ( c % 2 == 0 )
    return self
    
  def output(self):
    for r in range(self.n):
      for c in range(self.m):
        color = "W" if self.color[r][c] else "B"
        print(color if self.ok[r][c] else "-", end="")
      print("")
    return self

def run(input_iter):
  while input_iter.has_next():
    solver = Solver(input_iter)
    solver.input().solve().output()
    
run(InputIterator(sys.stdin.read()))
