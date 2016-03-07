require 'spec_helper'

describe Nmax::BignumsElector do
  describe '.elect' do
    let(:bignums) { %w(11 4 22 6 333) }
    let(:expected_bignums) { %w(11 22 333) }
    let(:n) { 3 }
    let(:fd) do
      rd, wr = IO.pipe
      wr.write(bignums.join("random delimiter"))
      wr.close
      rd.to_i
    end

    it 'returns expected bignums' do
      result = described_class.elect(n, fd)
      expect(result).to eq expected_bignums
    end
  end
end
