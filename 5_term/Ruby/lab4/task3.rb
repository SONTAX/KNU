#!/usr/bin/ruby
# frozen_string_literal: true

puts 'Input dimension (from 3 to 9): '
n = gets.chomp.to_i
while (n < 3) || (n > 9)
  puts 'Wrong number'
  n = gets.chomp.to_i
end

a = (0..(n - 1)).map { Array.new n }
b = Array.new n
x = Array.new n

(0..(n - 1)).each do |i|
  (0..(n - 1)).each do |j|
    a[i][j] = 13.0
    a[i][j] = 2.0 if i == j
  end
  b[i] = i + 1.0
end


(1..(n - 1)).each do |k|
  (k..(n - 1)).each do |i|
    coefficient = a[i][k - 1] / a[k - 1][k - 1]
    ((k - 1)..(n - 1)).each do |j|
      a[i][j] -= coefficient * a[k - 1][j]
    end
    b[i] -= coefficient * b[k - 1]
  end
end

x[n - 1] = b[n - 1] / a[n - 1][n - 1]
i = n - 2
while i >= 0
  ((i + 1)..(n - 1)).each do |j|
    b[i] -= x[j] * a[i][j]
  end
  x[i] = b[i] / a[i][i]
  i -= 1
end

puts 'result: '
p x
