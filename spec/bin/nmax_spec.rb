require 'spec_helper'

describe 'bin/nmax' do
  let(:output) do
    `echo "2 11 5 7" | ruby -Ilib bin/nmax 2`
  end

  it 'returns 2 max numbers' do
    expect(output).to eq "7\n11\n"
  end
end
