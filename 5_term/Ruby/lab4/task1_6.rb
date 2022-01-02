#!/usr/bin/ruby
# frozen_string_literal: true

a = Array.new(24)

i = 0
while i < 24
  a[i] = rand(-10..10)
  i += 1
end

sum_even = 0
sum_odd = 0

a.each do |x|
  sum_even += x if x.even? && x.negative?
  sum_odd += x if x.odd? && x.positive?
end

puts 'a: '
i = 0
while i < 24
  printf("#{a[i]}\t")
  i += 1
end
puts '', 'sum even: ', sum_even, 'sum odd: ', sum_odd, 'total sum: ', sum_even + sum_odd
