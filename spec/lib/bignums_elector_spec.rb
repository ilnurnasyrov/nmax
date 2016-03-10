require 'spec_helper'
require 'tempfile'

describe Nmax::BignumsElector do
  describe '.elect' do
    let(:bignums) { %w(11 22 6 333 4) }
    let(:size) { 3 }
    let(:input) do
      Tempfile.new('input').tap do |tempfile|
        tempfile.write(bignums.join("random delimiter"))
        tempfile.rewind
      end
    end

    let(:output) { Tempfile.new('output') }

    before do
      described_class.elect(
        size: size,
        input_fd: input.to_i,
        output_fd: output.to_i
      )
    end

    it 'returns expected bignums' do
      File.open(output.path) do |f|
        expect(f.read).to eq "11\n22\n333\n"
      end
    end
  end
end
