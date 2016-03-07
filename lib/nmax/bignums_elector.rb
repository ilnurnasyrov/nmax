module Nmax
  module BignumsElector
    def self.elect(size:, input_fd:, output_fd:)
      input = IO.new(input_fd)
      output = IO.new(output_fd)

      result = input.gets.scan(/\d+/).sort! do |left, right|
        next 1 if left.length > right.length
        next -1 if left.length < right.length

        left <=> right
      end.last(size)

      output.puts(result)
      output.flush
    end
  end
end
