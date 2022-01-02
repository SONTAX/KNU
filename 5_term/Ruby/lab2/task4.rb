#!/usr/bin/ruby
# frozen_string_literal: true

# 4

def dec_to_bin(number)
  in_bin = ''
  while number > 1
    in_bin += (number % 2).to_s
    number /= 2
  end
  in_bin += number.to_s
  in_bin.reverse
end

puts 'Result: ', dec_to_bin(111)
