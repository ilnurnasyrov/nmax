module Nmax
  module BignumsElector
    def self.elect(n, fd)
      IO.new(fd).gets.scan(/\d+/).sort! do |left, right|
        next 1 if left.length > right.length
        next -1 if left.length < right.length

        left <=> right
      end.last(n)
    end
  end
end
