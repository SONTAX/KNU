#!/usr/bin/ruby
# frozen_string_literal: true

# 3

def bin_to_dec(number)
  in_dec = 0
  pow = number.size - 1
  (0..(number.size - 1)).each do |i|
    in_dec += number[i].to_i * (2**pow)
    pow -= 1
  end
  in_dec
end

puts 'Result: ', bin_to_dec('1000100010001')
