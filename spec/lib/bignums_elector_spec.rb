require 'spec_helper'

describe Nmax::BignumsElector do
  describe '.elect' do
    let(:bignums) { %w(11 4 22 6 333) }
    let(:size) { 3 }
    let(:input) do
      rd, wr = IO.pipe
      wr.write(bignums.join("random delimiter"))
      wr.close
      rd
    end

    let(:output) do
      rd, wr = IO.pipe
      { rd: rd, wr: wr}
    end

    before do
      described_class.elect(
        size: size,
        input_fd: input.to_i,
        output_fd: output[:wr].to_i
      )
    end

    it 'returns expected bignums' do
      expect(output[:rd].read).to eq "11\n22\n333\n"
    end
  end
end
