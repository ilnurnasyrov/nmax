require "bignums_elector"

module Nmax
  class BignumsElector
    def self.elect(size:, input_fd:, output_fd:)
       ::BignumsElector.elect(size, input_fd, output_fd)
    end
  end
end
