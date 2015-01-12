# @snippet <contest.rb#0.0.6:namespace.rb>
module Solution; end
# @snippet <contest.rb#0.0.6:header.rb>
require "scanf"
# @snippet <contest.rb#0.0.6:runner.rb>
class Solution::Runner

  def self.run(input_format, input_stream = STDIN, output_stream = STDOUT, &block)
    Solution::Solver.new(input_format, input_stream, output_stream) do
      input do |args|
        if block.nil?
          output solve(*args)
        else
          output block.call(*args)
        end
      end
    end
  end

end
# @snippet <contest.rb#0.0.6:solver.rb>
class Solution::Solver

  attr_reader :input_format
  attr_reader :input_stream
  attr_reader :output_stream

  def initialize(new_input_format, new_input_stream, new_output_stream, &block)
    @input_format = new_input_format
    @input_stream = new_input_stream
    @output_stream = new_output_stream

    instance_eval(&block) if block_given?
  end

  def input
    while s = gets
      break if s.nil?
      s.scanf(input_format) do |*args|
        yield(*args)
      end
    end
  end

  def output(res)
    puts res
  end

end
# @snippet <contest.rb#0.0.6:main.rb>

def points(p, t)
  [3.0 * p / 10.0, p - p / 250.0 * t].max
end

input_format = "%d%d%d%d" # scanf(input_format)
Solution::Runner.run(input_format) do |a, b, c, d|
  p1 = points(a, c)
  p2 = points(b, d)
  if p1 == p2
    "Tie"
  elsif p1 > p2
    "Misha"
  else
    "Vasya"
  end
end

