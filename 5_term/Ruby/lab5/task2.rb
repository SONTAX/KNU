#!/usr/bin/ruby
# frozen_string_literal: true

def factorial(num)
  num > 1 ? num * factorial(num - 1) : 1
end

def range(x, n)
  sum = 0
  if n.zero?
    prev = 1
    i = 0
    while prev > 0.001
      prev = (2 * i + 1) / factorial(i) * x**(2 * i)
      sum += prev
      i += 1
    end
  else
    (0..n).each do |j|
      sum += (2 * j + 1) / factorial(j) * x**(2 * j)
    end
  end
  sum
end

puts 'Input n (from 10 to 58 or 0 to count infinitely): '
n = gets.chomp.to_i
if n != 0
  while (n < 10) || (n > 58)
    puts 'Wrong number'
    n = gets.chomp.to_i
  end
end

result = 0
i = 0.1
while i <= 1
  result += range(i, n)
  i += 0.1
end

puts 'result: ', result
