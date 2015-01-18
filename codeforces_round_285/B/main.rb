# @snippet<contest.rb#0.0.6:namespace.rb>
module Solution; end
# @snippet<contest.rb#0.0.6:header.rb>
require "scanf"
# @snippet<contest.rb#0.0.6:runner.rb>
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
# @snippet<contest.rb#0.0.6:solver.rb>
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
    puts res.size
    res.each do |key, value|
      puts "#{key} #{value}"
    end
  end

end
# @snippet<contest.rb#0.0.6:main.rb>

require "set"

class Disj

  attr_reader :parent
  attr_reader :root
  attr_reader :last_name

  def initialize
    @last_name = {}
    @parent = {}
    @root = Set.new
  end

  def size
    @root.size
  end

  def find(name)
    if parent[name].nil?
      name
    else
      find(parent[name])
    end
  end

  def parent?(name)
    find(name) === name
  end

  def update(old_name, new_name)
    if parent?(old_name)
      root.add old_name
    end
    last_name[find(old_name)] = new_name
    parent[new_name] = find(old_name)
    self
  end

  def each
    root.each do |name|
      yield name, last_name[name]
    end
  end

end

input_format = "%d" # scanf(input_format)
Solution::Runner.run(input_format) do |q|
  (1..q).to_a.map do
    old, new = gets.split
    {:new => new, :old => old, }
  end.inject(Disj.new) do |disj, info|
    disj.update info[:old], info[:new]
  end
end

